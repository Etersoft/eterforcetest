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

