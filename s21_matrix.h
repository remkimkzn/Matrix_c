#ifndef S21_MATRIX_H
#define S21_MATRIX_H

#define SUCCESS 1
#define FAILURE 0
#define EPSILON 1e-6

#define OK 0
#define INCORRECT_MATRIX 1
#define CALCULATION_ERROR 2
#define MEMORY_FAIL 3

typedef struct {
  double **matrix;
  int rows;
  int columns;

} matrix_t;

int s21_create_matrix(const int rows, const int columns, matrix_t *result);

void s21_remove_matrix(matrix_t *A);

int s21_eq_matrix(const matrix_t *A, const matrix_t *B);

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_sub_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result);

int s21_mult_number(const matrix_t *A, const double number, matrix_t *result);

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

int s21_transpose(const matrix_t *A, matrix_t *result);

int s21_calc_complements(const matrix_t *A, matrix_t *result);

int s21_determinant(matrix_t *A, double *result);

int s21_inverse_matrix(matrix_t *A, matrix_t *result);

#endif
