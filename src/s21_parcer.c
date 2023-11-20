#include "s21_smartcalc.h"

int is_sign(int i, char *str) {
  int res = 0;
  if ((str[i] == '-' && i == 0) || (str[i] == '(' && str[i + 1] == '-'))
    res = 1;
  if ((str[i] == '+' && i == 0) || (str[i] == '(' && str[i + 1] == '+'))
    res = 1;
  return res;
}

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
    if (is_sign(i, str)) {
      push_numbers(&num_stack, 0);
    }
    i++;
  }
  count_result(&num_stack, &oper_stack);
  while (num_stack) {
    pop_numbers(&num_stack);
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

void push_logic(int *i, operators **oper_stack, numbers **num_stack, int n,
                int opr, int prior, int required_nums) {
  calc_before_push(num_stack, oper_stack, prior);
  if (prior != BRAC_CLOSE) {
    push_operators(oper_stack, opr, prior, required_nums);
  }
  *i += n;
}

int parse_operator(char *str, int *i, operators **oper_stack,
                   numbers **num_stack) {
  int res = 0;
  if (str[*i] == '+') {
    push_logic(i, oper_stack, num_stack, 0, '+', PLUS, 2);
  }
  if (str[*i] == '-') {
    push_logic(i, oper_stack, num_stack, 0, '-', MINUS, 2);
  }
  if (str[*i] == '*') {
    push_logic(i, oper_stack, num_stack, 0, '*', MULT, 2);
  }
  if (str[*i] == '/') {
    push_logic(i, oper_stack, num_stack, 0, '/', DIV, 2);
  }
  if (str[*i] == '^') {
    push_logic(i, oper_stack, num_stack, 0, '^', EXP, 2);
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
  if (str[*i] == 'a' && str[*i + 1] == 's' && str[*i + 2] == 'o' &&
      str[*i + 3] == 's') { // asin
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
  // СКОБКИ
  if (str[*i] == '(') {
    push_logic(i, oper_stack, num_stack, 0, '(', BRAC_OPEN, 1);
  }
  if (str[*i] == ')') {
    push_logic(i, oper_stack, num_stack, 0, ')', BRAC_CLOSE, 1);
  }
  return res;
}