#include <windows.h>
#include "eterforcetest.h"

void test_memory()
{
	void *buffer;
	int size = 4096 * 25;

	printf("\n\n* * *  Memory operations  * * *\n");

	buffer = HeapAlloc( GetProcessHeap(), 0, size);
	MSTART(buffer, "HeapAlloc/HeapFree", 70) {
		buffer = HeapAlloc( GetProcessHeap(), 0, size);
		HeapFree(GetProcessHeap(), 0, buffer);
	} MEND

}
