#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  // переменная хранящая результат
  int res = 0;
  // проверяем можем ли создать матрицу
  if (result != NULL && rows > 0 && columns > 0) {
    // запоминаем количество строк и столбцов
    result->rows = rows;
    result->columns = columns;
    // выделяем память под матрицу и заполняем ее нулями
    result->matrix = calloc(rows, sizeof(int *));
    if (result->matrix != NULL) {
      for (int k = 0; k < rows && !res; ++k) {
        result->matrix[k] = calloc(columns, sizeof(int *));
        if (result->matrix[k] == NULL) res = 1;
      }
    } else {
      res = 1;
    }
  } else {
    res = 1;
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  for (int i = 0; i < A->rows; ++i) free(A->matrix[i]);
  free(A->matrix);
}

// SUCCESS 1
// FAILURE 0
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int flag = 1;
  // если кол-во строк и стобцов одинаковое - продолжаем
  if ((A != NULL) && (B != NULL) && (A->rows == B->rows) &&
      (A->columns == B->columns) && A->rows > 0) {
    int z = 0;
    for (int i = 0; i < A->rows && flag; ++i, z++) {
      for (int j = 0; j < A->columns && flag; ++j, z++) {
        if (!isinf(A->matrix[i][j]) || !isinf(B->matrix[i][j])) {
          double whole_A = trunc(A->matrix[i][j]);
          double whole_B = trunc(B->matrix[i][j]);
          double remainder_A = trunc((A->matrix[i][j] - whole_A) / 0.000001);
          double remainder_B = trunc((B->matrix[i][j] - whole_B) / 0.000001);
          if (whole_A != whole_B || remainder_A != remainder_B) flag = 0;
        }
      }
    }
  } else
    flag = 0;
  return flag;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if ((A != NULL && B != NULL && result != NULL)) {
    if (A->rows == B->rows && A->columns == B->columns && A->rows > 0 &&
        A->columns > 0 && !s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->columns; ++j)
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
    } else if (A->rows != B->rows || A->columns != B->columns)
      res = 2;
    else
      res = 1;
  } else
    res = 1;
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if ((A != NULL && B != NULL && result != NULL)) {
    if (A->rows == B->rows && A->columns == B->columns && A->rows > 0 &&
        A->columns > 0 && !s21_create_matrix(A->rows, A->columns, result)) {
      for (int i = 0; i < A->rows; ++i)
        for (int j = 0; j < A->columns; ++j)
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
    } else if (A->rows != B->rows || A->columns != B->columns)
      res = 2;
    else
      res = 1;
  } else
    res = 1;

  return res;
}
int s21_minor(matrix_t *A, matrix_t *result, int ignr_row, int ignr_col) {
  int minor_row = 0;

  int flag = 0;
  if (A->rows == 1 && A->columns == 1) return result->matrix[0][0] = 1;
  for (int i = 0; i < A->rows; i++) {
    if (i != ignr_row) {
      int minor_col = 0;
      for (int j = 0; j < A->columns; j++) {
        if (j != ignr_col) {
          result->matrix[minor_row][minor_col] = A->matrix[i][j];
          minor_col++;
        }
      }
      minor_row++;
    }
  }
  return flag;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (!check_correct(A) || result == NULL) return 1;
  if (A->columns != A->rows) return 2;
  matrix_t minor_tmp = {0};
  s21_create_matrix(A->rows, A->columns, result);
  if (A->rows == 1 && A->columns == 1)
    result->matrix[0][0] = 1;
  else {
    s21_create_matrix(A->rows - 1, A->columns - 1, &minor_tmp);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        double deter_res = 0;
        flag += s21_minor(A, &minor_tmp, i, j);
        flag += s21_determinant(&minor_tmp, &deter_res);
        result->matrix[i][j] = deter_res * powf(-1, (i + j));
      }
    }
    if (!flag) s21_remove_matrix(&minor_tmp);
  }
  return flag;
}

// int s21_cycle_calc_complements1(matrix_t *A, matrix_t *result) {
//   matrix_t temp_matr;
//   int index_rows = 0, index_column = 0, flag = 0;
//   double res_minor = 0.0;
//   flag += s21_create_matrix(A->rows - 1, A->columns - 1, &temp_matr);
//   flag += s21_create_matrix(A->rows, A->columns, result);
//   for (int i = 0; i < A->rows && flag == 0; i++) {
//     for (int j = 0; j < A->columns; j++) {
//       for (int l = 0; l < A->rows; l++) {
//         s21_cycle_calc_complements2(i, j, l, &index_rows, &index_column, A,
//                                     &temp_matr);
//       }
//       s21_determinant(&temp_matr, &res_minor);
//       result->matrix[i][j] = (int)pow(-1, i + j) * res_minor;
//     }
//   }
//   if (A->rows == 1 && A->columns == 1)
//     result->matrix[0][0] = A->matrix[0][0];
//   else if (flag == 0 && A->rows > 1 && A->columns > 1)
//     s21_remove_matrix(&temp_matr);
//   return flag;
// }

// void s21_cycle_calc_complements2(int i, int j, int l, int *index_rows,
//                                  int *index_column, matrix_t *A,
//                                  matrix_t *temp_matr) {
//   for (int k = 0; k < A->columns; k++) {
//     if (l != i && k != j) {
//       *index_rows %= A->rows - 1;
//       *index_column %= A->columns - 1;
//       temp_matr->matrix[*index_rows][*index_column] = A->matrix[l][k];
//       if (*index_column) (*index_rows)++;
//       (*index_column)++;
//     }
//   }
// }

// int s21_calc_complements(matrix_t *A, matrix_t *result) {
//   // Начало обработки ошибок
//   if (!check_correct(A)) return 1;
//   if (A->rows != A->columns) return 2;
//   // Конец обработки ошибок

//   int res = s21_cycle_calc_complements1(A, result);
//   return res;
// }

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if ((A != NULL && result != NULL) && (A->rows > 0 && A->columns > 0) &&
      !s21_create_matrix(A->rows, A->columns, result)) {
    for (int i = 0; i < A->rows; ++i)
      for (int j = 0; j < A->columns; ++j)
        result->matrix[i][j] = A->matrix[i][j] * number;
  } else
    res = 1;
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if ((A != NULL && B != NULL && result != NULL)) {
    if (A->columns == B->rows && A->rows > 0 && A->columns > 0 && B->rows > 0 &&
        B->columns > 0 && !s21_create_matrix(A->rows, B->columns, result)) {
      for (int i = 0; i < A->rows; i++)
        for (int j = 0; j < B->columns; j++)
          for (int k = 0; k < A->columns; k++)
            result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
    } else if (A->columns != B->rows || A->rows < 0 || A->columns < 0 ||
               B->rows < 0 || B->columns < 0)
      res = 2;
    else
      res = 1;
  } else
    res = 1;
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A != NULL && result != NULL && A->rows > 0 && A->columns > 0 &&
      !s21_create_matrix(A->columns, A->rows, result)) {
    for (int i = 0; i < A->columns; i++) {
      for (int j = 0; j < A->rows; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  } else
    res = 1;
  return res;
}

int s21_cycle_determinant(matrix_t *A, double *result) {
  double det = 0;
  int sign = 1;
  int flag = 0;
  for (int j = 0; j < A->columns && !flag; j++) {
    matrix_t subMatrix;
    flag = s21_create_matrix(A->rows - 1, A->columns - 1, &subMatrix);
    for (int m = 1; m < A->rows && !flag; m++) {
      for (int n = 0, p = 0; n < A->columns; n++) {
        if (n != j) {
          subMatrix.matrix[m - 1][p] = A->matrix[m][n];
          p++;
        }
      }
    }
    if (!flag) {
      double subResult;
      s21_determinant(&subMatrix, &subResult);
      det += sign * A->matrix[0][j] * subResult;
      sign = -sign;
      s21_remove_matrix(&subMatrix);
    }
  }
  *result = det;
  return flag;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (A != NULL && result != NULL && A->rows == A->columns && A->rows > 0) {
    if (A->rows == 1)
      *result = A->matrix[0][0];
    else if (A->rows == 2)
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    else {
      res = s21_cycle_determinant(A, result);
    }
  } else if (A != NULL && result != NULL && A->rows != A->columns)
    res = 2;
  else
    res = 1;
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int flag = 0;
  if (!check_correct(A) || result == NULL) return 1;
  double determ = 0;
  if (A->rows != A->columns) return 2;
  matrix_t complem_matrix = {0};
  matrix_t trans_complement = {0};
  flag = s21_determinant(A, &determ);
  if (determ == 0) {
    flag = 2;
  } else if (A->columns == 1) {
    flag = s21_create_matrix(A->rows, A->columns, result);
    if (!flag) result->matrix[0][0] = 1 / A->matrix[0][0];
  } else {
    flag += s21_calc_complements(A, &complem_matrix);
    flag += s21_transpose(&complem_matrix, &trans_complement);
    flag += s21_mult_number(&trans_complement, 1 / determ, result);
  }
  if (!flag) {
    s21_remove_matrix(&trans_complement);
    s21_remove_matrix(&complem_matrix);
  }
  return flag;
}

int check_correct(matrix_t *A) {
  return (A && A->matrix && A->rows > 0 && A->columns > 0);
}