#include "test.h"

START_TEST(test_s21_inverse_matrix_1) {
  matrix_t A, B, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 44300.0 / 367429.0;
  C.matrix[0][1] = -236300.0 / 367429.0;
  C.matrix[0][2] = 200360.0 / 367429.0;
  C.matrix[1][0] = 20600.0 / 367429.0;
  C.matrix[1][1] = 56000.0 / 367429.0;
  C.matrix[1][2] = -156483.0 / 367429.0;
  C.matrix[2][0] = 30900.0 / 367429.0;
  C.matrix[2][1] = 84000.0 / 367429.0;
  C.matrix[2][2] = -51010.0 / 367429.0;
  A.matrix[0][0] = 2.8;
  A.matrix[0][1] = 1.3;
  A.matrix[0][2] = 7.01;
  A.matrix[1][0] = -1.03;
  A.matrix[1][1] = -2.3;
  A.matrix[1][2] = 3.01;
  A.matrix[2][0] = 0;
  A.matrix[2][1] = -3;
  A.matrix[2][2] = 2;
  s21_inverse_matrix(&A, &B);

  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_inverse_matrix_2) {
  matrix_t A, C;
  s21_create_matrix(3, 3, &A);
  s21_create_matrix(3, 3, &C);
  C.matrix[0][0] = 1.0;
  C.matrix[0][1] = -1.0;
  C.matrix[0][2] = 1.0;
  C.matrix[1][0] = -38.0;
  C.matrix[1][1] = 41.0;
  C.matrix[1][2] = -34.0;
  C.matrix[2][0] = 27.0;
  C.matrix[2][1] = -29.0;
  C.matrix[2][2] = 24.0;
  A.matrix[0][0] = 2.0;
  A.matrix[0][1] = 5.0;
  A.matrix[0][2] = 7.0;
  A.matrix[1][0] = 6.0;
  A.matrix[1][1] = 3.0;
  A.matrix[1][2] = 4.0;
  A.matrix[2][0] = 5.0;
  A.matrix[2][1] = -2.0;
  A.matrix[2][2] = -3.0;
  matrix_t B;
  s21_inverse_matrix(&A, &B);
  int res = s21_eq_matrix(&B, &C);
  ck_assert_int_eq(res, SUCCESS);
  s21_remove_matrix(&A);
  s21_remove_matrix(&B);
  s21_remove_matrix(&C);
}
END_TEST

START_TEST(test_s21_inverse_matrix_3) {
  const int size = 3;
  matrix_t m = {0};
  s21_create_matrix(size, size, &m);

  m.matrix[0][0] = 2;
  m.matrix[0][1] = 5;
  m.matrix[0][2] = 7;
  m.matrix[1][0] = 6;
  m.matrix[1][1] = 3;
  m.matrix[1][2] = 4;
  m.matrix[2][0] = 5;
  m.matrix[2][1] = -2;
  m.matrix[2][2] = -3;

  matrix_t res = {0};
  s21_inverse_matrix(&m, &res);

  matrix_t expected = {0};
  s21_create_matrix(size, size, &expected);
  expected.matrix[0][0] = 1;
  expected.matrix[0][1] = -1;
  expected.matrix[0][2] = 1;
  expected.matrix[1][0] = -38;
  expected.matrix[1][1] = 41;
  expected.matrix[1][2] = -34;
  expected.matrix[2][0] = 27;
  expected.matrix[2][1] = -29;
  expected.matrix[2][2] = 24;

  ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);

  s21_remove_matrix(&expected);
  s21_remove_matrix(&res);
  s21_remove_matrix(&m);
}
END_TEST

START_TEST(test_s21_inverse_matrix_4) {
  matrix_t m = {0};
  matrix_t expected = {0};
  int codec1, codec2;
  codec1 = s21_create_matrix(3, 3, &m);
  if (!codec1) codec2 = s21_create_matrix(3, 3, &expected);

  if (!codec1 && !codec2) {
    m.matrix[0][0] = 2;
    m.matrix[0][1] = 5;
    m.matrix[0][2] = 7;

    m.matrix[1][0] = 6;
    m.matrix[1][1] = 3;
    m.matrix[1][2] = 4;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = -2;
    m.matrix[2][2] = -3;

    expected.matrix[0][0] = 1;
    expected.matrix[0][1] = -1;
    expected.matrix[0][2] = 1;

    expected.matrix[1][0] = -38;
    expected.matrix[1][1] = 41;
    expected.matrix[1][2] = -34;

    expected.matrix[2][0] = 27;
    expected.matrix[2][1] = -29;
    expected.matrix[2][2] = 24;
    matrix_t result = {0};
    int code = s21_inverse_matrix(&m, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, 0);

    s21_remove_matrix(&m);
    s21_remove_matrix(&result);
    s21_remove_matrix(&expected);
  }
}
END_TEST

START_TEST(test_s21_inverse_matrix_5) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 4, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, ERROR_CALC);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_s21_inverse_matrix_7) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(1, 1, &m);
  if (!codec) {
    int code = s21_inverse_matrix(&m, &result);
    ck_assert_int_eq(code, ERROR_CALC);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_s21_inverse_matrix_8) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_inverse_matrix(&m, &result);
  ck_assert_int_eq(code, NOTCORRECT);

  /*
    TRANSPONSE TESTS
  */
}
END_TEST

START_TEST(inverse_matrix_test_01) {
  int res = 0;
  matrix_t mat_1 = {0};
  matrix_t mat_res = {0};
  matrix_t mat_check = {0};

  s21_create_matrix(4, 4, &mat_1);
  s21_create_matrix(4, 4, &mat_check);

  mat_1.matrix[0][0] = 3.0;
  mat_1.matrix[0][1] = 2.0;
  mat_1.matrix[0][2] = 2.0;
  mat_1.matrix[0][3] = 2.0;
  mat_1.matrix[1][0] = 2.0;
  mat_1.matrix[1][1] = 3.0;
  mat_1.matrix[1][2] = 2.0;
  mat_1.matrix[1][3] = 2.0;
  mat_1.matrix[2][0] = 2.0;
  mat_1.matrix[2][1] = 2.0;
  mat_1.matrix[2][2] = 3.0;
  mat_1.matrix[2][3] = 2.0;
  mat_1.matrix[3][0] = 2.0;
  mat_1.matrix[3][1] = 2.0;
  mat_1.matrix[3][2] = 2.0;
  mat_1.matrix[3][3] = 3.0;

  mat_check.matrix[0][0] = -2.0;
  mat_check.matrix[0][1] = 1.0;
  mat_check.matrix[0][2] = 0.0;
  mat_check.matrix[1][0] = 19.0;
  mat_check.matrix[1][1] = -10.0;
  mat_check.matrix[1][2] = 1.5;
  mat_check.matrix[2][0] = -11.0;
  mat_check.matrix[2][1] = 6.0;
  mat_check.matrix[2][2] = -1.0;

  res = s21_inverse_matrix(&mat_1, &mat_res);
  ck_assert_int_eq(res, OK);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);
  s21_remove_matrix(&mat_check);
}
END_TEST

START_TEST(inverse_matrix_test_02) {
  int res = 0;
  matrix_t mat_1 = {0};
  matrix_t mat_res = {0};

  s21_create_matrix(3, 3, &mat_1);

  mat_1.matrix[0][0] = 1.0;
  mat_1.matrix[0][1] = 2.0;
  mat_1.matrix[0][2] = 3.0;
  mat_1.matrix[1][0] = 4.0;
  mat_1.matrix[1][1] = 5.0;
  mat_1.matrix[1][2] = 6.0;
  mat_1.matrix[2][0] = 7.0;
  mat_1.matrix[2][1] = 8.0;
  mat_1.matrix[2][2] = 9.0;

  res = s21_inverse_matrix(&mat_1, &mat_res);
  ck_assert_int_eq(res, ERROR_CALC);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);
}
END_TEST

START_TEST(inverse_matrix_test_03) {
  int res = 0;
  matrix_t mat_1 = {0};
  matrix_t mat_res = {0};

  s21_create_matrix(4, 3, &mat_1);

  res = s21_inverse_matrix(&mat_1, &mat_res);
  ck_assert_int_eq(res, ERROR_CALC);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);
}
END_TEST

START_TEST(inverse_matrix_test_04) {
  int res = 0;
  matrix_t mat_1 = {NULL, 0, 0};
  matrix_t mat_res = {0};

  res = s21_inverse_matrix(&mat_1, &mat_res);
  ck_assert_int_eq(res, NOTCORRECT);
  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);
}
END_TEST

Suite *suite_inverse(void) {
  Suite *s = suite_create("\033[45ms21_inverse_matrix\033[0m");
  TCase *tc = tcase_create("sqrt_tc");

  tcase_add_test(tc, test_s21_inverse_matrix_1);
  tcase_add_test(tc, test_s21_inverse_matrix_2);
  tcase_add_test(tc, test_s21_inverse_matrix_3);
  tcase_add_test(tc, test_s21_inverse_matrix_4);
  tcase_add_test(tc, test_s21_inverse_matrix_5);
  tcase_add_test(tc, test_s21_inverse_matrix_7);
  tcase_add_test(tc, test_s21_inverse_matrix_8);

  tcase_add_test(tc, inverse_matrix_test_01);
  tcase_add_test(tc, inverse_matrix_test_02);
  tcase_add_test(tc, inverse_matrix_test_03);
  tcase_add_test(tc, inverse_matrix_test_04);

  suite_add_tcase(s, tc);
  return s;
}