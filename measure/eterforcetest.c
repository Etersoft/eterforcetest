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
	printf("\nPerformance measurement instrument. (c) Etersoft 2008\n");
	printf("See description at http://winehq.org.ru/Measurement\n");
	printf("\n\n");
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
			printf("    %25s %2.02f\n",
				et_measure[i].name, (((double)et_measure[i].res / et_measure[i].ms)/s));
	}
	fclose(measure_f);
}

int main()
{
	/* We need static var against unused result optimization */
	static int i = 2;
	measure_init();

	MSTART(0+1, "Arithmetic", 1) {
		i = (i+3)*7;
		i = i / 4;
		i = i - 7;
		i = i^int_count;
		i = i << 1;
	} MEND

	test_compare();
	test_encoding();
	test_string();
	test_char();
	test_file();
	//test_time();
	test_memory();
	//test_window();
	//test_font();
	measure_report();
	return 0;
}
