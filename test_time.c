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

DWORD test_gettid(void)
{
//#if defined(__linux__) && defined(__i386__)
#if defined(__i386__)
    DWORD ret;
    __asm__("int $0x80" : "=a" (ret) : "0" (224) /* SYS_gettid */);
    return ret;
#else
#warning "Not Linux?"
    return -1;  /* FIXME */
#endif
}


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

WINAPI ticks ticks_func()
{
     unsigned a = 0x101, d = 0x202;
     return (((ticks)a) | (((ticks)d) << 32));
}

WINAPI ticks empty_func()
{
     unsigned a = 0x101;
     return a;
}

void test_time()
{
	SYSTEMTIME st, lt;
	FILETIME ft1, ft2;
	static DWORD tc;
	static ULONGLONG utc;
	WINBASEAPI ULONGLONG (WINAPI *pgtc)(void);
	static DWORD (WINAPI *pfunc)(void);
	static ticks (WINAPI *ptfunc)(void);
	HANDLE hModule;
	BOOL res;
	HKEY key;
	CRITICAL_SECTION cs;

	printf("\n\n* * *  Time operations  * * *\n");

	MSTART(1, "empty_loop", 1) {
	} MEND

	MSTART(1, "GetTickCount", 10) {
		tc = GetTickCount();
	} MEND

	pfunc = &func; /* forbid inline func */
	MSTART(1, "GetTickCount_func", 10) {
		tc = func();
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

	ptfunc = &empty_func; /* forbid inline func */
	MSTART(1, "empty_10func", 1) {
		/* ten times */
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
		utc = empty_func(); utc = empty_func();
	} MEND

	/* CompareFileTime on Windows Segfault with NULL args */
	memset (&ft1, 0, sizeof (ft1));
	memset (&ft2, 0, sizeof (ft2));
	MSTART(1, "kernel32_10call", 1) {
		/* ten times */
		res = CompareFileTime(&ft1, &ft2); res = CompareFileTime(&ft1, &ft2);
		res = CompareFileTime(&ft1, &ft2); res = CompareFileTime(&ft1, &ft2);
		res = CompareFileTime(&ft1, &ft2); res = CompareFileTime(&ft1, &ft2);
		res = CompareFileTime(&ft1, &ft2); res = CompareFileTime(&ft1, &ft2);
		res = CompareFileTime(&ft1, &ft2); res = CompareFileTime(&ft1, &ft2);
	} MEND

#if 0
/* Do not measure correctly */
	MSTART(1, "kernel32_via_ntdll_10call", 1) {
		/* ten times */
		res = DosDateTimeToFileTime( 0, 0, &ft1); res = DosDateTimeToFileTime( 0, 0, &ft1);
		res = DosDateTimeToFileTime( 0, 0, &ft1); res = DosDateTimeToFileTime( 0, 0, &ft1);
		res = DosDateTimeToFileTime( 0, 0, &ft1); res = DosDateTimeToFileTime( 0, 0, &ft1);
		res = DosDateTimeToFileTime( 0, 0, &ft1); res = DosDateTimeToFileTime( 0, 0, &ft1);
		res = DosDateTimeToFileTime( 0, 0, &ft1); res = DosDateTimeToFileTime( 0, 0, &ft1);
	} MEND
#endif

	/* Guess one GetSystemTime is one system call gettimeofday */
	MSTART(1, "OS_Kernel_call", 40) {
		GetSystemTime(&lt);
	} MEND

/* How to detect Linux under Wine: Wait for http://bugs.etersoft.ru/show_bug.cgi?id=3790 */
#if 0
	MSTART(1, "OS_Kernel_call_gettid", 40) {
		res = test_gettid();
	} MEND
#endif

	/* Guess close key is one wineserver call */
	res = (ERROR_SUCCESS==RegOpenKeyEx(HKEY_LOCAL_MACHINE,"Software",0,KEY_WRITE,&key));
	RegCloseKey(key);
	MSTART(res, "wineserver_call", 400) {
		RegCloseKey(key);
	} MEND

	InitializeCriticalSection( &cs );
	MSTART(1, "Critical section", 1) {
		EnterCriticalSection( &cs );
		LeaveCriticalSection( &cs );
	} MEND
	DeleteCriticalSection( &cs );
}
