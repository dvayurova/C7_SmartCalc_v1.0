#include "s21_smartcalc.h"

void parcer(char *str) {
  char number_tmp[255];
  int j = 0;
  int i = 0;
  int str_len = 0;
  double num = 0;
  const char operators_mas[] = "+-*/^mcstal()";
  numbers *num_stack = NULL;
  operators *oper_stack = NULL;
  str_len = strlen(str);
  while (i < str_len) {
    while (is_number(str[i])) {
      number_tmp[j] = str[i];
      j++;
      i++;
    }
    if (!is_number(str[i]) && j > 0) {
      to_number(number_tmp, &num);
      push_numbers(&num_stack, num);

      //   printf("\n *next_numbers = %p", num_stack->next_numbers);
      memset(&number_tmp, 0, sizeof(number_tmp));
      j = 0;
    }
    if (strchr(operators_mas, str[i]) != NULL) {
      parse_operator(str, &i, &oper_stack, &num_stack);
    }
    i++;
  }
  count_result(&num_stack, &oper_stack);
}

int is_number(char c) { return ((c >= '0' && c <= '9') || c == '.') ? 1 : 0; }

int to_number(char *str, double *num) {
  //   printf("\n number_tmp = %s\n", str);
  int res = 0;
  int i = 0;
  *num = 0;
  if (str[i] == '.') { // IF IT CHECKS IN VALIDATION - DELETE
    res = 1;
  }
  if (!res) {
    *num = atof(str);
  }
  //   printf("\n double num = %f\n", *num);
  return res;
}

int parse_operator(char *str, int *i, operators **oper_stack,
                   numbers **num_stack) {
  int res = 0;
  if (str[*i] == '+') {
    push_operators(oper_stack, '+', PLUS, num_stack);
  }
  if (str[*i] == '-') {
    push_operators(oper_stack, '-', MINUS, num_stack);
  }
  if (str[*i] == '*') {
    push_operators(oper_stack, '*', MULT, num_stack);
  }
  if (str[*i] == '/') {
    push_operators(oper_stack, '/', DIV, num_stack);
  }
  if (str[*i] == '^') {
    push_operators(oper_stack, '^', EXP, num_stack);
  }
  if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') { // mod
    push_operators(oper_stack, 'm', MOD, num_stack);
    *i += 3;
  }
  if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's') { // cos
    push_operators(oper_stack, 'c', FUNCS, num_stack);
    *i += 3;
  }
  if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n') { // sin
    push_operators(oper_stack, 's', FUNCS, num_stack);
    *i += 3;
  }
  if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n') { // tan
    push_operators(oper_stack, 't', FUNCS, num_stack);
    *i += 3;
  }
  if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's') { // acos
    push_operators(oper_stack, 'C', FUNCS, num_stack);
    *i += 4;
  }
  if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's') { // asin
    push_operators(oper_stack, 'S', FUNCS, num_stack);
    *i += 4;
  }
  if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
      str[*i + 3] == 'n') { // atan
    push_operators(oper_stack, 'T', FUNCS, num_stack);
    *i += 4;
  }
  if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
      str[*i + 3] == 't') { // sqrt
    push_operators(oper_stack, 'q', FUNCS, num_stack);
    *i += 4;
  }
  if (str[*i] == 'l' && str[*i + 1] == 'n') { // ln
    push_operators(oper_stack, 'l', FUNCS, num_stack);
    *i += 2;
  }
  if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g') { // log
    push_operators(oper_stack, 'g', FUNCS, num_stack);
    *i += 3;
  }
  // СКОБКИ
  return res;
}