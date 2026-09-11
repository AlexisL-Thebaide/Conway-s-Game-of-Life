#include <stdbool.h>
#include <stdio.h>
#include "matrix.h"

cell	empty_cell(void){
	cell	new;

	new.alive = false;
	new.status = 'n';
	return (new);
}

void	print_cell(cell *to_print){
	printf("%c", to_print->alive ? 'o' : ' ');
}

void	matrix_apply(matrix *m, void(*f)(matrix*, int, int)){
	int	x;
	int	y;

	x = 0;
	while (x < m->width){
		y = 0;
		while (y < m->height){
			f(m, x, y);
			y++;
		}
		x++;
	}
}

bool	cell_in_bounds(matrix *m, int x, int y){
	return (!(x < 0 || y < 0 || x >= m->width || y >= m->height));
}

int	neighbours_check(matrix *m, int x, int y, bool check){
	int	total;
	int	i;
	int	x_check;
	int	y_check;

	total = 0;
	i = 0;
	while (i < 9){
		x_check = x + ((i / 3) - 1);
		y_check = y + ((i % 3) - 1);
		if (cell_in_bounds(m, x_check, y_check) && !(x_check == x && y_check == y)){
			if (m->cells[y_check][x_check].alive == check){
				total++;
			}
		}
		i++;
	}
	return (total);
}

int	alive_neighbours(matrix *m, int x, int y){
	return (neighbours_check(m, x, y, true));
}

void	cell_birth(matrix *m, int x, int y){
	if (m->cells[y][x].alive == false && alive_neighbours(m, x, y) == 3)
		m->cells[y][x].status = 'b';
}

void	cell_kill(matrix *m, int x, int y){
	int	neighbours;

	neighbours = alive_neighbours(m, x, y);
	if (m->cells[y][x].alive == true && (neighbours < 2 || neighbours > 3))
		m->cells[y][x].status = 'd';
}

void	cell_update(matrix *m, int x, int y){
	if (m->cells[y][x].status == 'b'){
		m->cells[y][x].alive = true;
		m->cells[y][x].status = 'n';
	}
	if (m->cells[y][x].status == 'd'){
		m->cells[y][x].alive = false;
		m->cells[y][x].status = 'n';
	}
}

void	game_of_life_step(matrix *m){
	matrix_apply(m, cell_birth);
	matrix_apply(m, cell_kill);
	matrix_apply(m, cell_update);
}
