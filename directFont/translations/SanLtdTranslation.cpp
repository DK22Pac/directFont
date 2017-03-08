#include "SanLtdTranslation.h"

void SanLtdTranslation::TranslateString(char *str) {
    char *pText = str;
    while (*pText) {
        switch (*pText) {
        case 'A':
            *pText = '¿';
            break;
        case 'a':
            *pText = '‡';
            break;
        case 'Ä':
            *pText = '¡';
            break;
        case 'ó':
            *pText = '·';
            break;
        case 'ã':
            *pText = '¬';
            break;
        case '¢':
            *pText = '‚';
            break;
        case 'Ç':
            *pText = '√';
            break;
        case 'ô':
            *pText = '„';
            break;
        case 'É':
            *pText = 'ƒ';
            break;
        case 'ö':
            *pText = '‰';
            break;
        case 'E':
            *pText = '≈';
            break;
        case 'e':
            *pText = 'Â';
            break;
        case '∏':
            *pText = '∏';
            break;
        case 'Ñ':
            *pText = '∆';
            break;
        case 'õ':
            *pText = 'Ê';
            break;
        case 'à':
            *pText = '«';
            break;
        case 'ü':
            *pText = 'Á';
            break;
        case 'Ö':
            *pText = '»';
            break;
        case 'ú':
            *pText = 'Ë';
            break;
        case 'Ü':
            *pText = '…';
            break;
        case 'ù':
            *pText = 'È';
            break;
        case 'K':
            *pText = ' ';
            break;
        case 'k':
            *pText = 'Í';
            break;
        case 'á':
            *pText = 'À';
            break;
        case 'û':
            *pText = 'Î';
            break;
        case 'ñ':
            *pText = 'Ã';
            break;
        case 'Ø':
            *pText = 'Ï';
            break;
        case '\xAD':
            *pText = 'Õ';
            break;
        case 'Æ':
            *pText = 'Ì';
            break;
        case 'O':
            *pText = 'Œ';
            break;
        case 'o':
            *pText = 'Ó';
            break;
        case 'å':
            *pText = 'œ';
            break;
        case '£':
            *pText = 'Ô';
            break;
        case 'P':
            *pText = '–';
            break;
        case 'p':
            *pText = '';
            break;
        case 'C':
            *pText = '—';
            break;
        case 'c':
            *pText = 'Ò';
            break;
        case 'è':
            *pText = '“';
            break;
        case '¶':
            *pText = 'Ú';
            break;
        case 'Y':
            *pText = '”';
            break;
        case 'y':
            *pText = 'Û';
            break;
        case 'Å':
            *pText = '‘';
            break;
        case '\x98':
            *pText = 'Ù';
            break;
        case 'X':
            *pText = '’';
            break;
        case 'x':
            *pText = 'ı';
            break;
        case 'â':
            *pText = '÷';
            break;
        case '\xA0':
            *pText = 'ˆ';
            break;
        case 'ç':
            *pText = '◊';
            break;
        case '§':
            *pText = '˜';
            break;
        case 'é':
            *pText = 'ÿ';
            break;
        case '•':
            *pText = '¯';
            break;
        case 'ä':
            *pText = 'Ÿ';
            break;
        case '°':
            *pText = '˘';
            break;
        case 'ê':
            *pText = '⁄';
            break;
        case 'ß':
            *pText = '˙';
            break;
        case 'ë':
            *pText = '€';
            break;
        case '®':
            *pText = '˚';
            break;
        case 'í':
            *pText = '‹';
            break;
        case '©':
            *pText = '¸';
            break;
        case 'ì':
            *pText = '›';
            break;
        case '™':
            *pText = '˝';
            break;
        case 'î':
            *pText = 'ﬁ';
            break;
        case '´':
            *pText = '˛';
            break;
        case 'ï':
            *pText = 'ﬂ';
            break;
        case '¨':
            *pText = 'ˇ';
            break;
        }
        pText++;
    }
}