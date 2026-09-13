#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "includes.h"

matrix	*new_matrix(int h, int w)
{
	matrix	*new;
	int	i;
	int	j;
	
	if (h <= 0 || w <= 0)
		return (0);
	new = malloc(sizeof(matrix));
	if (new == NULL)
		return (NULL);
	new->height = h;
	new->width = w;
	new->cells = malloc(sizeof(cell*) * h);
	if (new->cells == NULL){
		free(new);
		return (NULL);
	}
	i = 0;
	while (i < h){
		new->cells[i] = malloc(sizeof(cell) * w);
		if (new->cells[i] == NULL){
			while (i > 0){
				i--;
				free(new->cells[i]);
			}
			free(new->cells);
			free(new);
			return (NULL);
		}
		j = 0;
		while (j < w){
			new->cells[i][j] = empty_cell();
			j++;
		}
		i++;
	}
	return (new);
}

void	print_matrix(matrix *to_print){
	int	x;
	int	y;

	if (to_print == NULL)
		return;
	y = 0;
	while (y < to_print->height){
		x = 0;
		while (x <  to_print->width){
			print_cell(&to_print->cells[y][x]);
			x++;
		}
		printf("\n");
		y++;
	}
}

void	free_matrix(matrix *to_free){
	int	i;
	int	j;

	if (to_free == NULL)
		return;
	i = 0;
	while (i < to_free->height){
		free(to_free->cells[i]);
		i++;
	}
	free(to_free->cells);
	free(to_free);
}

void	step(matrix *m){
	game_of_life_step(m);
}

