#include "test.h"

START_TEST(sum_matrix_same_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);
  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_different_size) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(2, 2, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 2);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_null_A) {
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &B);
  int code = s21_sum_matrix(NULL, &B, &result);
  ck_assert_int_eq(code, 1);

  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_null_B) {
  matrix_t A = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);

  int code = s21_sum_matrix(&A, NULL, &result);
  ck_assert_int_eq(code, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_null_result) {
  matrix_t A = {0};
  matrix_t B = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  int code = s21_sum_matrix(&A, &B, NULL);
  ck_assert_int_eq(code, 1);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
}
END_TEST

START_TEST(sum_matrix_large) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(1000, 1000, &A);
  s21_create_matrix(1000, 1000, &B);

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_negative_value) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Присваиваю некоторым элементам отрицательные значения
  A.matrix[0][0] = -1.0;
  B.matrix[0][0] = -1.0;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_zero_value) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Присваиваю всем элементам отрицательные значения
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 0.0;
      B.matrix[i][j] = 0.0;
    }
  }

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_positive_value) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &B);

  // Присваиваю всем элементам положительные значения
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      A.matrix[i][j] = 1.0;
      B.matrix[i][j] = 1.0;
    }
  }

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

START_TEST(sum_matrix_single_element) {
  matrix_t A = {0};
  matrix_t B = {0};
  matrix_t result = {0};

  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);

  A.matrix[0][0] = 1.0;
  B.matrix[0][0] = 1.0;

  int code = s21_sum_matrix(&A, &B, &result);
  ck_assert_int_eq(code, 0);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&result);
}
END_TEST

// START_TEST(sum_matrix)
// {
//   const int rows = rand() % 100 + 1;
//   const int cols = rand() % 100 + 1;
//   matrix_t m = {0};
//   s21_create_matrix(rows, cols, &m);
//   matrix_t mtx = {0};
//   s21_create_matrix(rows, cols, &mtx);
//   matrix_t check = {0};
//   s21_create_matrix(rows, cols, &check);

//   for (int i = 0; i < rows; ++i)
//   {
//     for (int j = 0; j < cols; ++j)
//     {
//       m.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
//       mtx.matrix[i][j] = get_rand(DBL_MIN, DBL_MAX);
//       check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
//     }
//   }
//   matrix_t res = {0};

//   ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
//   ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
//   s21_remove_matrix(&m);
//   s21_remove_matrix(&mtx);
//   s21_remove_matrix(&res);
//   s21_remove_matrix(&check);
// }
// END_TEST

START_TEST(sum_matrix_1) {
  matrix_t A, B, R, R2;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(1, 1, &B);
  s21_create_matrix(1, 1, &R2);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  R2.matrix[0][0] = 3.5;

  s21_sum_matrix(&A, &B, &R);

  ck_assert(fabs(R.matrix[0][0] - R2.matrix[0][0]) < 1e-7);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sum_matrix_2) {
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

  B.matrix[0][0] = 9.65;
  B.matrix[0][1] = 8.65;
  B.matrix[0][2] = 7.65;
  B.matrix[1][0] = 6.65;
  B.matrix[1][1] = 5.65;
  B.matrix[1][2] = 4.65;
  B.matrix[2][0] = 3.65;
  B.matrix[2][1] = 2.65;
  B.matrix[2][2] = 1.65;

  R2.matrix[0][0] = 9.9;
  R2.matrix[0][1] = 9.9;
  R2.matrix[0][2] = 9.9;
  R2.matrix[1][0] = 9.9;
  R2.matrix[1][1] = 9.9;
  R2.matrix[1][2] = 9.9;
  R2.matrix[2][0] = 9.9;
  R2.matrix[2][1] = 9.9;
  R2.matrix[2][2] = 9.9;

  s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(s21_eq_matrix(&R, &R2), SUCCESS);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&R);
  s21_remove_matrix(&R2);
}
END_TEST

START_TEST(sum_test_NOTCORRECT_matrix) {
  matrix_t A, B, R;
  s21_create_matrix(1, 1, &A);
  s21_create_matrix(2, 1, &B);

  A.matrix[0][0] = 1.25;
  B.matrix[0][0] = 2.25;

  int res = s21_sum_matrix(&A, &B, &R);

  ck_assert_int_eq(res, ERROR_CALC);

  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  //    s21_remove_matrix(&R);
}
END_TEST

START_TEST(sum_null) {
  matrix_t *A = NULL;
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_sum_matrix(A, B, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(sum_matrix) {
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
      check.matrix[i][j] = m.matrix[i][j] + mtx.matrix[i][j];
    }
  }
  matrix_t res = {0};

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), OK);
  ck_assert_int_eq(s21_eq_matrix(&check, &res), SUCCESS);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

START_TEST(sum_matrix1) {
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
  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), ERROR_CALC);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sum_matrix4) {
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

  ck_assert_int_eq(s21_sum_matrix(&m, &mtx, &res), NOTCORRECT);
  s21_remove_matrix(&m);
  s21_remove_matrix(&mtx);
  s21_remove_matrix(&res);
  s21_remove_matrix(&check);
}
END_TEST

Suite *suite_sum(void) {
  Suite *s = suite_create("\033[45ms21_sum_matrix\033[0m");
  TCase *tc = tcase_create("sqrt_tc");

  // Суммирование матриц
  tcase_add_test(tc, sum_matrix_same_size);
  tcase_add_test(tc, sum_matrix_different_size);
  tcase_add_test(tc, sum_matrix_null_A);
  tcase_add_test(tc, sum_matrix_null_B);
  tcase_add_test(tc, sum_matrix_null_result);
  tcase_add_test(tc, sum_matrix_large);
  tcase_add_test(tc, sum_matrix_negative_value);
  tcase_add_test(tc, sum_matrix_zero_value);
  tcase_add_test(tc, sum_matrix_positive_value);
  tcase_add_test(tc, sum_matrix_single_element);

  tcase_add_test(tc, sum_matrix_1);
  tcase_add_test(tc, sum_matrix_2);
  tcase_add_test(tc, sum_test_NOTCORRECT_matrix);
  tcase_add_test(tc, sum_null);
  tcase_add_loop_test(tc, sum_matrix, 0, 20);
  tcase_add_loop_test(tc, sum_matrix1, 0, 20);
  tcase_add_loop_test(tc, sum_matrix4, 0, 20);

  suite_add_tcase(s, tc);
  return s;
}