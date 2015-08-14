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

#include "sudoku.h"

void bitmap_free_bits_table(unsigned max)
{
	unsigned i, bits;

	printf("const s_type bitmap_free_bits_tab[][%u] = {\n", max);
	for (bits = 0; bits < 1 << max; bits++) {
		printf("\t[ 0x%03x ] = { ", bits);
		for (i = 1; i < max; i++)
			if (!(bits & (1 << i)))
				printf("%u, ", i);
		printf("},\n");
	}
	printf("};\n");
}

int main()
{
	bitmap_free_bits_table(D + 1);
	return 0;
}
