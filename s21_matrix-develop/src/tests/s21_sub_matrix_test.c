#include "test.h"

// вычитание матриц

START_TEST(sub_matrix_same_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_diff_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 4, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 2);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_null_A) {
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(NULL, &B, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_null_B) {
  matrix_t A = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &A);
  int code = s21_sub_matrix(&A, NULL, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
}
END_TEST

START_TEST(sub_matrix_null_result) {
  matrix_t A = {0};
  matrix_t B = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_sub_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_single_element) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_zero_rows) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(0, 3, &A);
  s21_create_matrix(0, 3, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_zero_columns) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 0, &A);
  s21_create_matrix(3, 0, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 1);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_matrix_large) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(1000, 1000, &A);
  s21_create_matrix(1000, 1000, &B);
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sub_matrix_negative_values) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  A.matrix[0][0] = -1;
  B.matrix[0][0] = -1;
  int code = s21_sub_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);
  ck_assert_double_eq(result.matrix[0][0], 0);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// Вычитание матриц

START_TEST(sub_test_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  R2.matrix[0][0] = -1;

  s21_sub_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sub_test_2) {
  matrix_t A, B, R, R2;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  s21_create_matrix(3, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;
  A.matrix[2][0] = 6.25;
  A.matrix[2][1] = 7.25;
  A.matrix[2][2] = 8.25;

  B.matrix[0][0] = 9.25;
  B.matrix[0][1] = 8.25;
  B.matrix[0][2] = 7.25;
  B.matrix[1][0] = 6.25;
  B.matrix[1][1] = 5.25;
  B.matrix[1][2] = 4.25;
  B.matrix[2][0] = 3.25;
  B.matrix[2][1] = 2.25;
  B.matrix[2][2] = 1.25;

  R2.matrix[0][0] = -9.0;
  R2.matrix[0][1] = -7.0;
  R2.matrix[0][2] = -5.0;
  R2.matrix[1][0] = -3.0;
  R2.matrix[1][1] = -1.0;
  R2.matrix[1][2] = 1.0;
  R2.matrix[2][0] = 3.0;
  R2.matrix[2][1] = 5.0;
  R2.matrix[2][2] = 7.0;

  s21_sub_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sub_test_NOTCORRECT_matrix) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  int res = s21_sub_matrix(&A, &B, &R);

  ck_assert_int_eq(res, ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sub_null) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sub_matrix(A, B, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(sub_matrix) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] - mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sub_matrix1) {
  matrix_t m = {0};
  const int rows = rand() % 100 + 1;
  const int cols = rand() % 100 + 1;
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  const int rows1 = rand() % 100 + 1;
  const int cols1 = rand() % 100 + 1;
  s21_create_matrix(rows1, cols1, &mtx);

  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX) + 1;
    }
  }
  for (int i = 0; i < rows1; i++) {
    for (int j = 0; j < cols1; j++) {
      mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
    }
  }

  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), ERROR_CALC);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t mtx = {0};
  s21_create_matrix(rows, cols, &mtx);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);

  matrix_t res = {0};
  ck_assert_int_eq(s21_sub_matrix(&m, &mtx, &res), NOTCORRECT);

  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_sub(void) {
  Suite *s = suite_create("\033[45ms21_sub_matrix\033[0m");
  TCase *tc = tcase_create("sqrt_tc");

  // Вычитание матриц
  tcase_add_test(tc, sub_matrix_same_size);
  tcase_add_test(tc, sub_matrix_diff_size);
  tcase_add_test(tc, sub_matrix_null_A);
  tcase_add_test(tc, sub_matrix_null_B);
  tcase_add_test(tc, sub_matrix_null_result);
  tcase_add_test(tc, sub_matrix_single_element);
  tcase_add_test(tc, sub_matrix_zero_rows);
  tcase_add_test(tc, sub_matrix_zero_columns);
  tcase_add_test(tc, sub_matrix_large);
  tcase_add_test(tc, sub_matrix_negative_values);

  tcase_add_test(tc, sub_test_1);
  tcase_add_test(tc, sub_test_2);
  tcase_add_test(tc, sub_test_NOTCORRECT_matrix);
  tcase_add_test(tc, sub_null);
  tcase_add_loop_test(tc, sub_matrix, 0, 20);
  tcase_add_loop_test(tc, sub_matrix1, 0, 20);
  tcase_add_loop_test(tc, sub_matrix2, 0, 20);

  suite_add_tcase(s, tc);
  return s;
}