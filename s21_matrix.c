#include "s21_matrix.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int s21_create_matrix(const int rows, const int columns, matrix_t *result) {
  if (result == NULL || rows <= 0 || columns <= 0) {
    return INCORRECT_MATRIX;
  }

  result->rows = rows;
  result->columns = columns;

  result->matrix = (double **)calloc(rows, sizeof(double *));
  if (result->matrix == NULL) {
    return MEMORY_FAIL;
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)calloc(columns, sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      result->matrix = NULL;
      return MEMORY_FAIL;
    }
    // for (int j = 0; j < columns; j++) {
    //   result->matrix[i][j] = 0.0;
    // }
  }

  return OK;
}

void s21_remove_matrix(matrix_t *A) {
  if (A == NULL || A->matrix == NULL) {
    return;
  }

  if (A->rows <= 0 || A->columns == 0) {
    return;
  }

  for (int i = 0; i < A->rows; i++) {
    free(A->matrix[i]);
  }

  free(A->matrix);

  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(const matrix_t *A, const matrix_t *B) {
  if (A == NULL || B == NULL) {
    return FAILURE;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return FAILURE;  //
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPSILON) {
        return FAILURE;
      }
    }
  }
  return SUCCESS;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows == 0 || B->rows == 0) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }

  result->rows = A->rows;
  result->columns = A->columns;
  result->matrix = (double **)malloc(result->rows * sizeof(double *));
  for (int i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    }
  }
  // s21_remove_matrix(result);
  return OK;
}

int s21_sub_matrix(const matrix_t *A, const matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows == 0 || B->rows == 0) {
    return INCORRECT_MATRIX;
  }

  if (A->rows != B->rows || A->columns != B->columns) {
    return CALCULATION_ERROR;
  }

  result->rows = A->rows;
  result->columns = A->columns;
  result->matrix = (double **)malloc(result->rows * sizeof(double *));
  for (int i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    }
  }
  return OK;
}

int s21_mult_number(const matrix_t *A, double number, matrix_t *result) {
  if (A == NULL || result == NULL) {
    return INCORRECT_MATRIX;
  }

  result->rows = A->rows;
  result->columns = A->columns;
  result->matrix = (double **)malloc(result->rows * sizeof(double *));
  for (int i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[i][j] = A->matrix[i][j] * number;
    }
  }
  return OK;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  if (A == NULL || B == NULL || result == NULL) {
    return INCORRECT_MATRIX;
  }

  if (A->rows == 0 || B->columns == 0 || A->columns != B->rows) {
    return CALCULATION_ERROR;
  }

  result->rows = A->rows;
  result->columns = B->columns;
  result->matrix = (double **)malloc(result->rows * sizeof(double *));
  if (result->matrix == NULL) {
    return MEMORY_FAIL;
  }

  for (int i = 0; i < result->rows; i++) {
    result->matrix[i] = (double *)malloc(result->columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return MEMORY_FAIL;
    }
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < B->columns; j++) {
      result->matrix[i][j] = 0;
      for (int k = 0; k < A->columns; k++) {
        result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
      }
    }
  }
  return OK;
}

int s21_transpose(const matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return INCORRECT_MATRIX;
  }

  if (s21_create_matrix(A->columns, A->rows, result) != OK) {
    return INCORRECT_MATRIX;
  }

  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      result->matrix[j][i] = A->matrix[i][j];
    }
  }
  return OK;
}

int s21_calc_complements(const matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL || result == NULL) {
    return INCORRECT_MATRIX;
  }

  int rows = A->rows;
  int columns = A->columns;

  if (rows != columns) {
    return CALCULATION_ERROR;
  }

  result->rows = rows;
  result->columns = columns;
  result->matrix = (double **)malloc(rows * sizeof(double *));
  if (result->matrix == NULL) {
    return MEMORY_FAIL;
  }

  for (int i = 0; i < rows; i++) {
    result->matrix[i] = (double *)malloc(columns * sizeof(double));
    if (result->matrix[i] == NULL) {
      for (int j = 0; j < i; j++) {
        free(result->matrix[j]);
      }
      free(result->matrix);
      return MEMORY_FAIL;
    }
  }

  if (rows == 1 && columns == 1) {
    result->matrix[0][0] = 1.0;
    return OK;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      matrix_t minor;
      if (s21_create_matrix(rows - 1, columns - 1, &minor) != OK) {
        s21_remove_matrix(result);
        return INCORRECT_MATRIX;
      }

      int current_row_minor = 0;
      for (int current_row = 0; current_row < rows; current_row++) {
        if (current_row == i) {
          continue;
        }
        int current_col_minor = 0;
        for (int current_col = 0; current_col < columns; current_col++) {
          if (current_col == j) {
            continue;
          }
          minor.matrix[current_row_minor][current_col_minor] =
              A->matrix[current_row][current_col];
          current_col_minor++;
        }
        current_row_minor++;
      }

      double minor_determinant = 0;
      if (s21_determinant(&minor, &minor_determinant) != OK) {
        s21_remove_matrix(&minor);
        s21_remove_matrix(result);
        return CALCULATION_ERROR;
      }

      double sign = ((i + j) % 2 == 0) ? 1.0 : -1.0;
      result->matrix[i][j] = sign * minor_determinant;
      s21_remove_matrix(&minor);
    }
  }

  return OK;
}

int s21_determinant(matrix_t *A, double *result) {
  if (A == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }
  int rows = A->rows;
  int columns = A->columns;

  if (rows != columns) {
    return CALCULATION_ERROR;
  }

  if (rows == 1) {
    *result = A->matrix[0][0];
    return OK;
  }

  double det = 0;
  int sign = 1;

  for (int i = 0; i < columns; i++) {
    matrix_t minor;
    if (s21_create_matrix(rows - 1, columns - 1, &minor) != OK) {
      return INCORRECT_MATRIX;
    }

    int current_row_minor = 0;
    // int current_sign = (i % 2 == 0) ? 1 : -1;
    for (int current_row = 1; current_row < rows; current_row++) {
      int current_col_minor = 0;
      for (int current_col = 0; current_col < columns; current_col++) {
        if (current_col == i) {
          continue;
        }
        minor.matrix[current_row_minor][current_col_minor] =
            A->matrix[current_row][current_col];
        current_col_minor++;
      }
      current_row_minor++;
    }

    double minor_determinant = 0;
    if (s21_determinant(&minor, &minor_determinant) != OK) {
      s21_remove_matrix(&minor);
      return CALCULATION_ERROR;
    }

    det += sign * A->matrix[0][i] * minor_determinant;
    sign = -sign;
    s21_remove_matrix(&minor);
  }

  *result = det;
  return OK;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  if (A == NULL || A->matrix == NULL) {
    return INCORRECT_MATRIX;
  }

  int rows = A->rows;
  int columns = A->columns;

  if (rows != columns) {
    return CALCULATION_ERROR;
  }

  double determinant = 0;
  if (s21_determinant(A, &determinant) != OK || determinant == 0) {
    return CALCULATION_ERROR;
  }

  matrix_t comatrix;
  if (s21_calc_complements(A, &comatrix) != OK) {
    return INCORRECT_MATRIX;
  }

  matrix_t transposed_comatrix;
  if (s21_transpose(&comatrix, &transposed_comatrix) != OK) {
    s21_remove_matrix(&comatrix);
    return FAILURE;
  }

  matrix_t temp_result;
  if (s21_create_matrix(rows, columns, &temp_result) != OK) {
    s21_remove_matrix(&comatrix);
    s21_remove_matrix(&transposed_comatrix);
    return MEMORY_FAIL;
  }

  if (s21_create_matrix(rows, columns, result) != OK) {
    s21_remove_matrix(&temp_result);
    s21_remove_matrix(&comatrix);
    s21_remove_matrix(&transposed_comatrix);
    return MEMORY_FAIL;
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      temp_result.matrix[i][j] = transposed_comatrix.matrix[i][j] / determinant;
    }
  }

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < columns; j++) {
      result->matrix[i][j] = temp_result.matrix[i][j];
    }
  }

  s21_remove_matrix(&temp_result);
  s21_remove_matrix(&comatrix);
  s21_remove_matrix(&transposed_comatrix);

  return OK;
}
