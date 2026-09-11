#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "matrix.h"
#include "includes.h"

typedef enum{
	NO_ERROR,
	MALLOC,
	READ
} error;

void	matrix_size_from_file(FILE *fp, int *longest_line, int *lines){
	int	ch;
	int	current_line;

	*longest_line = 0;
	*lines = 0;
	current_line = 0;
	while ((ch = fgetc(fp)) != EOF){
		if (ch == '\n'){
			(*lines)++;
			if (current_line > *longest_line)
				*longest_line = current_line;
			current_line = 0;
		}
		else
			current_line++;
	}
	if (*longest_line == 0)
		*longest_line = 1;
	if (*lines == 0)
		*lines = 1;
	rewind(fp);
}

void	fill_from_file(matrix *m, FILE *fp){
	int	ch;
	int	x;
	int	y;

	x = 0;
	y = 0;
	while ((ch = fgetc(fp)) != EOF){
		if (ch == '\n'){
			y++;
			x = 0;
		}
		else{
			if (!isspace(ch))
				m->cells[y][x].alive = true;
			x++;
		}
	}
}

error	parse_file(matrix **m, char *filename){
	FILE	*fp;
	int	longest_line;
	int	lines;

	fp = fopen(filename, "r");
	if (fp){
		matrix_size_from_file(fp, &longest_line, &lines);
		*m = new_matrix(lines, longest_line);
		if (*m != NULL)
			fill_from_file(*m, fp);
		else{
			fclose(fp);
			return (MALLOC);
		}
	}
	else
		return (READ);
	fclose(fp);
	return (NO_ERROR);
}

error	initial_fill(matrix **m, int argc, char *argv[]){
	error	msg;

	if (argc == 1){
		*m = new_matrix(19, 19);
		if (*m == NULL)
			return (MALLOC);
		(*m)->cells[4][1].alive = true;
		(*m)->cells[4][2].alive = true;
		(*m)->cells[4][3].alive = true;
		(*m)->cells[3][3].alive = true;
		(*m)->cells[2][2].alive = true;
		(*m)->cells[15][15].alive = true;
		(*m)->cells[15][14].alive = true;
		(*m)->cells[15][17].alive = true;
		(*m)->cells[14][16].alive = true;
		(*m)->cells[15][15].alive = true;
		(*m)->cells[15][14].alive = true;
		(*m)->cells[15][17].alive = true;
		(*m)->cells[14][16].alive = true;
		(*m)->cells[16][16].alive = true;
		printf("example matrix because main wasn't given a command line argument\n");
	}
	else{
		msg = parse_file(m, argv[1]);
		if (msg){
			printf("parsing from file %s failed\n", argv[1]);
			return(msg);
		}
		else
			printf("parsed from file %s\n", argv[1]);
	}
	return (NO_ERROR);
}

char	get_input(){
	char	buffer[200];

	fgets(buffer, sizeof(buffer), stdin);
	return (*buffer);
}

int	main(int argc, char *argv[]){
	matrix	*m;
	error	msg;
	int	i;
	char	input;
		
	msg = initial_fill(&m, argc, argv);//send adress of [ptr to matrix] so that malloc can properly modify [ptr to matrix]
	if (!msg){
		i = 0;
		input = 0;
		while (input != 'q'){
			printf("step %d\n", i);
			print_matrix(m);
			step(m);
			i++;
			printf("write \'q\' to quit\n");
			input = get_input();
		}
		free_matrix(m);
		m = NULL;
	}
	else if (msg == MALLOC)
		printf("malloc error\n");
	else if (msg == READ)
		printf("reading error\n");
	return (msg);
}
