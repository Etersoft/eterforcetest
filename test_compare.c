/*
 * ETERFORCETEST
 *
 * Copyright 2008 Vitaly Lipatov, Etersoft
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#include <windows.h>
#include "eterforcetest.h"


static WCHAR test_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test_stringW

static WCHAR test_string2W[] = {'a','b','c','d','e','f','g','h','r','t','g','o','\0'};
#define TEST_STRING2W test_string2W

static CHAR test1_string[] = "ABCDEFGHRTPENDOFPROZMIY";
#define TEST_STRING test1_string

static CHAR test1_string2[] = "abcdefghrtgo";
#define TEST_STRING2 test1_string2


static void test_compare_lang(int lang, const char*langname)
{
	static int res;
	char name[100];
	LCID lcid = MAKELCID(MAKELANGID(lang, SUBLANG_DEFAULT), SORT_DEFAULT);

	sprintf(name, "CompareStringA/%s", langname + strlen("LANG_"));
	MSTART(lang, name, 20) {
		res = CompareStringA(lcid, 0, TEST_STRING, -1, TEST_STRING2, -1);
	} MEND

	sprintf(name, "CompareStringA/ICase/%s", langname + strlen("LANG_"));
	MSTART(lang, name, 6) {
		res = CompareStringA(lang, NORM_IGNORECASE|LOCALE_USE_CP_ACP, TEST_STRING, -1, TEST_STRING2, -1);
	} MEND
}
#define TEST_COMPARE_LANG(lang) \
	test_compare_lang(lang, ""#lang);

void test_compare()
{
	int res;
	#define BUFLEN 100
	static WCHAR destW[BUFLEN];
	static char dest[BUFLEN];

	printf("\n\n* * *  Comparing operations  * * *\n");

	lstrcpyA(dest, TEST_STRING);
	MSTART(1, "lstrcmpiA", 2) {
		res = lstrcmpiA(dest, TEST_STRING2);
	} MEND

	MSTART(1, "lstrcmpA", 2) {
		res = lstrcmpA(dest, TEST_STRING2);
	} MEND

	TEST_COMPARE_LANG(LANG_BELARUSIAN);
	TEST_COMPARE_LANG(LANG_ESTONIAN);
	TEST_COMPARE_LANG(LANG_LATVIAN);
	TEST_COMPARE_LANG(LANG_RUSSIAN)
	TEST_COMPARE_LANG(LANG_UKRAINIAN);
	TEST_COMPARE_LANG(LANG_ENGLISH);
	TEST_COMPARE_LANG(LANG_FRENCH);

	MSTART(1, "CompareStringA/CURRENT", 20) {
		res = CompareStringA(GetThreadLocale(), 0, dest, -1, TEST_STRING2, -1);
	} MEND

	MSTART(1, "CompareStringA/ICase/CURRENT", 6) {
		res = CompareStringA(GetThreadLocale(), NORM_IGNORECASE|LOCALE_USE_CP_ACP, dest, -1, TEST_STRING2, -1);
	} MEND


	lstrcpyW(destW, TEST_STRINGW);
	MSTART(1, "lstrcmpiW", 2) {
		res = lstrcmpiW(destW, TEST_STRING2W);
	} MEND

	/* TODO
	CompareStringW
	*W functions
	*/
	/* TODO: с кириллицей CP1251/UCS2 */

}

