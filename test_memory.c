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

void test_memory()
{
	static void *buffer, *buffer1, *buffer2;
	int size = 4096 * 25;
	DWORD old_prot;

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

	buffer = malloc(size);
	MSTART(buffer, "VirtualProtect", 100) {
		VirtualProtect(buffer, size, PAGE_READWRITE, &old_prot);
	} MEND
	free(buffer);
}
