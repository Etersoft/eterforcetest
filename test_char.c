/*
 * ETERFORCETEST
 *
 * Copyright 2008, 2009 Vitaly Lipatov, Etersoft
 * Copyright 2008 Denis Baranov, Etersoft
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

#define WINE_UNICODE_INLINE inline
#include "unicode.h"

#define BUFLEN 100

static const CHAR test1_string[] = "ABCDEFGHRTPENDOFPROZMIY";
static const CHAR test2_string[] = "abcdefghrtpendofprozmiy";
#define TEST_STRING test1_string
#define test_STRING test2_string

/* Cyrillic letters */
static const WCHAR test_stringCyW[] = {0x410, 0x411, 0x42F, 0x414, 0x419, 0x41A, 0x41B, 0x421, 0x412, 0x413,
	0x412, 0x414, 0x415, 0x416, 0x417, 0x418, 0x422, 0x423, 0x425, 0x424, 0x427, 0x428, 0x429, '\0'};
static CHAR test_stringCy[BUFLEN];

static const WCHAR test1_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test1_stringW

static const WCHAR test2_stringW[] = {'a','b','c','d','e','f','g','h','r','t','p','e','n','d','o','f','p','r','o','z','m','i','y', '\0'};
#define test_STRINGW test2_stringW

void test_char()
{
	/* we need static var for save result */
	static CHAR *str;
	static WCHAR *strW;
	int ok = strchr(TEST_STRING, 'Z') != NULL;
	static BOOL flag;

	static WCHAR destW[BUFLEN];
	static char dest[BUFLEN];

	/* Hope we run in cp1251 locale. Prepare 8bit string */
	WideCharToMultiByte( CP_ACP, 0, test_stringCyW, -1, test_stringCy, BUFLEN, NULL, NULL);

	printf("\n\n* * *  Char operations  * * *\n");


	MSTART(ok, "strchr", 1) {
		/* We need save result due optimizations */
		str = strchr(TEST_STRING, 'z');
	} MEND

	MSTART(1, "strchrW", 2) {
		strW = strchrW(TEST_STRINGW, 'z');
	} MEND

	MSTART(1, "IscharAlphaNumericA",1) {
		flag = IsCharAlphaNumericA('Z');
	} MEND

	MSTART(1, "IscharAlphaNumericW",1) {
		flag = IsCharAlphaNumericW('Z');
	} MEND

	MSTART(1, "IscharAlphaA",1) {
		flag = IsCharAlphaA('Z');
	} MEND

	MSTART(1, "IscharAlphaW",1) {
		flag = IsCharAlphaW('Z');
	} MEND

	/* Test Char Upper/Lower */
	lstrcpyA(dest, test_STRING);
	MSTART(1, "CharUpperA",5) {
		str = CharUpperA(dest);
	} MEND

	lstrcpyW(destW, test_STRINGW);
	MSTART(1, "CharUpperW",1) {
		strW = CharUpperW(destW);
	} MEND

	lstrcpyA(dest, TEST_STRING);
	MSTART(1, "CharLowerA",5) {
		str = CharLowerA(dest);
	} MEND

	lstrcpyW(destW, TEST_STRINGW);
	MSTART(1, "CharLowerW",1) {
		strW = CharLowerW(destW);
	} MEND


	/* Test Char Upper/Lower with cyrillic string */
	/* FIXME: test with lower string */
	lstrcpyA(dest, test_stringCy);
	MSTART(1, "CharUpperA/Cyr",5) {
		str = CharUpperA(dest);
	} MEND

	lstrcpyW(destW, test_stringCyW);
	MSTART(1, "CharUpperW/Cyr",1) {
		strW = CharUpperW(destW);
	} MEND

	lstrcpyA(dest, test_stringCy);
	MSTART(1, "CharLowerA/Cyr",5) {
		str = CharLowerA(dest);
	} MEND

	lstrcpyW(destW, test_stringCyW);
	MSTART(1, "CharLowerW/Cyr",1) {
		strW = CharLowerW(destW);
	} MEND

	/* Skip CharUpper/Lower on single character */

}

