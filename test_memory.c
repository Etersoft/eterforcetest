#include <windows.h>
#include "eterforcetest.h"

void test_memory()
{
	static void *buffer, *buffer1, *buffer2;
	int size = 4096 * 25;

	printf("\n\n* * *  Memory operations  * * *\n");

	buffer = HeapAlloc( GetProcessHeap(), 0, size);
	MSTART(buffer, "HeapAlloc/HeapFree", 100) {
		buffer = HeapAlloc( GetProcessHeap(), 0, size);
		HeapFree(GetProcessHeap(), 0, buffer);
	} MEND
	/* lost initial buffer */

	MSTART(buffer, "HeapAlloc/HeapFree", 100) {
		buffer1 = HeapAlloc( GetProcessHeap(), 0, size);
		HeapFree(GetProcessHeap(), 0, buffer1);
	} MEND

	MSTART(buffer, "HeapAlloc/HeapFree/100b", 70) {
		buffer = HeapAlloc( GetProcessHeap(), 0, 100);
		HeapFree(GetProcessHeap(), 0, buffer);
	} MEND

	MSTART(buffer, "HeapAlloc/HeapFree/2x", 140) {
		buffer = HeapAlloc( GetProcessHeap(), 0, size);
		buffer1 = HeapAlloc( GetProcessHeap(), 0, size*2);
		HeapFree(GetProcessHeap(), 0, buffer);
		HeapFree(GetProcessHeap(), 0, buffer1);
	} MEND

	MSTART(buffer, "malloc", 140) {
		buffer = malloc(size);
		free(buffer);
	} MEND

	MSTART(buffer, "malloc/2x", 140) {
		buffer = malloc(size);
		buffer1 = malloc(size*2);
		free(buffer);
		free(buffer1);
	} MEND

	MSTART(buffer, "malloc/3x", 200) {
		buffer = malloc(size*3);
		free(buffer);
		buffer1 = malloc(size);
		buffer2 = malloc(size*2+100);
		free(buffer1);
		free(buffer2);
	} MEND
}
