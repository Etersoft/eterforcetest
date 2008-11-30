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

