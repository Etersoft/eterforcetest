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


#define TEST_STRING "ABCDEFGHRTPENDOFPROZMIY"
static WCHAR test_stringW[] = {'A','B','C','D','E','F','G','H','R','T','P','E','N','D','O','F','P','R','O','Z','M','I','Y', '\0'};
#define TEST_STRINGW test_stringW

static WCHAR test_string2W[] = {'a','b','c','d','e','f','g','h','r','t','g','o','\0'};
#define TEST_STRING2W test_string2W

void test_compare()
{
	int res;
	#define BUFLEN 100
	WCHAR destW[BUFLEN];
	char dest[BUFLEN];

	printf("\n\n* * *  Comparing operations  * * *\n");

	lstrcpyA(dest, TEST_STRING);
	MSTART(1, "lstrcmpiA", 2) {
		res = lstrcmpiA(dest, "abcdefghrtgo");
	} MEND

	MSTART(1, "lstrcmpA", 2) {
		res = lstrcmpA(dest, "abcdefghrtgo");
	} MEND

	MSTART(1, "CompareStringA/NEUTRAL", 20) {
		res = CompareStringA(LOCALE_NEUTRAL, 0, dest, -1, "abcdefghrtgo", -1);
	} MEND

	MSTART(1, "CompareStringA/cp1251", 20) {
		res = CompareStringA(LOCALE_SYSTEM_DEFAULT, 0, dest, -1, "abcdefghrtgo", -1);
	} MEND

	MSTART(1, "CompareStringA/cp1256", 20) {
		res = CompareStringA(LOCALE_SYSTEM_DEFAULT, 0, dest, -1, "abcdefghrtgo", -1);
	} MEND


	MSTART(1, "CompareStringA/NEUTRAL/IgnoreCase", 6) {
		res = CompareStringA(LOCALE_NEUTRAL, NORM_IGNORECASE|LOCALE_USE_CP_ACP, dest, -1, "abcdefghrtgo", -1);
	} MEND

	MSTART(1, "CompareStringA/cp1251/IgnoreCase", 6) {
		res = CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE|LOCALE_USE_CP_ACP, dest, -1, "abcdefghrtgo", -1);
	} MEND

	MSTART(1, "CompareStringA/cp1256/IgnoreCase", 6) {
		res = CompareStringA(LOCALE_SYSTEM_DEFAULT, NORM_IGNORECASE|LOCALE_USE_CP_ACP, dest, -1, "abcdefghrtgo", -1);
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

