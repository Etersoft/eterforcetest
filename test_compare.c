/*
 * ETERFORCETEST
 *
 * Copyright 2008,2009 Vitaly Lipatov, Etersoft
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

#define BUFLEN 100

/* 23 chars */
static const WCHAR test_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test_stringW

/* Cyrillic letters */
static const WCHAR test_stringCyW[] = {0x410, 0x411, 0x42F, 0x414, 0x419, 0x41A, 0x41B, 0x421, 0x412, 0x413,
	0x412, 0x414, 0x415, 0x416, 0x417, 0x418, 0x422, 0x423, 0x425, 0x424, 0x427, 0x428, 0x429, '\0'};
static CHAR test_stringCy[BUFLEN];

static const WCHAR test_string2W[] = {'a','b','c','d','e','f','g','h','r','t','g','o','\0'};
#define TEST_STRING2W test_string2W

static CHAR test1_string[BUFLEN];
#define TEST_STRING test1_string

static const CHAR test1_string2[] = "abcdefghrtgo";
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

static void test_comparew_lang(int lang, const char*langname)
{
	static int res;
	char name[100];
	LCID lcid = MAKELCID(MAKELANGID(lang, SUBLANG_DEFAULT), SORT_DEFAULT);

	sprintf(name, "CompareStringW/%s", langname + strlen("LANG_"));
	MSTART(lang, name, 20) {
		res = CompareStringW(lcid, 0, TEST_STRINGW, -1, TEST_STRING2W, -1);
	} MEND

	sprintf(name, "CompareStringW/ICase/%s", langname + strlen("LANG_"));
	MSTART(lang, name, 6) {
		res = CompareStringW(lang, NORM_IGNORECASE|LOCALE_USE_CP_ACP, TEST_STRINGW, -1, TEST_STRING2W, -1);
	} MEND
}

void test_compare()
{
	int res;

	/* Hope we run in cp1251 locale. Prepare 8bit string */
	WideCharToMultiByte( CP_ACP, 0, test_stringCyW, -1, test_stringCy, BUFLEN, NULL, NULL);
	WideCharToMultiByte( CP_ACP, 0, test_stringW, -1, test1_string, BUFLEN, NULL, NULL);
	/* printf("Test String: %s\n", test_stringCy); */

	printf("\n\n* * *  Comparing operations  * * *\n");

	MSTART(1, "lstrcmpiA", 2) {
		res = lstrcmpiA(TEST_STRING, TEST_STRING2);
	} MEND

	MSTART(1, "lstrcmpA", 2) {
		res = lstrcmpA(TEST_STRING, TEST_STRING2);
	} MEND

	MSTART(1, "lstrcmpiW", 2) {
		res = lstrcmpiW(TEST_STRINGW, TEST_STRING2W);
	} MEND

	MSTART(1, "lstrcmpW", 2) {
		res = lstrcmpW(TEST_STRINGW, TEST_STRING2W);
	} MEND

#define TEST_COMPARE_LANG(lang) \
	test_compare_lang(lang, ""#lang);

	TEST_COMPARE_LANG(LANG_BELARUSIAN);
	TEST_COMPARE_LANG(LANG_ESTONIAN);
	TEST_COMPARE_LANG(LANG_LATVIAN);
	TEST_COMPARE_LANG(LANG_RUSSIAN)
	TEST_COMPARE_LANG(LANG_UKRAINIAN);
	TEST_COMPARE_LANG(LANG_ENGLISH);
	TEST_COMPARE_LANG(LANG_FRENCH);
#undef TEST_COMPARE_LANG


	/* Test CompareStringA */
	MSTART(1, "CompareStringA/CURRENT", 20) {
		res = CompareStringA(GetThreadLocale(), 0, TEST_STRING, -1, TEST_STRING2, -1);
	} MEND

	MSTART(1, "CompareStringA/ICase/CURRENT", 6) {
		res = CompareStringA(GetThreadLocale(), NORM_IGNORECASE|LOCALE_USE_CP_ACP, TEST_STRING, -1, TEST_STRING2, -1);
	} MEND

	MSTART(1, "CompareStringA/CURRENT/Cyr", 20) {
		res = CompareStringA(GetThreadLocale(), 0, test_stringCy, -1, TEST_STRING2, -1);
	} MEND

	MSTART(1, "CompareStringA/ICase/CURRENT/Cyr", 6) {
		res = CompareStringA(GetThreadLocale(), NORM_IGNORECASE|LOCALE_USE_CP_ACP, test_stringCy, -1, TEST_STRING2, -1);
	} MEND


#define TEST_COMPAREW_LANG(lang) \
	test_comparew_lang(lang, ""#lang);

	TEST_COMPAREW_LANG(LANG_BELARUSIAN);
	TEST_COMPAREW_LANG(LANG_ESTONIAN);
	TEST_COMPAREW_LANG(LANG_LATVIAN);
	TEST_COMPAREW_LANG(LANG_RUSSIAN)
	TEST_COMPAREW_LANG(LANG_UKRAINIAN);
	TEST_COMPAREW_LANG(LANG_ENGLISH);
	TEST_COMPAREW_LANG(LANG_FRENCH);
#undef TEST_COMPAREW_LANG


	/* Test CompareStringW */
	MSTART(1, "CompareStringW/CURRENT", 20) {
		res = CompareStringW(GetThreadLocale(), 0, TEST_STRINGW, -1, TEST_STRING2W, -1);
	} MEND

	MSTART(1, "CompareStringW/ICase/CURRENT", 6) {
		res = CompareStringW(GetThreadLocale(), NORM_IGNORECASE|LOCALE_USE_CP_ACP, TEST_STRINGW, -1, TEST_STRING2W, -1);
	} MEND

	MSTART(1, "CompareStringW/CURRENT/Cyr", 20) {
		res = CompareStringW(GetThreadLocale(), 0, test_stringCyW, -1, TEST_STRING2W, -1);
	} MEND

	MSTART(1, "CompareStringW/ICase/CURRENT/Cyr", 6) {
		res = CompareStringW(GetThreadLocale(), NORM_IGNORECASE|LOCALE_USE_CP_ACP, test_stringCyW, -1, TEST_STRING2W, -1);
	} MEND

}

