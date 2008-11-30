#include <windows.h>
#include "eterforcetest.h"

FILE *measure_f;
void measure_init()
{
	measure_f = fopen("eterforcetest.log","w+");
}

void measure_report()
{
	int i, count = 0;
	double s = 0;
	for (i = 0 ; et_measure[i].name ; i++) {
		if (!et_measure[i].res)
			continue;
		s += ((double)et_measure[i].res / et_measure[i].ms);
		count++;
	}
	s /= count;
	/* TODO: посчитать СКО, и вычислить среднее без выходящих за пределы */
	printf ("Average: %2.02f\n", s);
	printf ("\nNormalize result:\n");
	for (i = 0 ; et_measure[i].name ; i++) {
		if (et_measure[i].ms)
			printf("    %15s %2.02f\n", et_measure[i].name, (((double)et_measure[i].res / et_measure[i].ms)/s));
	}
	fclose(measure_f);
}

void test_string()
{
	int len;
	char dest[100];

	#define TEST_STRING "ABCDEFGHRTPENDOFPROZMIY"
	len = strlen(TEST_STRING);

	MSTART(1, "lstrcpyA", 1) {
		lstrcpyA(dest, TEST_STRING);
	} MEND

	MSTART(1, "lstrcpynA", 1) {
		lstrcpynA(dest, TEST_STRING, len);
	} MEND


	lstrcpyA(dest, TEST_STRING);
	MSTART(1, "lstrlenA", 1) {
		lstrlenA(dest);
		lstrlenA(dest);
	} MEND

	MSTART(1, "lstrcmpiA", 2) {
		lstrcmpiA(dest, "abcdefghrtgo");
	} MEND

	MSTART(1, "lstrcmpA", 2) {
		lstrcmpA(dest, "abcdefghrtgo");
	} MEND

	MSTART(1, "lstrcatA", 1) {
		lstrcatA(dest, "abcdefghrtgo");
		dest[len] = 0;
	} MEND
}

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

int main()
{
	measure_init();
	//test_string();
	test_file();
	test_time();
	//test_window();
	//test_font();
	measure_report();
}
