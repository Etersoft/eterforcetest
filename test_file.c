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

void test_file()
{
	HANDLE hFile;
	DWORD rd;
	char filename[]="testfile.tmp";
	char buf[10000];

	printf("\n\n* * *  File operations  * * *\n");

	hFile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		perror("Skip the file test due errors");
	}
	WriteFile(hFile, buf, sizeof(buf), &rd, NULL);
	CloseHandle(hFile);

	MSTART(hFile != INVALID_HANDLE_VALUE, "CreateFile/CloseHandle", 700) {
		hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
			CloseHandle(hFile);
		else
			printf("Fatal, stop me\n");
	} MEND

	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	MSTART(hFile != INVALID_HANDLE_VALUE, "SetFilePointer", 20) {
		SetFilePointer(hFile, int_count, 0, FILE_BEGIN);
	} MEND
	CloseHandle(hFile);

	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	MSTART(hFile != INVALID_HANDLE_VALUE, "ReadFile", 50) {
		SetFilePointer(hFile, 0, 0, FILE_BEGIN);
		ReadFile(hFile, buf, sizeof(buf), &rd, NULL);
	} MEND
	CloseHandle(hFile);

	hFile = CreateFile(filename, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	MSTART(hFile != INVALID_HANDLE_VALUE, "WriteFile", 50) {
		SetFilePointer(hFile, 0, 0, FILE_BEGIN);
		WriteFile(hFile, buf, sizeof(buf), &rd, NULL);
	} MEND
	CloseHandle(hFile);

	DeleteFile(filename);
}

