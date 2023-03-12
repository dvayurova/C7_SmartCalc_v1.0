#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_smartcalc.h"

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
      if (i + 1 < str_len && str[i + 1] == '.')
        dot += 1;
    } else {
      if (i + 1 < str_len && str[i + 1] == '.') {
        res = 1;
      }
    }
    if (dot > 1) {
      res = 1;
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

int incorrect_brackets(char *str) {
  int open_bracket = 0;
  int str_len = 0;
  str_len = strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] == '(') {
      open_bracket += 1;
    }
    if (str[i] == ')') {
      open_bracket -= 1;
    }
    if (str[i] == '(' && str[i + 1] == ')') {
      open_bracket = -10;
    }
  }
  return open_bracket == 0 ? 0 : 1;
}

int incorrect_function(char *str) {
  int res = 0;
  int str_len = 0;
  str_len = strlen(str);
  for (int i = 0; i < str_len; i++) {
    if (str[i] == 'm' && str[i + 1] == 'o' && str[i + 2] == 'd' &&
        strchr("0123456789 -", str[i + 3]) != NULL) {
      i += 2;
    } else if (str[i] == 'c' && str[i + 1] == 'o' && str[i + 2] == 's' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 's' && str[i + 1] == 'i' && str[i + 2] == 'n' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 't' && str[i + 1] == 'a' && str[i + 2] == 'n' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (str[i] == 'a' && str[i + 1] == 'c' && str[i + 2] == 'o' &&
               str[i + 3] == 's' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 'a' && str[i + 1] == 's' && str[i + 2] == 'i' &&
               str[i + 3] == 'n' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 'a' && str[i + 1] == 't' && str[i + 2] == 'a' &&
               str[i + 3] == 'n' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 's' && str[i + 1] == 'q' && str[i + 2] == 'r' &&
               str[i + 3] == 't' && str[i + 4] == '(') {
      i += 4;
    } else if (str[i] == 'l' && str[i + 1] == 'n' && str[i + 2] == '(') {
      i += 2;
    } else if (str[i] == 'l' && str[i + 1] == 'o' && str[i + 2] == 'g' &&
               str[i + 3] == '(') {
      i += 3;
    } else if (strchr("+-*/^() xX", str[i]) == NULL && !is_number(str[i])) {
      res = 1;
    }
  }
  return res;
}

int missed_numbers(char *str) {
  int str_len = 0;
  str_len = strlen(str);
  int stop = 0;
  int i = 0;
  while (i < str_len && stop < 2) {
    if (strchr("+-*/^", str[i]) != NULL)
      stop += 1;
    if (strchr("0123456789xX(", str[i]) != NULL)
      stop = 0;
    if (str[i] == '(' && strchr("*/^m", str[i + 1]) != NULL)
      stop = 2;
    // if ((str[i] == 'x' || str[i] == 'X') &&
    //     strchr("0123456789", str[i + 1]) != NULL)
    //   stop = 2;
    if (strchr("0123456789", str[i]) != NULL &&
        (str[i + 1] == 'x' || str[i + 1] == 'X'))
      stop = 2;
    if (strchr("0123456789x", str[i]) != NULL && str[i + 1] == '(')
      stop = 2;
    i++;
  }
  if (strchr("0123456789x)", str[str_len - 1]) == NULL)
    stop = 1;
  return stop ? 1 : 0;
}

int validation(char *str, double x) {
  int i = 0;
  int stop = 0;
  char number_tmp[255] = "";
  int j = 0;
  double num = 0;
  int str_len = 0;
  int divide = 0;
  str_len = strlen(str);
  if (str_len > 255)
    stop += 1;
  if (str_len == 1 && strchr("0123456789", str[0]) == NULL) {
    stop += 1;
  }
  stop += incorrect_brackets(str);
  stop += incorrect_function(str);
  stop += missed_numbers(str);
  while (i < str_len && !stop) {
    // check first symbol e.g. it's '^' or ')'
    if (strchr("pcstal0123456789(x+- ", str[0]) == NULL) {
      stop += 1;
    }
    if (str[i] == '/' && (str[i + 1] == 'x' || str[i + 1] == 'X')) {
      stop += divide_zero(1, x);
    }
    while (is_number(str[i])) {
      number_tmp[j] = str[i];
      j++;
      i++;
    }
    if (str[i] == '/') {
      divide = 1;
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
