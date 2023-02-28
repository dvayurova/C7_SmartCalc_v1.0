#include "s21_smartcalc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int correct_dot(char *str) {
  int res = 0;
  int i = 0;
  int str_len = 0;
  int dot = 0;
  str_len = strlen(str);
  while (i < str_len) {
    if (str[0] == '.') {
      res = 1;
    }
    if (str[i] >= '0' && str[i] <= '9') {
      if (str[i + 1] == '.')
        dot += 1;
    } else {
      if (str[i + 1] == '.') {
        res = 1;
        printf("stop2.");
      }
    }
    if (dot > 1) {
      res = 1;
      printf("stop3.");
    }
    i++;
  }
  return res;
}

int divide_zero(int divide, double num) {
  int res = 0;
  if (divide && fabs(num) <= 1e-7) {
    res = 1;
  }
  return res;
}

// int correct_brackets(char *str) {
//   int res = 0;
//   if ()
//     return res;
// }

int validation(char *str, double x) {
  int i = 0;
  int stop = 0;
  char number_tmp[255];
  int j = 0;
  double num = 0;
  int str_len = 0;
  int divide = 0;
  const char first_char[] = "cstal0123456789(x+- ";
  str_len = strlen(str);
  if (strlen(str) > 255)
    stop += 1;
  while (i < str_len && !stop) {
    // check first symbol e.g. it's '^' or ')'
    if (strchr(first_char, str[0]) == NULL) {
      stop += 1;
      printf("stop1.");
    }
    if (str[i] == '/' && str[i + 1] >= '0' && str[i + 1] <= '9') {
      divide = 1;
    }
    if (str[i] == '/' && (str[i + 1] == 'x' || str[i + 1] == 'X')) {
      stop += divide_zero(1, x);
    }
    while (is_number(str[i])) {
      number_tmp[j] = str[i];
      j++;
      i++;
    }
    if (!is_number(str[i]) && j > 0) {
      to_number(number_tmp, &num);
      stop += correct_dot(number_tmp);
      stop += divide_zero(divide, num);
      memset(&number_tmp, 0, sizeof(number_tmp));
      j = 0;
    }
    i++;
  }
  return stop ? 0 : 1;
}
