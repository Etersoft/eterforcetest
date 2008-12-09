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

TODO for mingw:
#if _WIN32_WINNT >= 0x0600
WINBASEAPI ULONGLONG   WINAPI GetTickCount64(void);
#endif

*/


typedef unsigned long long ticks;

/* FIXME: fix me for other compilers */
ticks getticks(void)
{
     unsigned a, d;
     asm("cpuid");
     asm volatile("rdtsc" : "=a" (a), "=d" (d));

     return (((ticks)a) | (((ticks)d) << 32));
}

WINAPI DWORD func()
{
	return GetTickCount();
}

WINAPI ticks empty_func()
{
     unsigned a = 0x101, d = 0x202;
     return (((ticks)a) | (((ticks)d) << 32));
}

void test_time()
{
	SYSTEMTIME st, lt;
	static DWORD tc;
	static ULONGLONG utc;
	WINBASEAPI ULONGLONG (WINAPI *pgtc)(void);
	static DWORD (WINAPI *pfunc)(void);
	static ticks (WINAPI *ptfunc)(void);
	HANDLE hModule;

	printf("\n\n* * *  Time operations  * * *\n");

	MSTART(1, "GetTickCount", 10) {
		tc = GetTickCount();
	} MEND

	pfunc = &func; /* forbid inline func */
	MSTART(1, "GetTickCount_func", 10) {
		tc = func();
	} MEND

	ptfunc = &empty_func; /* forbid inline func */
	MSTART(1, "empty_10func", 1) {
		/* ten times */
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
	} MEND

	/* FIXME: detect if rdtsc using will correct */
	MSTART(1, "getticks_via_rdtsc", 1) {
		utc = getticks();
	} MEND

	MSTART(1, "GetLocalTime", 20) {
		GetLocalTime(&lt);
	} MEND

	MSTART(1, "GetSystemTime", 20) {
		GetSystemTime(&st);
	} MEND

	/* Since Windows Vista / 2008 */
	hModule = LoadLibraryA("kernel32.dll");
	pgtc = (void*)GetProcAddress(hModule, "GetTickCount64");
	MSTART(pgtc, "GetTickCount64", 10) {
		utc = pgtc();
	} MEND

}
