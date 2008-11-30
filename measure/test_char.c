#include <windows.h>
#include "eterforcetest.h"

#define WINE_UNICODE_INLINE inline
/* copied from wine/unicode.h, LGPL license
*/
WINE_UNICODE_INLINE WCHAR *strchrW( const WCHAR *str, WCHAR ch )
{
    do { if (*str == ch) return (WCHAR *)(ULONG_PTR)str; } while (*str++);
    return NULL;
}

WINE_UNICODE_INLINE WCHAR *strrchrW( const WCHAR *str, WCHAR ch )
{
    WCHAR *ret = NULL;
    do { if (*str == ch) ret = (WCHAR *)(ULONG_PTR)str; } while (*str++);
    return ret;
}


/* TODO: с кириллицей CP1251 */
static CHAR test1_string[] = "ABCDEFGHRTPENDOFPROZMIY";
/*  "ABCDEFGHRTPENDOFPROZMIY"; */
#define TEST_STRING test1_string

static WCHAR test_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test_stringW

void test_char()
{
	/* we need static var for save result */
	static CHAR *str;
	static WCHAR *strW;
	int ok = strchr(TEST_STRING, 'Z') != NULL;

	printf("\n\n* * *  Char operations  * * *\n");


	MSTART(ok, "strchr", 1) {
		/* We need save result due optimizations */
		str = strchr(TEST_STRING, 'z');
	} MEND

	MSTART(1, "strchrW", 2) {
		strW = strchrW(TEST_STRINGW, 'z');
	} MEND

	/* TODO
	IsCharAlphaNumericA
	CharUpperA
	IsCharAlphaA
	*/
}

