/*
 * ETERFORCETEST
 *
 * Copyright 2008 Vitaly Lipatov, Etersoft
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


/* TODO: с кириллицей CP1251 */
static CHAR test1_string[] = "ABCDEFGHRTPENDOFPROZMIY";
static CHAR test2_string[] = "abcdefghrtpendofprozmiy";
/*  "ABCDEFGHRTPENDOFPROZMIY"; */
#define TEST_STRING test1_string
#define test_STRING test2_string

static WCHAR test1_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test1_stringW
static WCHAR test2_stringW[] = {'a','b','c','d','e','f','g','h','r','t','p','e','n','d','o','f','p','r','o','z','m','i','y', '\0'};
#define test_STRINGW test2_stringW

void test_char()
{
	/* we need static var for save result */
	static CHAR *str;
	static WCHAR *strW;
	int ok = strchr(TEST_STRING, 'Z') != NULL;
	static BOOL flag;
	
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
	
	MSTART(1, "CharUpperA",1) {
		str = CharUpperA(test_STRING);
	} MEND
	
	MSTART(1, "CharUpperW",1) {
		strW = CharUpperW(test_STRINGW);
	} MEND
	
	/* TODO
	IsCharAlphaNumericA
	CharUpperA
	IsCharAlphaA
	*/
}

