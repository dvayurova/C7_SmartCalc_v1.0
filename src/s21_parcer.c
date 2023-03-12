#include "s21_smartcalc.h"

double s21_calculator(char *str, double x) {
  double res = 0;
  numbers *num_stack = NULL;
  operators *oper_stack = NULL;
  if (strlen(str) != 0) {
    parcer(str, x, &num_stack, &oper_stack);
    res = count_result(&num_stack, &oper_stack);

    while (num_stack) {
      pop_numbers(&num_stack);
    }
    while (oper_stack) {
      pop_operators(&oper_stack);
    }
  }
  return res;
}

int is_sign(int i, char *str) {
  int res = 0;
  if ((str[i] == '-' && i == 0) || (str[i] == '(' && str[i + 1] == '-'))
    res = 1;
  if ((str[i] == '+' && i == 0) || (str[i] == '(' && str[i + 1] == '+'))
    res = 1;
  return res;
}

void parcer(char *str, double x, numbers **num_stack, operators **oper_stack) {
  char number_tmp[255] = "";
  int j = 0;
  int i = 0;
  int str_len = 0;
  double num = 0;
  const char operators_mas[] = "+-*/^mcstal()";
  str_len = strlen(str);
  while (i < str_len) {
    while (is_number(str[i])) {
      number_tmp[j] = str[i];
      j++;
      i++;
    }
    if (!is_number(str[i]) && j > 0) {
      to_number(number_tmp, &num);
      push_numbers(num_stack, num);
      memset(&number_tmp, 0, sizeof(number_tmp));
      j = 0;
    }
    if (str[i] == 'x' || str[i] == 'X') {
      push_numbers(num_stack, x);
    }
    if (strchr(operators_mas, str[i]) != NULL) {
      parse_operator(str, &i, oper_stack, num_stack);
    }
    if (is_sign(i, str)) {
      push_numbers(num_stack, 0);
    }
    i++;
  }
}

int is_number(char c) {
  return ((c >= '0' && c <= '9') || c == '.' || c == 'e') ? 1 : 0;
}

void to_number(char *str, double *num) {
  *num = 0;
  *num = atof(str);
}

void push_logic(int *i, operators **oper_stack, numbers **num_stack, int n,
                int opr, int prior, int required_nums) {
  calc_before_push(num_stack, oper_stack, prior);
  if (prior != BRAC_CLOSE) {
    push_operators(oper_stack, opr, prior, required_nums);
  }
  *i += n - 1;
}

int parse_operator(char *str, int *i, operators **oper_stack,
                   numbers **num_stack) {
  int res = 0;
  if (str[*i] == '+') {
    push_logic(i, oper_stack, num_stack, 1, '+', PLUS, 2);
  }
  if (str[*i] == '-') {
    push_logic(i, oper_stack, num_stack, 1, '-', MINUS, 2);
  }
  if (str[*i] == '*') {
    push_logic(i, oper_stack, num_stack, 1, '*', MULT, 2);
  }
  if (str[*i] == '/') {
    push_logic(i, oper_stack, num_stack, 1, '/', DIV, 2);
  }
  if (str[*i] == '^') {
    push_logic(i, oper_stack, num_stack, 1, '^', EXP, 2);
  }
  if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') { // mod
    push_logic(i, oper_stack, num_stack, 3, 'm', MOD, 2);
  }
  if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's') { // cos
    push_logic(i, oper_stack, num_stack, 3, 'c', FUNCS, 1);
  }
  if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n') { // sin
    push_logic(i, oper_stack, num_stack, 3, 's', FUNCS, 1);
  }
  if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n') { // tan
    push_logic(i, oper_stack, num_stack, 3, 't', FUNCS, 1);
  }
  if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's') { // acos
    push_logic(i, oper_stack, num_stack, 4, 'C', FUNCS, 1);
  }
  if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'i' &&
      str[*i + 3] == 'n') { // asin
    push_logic(i, oper_stack, num_stack, 4, 'S', FUNCS, 1);
  }
  if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
      str[*i + 3] == 'n') { // atan
    push_logic(i, oper_stack, num_stack, 4, 'T', FUNCS, 1);
  }
  if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
      str[*i + 3] == 't') { // sqrt
    push_logic(i, oper_stack, num_stack, 4, 'q', FUNCS, 1);
  }
  if (str[*i] == 'l' && str[*i + 1] == 'n') { // ln
    push_logic(i, oper_stack, num_stack, 2, 'l', FUNCS, 1);
  }
  if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g') { // log
    push_logic(i, oper_stack, num_stack, 3, 'g', FUNCS, 1);
  }
  if (str[*i] == '(') {
    push_logic(i, oper_stack, num_stack, 1, '(', BRAC_OPEN, 1);
  }
  if (str[*i] == ')') {
    push_logic(i, oper_stack, num_stack, 1, ')', BRAC_CLOSE, 1);
  }
  return res;
}
