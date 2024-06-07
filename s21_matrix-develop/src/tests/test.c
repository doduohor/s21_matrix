#include "test.h"

double get_rand(double min, double max) {
  double val = (double)rand() / RAND_MAX;
  return min + val * (max - min);
}

void run_tests(void) {
  Suite *list_cases[] = {suite_cr_rm(),
                         suite_calc(),
                         suite_det(),
                         suite_eq(),
                         suite_inverse(),
                         suite_mult_mat(),
                         suite_mult_num(),
                         suite_sub(),
                         suite_sum(),
                         suite_transport(),
                         NULL};
  for (Suite **current_testcase = list_cases; *current_testcase != NULL;
       current_testcase++) {
    run_testcase(*current_testcase);
  }
}

void run_testcase(Suite *testcase) {
  static int counter_testcase = 1;

  if (counter_testcase > 0) putchar('\n');
  printf("%s%d%s", "CURRENT TEST: ", counter_testcase, "\n");
  counter_testcase++;
  SRunner *sr = srunner_create(testcase);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);

  srunner_free(sr);
  // sleep(1);
}

int main(void) {
  run_tests();
  return 0;
}