#ifndef S21_MATRIX
#define S21_MATRIX
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0  // Код успешного выполнения
#define ERROR_CALC 2  // Код ошибки при выполнении вычислений
#define NOTCORRECT 1  // Код ошибки для некорректных данных
#define SUCCESS 1  // Код успешного выполнения (в контексте логических операций)
#define FAILURE \
  0  // Код неуспешного выполнения (в контексте логических операций)

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

// Все операции (кроме сравнения матриц) должны возвращать результирующий код:
// 0 - OK
// 1 - Ошибка, некорректная матрица
// 2 - Ошибка вычисления (несовпадающие размеры матриц; матрица, для которой
// нельзя провести вычисления и т.д.)

// Создание матриц
int s21_create_matrix(int rows, int columns, matrix_t *result);

// Очистка матриц
void s21_remove_matrix(matrix_t *A);

// Сравненение матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);

// Сложение и вычитание матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Умножение матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
// Умножение двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);

// Транспонирование матрицы
int s21_transpose(matrix_t *A, matrix_t *result);

// Минор матрицы
int s21_calc_complements(matrix_t *A, matrix_t *result);

int s21_cycle_calc_complements1(matrix_t *A, matrix_t *result);
void s21_cycle_calc_complements2(int i, int j, int l, int *index_rows,
                                 int *index_column, matrix_t *A,
                                 matrix_t *temp_matr);

// Определитель матрицы
int s21_determinant(matrix_t *A, double *result);

// Обратная матрица
int s21_inverse_matrix(matrix_t *A, matrix_t *result);

int check_correct(matrix_t *A);

#endif