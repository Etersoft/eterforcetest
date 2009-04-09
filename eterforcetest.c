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

/*
  Measure function work time
  http://bugs.etersoft.ru/show_bug.cgi?id=3031
*/

FILE *measure_f;
void measure_init()
{
	measure_f = fopen("eterforcetest.log","w+");

}

/* Check for host OS */
void (CDECL *p_wine_get_host_version)(const char **, const char **);


const char *get_sysname()
{
    const char *sysname, *release;
    HMODULE ntdll;

    ntdll = LoadLibrary("ntdll.dll");
    if (ntdll == NULL)
        return NULL;

    p_wine_get_host_version = (void *)GetProcAddress(ntdll, "wine_get_host_version");
    if (p_wine_get_host_version == NULL) {
        FreeLibrary(ntdll);
        return "Windows";
    }

    p_wine_get_host_version(&sysname, &release);
    FreeLibrary(ntdll);
    return sysname;
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
		if (et_measure[i].res)
			printf("    %25s %2.02f\n",
				et_measure[i].name, (((double)et_measure[i].res / et_measure[i].ms)/s));
	}
	fclose(measure_f);
}

int main(int argc, char**argv)
{
	char *test = NULL;
	/* We need static var against unused result optimization */
	static int i = 2;
	int list = 0;

	printf("\nPerformance measurement instrument. (c) Etersoft 2008, 2009\n");
	printf("See description at http://winehq.org.ru/Measurement\n");
	printf("Running under host OS: %s", get_sysname());
	printf("\n\n");

	if (argc > 1) {
		test = argv[1];
		if (!strcmp(test,"-h") || !strcmp(test,"--help")) {
			printf("\nUsage: %s [testname]\n", argv[0]);
			exit (0);
		}
		if (!strcmp(test,"-l") || !strcmp(test,"--list")) {
			list = 1;
		} else
			printf("Run '%s' test only\n", test);
	}

	if (!list) {
		measure_init();
		MSTART(!list, "Arithmetic", 1) {
			i = (i+3)*7;
			i = i / 4;
			i = i - 7;
			i = i^int_count;
			i = i << 1;
		} MEND
	}

	#define TEST(n) \
		void test_##n(); \
		if (!list && (!test || !stricmp(test, ""#n))) test_##n(); \
		if (list) printf("\t%s\n",""#n);

	if (list)
		printf("Allowed testnames:\n");
	TEST(compare);
	TEST(encoding);
	TEST(string);
	TEST(char);
	TEST(file);
	TEST(time);
	TEST(memory);
	TEST(window);
	TEST(menu);
	TEST(message);
	TEST(dialog);
	TEST(x11dc);
	TEST(memdc);
	TEST(font);
	TEST(ole32);
	TEST(reg);

	if (!list)
		measure_report();
	return 0;
}
