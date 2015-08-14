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
#include <string.h>
#include <ctype.h>
#include <errno.h>

#include "sudoku.h"

int sudoku_file_parse(const char *file_name, struct sudoku sudoku[],
		      unsigned size)
{
	char line[4096];
	s_type s[D * D];
	int n = 0;
	FILE *f;

	f = fopen(file_name, "r");
	if (!f) {
		fprintf(stderr, "fopen(\'%s\'): %s\n", file_name,
			strerror(errno));
		return -1;
	}

	while (n < size && fgets(line, sizeof(line), f)) {
		unsigned i = 0;
		char *p = line;
		//printf("--> %s", p);
		while (*p && !(isdigit(*p)))
			p++;
		if (!*p)
			continue;
		while (isdigit(*p) && i < D * D)
			s[i++] = *p++ - '0';
		if (i < D * D)
			continue;
#if 0
		for (i = 0; i < 81; i++)
			printf("%u", s[i]);
		printf("\n");
#endif
		sudoku_init(&sudoku[n], s);
		n++;
	}

	fclose(f);
	return n;
}
