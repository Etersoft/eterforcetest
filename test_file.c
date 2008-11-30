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

}

