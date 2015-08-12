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
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <getopt.h>

#include "sudoku.h"

#define NUM_OF_SUDOKUS (4096 * 4)

extern int sudoku_file_parse(const char *file_name, struct sudoku sudoku[],
			     unsigned size);

static int do_multi(unsigned verbose, unsigned num_sudokus, unsigned sudoku_num,
		    int num_files, char * const file_names[])
{
	struct sudoku *s;
	unsigned n = 0, i;

	if (num_sudokus < sudoku_num)
		num_sudokus = sudoku_num + 1;

	s = malloc(num_sudokus * sizeof(*s));
	if (!s) {
		perror("malloc");
		return -1;
	}

	for (i = 0; i < num_files; i++)
		n += sudoku_file_parse(file_names[i], s + n, num_sudokus - n);

	if (num_files != 1)
		for (; n < num_sudokus; n++)
			sudoku_init(&s[n], sudoku_collection_get(n % sudoku_collection_size()));

	if (sudoku_num) {
		for (n = 0; n < sudoku_num; n++)
			sudoku_init(&s[n], s[sudoku_num].orig);
		for (n = sudoku_num + 1; n < num_sudokus; n++)
			sudoku_init(&s[n], s[sudoku_num].orig);
		sudoku_multi_solver(s, n);
		if (verbose)
			sudoku_printf(&s[sudoku_num], "Sudoku %u:", sudoku_num);
	} else if (verbose)
		sudoku_multi_solver_each(s, n, verbose);
	else
		sudoku_multi_solver(s, n);

	free(s);

	return 0;
}

void usage(const char *prog)
{
	printf("usage: %s [-vh] [-s N] [-n N] [sudoku_file...]\n", prog);
	printf("  --help, -h       - this usage message.\n");
	printf("  --verbose, -v    - increase verbosity - show sudoku.\n");
	printf("  --sudoku, -s NUM - solve specified puzzle.\n");
	printf("  --number, -n NUM - solve NUM of puzzles (default %u).\n",
	       NUM_OF_SUDOKUS);
	exit(2);
}

int main(int argc, char * const argv[])
{
	unsigned num_of_sudokus = NUM_OF_SUDOKUS;
	unsigned sudoku_num = 0;
	unsigned verbose = 0;
	int c;
	static const struct option opt[] = {
		{"sudoku", 1, 0, 's'},
		{"number", 1, 0, 'n'},
		{"verbose", 0, 0, 'v'},
		{"help", 0, 0, 'h'},
	};

	while ((c = getopt_long(argc, argv, "vhs:n:", opt, NULL)) >= 0) {
		switch (c) {
		case 's':
			sudoku_num = strtoul(optarg, NULL, 0);
			break;
		case 'n':
			num_of_sudokus = strtoul(optarg, NULL, 0);
			break;
		case 'v':
			verbose = 1;
			break;
		case 'h':
		default:
			usage(argv[0]);
			break;
		}
	}

	solver_init();

	return do_multi(verbose, num_of_sudokus, sudoku_num,
			argc - optind, argv + optind);
}
