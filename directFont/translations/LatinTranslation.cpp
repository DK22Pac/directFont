#include "LatinTranslation.h"

void LatinTranslation::TranslateString(char *str) {
    char *pText = str;
    while (*pText) {
		switch (*pText) {
		case 'ò':
			*pText = '·';
			break;
		case 'ó':
			*pText = '‡';
			break;
		case 'ö':
			*pText = '„';
			break;
		case 'ô':
			*pText = '‚';
			break;
		case 'û':
			*pText = 'È';
			break;
		case 'ü':
			*pText = 'Í';
			break;
		case '¢':
			*pText = 'Ì';
			break;
		case '¶':
			*pText = 'Û';
			break;
		case '•':
			*pText = 'Ú';
			break;
		case '®':
			*pText = 'ı';
			break;
		case 'ß':
			*pText = 'Ù';
			break;
		case '™':
			*pText = '˙';
			break;
		case 'ú':
			*pText = 'Á';
			break;
		case 'Å':
			*pText = '¡';
			break;
		case 'Ä':
			*pText = '¿';
			break;
		case 'É':
			*pText = '√';
			break;
		case 'Ç':
			*pText = '¬';
			break;
		case 'á':
			*pText = '…';
			break;
		case 'à':
			*pText = ' ';
			break;
		case 'ã':
			*pText = 'Õ';
			break;
		case 'å':
			*pText = 'Œ';
			break;
		case 'è':
			*pText = '”';
			break;
		case 'éè':
			*pText = '“';
			break;
		case 'ëè':
			*pText = '’';
			break;
		case 'ê':
			*pText = '‘';
			break;
		case 'ìè':
			*pText = '⁄';
			break;
		case 'íè':
			*pText = 'Ÿ';
			break;
		case 'ï':
			*pText = '‹';
			break;
		case 'Ö':
			*pText = '«';
			break;
		}
        pText++;
    }
}