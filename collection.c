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

#include "sudoku.h"

s_type s_collection[][D * D] = {
	{},
	{
	 0, 1, 6, 2, 3, 0, 0, 0, 0,
	 2, 0, 0, 0, 0, 4, 0, 0, 8,
	 0, 7, 0, 0, 0, 0, 0, 2, 0,
	 0, 3, 0, 0, 6, 0, 9, 0, 0,
	 0, 0, 1, 0, 0, 0, 6, 0, 0,
	 0, 0, 9, 0, 1, 0, 0, 4, 0,
	 0, 4, 0, 0, 0, 0, 0, 7, 0,
	 5, 0, 0, 4, 0, 0, 0, 0, 3,
	 0, 0, 0, 0, 7, 5, 1, 8, 0,
	},
	{
	 2, 0, 1, 8, 0, 0, 0, 0, 0,
	 6, 0, 0, 0, 7, 0, 0, 0, 0,
	 0, 4, 3, 0, 0, 0, 2, 0, 0,
	 0, 0, 5, 0, 3, 0, 0, 2, 9,
	 0, 0, 0, 1, 0, 2, 0, 0, 0,
	 8, 2, 0, 0, 6, 0, 1, 0, 0,
	 0, 0, 6, 0, 0, 0, 5, 8, 0,
	 0, 0, 0, 0, 4, 0, 0, 0, 1,
	 0, 0, 0, 0, 0, 8, 9, 0, 4,
	},
	{
	 4, 0, 0, 2, 0, 0, 8, 9, 7,
	 0, 0, 0, 0, 0, 0, 2, 0, 1,
	 7, 0, 0, 0, 1, 3, 0, 0, 0,
	 8, 0, 7, 0, 0, 9, 0, 6, 3,
	 0, 6, 0, 1, 4, 8, 0, 5, 0,
	 5, 2, 0, 6, 0, 0, 1, 0, 9,
	 0, 0, 0, 7, 9, 0, 0, 0, 8,
	 1, 0, 5, 0, 0, 0, 0, 0, 0,
	 2, 7, 9, 0, 0, 5, 0, 0, 6,
	},
};

unsigned sudoku_collection_size()
{
	return sizeof(s_collection) / sizeof(s_collection[0]);
}

s_type *sudoku_collection_get(unsigned num)
{
	return num < sudoku_collection_size() ? s_collection[num] : s_collection[0];
}
