#include "s21_smartcalc.h"

void parcer(char *str) {
  char number_tmp[255];
  int j = 0;
  int i = 0;
  double num = 0;
  const char operators_mas[] = "+-*/^mcstal()";
  numbers *num_stack = NULL;
  num_stack = init_numbers(0);
  operators *oper_stack = NULL;
  oper_stack = init_operators('+', 1);
  while (str[i] != '\0') {
    while (is_number(str[i])) {
      number_tmp[j] = str[i];
      j++;
      i++;
    }
    if (!is_number(str[i]) && j > 0) {
      to_number(number_tmp, &num);
      push_numbers(&num_stack, num);
      printf("\n num in stack = %f", num_stack->num);
      //   printf("\n *next_numbers = %p", num_stack->next_numbers);
      memset(&number_tmp, 0, sizeof(number_tmp));
      j = 0;
    }
    if (strchr(operators_mas, str[i]) != NULL) {
      parse_operator(str, &i, &oper_stack);
    }
    i++;
  }
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

int parse_operator(char *str, int *i, operators **oper_stack) {
  int res = 0;
  if (str[*i] == '+') {
    push_operators(oper_stack, '+', PLUS);
  }
  if (str[*i] == '-') {
    push_operators(oper_stack, '-', MINUS);
  }
  if (str[*i] == '*') {
    push_operators(oper_stack, '*', MULT);
  }
  if (str[*i] == '/') {
    push_operators(oper_stack, '/', DIV);
  }
  if (str[*i] == '^') {
    push_operators(oper_stack, '^', EXP);
  }
  if (str[*i] == 'm' && str[*i + 1] == 'o' && str[*i + 2] == 'd') { // mod
    push_operators(oper_stack, 'm', MOD);
    *i += 3;
  }
  if (str[*i] == 'c' && str[*i + 1] == 'o' && str[*i + 2] == 's') { // cos
    push_operators(oper_stack, 'c', FUNCS);
    *i += 3;
  }
  if (str[*i] == 's' && str[*i + 1] == 'i' && str[*i + 2] == 'n') { // sin
    push_operators(oper_stack, 's', FUNCS);
    *i += 3;
  }
  if (str[*i] == 't' && str[*i + 1] == 'a' && str[*i + 2] == 'n') { // tan
    push_operators(oper_stack, 't', FUNCS);
    *i += 3;
  }
  if (str[*i] == 'a' && str[*i + 1] == 'c' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's') { // acos
    push_operators(oper_stack, 'C', FUNCS);
    *i += 4;
  }
  if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's') { // asin
    push_operators(oper_stack, 'S', FUNCS);
    *i += 4;
  }
  if (str[*i] == 'a' && str[*i + 1] == 't' && str[*i + 2] == 'a' &&
      str[*i + 3] == 'n') { // atan
    push_operators(oper_stack, 'T', FUNCS);
    *i += 4;
  }
  if (str[*i] == 's' && str[*i + 1] == 'q' && str[*i + 2] == 'r' &&
      str[*i + 3] == 't') { // sqrt
    push_operators(oper_stack, 'q', FUNCS);
    *i += 4;
  }
  if (str[*i] == 'l' && str[*i + 1] == 'n') { // ln
    push_operators(oper_stack, 'l', FUNCS);
    *i += 2;
  }
  if (str[*i] == 'l' && str[*i + 1] == 'o' && str[*i + 2] == 'g') { // log
    push_operators(oper_stack, 'g', FUNCS);
    *i += 3;
  }
  // СКОБКИ!
  return res;
}