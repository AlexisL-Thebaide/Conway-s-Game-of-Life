#ifndef MATRIX_H
#define MATRIX_H

typedef struct{
	bool	alive;
	char	status;
} cell;

typedef struct{
	int	height;
	int	width;
	cell	**cells;
} matrix;
#endif
