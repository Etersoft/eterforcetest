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
//#include <time.h>
#include <string.h>
#include <stdio.h>

#define MEASURE_COUNT 7000000

#define REPEAT_MEASURE 5

static int measure_count;
static char measure_name[100];
static DWORD measure_iresult[REPEAT_MEASURE];
static int measure_result;
static DWORD time_start;
static DWORD time_end;
static int measure_divid;

extern FILE *measure_f;
void measure_init();

extern struct { char *name; int ms; int res;} et_measure[];

static inline void measure_start() {
	register DWORD ts;
	putchar('.');
	fflush(stdout);
	ts = GetTickCount();
	/* Align to interval start, wait for next time step */
	time_start = ts + 1;
	while (ts == GetTickCount());
}

static inline void measure_end() {
	time_end = GetTickCount();
	measure_iresult[measure_count] = time_end - time_start;
}

static inline void print_measure()
{
	int i, etres = 0;
	double mks;

	/* Calc the average result to measure_result */
	measure_result = 0;
	for (i = 0 ; i < REPEAT_MEASURE ; i++)
		measure_result += measure_iresult[i];
	measure_result /= REPEAT_MEASURE;

	/* Check for etalon result */
	for (i = 0 ; et_measure[i].name ; i++) {
		if (!strcmp(et_measure[i].name, measure_name)) {
			etres = et_measure[i].ms;
			et_measure[i].res = measure_result;
		}
	}
	if (!etres)
		etres = measure_result;

	/* Get real time per one function call */
	mks = (1000.0*measure_result*measure_divid)/(MEASURE_COUNT);

	printf("%8.3fmks pc (%5u ms) (%3d%%) (1/%d - %.2fm iterations)\n\n",
		mks,
		measure_result * REPEAT_MEASURE,
		(100*measure_result)/etres, measure_divid, 0.000001*(MEASURE_COUNT*REPEAT_MEASURE)/measure_divid);
	fprintf( measure_f, "%30s %10d %8.3f\n", measure_name, measure_result, mks);
}

#define MSTART(ok, name, divid) \
	{ \
	register int int_count; \
	printf("Test for %25s ", name); \
	measure_divid = (divid); \
	strcpy(measure_name, name); \
	if (!(ok)) { \
		printf("skipping\n"); \
		time_start = 0;\
	} \
	else \
	for (measure_count = 0 ; measure_count < REPEAT_MEASURE ; measure_count++ ) { \
		measure_start(); \
		for(int_count = MEASURE_COUNT/divid; int_count-- ;)

#define MEND \
		measure_end(); \
		Sleep(50); \
	} \
	if (time_start) \
		print_measure(); }

