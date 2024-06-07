#include "test.h"

// Умножение матрицы на число
START_TEST(test_mult_float) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1.0;
  A.matrix[0][1] = 1.0;
  A.matrix[1][0] = 1.0;
  A.matrix[1][1] = 1.0;
  double number = 0.5;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.5;
  B.matrix[0][1] = 0.5;
  B.matrix[1][0] = 0.5;
  B.matrix[1][1] = 0.5;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_large) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 1000000.0;
  A.matrix[0][1] = 1000000.0;
  A.matrix[1][0] = 1000000.0;
  A.matrix[1][1] = 1000000.0;
  double number = 1000000.0;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 1000000000000.0;
  B.matrix[0][1] = 1000000000000.0;
  B.matrix[1][0] = 1000000000000.0;
  B.matrix[1][1] = 1000000000000.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_small) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.0000001;
  A.matrix[0][1] = 0.0000001;
  A.matrix[1][0] = 0.0000001;
  A.matrix[1][1] = 0.0000001;
  double number = 0.0000001;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.00000000000001;
  B.matrix[0][1] = 0.00000000000001;
  B.matrix[1][0] = 0.00000000000001;
  B.matrix[1][1] = 0.00000000000001;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_random) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 3.2;
  A.matrix[0][1] = 4.5;
  A.matrix[1][0] = 6.7;
  A.matrix[1][1] = 8.9;
  double number = 2.0;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 6.4;
  B.matrix[0][1] = 9.0;
  B.matrix[1][0] = 13.4;
  B.matrix[1][1] = 17.8;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(test_mult_zero_result) {
  matrix_t A, B, result;
  s21_create_matrix(2, 2, &A);
  A.matrix[0][0] = 0.0;
  A.matrix[0][1] = 0.0;
  A.matrix[1][0] = 0.0;
  A.matrix[1][1] = 0.0;
  double number = 2.0;
  s21_create_matrix(2, 2, &B);
  B.matrix[0][0] = 0.0;
  B.matrix[0][1] = 0.0;
  B.matrix[1][0] = 0.0;
  B.matrix[1][1] = 0.0;
  ck_assert_int_eq(s21_mult_number(&A, number, &result), 0);
  ck_assert(s21_eq_matrix(&B, &result));
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(mult_number_test_1) {
  matrix_t A, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;

  R2.matrix[0][0] = -5;

  s21_mult_number(&A, -4, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_number_test_2) {
  matrix_t A, R, R2;
  s21_create_matrix(3, 3, &A);
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

  R2.matrix[0][0] = 1;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 9;
  R2.matrix[1][0] = 13;
  R2.matrix[1][1] = 17;
  R2.matrix[1][2] = 21;
  R2.matrix[2][0] = 25;
  R2.matrix[2][1] = 29;
  R2.matrix[2][2] = 33;

  s21_mult_number(&A, 4, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(mult_number_test_3) {
  matrix_t A, R, R2;
  s21_create_matrix(2, 3, &A);
  s21_create_matrix(2, 3, &R2);

  A.matrix[0][0] = 0.25;
  A.matrix[0][1] = 1.25;
  A.matrix[0][2] = 2.25;
  A.matrix[1][0] = 3.25;
  A.matrix[1][1] = 4.25;
  A.matrix[1][2] = 5.25;

  R2.matrix[0][0] = 1;
  R2.matrix[0][1] = 5;
  R2.matrix[0][2] = 9;
  R2.matrix[1][0] = 13;
  R2.matrix[1][1] = 17;
  R2.matrix[1][2] = 21;

  s21_mult_number(&A, 4, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(null_mult_num) {
  matrix_t *B = NULL;
  double num = 0;
  matrix_t *R = NULL;
  int res = s21_mult_number(B, num, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(mult_number_matrix) {
  int rows = rand() % 10 + 1;
  int cols = rand() % 10 + 1;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  double mult_number = get_rand(-10e5, 10e5);
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
      check.matrix[i][j] = m.matrix[i][j] * mult_number;
    }
  }
  matrix_t res = {0};

  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(mult_number_matrix2) {
  int rows = rand() % 100 + 1;
  int cols = rand() % 100 + 1;
  rows = -rows;
  cols = -cols;
  matrix_t m = {0};
  s21_create_matrix(rows, cols, &m);
  matrix_t check = {0};
  s21_create_matrix(rows, cols, &check);
  double mult_number = get_rand(-10e5, 10e5);

  matrix_t res = {0};
  ck_assert_int_eq(s21_mult_number(&m, mult_number, &res), NOTCORRECT);

  s21_remove_matrix(&m);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_mult_num(void) {
  Suite *s = suite_create("\033[45ms21_mult_number\033[0m");
  TCase *tc = tcase_create("sqrt_tc");

  // // Умножение матрицы на число
  tcase_add_test(tc, test_mult_float);
  tcase_add_test(tc, test_mult_large);
  tcase_add_test(tc, test_mult_small);
  tcase_add_test(tc, test_mult_random);
  tcase_add_test(tc, test_mult_zero_result);
  tcase_add_test(tc, mult_number_test_1);
  tcase_add_test(tc, mult_number_test_2);
  tcase_add_test(tc, mult_number_test_3);
  tcase_add_test(tc, null_mult_num);

  tcase_add_loop_test(tc, mult_number_matrix, 0, 20);
  tcase_add_loop_test(tc, mult_number_matrix2, 0, 20);

  suite_add_tcase(s, tc);
  return s;
}