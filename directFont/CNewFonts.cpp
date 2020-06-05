#include "CNewFonts.h"
#include "plugin.h"
#include "game_sa\CSprite2d.h"
#include "game_sa\CMessages.h"
#include "game_sa\CHudColours.h"
#include "translations\SanLtdTranslation.h"
#include "translations\LatinTranslation.h"
#include <stdio.h>

using namespace plugin;

extern LPDIRECT3DDEVICE9 &_RwD3DDevice;
CD3DSprite *CNewFonts::m_pFontSprite;
CNewFont CNewFonts::m_aFonts[4];
eTranslation CNewFonts::m_Translation;
eFontStyle CNewFonts::m_FontId;
CRGBA CNewFonts::gLetterColors[MAX_TEXT_SIZE];
unsigned int CNewFonts::gNumLetters;
bool CNewFonts::gShadow;

bool CNewFont::SetupFont(char *fontName, unsigned int width, int height, float scaleX, float scaleY, unsigned int weight, bool italic,
    unsigned int charSet, unsigned int outputPrecision, unsigned int quality, unsigned int pitchAndFamily, bool upperCase,
    bool replaceUS)
{
    HRESULT hr = D3DXCreateFont(CNewFonts::GetCurrentDevice(), width, height, weight, 0, italic, charSet, outputPrecision, quality,
        pitchAndFamily, fontName, &m_pD3DXFont);
    if (hr != S_OK) {
        m_pD3DXFont = NULL;
        return Error("CNewFont::SetupFont: Can't load \"%s\" font", fontName);
    }
    m_initialised = true;
    strcpy_s(m_fontName, fontName);
    m_width = width;
    m_height = height;
    m_scaleX = scaleX;
    m_scaleY = scaleY;
    m_weight = weight;
    m_italic = italic;
    m_charSet = charSet;
    m_outputPrecision = outputPrecision;
    m_quality = quality;
    m_pitchAndFamily = pitchAndFamily;
    m_upperCase = upperCase;
    m_replaceUS = replaceUS;
    return true;
}

void CNewFont::PrintString(char *text, CRect const& rect, float scale_x, float scale_y, CRGBA const& color, DWORD format, CRGBA const* backgroundColor,
    float shadow, float outline, CRGBA const* dropColor)
{
    RECT d3drect; SetRect(&d3drect, rect.left, rect.top, rect.right, rect.bottom);
    if (backgroundColor)
        DrawRect(text, rect, scale_x, scale_y, format, *backgroundColor);
    RECT d3drect2; SetRect(&d3drect2, d3drect.left / (scale_x / 2), d3drect.top / (scale_y / 2), d3drect.right / (scale_x / 2), d3drect.bottom / (scale_y / 2));
    D3DXMATRIX S, P;
    D3DXMatrixScaling(&S, scale_x / 2, scale_y / 2, 1.0f);
    CNewFonts::m_pFontSprite->GetTransform(&P);
    CNewFonts::m_pFontSprite->SetTransform(&S);
    CNewFonts::m_pFontSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
    if (shadow > 0.0f) {
        RECT shadowRect(d3drect2);
        shadowRect.left += shadow;
        shadowRect.right += shadow;
        shadowRect.top += shadow;
        shadowRect.bottom += shadow;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &shadowRect, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
    }
    else if (outline > 0.0f) {
        RECT outl1(d3drect2);
        outl1.left -= outline;
        outl1.right -= outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl1, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
        RECT outl2(d3drect2);
        outl2.left += outline;
        outl2.right += outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl2, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
        RECT outl3(d3drect2);
        outl3.top -= outline;
        outl3.bottom -= outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl3, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
        RECT outl4(d3drect2);
        outl4.top += outline;
        outl4.bottom += outline;
        CNewFonts::gShadow = true;
        m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &outl4, format, D3DCOLOR_ARGB(dropColor->a,
            dropColor->r, dropColor->g, dropColor->b));
    }
    CNewFonts::gNumLetters = 0;
    CNewFonts::gShadow = false;
    m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &d3drect2, format, D3DCOLOR_ARGB(color.a,
        color.r, color.g, color.b));
    CNewFonts::m_pFontSprite->SetTransform(&P);
    CNewFonts::m_pFontSprite->End();
}

void CNewFont::DrawRect(char *text, CRect const& rect, float scale_x, float scale_y, DWORD format, CRGBA const& backgroundColor) {
    float x2 = rect.right;
    RECT d3drect; SetRect(&d3drect, rect.left, rect.top, rect.right, rect.bottom);
    RECT d3drect2; SetRect(&d3drect2, d3drect.left / (scale_x / 2), d3drect.top / (scale_y / 2), d3drect.right / (scale_x / 2), d3drect.bottom / (scale_y / 2));
    D3DXMATRIX S, P;
    D3DXMatrixScaling(&S, scale_x / 2, scale_y / 2, 1.0f);
    CNewFonts::m_pFontSprite->GetTransform(&P);
    CNewFonts::m_pFontSprite->SetTransform(&S);
    CNewFonts::m_pFontSprite->Begin(0);
    this->m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, text, -1, &d3drect2, format | DT_CALCRECT, 0xFFFFFFFF);
    CNewFonts::m_pFontSprite->SetTransform(&P);
    CNewFonts::m_pFontSprite->End();
    CSprite2d::DrawRect(CRect(d3drect2.left*(scale_x / 2) - 8, d3drect2.top*(scale_y / 2) - 8, x2 + 8, d3drect2.bottom*(scale_y / 2) + 8), backgroundColor);
}

void CNewFont::ReleaseFont() {
    if (this->m_pD3DXFont) {
        this->m_pD3DXFont->Release();
        this->m_pD3DXFont = NULL;
    }
}

void CNewFont::OnLost() {
    ReleaseFont();
}

void CNewFont::OnReset() {
    D3DXCreateFont(CNewFonts::GetCurrentDevice(), m_width, m_height, m_weight, 0, m_italic, m_charSet, m_outputPrecision, m_quality,
        m_pitchAndFamily, m_fontName, &this->m_pD3DXFont);
}

float __declspec(naked) _GetWidth() {
    __asm add esp, 0x198
    __asm jmp CNewFonts::GetStringWidth
}

void CNewFonts::Initialise() {
    char app[8];
    char fontName[256];
    char scaleFactorStr[16];
    char translation[16];
    unsigned int fontId;
    int width;
    unsigned int height;
    float scaleX;
    float scaleY;
    unsigned int weight;
    bool italic;
    unsigned int charSet;
    unsigned int outputPrecision;
    unsigned int quality;
    unsigned int pitchAndFamily;
    bool upperCase;
    bool replaceUS;
    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        sprintf(app, "FONT%d", i + 1);
        GetPrivateProfileString(app, "FontName", "USE_DEFAULT", fontName, 256, PLUGIN_PATH("directFont.ini"));
        if (!strcmp(fontName, "USE_DEFAULT")) {
            m_aFonts[i].m_initialised = false;
            continue;
        }
        if (!strncmp(fontName, "USE_FONT", 8)) {
            if (!i) {
                Error("CNewFonts::Initialise\nCan't apply USE_FONT to first font.");
                m_aFonts[i].m_initialised = false;
                continue;
            }
            sscanf(fontName, "USE_FONT%d", &fontId);
            if (fontId > MAX_NUM_FONTS) {
                Error("CNewFonts::Initialise\nUnknown font used with USE_FONT construction.");
                m_aFonts[i].m_initialised = false;
                continue;
            }
            if (fontId == i) {
                Error("CNewFonts::Initialise\nCan't apply USE_FONT to this font.");
                m_aFonts[i].m_initialised = false;
                continue;
            }
            m_aFonts[i].SetupFont(m_aFonts[fontId].m_fontName, m_aFonts[fontId].m_width, m_aFonts[fontId].m_height, m_aFonts[fontId].m_scaleX,
                m_aFonts[fontId].m_scaleY, m_aFonts[fontId].m_weight, m_aFonts[fontId].m_italic, m_aFonts[fontId].m_charSet,
                m_aFonts[fontId].m_outputPrecision, m_aFonts[fontId].m_quality, m_aFonts[fontId].m_pitchAndFamily, m_aFonts[fontId].m_upperCase,
                m_aFonts[fontId].m_replaceUS);
        }
        else {
            height = GetPrivateProfileInt(app, "Height", 64, PLUGIN_PATH("directFont.ini"));
            width = GetPrivateProfileInt(app, "Width", 40, PLUGIN_PATH("directFont.ini"));
            GetPrivateProfileString(app, "ScaleFactor.x", "0.6", scaleFactorStr, 16, PLUGIN_PATH("directFont.ini"));
            sscanf(scaleFactorStr, "%f", &scaleX);
            GetPrivateProfileString(app, "ScaleFactor.y", "0.4", scaleFactorStr, 16, PLUGIN_PATH("directFont.ini"));
            sscanf(scaleFactorStr, "%f", &scaleY);
            weight = GetPrivateProfileInt(app, "Weight", 500, PLUGIN_PATH("directFont.ini"));
            italic = GetPrivateProfileInt(app, "Italic", 0, PLUGIN_PATH("directFont.ini"));
            charSet = GetPrivateProfileInt(app, "CharSet", 1, PLUGIN_PATH("directFont.ini"));
            outputPrecision = GetPrivateProfileInt(app, "OutputPrecision", 0, PLUGIN_PATH("directFont.ini"));
            quality = GetPrivateProfileInt(app, "Quality", 0, PLUGIN_PATH("directFont.ini"));
            pitchAndFamily = GetPrivateProfileInt(app, "PitchAndFamily", 0, PLUGIN_PATH("directFont.ini"));
            upperCase = GetPrivateProfileInt(app, "UpcaseAlways", 0, PLUGIN_PATH("directFont.ini"));
            replaceUS = GetPrivateProfileInt(app, "ReplaceUnderscoreWithSpace", 0, PLUGIN_PATH("directFont.ini"));
            m_aFonts[i].SetupFont(fontName, width, height, scaleX, scaleY, weight, italic, charSet, outputPrecision, quality, pitchAndFamily,
                upperCase, replaceUS);
        }
    }
    GetPrivateProfileString("GENERAL", "UseTranslator", "NONE", translation, 16, PLUGIN_PATH("directFont.ini"));
    if (!strncmp(translation, "NONE", 4))
        m_Translation = TRANSLATION_NONE;
    else if (!strncmp(translation, "SANLTD", 6))
        m_Translation = TRANSLATION_SANLTD;
	else if (!strncmp(translation, "LATIN", 6))
		m_Translation = TRANSLATION_LATIN;
    else {
        Error("CNewFonts::Initialise\nUnknown translation name.");
        m_Translation = TRANSLATION_NONE;
    }
    patch::RedirectJump(0x71A700, PrintString);
    patch::RedirectJump(0x71A0E6, _GetWidth);
    patch::SetChar(0x58DCEF, '*');
    patch::RedirectJump(0x719490, SetFontStyle);
    m_pFontSprite = new CD3DSprite;
}

void CNewFonts::Reset() {
    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        if (m_aFonts[i].m_initialised)
            m_aFonts[i].OnReset();
    }
    if (m_pFontSprite)
        m_pFontSprite->OnResetDevice();
}

void CNewFonts::Lost() {
    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        if (m_aFonts[i].m_initialised)
            m_aFonts[i].OnLost();
    }
    if (m_pFontSprite)
        m_pFontSprite->OnLostDevice();
}

void CNewFonts::Shutdown() {
    for (int i = 0; i < MAX_NUM_FONTS; i++) {
        if (m_aFonts[i].m_initialised)
            m_aFonts[i].ReleaseFont();
    }
    delete m_pFontSprite;
}

IDirect3DDevice9 *CNewFonts::GetCurrentDevice() {
    return _RwD3DDevice;
}

void _UpCase(unsigned char *str) {
    unsigned char *pStr = str;
    while (*pStr) {
        if ((*pStr >= 97 && *pStr <= 122) || (*pStr >= 224 && *pStr <= 255))
            *pStr = *pStr - 32;
        else if (*pStr == 183)
            *pStr = 167;
        pStr++;
    }
}

void ReplaceUsWithSpace(unsigned char *str) {
    unsigned char *pStr = str;
    while (*pStr) {
        if (*pStr == '_')
            *pStr = ' ';
        pStr++;
    }
}

void CNewFonts::PrintString(float x, float y, char *text) {
    if (m_aFonts[m_FontId].m_initialised) {
        static char taggedText[MAX_TEXT_SIZE];
        CRect *rect;
        unsigned int flag;
        if (CFont::m_bFontCentreAlign) {
            rect = &CRect(x - CFont::m_fFontCentreSize / 2, y, x + CFont::m_fFontCentreSize / 2, SCREEN_HEIGHT);
            flag = DT_CENTER;
        }
        else if (CFont::m_bFontRightAlign) {
            rect = &CRect(CFont::m_fRightJustifyWrap, y, x, SCREEN_HEIGHT);
            flag = DT_RIGHT;
        }
        else {
            rect = &CRect(x, y, CFont::m_fWrapx, SCREEN_HEIGHT);
            flag = DT_LEFT;
        }
        ProcessTags(taggedText, text);
        if (m_Translation == TRANSLATION_SANLTD) {
            SanLtdTranslation tr;
            tr.TranslateString(taggedText);
        } else if (m_Translation == TRANSLATION_LATIN) {
			LatinTranslation tr;
			tr.TranslateString(taggedText);
		}
        if (m_aFonts[m_FontId].m_upperCase)
            _UpCase((unsigned char *)taggedText);
        if (m_aFonts[m_FontId].m_replaceUS)
            ReplaceUsWithSpace((unsigned char *)taggedText);
        m_aFonts[m_FontId].PrintString(taggedText, *rect, CFont::m_Scale->x * m_aFonts[m_FontId].m_scaleX,
            CFont::m_Scale->y * m_aFonts[m_FontId].m_scaleY, *CFont::m_Color,
            DT_TOP | DT_NOCLIP | DT_WORDBREAK | flag, CFont::m_bFontBackground ? CFont::m_FontBackgroundColor : NULL,
            CFont::m_nFontShadow * 2, CFont::m_nFontOutlineSize * 2, CFont::m_FontDropColor);
    }
    else
        CFont::PrintString(x, y, text);
}

HRESULT CD3DSprite::Draw(LPDIRECT3DTEXTURE9 pTexture, CONST RECT * pSrcRect, CONST D3DXVECTOR3 * pCenter,
    CONST D3DXVECTOR3 * pPosition, D3DCOLOR Color)
{
    HRESULT result;
    if (CNewFonts::gShadow)
        result = m_pSprite->Draw(pTexture, pSrcRect, pCenter, pPosition, Color);
    else {
        result = m_pSprite->Draw(pTexture, pSrcRect, pCenter, pPosition, D3DCOLOR_RGBA(CNewFonts::gLetterColors[CNewFonts::gNumLetters].r,
            CNewFonts::gLetterColors[CNewFonts::gNumLetters].g, CNewFonts::gLetterColors[CNewFonts::gNumLetters].b, 
            CNewFonts::gLetterColors[CNewFonts::gNumLetters].a));
        CNewFonts::gNumLetters++;
    }
    return result;
}

void CNewFonts::ProcessTags(char *dest, char *src) {
    bool bBreak = false;
    static char text[MAX_TEXT_SIZE];
    char *pDest = dest;
    char *pText = text;
    strcpy_s(text, src);
    CMessages::InsertPlayerControlKeysInString(text);
    CRGBA currColor(*CFont::m_Color);
    unsigned int numLetters = 0;
    while (true) {
        // if string was finished
        if (!*pText)
            break;
        // if we found a tag
        if (*pText == '~') {
            // process tag
            pText++;
            // if string was finished
            if (!*pText)
                break;
            // if new line tag
            switch (*pText) {
            case 'N':
            case 'n':
                *pDest = '\n';
                pDest++;
                pText++;
                break;
            case 'R':
            case 'r':
                currColor = CRGBA(HudColour.GetRGB(0, CFont::m_Color->a));
                pText++;
                break;
            case 'G':
            case 'g':
                currColor = CRGBA(HudColour.GetRGB(1, CFont::m_Color->a));
                pText++;
                break;
            case 'B':
            case 'b':
                currColor = CRGBA(HudColour.GetRGB(2, CFont::m_Color->a));
                pText++;
                break;
            case 'W':
            case 'w':
                currColor = CRGBA(HudColour.GetRGB(4, CFont::m_Color->a));
                pText++;
                break;
            case 'H':
            case 'h':
                currColor = CRGBA(min((float)CFont::m_Color->r * 1.5f, 255.0f),
                    min((float)CFont::m_Color->g * 1.5f, 255.0f),
                    min((float)CFont::m_Color->b * 1.5f, 255.0f),
                    CFont::m_Color->a);
                pText++;
                break;
            case 'Y':
            case 'y':
                currColor = CRGBA(HudColour.GetRGB(11, CFont::m_Color->a));
                pText++;
                break;
            case 'P':
            case 'p':
                currColor = CRGBA(HudColour.GetRGB(7, CFont::m_Color->a));
                pText++;
                break;
            case 'l':
                currColor = CRGBA(HudColour.GetRGB(5, CFont::m_Color->a));
                pText++;
                break;
            case 'S':
            case 's':
                currColor = CRGBA(HudColour.GetRGB(4, CFont::m_Color->a));
                pText++;
                break;
            }
            // close tag
            while (*pText != '~') {
                if (!pText) {
                    *pDest = '\0';
                    return;
                }
                pText++;
            }
            pText++;
        }
        else {
            *pDest = *pText;
            if (*pText != ' ') {
                gLetterColors[numLetters] = currColor;
                numLetters++;
            }
            pDest++;
            pText++;
        }
    }
    *pDest = '\0';
}

float CNewFonts::GetStringWidth(char *str, char bFull, char bScriptText) {
    if (m_aFonts[m_FontId].m_initialised) {
        static char text[MAX_TEXT_SIZE];
        static char taggedText[MAX_TEXT_SIZE];
        char *pText = taggedText;
        strncpy(text, str, CMessages::GetStringLength(str));
        CNewFonts::ProcessTags(taggedText, text);
        if (!bFull)
        {
            while (*pText && *pText != ' ')
                pText++;
            *pText = '\0';
        }
        return CNewFonts::m_aFonts[m_FontId].GetStringWidth(taggedText);
    }
    else
        return CFont::GetStringWidth(str, bFull, bScriptText);
}

float CNewFont::GetStringWidth(char *str) {
    float scale_x = CFont::m_Scale->x * m_scaleX;
    float scale_y = CFont::m_Scale->y * m_scaleY;
    RECT d3drect; SetRect(&d3drect, 0, 0, 0, 0);
    D3DXMATRIX S, P;
    D3DXMatrixScaling(&S, scale_x / 2, scale_y / 2, 1.0f);
    CNewFonts::m_pFontSprite->GetTransform(&P);
    CNewFonts::m_pFontSprite->SetTransform(&S);
    CNewFonts::m_pFontSprite->Begin(0);
    this->m_pD3DXFont->DrawText(CNewFonts::m_pFontSprite, str, -1, &d3drect, DT_TOP | DT_NOCLIP | DT_SINGLELINE | DT_CALCRECT, 0xFFFFFFFF);
    CNewFonts::m_pFontSprite->SetTransform(&P);
    CNewFonts::m_pFontSprite->End();
    return (d3drect.right - d3drect.left) * (scale_x / 2);
}

void CNewFonts::SetFontStyle(eFontStyle style) {
    m_FontId = style;
    if (style == 2) {
        CFont::m_FontTextureId = 0;
        CFont::m_FontStyle = 2;
    }
    else if (style == 3) {
        CFont::m_FontTextureId = 1;
        CFont::m_FontStyle = 1;
    }
    else {
        CFont::m_FontTextureId = style;
        CFont::m_FontStyle = 0;
        CFont::m_FontStyle = 0;
    }
}