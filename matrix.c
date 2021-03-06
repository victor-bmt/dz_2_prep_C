#include "matrix.h"
#include <stdio.h>
#include <stdlib.h>

void free_matrix(Matrix *matrix) {
	if (matrix) {
		printf("Incorrect call of 'free_matrix()'\n");
		exit(1);
	
	int rows_n = get_rows(matrix);
	for (int i = 0; i < rows_n; ++i)
		free((matrix->p)[i]);

	free(matrix->p);
	}return;
}
#ifndef SPARSE_FILE
Matrix *create_matrix_from_file(FILE* file) {
	if (!file) {
		printf("Incorrect call of 'create_matrix_from_file()'\n");
		exit(1);
	}
	
	int rows_n = 0;
	int cols_n = 0;
	char ch = 0;

	if (fscanf(file, "%d%c", &rows_n, &ch) != 2) {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	if (ch != '\n') {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	if (fscanf(file, "%d%c", &cols_n, &ch) != 2) {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	if (ch != '\n') {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}
	Matrix *m = create_matrix(rows_n, cols_n);
	if (!m) {
		fclose(file);
		printf("Bad allocation\n");
		free_matrix(m);
		exit(1);
	}

	double buf = 0.0;

	for (int i = 0; i < rows_n; ++i) {
		for (int j = 0; j < cols_n - 1; ++j) {
			if (fscanf(file, "%lf%c", &buf, &ch) != 2) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

			if (ch != ' ') {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

			set_elem(m, i, j, buf);
		}
		
		// Для всех строк, кроме последней
		if (i != rows_n - 1) {
			if (fscanf(file, "%lf%c", &buf, &ch) != 2) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

			if (ch != '\n') {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}
		}

		else
			if (fscanf(file, "%lf", &buf) != 1) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

		set_elem(m, i, cols_n - 1, buf);
	}

	int dummy = 0;
	fscanf(file, "%d", &dummy);
	if (!feof(file)) {
		fclose(file);
		printf("Incorrect file!\n");
		free_matrix(m);
		exit(1);
	}

	return m;
}
#endif

#ifdef SPARSE_FILE
Matrix *create_matrix_from_file(FILE* file) {
	if(!file) {
		printf("Incorrect call of 'create_matrix_from_file()'\n");
		exit(1);
	}
	
	int rows_n = 0;
	int cols_n = 0;
	char ch = 0;

	if (fscanf(file, "%d%c", &rows_n, &ch) != 2) {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	if (ch != '\n') {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	if (fscanf(file, "%d%c", &cols_n, &ch) != 2) {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	if (ch != '\n') {
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}
	Matrix *m = create_matrix(rows_n, cols_n);
	if (!m) {
		fclose(file);
		printf("Bad allocation\n");
		free_matrix(m);
		exit(1);
	}

	int non_zero_n = 0;

	if (fscanf(file, "%d%c", &non_zero_n, &ch) != 2) {
		free_matrix(m);
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	if ((ch != '\n') || (non_zero_n > (rows_n * cols_n))) {
		free_matrix(m);
		fclose(file);
		printf("Incorrect file!\n");
		exit(1);
	}

	int i = 0;
	int j = 0;
	double buf = 0.0;
	char ch1 = 0;
	char ch2 = 0;
	char ch3 = 0;

	int count = 0;

	for (int k = 0; k < non_zero_n; ++k) {
		if (k != non_zero_n - 1) {
			if (fscanf(file, "%d%c%d%c%lf%c", &i, &ch1, &j, &ch2, &buf, &ch3) != 6) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

			if ((ch1 != ' ') || (ch2 != ' ') || (ch3 != '\n')) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

			// Если ячейка заполняется повторно, значит проблема в файле
			if (get_elem(m, i, j)) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

		}
		else {
			if (fscanf(file, "%d%c%d%c%lf", &i, &ch1, &j, &ch2, &buf) != 5) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}

			if ((ch1 != ' ') || (ch2 != ' ')) {
				fclose(file);
				printf("Incorrect file!\n");
				free_matrix(m);
				exit(1);
			}
	
		}

		set_elem(m, i, j, buf);
		++count;
	}

	int dummy = 0;
	fscanf(file, "%d", &dummy);
	if (!feof(file)) {
		fclose(file);
		printf("Incorrect file!\n");
		free_matrix(m);
		exit(1);
	}



	return m;
}
#endif


Matrix *create_matrix(int row, int col) {
	Matrix* m = malloc(sizeof(Matrix);
	m->rows_n = row;
	m.cols_n= col;
	m.p = NULL;

	m.p = calloc(row, sizeof(double *));
	if (!(m.p))
		return NULL;

	for (int i = 0; i < row; ++i) {
		(m.p)[i] = calloc(col, sizeof(double));
		if (!((m.p)[i]))
			return NULL;
	}
	
	return m;
}

void set_elem(Matrix* matrix, int row, int col, double val) {
	if ((row >= get_rows(matrix)) || (col >= get_cols(matrix)) || (!matrix)) {
		free_matrix(matrix);
		printf("Incorrect call of 'set_elem()'\n");
		exit(1);
	}
	
	(matrix->p)[row][col] = val;
       return;	
}

double get_elem(Matrix *matrix, int row, int col) {
	if ((row >= get_rows(matrix)) || (col >= get_cols(matrix)) || (!matrix)) {
		free_matrix(matrix);
		printf("Incorrect call of 'get_elem()'\n");
		exit(1);
	}

	return (matrix->p)[row][col];
}

int get_rows(Matrix *matrix) {
	if (!matrix) {
		printf("Incorrect call of 'get_rows()'\n");
		exit(1);
	}
	return matrix->rows_n;
}

int get_cols(Matrix *matrix) {
	if (!matrix) {
		printf("Incorrect call of 'get_rows()'\n");
		exit(1);
	}
	
	return matrix->cols_n;
}
