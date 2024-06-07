#include "test.h"

// Минор матрицы и матрица алгебраических дополнений

START_TEST(compliment_test_1) {
  matrix_t A, B, R;
  int flag = 0;
  flag += s21_create_matrix(3, 3, &B);  // 1 2 3
  flag += s21_create_matrix(3, 3, &A);  // 0 4 2
  if (!flag) {
    B.matrix[0][0] = 1;  // 5 2 1
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 4;
    B.matrix[1][2] = 2;
    B.matrix[2][0] = 5;
    B.matrix[2][1] = 2;
    B.matrix[2][2] = 1;

    A.matrix[0][0] = 0;    // 0  10 -20
    A.matrix[0][1] = 10;   // 4 -14  8
    A.matrix[0][2] = -20;  //-8  -2  4
    A.matrix[1][0] = 4;
    A.matrix[1][1] = -14;
    A.matrix[1][2] = 8;
    A.matrix[2][0] = -8;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = 4;

    int code = s21_calc_complements(&B, &R);
    ck_assert_int_eq(code, OK);
    ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(compliment_test_2) {
  matrix_t A, B, R;
  int flag = 0;
  flag += s21_create_matrix(3, 3, &B);
  flag += s21_create_matrix(3, 3, &A);
  if (!flag) {
    A.matrix[0][0] = 5;
    A.matrix[0][1] = -1;
    A.matrix[0][2] = 1;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 1;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 3;

    s21_calc_complements(&A, &R);

    B.matrix[0][0] = 9;
    B.matrix[0][1] = -2;
    B.matrix[0][2] = -3;
    B.matrix[1][0] = 3;
    B.matrix[1][1] = 14;
    B.matrix[1][2] = -1;
    B.matrix[2][0] = -7;
    B.matrix[2][1] = -18;
    B.matrix[2][2] = 17;

    ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
  }
}
END_TEST

START_TEST(compliment_test_not_square) {
  matrix_t B, R;
  if (!s21_create_matrix(2, 3, &B)) {
    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 4;
    B.matrix[1][2] = 2;

    int code = s21_calc_complements(&B, &R);

    ck_assert_int_eq(code, ERROR_CALC);
    s21_remove_matrix(&B);
  }
  // s21_remove_matrix(&R);
}
END_TEST

START_TEST(null_compliments) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_calc_complements(B, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(s21_calc_compl_1) {
  matrix_t A, B, C;
  int flag = 0;
  flag += s21_create_matrix(3, 3, &A);
  flag += s21_create_matrix(3, 3, &C);
  if (!flag) {
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 2.0;
    A.matrix[0][2] = 3.0;
    A.matrix[1][0] = 0.0;
    A.matrix[1][1] = 4.0;
    A.matrix[1][2] = 2.0;
    A.matrix[2][0] = 5.0;
    A.matrix[2][1] = 2.0;
    A.matrix[2][2] = 1.0;
    s21_calc_complements(&A, &B);
    C.matrix[0][0] = 0.0;
    C.matrix[0][1] = 10.0;
    C.matrix[0][2] = -20.0;
    C.matrix[1][0] = 4.0;
    C.matrix[1][1] = -14.0;
    C.matrix[1][2] = 8.0;
    C.matrix[2][0] = -8.0;
    C.matrix[2][1] = -2.0;
    C.matrix[2][2] = 4.0;
    int res = s21_eq_matrix(&B, &C);
    ck_assert_int_eq(res, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
  }
}
END_TEST

START_TEST(s21_calc_compl_2) {
  int flag = 0;
  matrix_t a = {0};
  flag += s21_create_matrix(3, 3, &a);
  matrix_t res = {0};
  flag += s21_create_matrix(3, 3, &res);
  matrix_t m;
  if (!flag) {
    res.matrix[0][0] = 0;
    res.matrix[0][1] = 10;
    res.matrix[0][2] = -20;
    res.matrix[1][0] = 4;
    res.matrix[1][1] = -14;
    res.matrix[1][2] = 8;
    res.matrix[2][0] = -8;
    res.matrix[2][1] = -2;
    res.matrix[2][2] = 4;

    a.matrix[0][0] = 1;
    a.matrix[0][1] = 2;
    a.matrix[0][2] = 3;
    a.matrix[1][0] = 0;
    a.matrix[1][1] = 4;
    a.matrix[1][2] = 2;
    a.matrix[2][0] = 5;
    a.matrix[2][1] = 2;
    a.matrix[2][2] = 1;
    s21_calc_complements(&a, &m);
    ck_assert_int_eq(s21_eq_matrix(&res, &m), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&a);
    s21_remove_matrix(&res);
  }
}
END_TEST

START_TEST(empty) {
  matrix_t a = {0};
  matrix_t b = {0};
  ck_assert_int_eq(s21_calc_complements(&a, &b), NOTCORRECT);
}
END_TEST

START_TEST(size_mismatch) {
  matrix_t a = {0};
  matrix_t b = {0};
  if (!s21_create_matrix(1, 2, &a)) {
    ck_assert_int_eq(s21_calc_complements(&a, &b), ERROR_CALC);
    s21_remove_matrix(&a);
  }
}
END_TEST

START_TEST(complements) {
  int flag = 0;
  const int size = 3;
  matrix_t m = {0};
  if (!s21_create_matrix(size, size, &m)) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;
    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;
  } else
    flag = 1;

  matrix_t expected = {0};
  if (!s21_create_matrix(size, size, &expected)) {
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;
  } else
    flag = 1;

  if (!flag) {
    matrix_t res = {0};
    s21_calc_complements(&m, &res);

    ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}
END_TEST

START_TEST(test_incorrect) {
  matrix_t m = {0};
  matrix_t result = {0};
  int code = s21_calc_complements(&m, &result);
  if (!code) ck_assert_int_eq(code, NOTCORRECT);
}
END_TEST

START_TEST(test_not_sqare) {
  matrix_t m = {0};
  matrix_t result = {0};
  int codec = s21_create_matrix(3, 4, &m);
  if (!codec) {
    int code = s21_calc_complements(&m, &result);
    ck_assert_int_eq(code, ERROR_CALC);
    s21_remove_matrix(&m);
  }
}
END_TEST

START_TEST(test_normal) {
  matrix_t expected = {0};
  matrix_t m = {0};
  matrix_t result = {0};
  int flag = 0;
  flag += s21_create_matrix(3, 3, &m);
  flag += s21_create_matrix(3, 3, &expected);
  if (!flag) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;

    m.matrix[1][0] = 0;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;

    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;

    expected.matrix[0][0] = 0;
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;

    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;

    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;

    int code = s21_calc_complements(&m, &result);

    ck_assert_int_eq(s21_eq_matrix(&result, &expected), SUCCESS);
    ck_assert_int_eq(code, OK);
    s21_remove_matrix(&result);
    s21_remove_matrix(&m);
    s21_remove_matrix(&expected);
  }
}
END_TEST

START_TEST(test_s21_calc_complements_1) {
  matrix_t A, B, R;
  int flag = 0;
  flag += s21_create_matrix(3, 3, &B);
  flag += s21_create_matrix(3, 3, &A);
  if (!flag) {
    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 4;
    B.matrix[1][2] = 2;
    B.matrix[2][0] = 5;
    B.matrix[2][1] = 2;
    B.matrix[2][2] = 1;

    A.matrix[0][0] = 0;
    A.matrix[0][1] = 10;
    A.matrix[0][2] = -20;
    A.matrix[1][0] = 4;
    A.matrix[1][1] = -14;
    A.matrix[1][2] = 8;
    A.matrix[2][0] = -8;
    A.matrix[2][1] = -2;
    A.matrix[2][2] = 4;

    int code = s21_calc_complements(&B, &R);
    ck_assert_int_eq(code, 0);
    ck_assert_int_eq(s21_eq_matrix(&R, &A), SUCCESS);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
    s21_remove_matrix(&A);
  }
}
END_TEST

START_TEST(test_s21_calc_complements_2) {
  matrix_t A, B, R;
  int flag = 0;
  flag += s21_create_matrix(3, 3, &A);
  flag += s21_create_matrix(3, 3, &B);
  if (!flag) {
    A.matrix[0][0] = 5;
    A.matrix[0][1] = -1;
    A.matrix[0][2] = 1;
    A.matrix[1][0] = 2;
    A.matrix[1][1] = 3;
    A.matrix[1][2] = 4;
    A.matrix[2][0] = 1;
    A.matrix[2][1] = 0;
    A.matrix[2][2] = 3;

    s21_calc_complements(&A, &R);

    B.matrix[0][0] = 9;
    B.matrix[0][1] = -2;
    B.matrix[0][2] = -3;
    B.matrix[1][0] = 3;
    B.matrix[1][1] = 14;
    B.matrix[1][2] = -1;
    B.matrix[2][0] = -7;
    B.matrix[2][1] = -18;
    B.matrix[2][2] = 17;

    ck_assert_int_eq(s21_eq_matrix(&R, &B), SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&R);
  }
}
END_TEST

START_TEST(test_s21_calc_complements_3) {
  matrix_t B, R;
  if (!s21_create_matrix(2, 3, &B)) {
    B.matrix[0][0] = 1;
    B.matrix[0][1] = 2;
    B.matrix[0][2] = 3;
    B.matrix[1][0] = 0;
    B.matrix[1][1] = 4;
    B.matrix[1][2] = 2;

    int code = s21_calc_complements(&B, &R);

    ck_assert_int_eq(code, ERROR_CALC);
    s21_remove_matrix(&B);
  }
  // s21_remove_matrix(&R);
}
END_TEST

START_TEST(test_s21_calc_complements_5) {
  matrix_t *B = NULL;
  matrix_t *R = NULL;
  int res = s21_calc_complements(B, R);
  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(test_s21_calc_complements_6) {
  matrix_t A, B, C;
  int flag = 0;
  flag += s21_create_matrix(3, 3, &A);
  flag += s21_create_matrix(3, 3, &C);
  if (!flag) {
    A.matrix[0][0] = 1.0;
    A.matrix[0][1] = 2.0;
    A.matrix[0][2] = 3.0;
    A.matrix[1][0] = 0.0;
    A.matrix[1][1] = 4.0;
    A.matrix[1][2] = 2.0;
    A.matrix[2][0] = 5.0;
    A.matrix[2][1] = 2.0;
    A.matrix[2][2] = 1.0;
    s21_calc_complements(&A, &B);
    C.matrix[0][0] = 0.0;
    C.matrix[0][1] = 10.0;
    C.matrix[0][2] = -20.0;
    C.matrix[1][0] = 4.0;
    C.matrix[1][1] = -14.0;
    C.matrix[1][2] = 8.0;
    C.matrix[2][0] = -8.0;
    C.matrix[2][1] = -2.0;
    C.matrix[2][2] = 4.0;
    int res = s21_eq_matrix(&B, &C);
    ck_assert_int_eq(res, SUCCESS);
    s21_remove_matrix(&A);
    s21_remove_matrix(&B);
    s21_remove_matrix(&C);
  }
}
END_TEST

START_TEST(test_s21_calc_complements_7) {
  int flag = 0;
  matrix_t a = {0};
  flag += s21_create_matrix(3, 3, &a);
  matrix_t res = {0};
  flag += s21_create_matrix(3, 3, &res);
  matrix_t m;
  if (!flag) {
    res.matrix[0][0] = 0;
    res.matrix[0][1] = 10;
    res.matrix[0][2] = -20;
    res.matrix[1][0] = 4;
    res.matrix[1][1] = -14;
    res.matrix[1][2] = 8;
    res.matrix[2][0] = -8;
    res.matrix[2][1] = -2;
    res.matrix[2][2] = 4;

    a.matrix[0][0] = 1;
    a.matrix[0][1] = 2;
    a.matrix[0][2] = 3;
    a.matrix[1][0] = 0;
    a.matrix[1][1] = 4;
    a.matrix[1][2] = 2;
    a.matrix[2][0] = 5;
    a.matrix[2][1] = 2;
    a.matrix[2][2] = 1;
    s21_calc_complements(&a, &m);
    ck_assert_int_eq(s21_eq_matrix(&res, &m), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&a);
    s21_remove_matrix(&res);
  }
}
END_TEST

START_TEST(test_s21_calc_complements_8) {
  matrix_t a = {0};
  matrix_t b = {0};
  ck_assert_int_eq(s21_calc_complements(&a, &b), NOTCORRECT);
}
END_TEST

START_TEST(test_s21_calc_complements_9) {
  matrix_t a = {0};
  matrix_t b = {0};
  int core = s21_create_matrix(1, 2, &a);
  if (!core) {
    ck_assert_int_eq(s21_calc_complements(&a, &b), ERROR_CALC);
    s21_remove_matrix(&a);
  }
}
END_TEST

START_TEST(test_s21_calc_complements_10) {
  int flag = 0;
  const int size = 3;
  matrix_t m = {0};
  if (!s21_create_matrix(size, size, &m)) {
    m.matrix[0][0] = 1;
    m.matrix[0][1] = 2;
    m.matrix[0][2] = 3;
    m.matrix[1][1] = 4;
    m.matrix[1][2] = 2;
    m.matrix[2][0] = 5;
    m.matrix[2][1] = 2;
    m.matrix[2][2] = 1;
  } else
    flag = 1;

  matrix_t expected = {0};
  if (!s21_create_matrix(size, size, &expected)) {
    expected.matrix[0][1] = 10;
    expected.matrix[0][2] = -20;
    expected.matrix[1][0] = 4;
    expected.matrix[1][1] = -14;
    expected.matrix[1][2] = 8;
    expected.matrix[2][0] = -8;
    expected.matrix[2][1] = -2;
    expected.matrix[2][2] = 4;
  } else
    flag = 1;
  if (!flag) {
    matrix_t res = {0};
    s21_calc_complements(&m, &res);

    ck_assert_int_eq(s21_eq_matrix(&expected, &res), SUCCESS);
    s21_remove_matrix(&m);
    s21_remove_matrix(&res);
    s21_remove_matrix(&expected);
  }
}
END_TEST

START_TEST(fun_s21_calc_complements) {
  matrix_t initial_matrix;
  matrix_t result_matrix;
  matrix_t test_matrix;
  int err = 0;

  s21_create_matrix(12, 21, &initial_matrix);
  s21_create_matrix(21, 12, &test_matrix);

  err = s21_calc_complements(NULL, &result_matrix);
  ck_assert_int_eq(NOTCORRECT, err);

  err = s21_calc_complements(&initial_matrix, NULL);
  ck_assert_int_eq(NOTCORRECT, err);

  err = s21_calc_complements(&initial_matrix, &result_matrix);
  ck_assert_int_eq(ERROR_CALC, err);

  s21_remove_matrix(&initial_matrix);
  s21_remove_matrix(&test_matrix);

  s21_create_matrix(3, 3, &initial_matrix);
  s21_create_matrix(3, 3, &test_matrix);

  initial_matrix.matrix[0][0] = 1;
  initial_matrix.matrix[0][1] = 2;
  initial_matrix.matrix[0][2] = 3;
  initial_matrix.matrix[1][0] = 4;
  initial_matrix.matrix[1][1] = 5;
  initial_matrix.matrix[1][2] = 6;
  initial_matrix.matrix[2][0] = 7;
  initial_matrix.matrix[2][1] = 8;
  initial_matrix.matrix[2][2] = 9;

  test_matrix.matrix[0][0] = -3;
  test_matrix.matrix[0][1] = -6;
  test_matrix.matrix[0][2] = -3;
  test_matrix.matrix[1][0] = -6;
  test_matrix.matrix[1][1] = -12;
  test_matrix.matrix[1][2] = -6;
  test_matrix.matrix[2][0] = -3;
  test_matrix.matrix[2][1] = -6;
  test_matrix.matrix[2][2] = -3;

  err = s21_calc_complements(&initial_matrix, &result_matrix);
  ck_assert_int_eq(OK, err);
  err = s21_eq_matrix(&result_matrix, &test_matrix);
  ck_assert_int_eq(FAILURE, err);

  test_matrix.matrix[0][0] = -3;
  test_matrix.matrix[0][1] = 6;
  test_matrix.matrix[0][2] = -3;
  test_matrix.matrix[1][0] = 6;
  test_matrix.matrix[1][1] = -12;
  test_matrix.matrix[1][2] = 6;
  test_matrix.matrix[2][0] = -3;
  test_matrix.matrix[2][1] = 6;
  test_matrix.matrix[2][2] = -3;

  err = s21_eq_matrix(&result_matrix, &test_matrix);
  ck_assert_int_eq(SUCCESS, err);

  s21_remove_matrix(&initial_matrix);
  s21_remove_matrix(&result_matrix);
  s21_remove_matrix(&test_matrix);
}
END_TEST

START_TEST(calc_complements_test_01) {
  int res = 0;
  matrix_t mat_1 = {0};
  matrix_t mat_res = {0};
  matrix_t mat_check = {0};

  s21_create_matrix(3, 3, &mat_1);
  s21_create_matrix(3, 3, &mat_check);

  mat_1.matrix[0][0] = 1.0;
  mat_1.matrix[0][1] = 2.0;
  mat_1.matrix[0][2] = 3.0;
  mat_1.matrix[1][0] = 4.0;
  mat_1.matrix[1][1] = 5.0;
  mat_1.matrix[1][2] = 6.0;
  mat_1.matrix[2][0] = 7.0;
  mat_1.matrix[2][1] = 8.0;
  mat_1.matrix[2][2] = 9.0;

  mat_check.matrix[0][0] = -3.0;
  mat_check.matrix[0][1] = 6.0;
  mat_check.matrix[0][2] = -3.0;
  mat_check.matrix[1][0] = 6.0;
  mat_check.matrix[1][1] = -12.0;
  mat_check.matrix[1][2] = 6.0;
  mat_check.matrix[2][0] = -3.0;
  mat_check.matrix[2][1] = 6.0;
  mat_check.matrix[2][2] = -3.0;

  res = s21_calc_complements(&mat_1, &mat_res);

  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);
  s21_remove_matrix(&mat_check);

  ck_assert_int_eq(res, 0);
}
END_TEST

START_TEST(calc_complements_test_02) {
  int res = 0;
  matrix_t mat_1 = {0};
  matrix_t mat_res = {0};

  s21_create_matrix(4, 3, &mat_1);

  mat_1.matrix[0][0] = 1.0;
  mat_1.matrix[0][1] = 2.0;
  mat_1.matrix[0][2] = 3.0;
  mat_1.matrix[1][0] = 4.0;
  mat_1.matrix[1][1] = 5.0;
  mat_1.matrix[1][2] = 6.0;
  mat_1.matrix[2][0] = 7.0;
  mat_1.matrix[2][1] = 8.0;
  mat_1.matrix[2][2] = 9.0;

  res = s21_calc_complements(&mat_1, &mat_res);

  ck_assert_int_eq(res, ERROR_CALC);

  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);
}
END_TEST

START_TEST(calc_complements_test_03) {
  int res = 0;
  matrix_t mat_1 = {NULL, 0, 0};
  matrix_t mat_res = {0};

  res = s21_calc_complements(&mat_1, &mat_res);

  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);

  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

START_TEST(calc_complements_test_04) {
  int res = 0;
  matrix_t mat_1 = {0, 0, 0};
  matrix_t mat_res = {0};

  res = s21_calc_complements(&mat_1, &mat_res);

  s21_remove_matrix(&mat_1);
  s21_remove_matrix(&mat_res);

  ck_assert_int_eq(res, NOTCORRECT);
}
END_TEST

Suite *suite_calc(void) {
  Suite *s = suite_create("\033[45ms21_calc_complements\033[0m");
  TCase *tc = tcase_create("sqrt_tc");

  // Минор матрицы и матрица алгебраических дополнений

  tcase_add_test(tc, compliment_test_1);
  tcase_add_test(tc, compliment_test_2);
  tcase_add_test(tc, compliment_test_not_square);
  tcase_add_test(tc, null_compliments);
  tcase_add_test(tc, s21_calc_compl_1);
  tcase_add_test(tc, s21_calc_compl_2);
  tcase_add_test(tc, empty);
  tcase_add_test(tc, size_mismatch);
  tcase_add_test(tc, complements);
  tcase_add_test(tc, test_normal);
  tcase_add_test(tc, test_not_sqare);
  tcase_add_test(tc, test_incorrect);

  tcase_add_test(tc, test_s21_calc_complements_1);
  tcase_add_test(tc, test_s21_calc_complements_2);
  tcase_add_test(tc, test_s21_calc_complements_3);
  tcase_add_test(tc, test_s21_calc_complements_5);
  tcase_add_test(tc, test_s21_calc_complements_6);
  tcase_add_test(tc, test_s21_calc_complements_7);
  tcase_add_test(tc, test_s21_calc_complements_8);
  tcase_add_test(tc, test_s21_calc_complements_9);
  tcase_add_test(tc, test_s21_calc_complements_10);
  tcase_add_test(tc, fun_s21_calc_complements);

  tcase_add_test(tc, calc_complements_test_01);
  tcase_add_test(tc, calc_complements_test_02);
  tcase_add_test(tc, calc_complements_test_03);
  tcase_add_test(tc, calc_complements_test_04);

  suite_add_tcase(s, tc);
  return s;
}
