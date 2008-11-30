#include <windows.h>
#include "eterforcetest.h"

void test_time()
{
	MSTART(1, "GetTickCount", 10) {
		GetTickCount();
	} MEND

	MSTART(1, "MultiByteToWideChar", 4) {
		GetTickCount();
	} MEND

	MSTART(1, "WideCharToMultiByte", 4) {
		GetTickCount();
	} MEND
}
