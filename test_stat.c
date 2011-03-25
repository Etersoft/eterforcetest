#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <shellapi.h>
#include <dir.h>
#include <ctype.h>
#include "eterforcetest.h"


#define LEN 10000
#define FNLEN 15

/*
 *Change reg
 */
void ChangeReg(char *a)
{
	char *c = &a[strlen(a) + 1 - FNLEN];
	if (isupper(*c))
		CharLowerA(c);
	else
		CharUpperA(c);
}
/*
 *Generate File Name
 */
void GenerateFileName(char *a, char *b)
{
	int i;
	int len_b;

	len_b = strlen(b)+1;
	strcpy( a, b );
	a[len_b-1] = '/';
	a[(len_b + FNLEN) - 1]=0;
	for ( i = len_b; i<(len_b + FNLEN) - 1; i++)
	{
		a[i] = rand() % ('z' -'a') + 'a';
	}
	if( (rand() % 2 + 0) == 0)
	{
		CharUpperA(a + len_b);
	}
}

void test_stat()
{
	printf("\n\n\n\n Runing stat test  ");
	char name_dir[] = "container";    //name dir
	char mas[25];                     //contain files name
	int i;

	/*
	*Create new directroy
	*/
	if(!(CreateDirectory(name_dir,NULL)))
	{
		printf("\nCan't create directory...");
		exit (1);
	}
	FILE *hFile;                          //for create files
	char mass_name_of_files[LEN][25];   //use for delete files
	for(i=0;i<LEN;i++)
	{
		GenerateFileName(mas, name_dir);
		strcpy(mass_name_of_files[i],mas);
		hFile = CreateFile(mas, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		CloseHandle(hFile);
	}

	printf("\n\nCreateFile() for \t\n  %s ", mas);
	MSTART(1, "CreateFile", 1000)
	{
		hFile = CreateFile(mas, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		CloseHandle(hFile);
	}MEND

	ChangeReg(mas);
	printf("\n\nCreateFile() for \t\n  %s ", mas);
	MSTART(1, "CreateFile", 1000)
	{
		hFile = CreateFile(mas, GENERIC_WRITE, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
		CloseHandle(hFile);
	}MEND

	for(i=0;i<LEN;i++)
	{
		DeleteFile(mass_name_of_files[i]);
	}
	if(!(RemoveDirectory(name_dir)))
		printf("\n Can't remove files and directory...Do it yourself...\n");
}
