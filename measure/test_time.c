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
