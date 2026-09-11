#ifndef INCLUDES_H
#define INCLUDES_H

//conway.h
void	game_of_life_step(matrix *m);
cell	empty_cell(void);
void	print_cell(cell *to_print);
//matrix.h
matrix	*new_matrix(int h, int w);
void	print_matrix(matrix *to_print);
void	free_matrix(matrix *to_free);
void	step(matrix *m);
#endif
