#include <stdio.h>

#define SPARSE_FILE
//#undef SPARSE_FILE

typedef struct Matrix {
	int rows_n;
	int cols_n;
	double **p;
} Matrix;

// Функция освобождения дин. памяти, выделенной под матрицу
void free_matrix(Matrix *matrix);
// Создает матрицу и заполняет ее
Matrix *create_matrix_from_file(FILE* file);
// Выделяет дин. память под матрицу
Matrix *create_matrix(int row, int col);
// Устанавливает в элемент матрицы в строке [row] столбце [col] значение val
void set_elem(Matrix* matrix, int row, int col, double val);
// Возвращает элемент матрицы из строки [row] столбца [col]
double get_elem(Matrix *matrix, int row, int col);
// Возвращает количество строк матрицы
int get_rows(Matrix *matrix);
// Возвращает количество столбцов матрицы
int get_cols(Matrix *matrix);
