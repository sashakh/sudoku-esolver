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

#ifndef __SUDOKU_H__
#define __SUDOKU_H__

#define N 3			/* base dimension */
#define D (N * N)		/* dimension */

typedef unsigned s_type;

struct sudoku {
	unsigned rows[D], cols[D], sqrs[D];
	s_type *s;
	s_type new[D * D];
	s_type orig[D * D];
	long nsec;
};

void sudoku_printf(struct sudoku *s, const char *fmt, ...);

void sudoku_init(struct sudoku *s, s_type n[]);
int sudoku_solver(struct sudoku *s);
void sudoku_multi_solver(struct sudoku s[], unsigned size);
void sudoku_multi_solver_each(struct sudoku s[], unsigned size, unsigned print);

unsigned sudoku_collection_size();
s_type *sudoku_collection_get(unsigned num);

void solver_init(void);

#endif /* __SUDOKU_H__ */
