/*
 *   Sudoku E-solver - simple sudoku solver
 *
 *   Copyright (c) 2015 Sasha Khapyorsky <sashakh@gmail.com>
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 */

#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#include "sudoku.h"

static void bitmaps_clear_bit(struct sudoku *s, unsigned i, unsigned bit)
{
	s->rows[i / D] &= ~(1 << bit);
	s->cols[i % D] &= ~(1 << bit);
	s->sqrs[(i / (D * N)) * N + (i % D) / N] &= ~(1 << bit);
}

static void bitmaps_set_bit(struct sudoku *s, unsigned i, unsigned bit)
{
	s->rows[i / D] |= 1 << bit;
	s->cols[i % D] |= 1 << bit;
	s->sqrs[(i / (D * N)) * N + (i % D) / N] |= 1 << bit;
}

static s_type bitmap_free_bits_tab[1 << (D + 1)][D + 1];

static s_type *get_free_nums(struct sudoku *s, unsigned i)
{
	return bitmap_free_bits_tab[(s->rows[i / D] | s->cols[i % D]
		| s->sqrs[(i / (D * N)) * N + (i % D) / N])];
}

void solver_init()
{
	unsigned i, n, bits;

	for (bits = 0; bits < 1 << (D + 1); bits++)
		for (i = 1, n = 0; i < D + 1; i++)
			if (!(bits & (1 << i)))
				bitmap_free_bits_tab[bits][n++] = i;
}

static unsigned solve_one(struct sudoku *s, unsigned start)
{
	for (; start < D * D; start++)
		if (!s->s[start])
			break;

	if (start == D * D)		/* finally solved */
		return 1;

	s_type *n = get_free_nums(s, start);
	while (*n) {
		bitmaps_set_bit(s, start, *n);
		if (solve_one(s, start + 1)) {
			s->s[start] = *n;	/* solved */
			return 1;
		}
		bitmaps_clear_bit(s, start, *n++);
	}

	return 0;
}

void sudoku_printf(struct sudoku *s, const char *fmt, ...)
{
	va_list ap;
	unsigned i, j;

	va_start(ap, fmt);
	vprintf(fmt, ap);
	va_end(ap);
	printf("\n");
	for (i = 0; i < D; i++) {
		for (j = 0; j < D; j++)
			printf(" %2u", s->orig[j + i * D]);
		printf("        ");
		for (j = 0; j < D; j++)
			printf(" %2u", s->new[j + i * D]);
		printf("\n");
	}
	printf("\n");
}

void sudoku_init(struct sudoku *s, s_type n[])
{
	unsigned i;

	memset(s, 0, sizeof(*s));
	for (i = 0; i < D * D; i++)
		if (n[i])
			bitmaps_set_bit(s, i, n[i]);
	s->s = s->new;
	memcpy(s->new, n, sizeof(s->new));
	memcpy(s->orig, n, sizeof(s->orig));
}

int sudoku_solve(struct sudoku *s)
{
	return solve_one(s, 0);
}

int sudoku_solver(struct sudoku *s)
{
	struct timespec ts1, ts2;

	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts1);

	solve_one(s, 0);

	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts2);
	s->nsec = (ts2.tv_sec - ts1.tv_sec) * 1000000000 +
	    ts2.tv_nsec - ts1.tv_nsec;
	printf("done in %09lu nanoseconds\n", s->nsec);

	return 0;
}

void sudoku_multi_solver_each(struct sudoku s[], unsigned size, unsigned print)
{
	struct timespec ts1, ts2;
	unsigned long t = 0;
	unsigned i;

	for (i = 0; i < size; i++) {
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts1);
		sudoku_solve(&s[i]);
		clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts2);
		s[i].nsec = (ts2.tv_sec - ts1.tv_sec) * 1000000000 +
		    ts2.tv_nsec - ts1.tv_nsec;
		if (print)
			sudoku_printf(&s[i], "Sudoku %u"
				      " solved in %lu nanosecs:", i, s[i].nsec);
		t += s[i].nsec;
	}

	printf("done %u puzzles in %09lu nanoseconds (average %lu)\n", i,
	       t, size ? t / size : 0);
}

void sudoku_multi_solver(struct sudoku s[], unsigned size)
{
	struct timespec ts1, ts2;
	unsigned long t = 0;
	unsigned i;

	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts1);
	for (i = 0; i < size; i++)
		sudoku_solve(&s[i]);
	clock_gettime(CLOCK_THREAD_CPUTIME_ID, &ts2);

	t = (ts2.tv_sec - ts1.tv_sec) * 1000000000 + ts2.tv_nsec - ts1.tv_nsec;
	printf("done %u puzzles in %09lu nanoseconds (average %lu)\n", i,
	       t, size ? t / size : 0);
}
