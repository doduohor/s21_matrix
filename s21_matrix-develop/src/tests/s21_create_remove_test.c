#include "test.h"

// Создание и удаление матрицы

START_TEST(create_matrix_positive) {
  matrix_t m = {0};
  int code = s21_create_matrix(3, 3, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_single_element) {
  matrix_t m = {0};
  int code = s21_create_matrix(1, 1, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_rectangle) {
  matrix_t m = {0};
  int code = s21_create_matrix(2, 3, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_large) {
  matrix_t m = {0};
  int code = s21_create_matrix(1000, 1000, &m);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(create_matrix_zero_rows) {
  matrix_t m = {0};
  int code = s21_create_matrix(0, 3, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_zero_cols) {
  matrix_t m = {0};
  int code = s21_create_matrix(3, 0, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_negative_rows) {
  matrix_t m = {0};
  int code = s21_create_matrix(-3, 3, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_negative_cols) {
  matrix_t m = {0};
  int code = s21_create_matrix(3, -3, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_zero_size) {
  matrix_t m = {0};
  int code = s21_create_matrix(0, 0, &m);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix_null_pointer) {
  int code = s21_create_matrix(3, 3, NULL);
  ck_assert_int_eq(code, 1);
}
END_TEST

START_TEST(create_matrix) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  int code = s21_create_matrix(rows, cols, &m);
  if (code == 0) {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < cols; ++j) {
        m.matrix[i][j] = 0;
        ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
      }
    }
    ck_assert_int_eq(m.rows, rows);
    ck_assert_int_eq(m.columns, cols);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(create_normal) {
  int rows = 10;
  int columns = 10;
  matrix_t matrix = {0};
  int status1 = s21_create_matrix(rows, columns, &matrix);

  if (matrix.matrix) {
    for (int i = 0; i < rows; ++i) {
      for (int j = 0; j < columns; ++j) {
        ck_assert(fabs(matrix.matrix[i][j]) < 1e-7);
      }
    }
    ck_assert_int_eq(matrix.rows, rows);
    ck_assert_int_eq(matrix.columns, columns);
    ck_assert_int_eq(status1, OK);
  } else {
    ck_assert_int_eq(status1, ERROR_CALC);
  }

  if (status1 == OK) s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_no_rows) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), NOTCORRECT);
}
END_TEST

START_TEST(create_no_cols) {
  const int rows = 10;
  const int cols = 0;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), NOTCORRECT);
}
END_TEST

START_TEST(create_NOTCORRECT) {
  int rows = -10;
  int columns = 10;
  matrix_t matrix = {0};
  int status = s21_create_matrix(rows, columns, &matrix);

  ck_assert_int_eq(status, NOTCORRECT);

  if (status == OK) s21_remove_matrix(&matrix);
}
END_TEST

START_TEST(create_1) {
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  if (m.matrix) {
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        m.matrix[i][j] = 0;
        ck_assert_ldouble_eq_tol(0, m.matrix[i][j], 1e-07);
      }
    }
    ck_assert_int_eq(m.rows, rows);
    ck_assert_int_eq(m.columns, cols);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(create_2) {
  const int rows = 0;
  const int cols = 10;
  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), NOTCORRECT);
}
END_TEST

START_TEST(create_3) {
  const int rows = 10;
  const int cols = 0;

  matrix_t m = {0};
  ck_assert_int_eq(s21_create_matrix(rows, cols, &m), NOTCORRECT);
}
END_TEST

Suite *suite_cr_rm(void) {
  Suite *s = suite_create("\033[45ms21create_and_remove\033[0m");
  TCase *tc = tcase_create("sqrt_tc");

  // Создание и удаление матрицы
  tcase_add_test(tc, create_matrix_positive);
  tcase_add_test(tc, create_matrix_single_element);
  tcase_add_test(tc, create_matrix_rectangle);
  tcase_add_test(tc, create_matrix_large);
  tcase_add_test(tc, create_matrix_zero_rows);
  tcase_add_test(tc, create_matrix_zero_cols);
  tcase_add_test(tc, create_matrix_negative_rows);
  tcase_add_test(tc, create_matrix_negative_cols);
  tcase_add_test(tc, create_matrix_zero_size);
  tcase_add_test(tc, create_matrix_null_pointer);

  tcase_add_test(tc, create_matrix);
  tcase_add_test(tc, create_normal);
  tcase_add_test(tc, create_no_rows);
  tcase_add_test(tc, create_no_cols);
  tcase_add_test(tc, create_NOTCORRECT);

  tcase_add_test(tc, create_1);
  tcase_add_test(tc, create_2);
  tcase_add_test(tc, create_3);

  suite_add_tcase(s, tc);
  return s;
}