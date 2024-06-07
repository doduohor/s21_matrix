# S21_Matrix

## Contents

1. [Introduction](#introduction)
2. [Chapter I](#chapter-i) \
    2.1. [Information](#information)
3. [Chapter II](#chapter-ii) \
    3.1. [Part 1](#part-1-реализация-функции-библиотеки-matrixh)

## Introduction

В данном проекте необходимо реализовать библиотеку для обработки числовых матриц на языке C. Матрицы используются для представления табличных значений, вычислительных задач и нейронных сетей. Этот проект поможет детально познакомиться с матрицами и закрепить структурный подход.

## Chapter I

## Information

### Матрица

Матрица - это набор чисел, расположенных в фиксированном количестве строк и столбцов.

```c
typedef struct matrix_struct {
    double** matrix;
    int rows;
    int columns;
} matrix_t;
```

### Операции над матрицами

Операции (кроме сравнения матриц) должны возвращать код результата:
- 0 - OK
- 1 - Некорректная матрица
- 2 - Ошибка вычисления

#### Создание матриц

```c
int s21_create_matrix(int rows, int columns, matrix_t *result);
```

#### Очистка матриц

```c
void s21_remove_matrix(matrix_t *A);
```

#### Сравнение матриц

```c
#define SUCCESS 1
#define FAILURE 0

int s21_eq_matrix(matrix_t *A, matrix_t *B);
```

#### Сложение и вычитание матриц

```c
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

#### Умножение матрицы на число и умножение двух матриц

```c
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
```

#### Транспонирование матрицы

```c
int s21_transpose(matrix_t *A, matrix_t *result);
```

#### Минор и матрица алгебраических дополнений

```c
int s21_calc_complements(matrix_t *A, matrix_t *result);
```

#### Определитель матрицы

```c
int s21_determinant(matrix_t *A, double *result);
```

#### Обратная матрица

```c
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
```

## Chapter II

## Part 1. Реализация функции библиотеки matrix.h

Реализовать основные действия с матрицами, описанные выше: create_matrix, remove_matrix, eq_matrix, sum_matrix, sub_matrix, mult_matrix, mult_number, transpose, determinant, calc_complements, inverse_matrix.

- Библиотека должна быть разработана на языке С стандарта C11 с использованием компилятора gcc.
- Код библиотеки должен находиться в папке src в ветке develop.
- Не использовать устаревшие конструкции языка и библиотечные функции.
- Код должен соответствовать Google Style.
- Оформить решение как статическую библиотеку (с заголовочным файлом s21_matrix.h).
- Библиотека должна быть разработана в соответствии с принципами структурного программирования.
- Перед каждой функцией использовать префикс s21_.
- Подготовить полное покрытие unit-тестами функций библиотеки с помощью библиотеки Check.
- Unit-тесты должны покрывать не менее 80% каждой функции.
- Предусмотреть Makefile для сборки библиотеки и тестов (с целями all, clean, test, s21_matrix.a, gcov_report).
- В цели gcov_report должен формироваться отчет gcov в виде HTML-страницы. Unit-тесты должны запускаться с флагами gcov.
- Матрица должна быть реализована в виде структуры, описанной выше.
- Проверяемая точность дробной части - максимум 6 знаков после запятой.
