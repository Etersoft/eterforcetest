#include <windows.h>
#include "eterforcetest.h"


/* TODO: с кириллицей CP1251 */
#define TEST_STRING "ABCDEFGHRTPENDOFPROZMIY"
static WCHAR test_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test_stringW

void test_string()
{
	int len;
	static CHAR dest[100];
	static WCHAR destW[100];
	static int res;

	len = strlen(TEST_STRING);

	printf("\n\n* * *  String operations  * * *\n");

	MSTART(1, "lstrcpyA", 1) {
		lstrcpyA(dest, TEST_STRING);
	} MEND

	MSTART(1, "lstrcpynA", 1) {
		lstrcpynA(dest, TEST_STRING, len);
	} MEND


	lstrcpyA(dest, TEST_STRING);
	MSTART(1, "lstrlenA", 1) {
		res = lstrlenA(dest);
		res = lstrlenA(dest);
	} MEND

	lstrcpyW(destW, TEST_STRINGW);
	MSTART(1, "lstrlenW", 1) {
		res = lstrlenW(destW);
		res = lstrlenW(destW);
	} MEND

	MSTART(1, "lstrcatA", 1) {
		lstrcatA(dest, "abcdefghrtgo");
		dest[len] = 0;
	} MEND

	/* TODO:
		*W functions
	*/
}

