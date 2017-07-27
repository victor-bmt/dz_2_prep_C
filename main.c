#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Incorrect input! The correct input is './a.out (file_name)'.\n");
		return 0;
	}

	FILE *fp = NULL;
	fp = fopen(argv[1], "r");
	if (!fp) {
		printf("File '%s' is inaccessible!\n", argv[1]);
		return 0;
	}

	Matrix *p_matrix = create_matrix_from_file(fp);
	fclose(fp);

	int rows_n = get_rows(p_matrix);
	int cols_n = get_cols(p_matrix);

	for (int i = 0; i < rows_n; ++i) {
		printf("\n");
		for (int j = 0; j < cols_n; ++j)
			printf("\t%.3lf", get_elem(p_matrix, i, j));
	}

	printf("\n\n");

	// Ищем L-норму
	double max = 0.0;
	for (int i = 0; i < rows_n; ++i)
		max += get_elem(p_matrix, i, 0);

	for (int j = 1; j < cols_n; ++j) {
		double buf = 0.0;
		for (int i = 0; i < rows_n; ++i)
			buf += get_elem(p_matrix, i, j);
		if (buf > max)
			max = buf;
	}

	printf("\tL-norm of this matrix : %.3lf\n\n", max);

	free_matrix(p_matrix);
	return 0;
}
