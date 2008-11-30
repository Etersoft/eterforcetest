#include <windows.h>
#include "eterforcetest.h"

void test_file()
{
	HANDLE hFile;
	char filename[]="testfile.tmp";

	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) {
		perror("");
	} else
		CloseHandle(hFile);

	MSTART(hFile != INVALID_HANDLE_VALUE, "CreateFile - CloseHandle", 700) {
		hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		if (hFile != INVALID_HANDLE_VALUE)
			CloseHandle(hFile);
		else
			printf("Fatal, stop me\n");
	} MEND

	hFile = CreateFile(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	MSTART(hFile == INVALID_HANDLE_VALUE, "SetFilePointer", 700) {
		SetFilePointer(hFile, int_count, 0, FILE_BEGIN);
	} MEND
	if (hFile != INVALID_HANDLE_VALUE)
		CloseHandle(hFile);


}

