#include <windows.h>
#include "eterforcetest.h"


/* TODO: с кириллицей CP1251 */
#define TEST_STRING "ABCDEFGHRTPENDOFPROZMIY"
static WCHAR test_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test_stringW

void test_encoding()
{
	#define BUFLEN 100
	WCHAR bufW[BUFLEN];
	char buf[BUFLEN];
	int ok;

	printf("\n\n* * *  Encoding operations  * * *\n");

	ok = MultiByteToWideChar( CP_ACP, 0, TEST_STRING, -1, bufW, BUFLEN );
	MSTART(ok, "MultiByteToWideChar/Latin", 2) {
		MultiByteToWideChar( CP_ACP, 0, TEST_STRING, -1, bufW, BUFLEN );
	} MEND

	ok = WideCharToMultiByte( CP_ACP, 0, TEST_STRINGW, -1, buf, BUFLEN, NULL, NULL );
	MSTART(ok, "WideCharToMultiByte/Latin", 4) {
		WideCharToMultiByte( CP_ACP, 0, bufW, -1, buf, BUFLEN, NULL, NULL );
	} MEND

	/* TODO
	LCMapStringW
	*/
}

