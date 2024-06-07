#ifndef SRC_S21_MATRIX_TEST_H_
#define SRC_S21_MATRIX_TEST_H_

#include <check.h>

#include "../s21_matrix.h"

#define OK 0  // Код успешного выполнения
#define ERROR_CALC 2  // Код ошибки при выполнении вычислений
#define NOTCORRECT 1  // Код ошибки для некорректных данных
#define SUCCESS 1  // Код успешного выполнения (в контексте логических операций)
#define FAILURE \
  0  // Код неуспешного выполнения (в контексте логических операций)

Suite *suite_calc(void);
Suite *suite_cr_rm(void);
Suite *suite_det(void);
Suite *suite_eq(void);
Suite *suite_inverse(void);
Suite *suite_mult_mat(void);
Suite *suite_mult_num(void);
Suite *suite_sub(void);
Suite *suite_sum(void);
Suite *suite_transport(void);

void run_test(void);
void run_testcase(Suite *testcase);
double get_rand(double min_val, double max_val);

#endif  //  SRC_S21_MATRIX_TEST_H_