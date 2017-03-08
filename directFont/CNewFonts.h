#pragma once
#include "d3dx9.h"
#include "game_sa\CRect.h"
#include "game_sa\CRGBA.h"
#include "game_sa\CFont.h"
#include "CD3DSprite.h"

#define MAX_NUM_FONTS 4
#define MAX_TEXT_SIZE 2048

enum eTranslation {
    TRANSLATION_NONE = 0,
    TRANSLATION_SANLTD = 1
};

class CNewFont {
    ID3DXFont *m_pD3DXFont;
public:
    char m_fontName[128];
    int m_width;
    unsigned int m_height;
    unsigned int m_weight;
    float m_scaleX;
    float m_scaleY;
    bool m_italic;
    unsigned int m_charSet;
    unsigned int m_outputPrecision;
    unsigned int m_quality;
    unsigned int m_pitchAndFamily;
    bool m_upperCase;
    bool m_replaceUS;
    bool m_initialised;
    bool SetupFont(char *fontName, unsigned int width, int height, float scaleX, float scaleY, unsigned int weight, bool italic,
        unsigned int charSet, unsigned int outputPrecision, unsigned int quality, unsigned int pitchAndFamily, bool upperCase, bool replaceUS);
    void PrintString(char *text, CRect const& rect, float scale_x, float scale_y, CRGBA const& color, DWORD format,
        CRGBA const* backgroundColor, float shadow, float outline, CRGBA const* dropColor);
    void DrawRect(char *text, CRect const& rect, float scale_x, float scale_y, DWORD format, CRGBA const& backgroundColor);
    void ReleaseFont();
    void OnLost();
    void OnReset();
    float GetStringWidth(char *str);
};

class CNewFonts {
public:
    static eFontStyle m_FontId;
    static CD3DSprite *m_pFontSprite;
    static CNewFont m_aFonts[MAX_NUM_FONTS];
    static eTranslation m_Translation;
    static CRGBA gLetterColors[MAX_TEXT_SIZE];
    static unsigned int gNumLetters;
    static bool gShadow;

    static IDirect3DDevice9 *GetCurrentDevice();
    static void Initialise();
    static void Shutdown();
    static void Lost();
    static void Reset();
    static void SetFontStyle(eFontStyle style);
    static void PrintString(float x, float y, char *text);
    static void ProcessTags(char *dest, char *src);
    static float GetStringWidth(char *str, char bFull, char bScriptText);
};