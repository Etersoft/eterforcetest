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

/*
	GetSystemTime / GetLocalTime
	http://msdn.microsoft.com/en-us/library/ms724950(VS.85).aspx
*/

void test_time()
{
	SYSTEMTIME st, lt;

	printf("\n\n* * *  Time operations  * * *\n");

	MSTART(1, "GetTickCount", 10) {
		GetTickCount();
	} MEND

	MSTART(1, "GetLocalTime", 20) {
		GetLocalTime(&lt);
	} MEND

	MSTART(1, "GetSystemTime", 20) {
		GetSystemTime(&st);
	} MEND


}
