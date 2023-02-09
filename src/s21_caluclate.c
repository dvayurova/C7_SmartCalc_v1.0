#include "s21_smartcalc.h"

void get_operands(numbers **num_stack, double *a, double *b) {
  *b = (*num_stack)->num;
  pop_numbers(num_stack);
  *a = (*num_stack)->num;
  pop_numbers(num_stack);
}

double calc(double a, double b, operators *oper_stack) {
  double res = 0;
  if (oper_stack->operator== '+') {
    res = a + b;
  } else if (oper_stack->operator== '-') {
    res = a - b;
  } else if (oper_stack->operator== '*') {
    res = a * b;
  } else if (oper_stack->operator== '/') {
    res = a / b;
  } else if (oper_stack->operator== '^') {
    res = pow(a, b);
  } else if (oper_stack->operator== 'm') {
    res = fmod(a, b);
  } else if (oper_stack->operator== 'c') {
    res = cos(a);
  } else if (oper_stack->operator== 's') {
    res = sin(a);
  } else if (oper_stack->operator== 't') {
    res = tan(a);
  } else if (oper_stack->operator== 'C') {
    res = acos(a);
  } else if (oper_stack->operator== 'S') {
    res = asin(a);
  } else if (oper_stack->operator== 'T') {
    res = atan(a);
  } else if (oper_stack->operator== 'q') {
    res = sqrt(a);
  } else if (oper_stack->operator== 'l') {
    res = log(a);
  } else if (oper_stack->operator== 'g') {
    res = log10(a);
  }
  // printf("\n calc_res = %f\n", res);
  return res;
}

double count_result(numbers **num_stack, operators **oper_stack) {
  double a = 0;
  double b = 0;
  double res = 0;
  while ((*oper_stack)->size > 1) {
    get_operands(num_stack, &a, &b);
    res = calc(a, b, *oper_stack);
    push_numbers(num_stack, res);
    pop_operators(oper_stack);
  }
  get_operands(num_stack, &a, &b);
  res = calc(a, b, *oper_stack);

  // pop_numbers(num_stack);
  // res = (*num_stack)->num;
  printf("\n RES = %f", res);
  return res;
}