#include "s21_smartcalc.h"

void get_operands(numbers **num_stack, double *a, double *b, int required_num) {
  *b = (*num_stack)->num;
  pop_numbers(num_stack);
  if (required_num == 2) {
    *a = (*num_stack)->num;
    pop_numbers(num_stack);
  }
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
    res = cos(b);
  } else if (oper_stack->operator== 's') {
    res = sin(b);
  } else if (oper_stack->operator== 't') {
    res = tan(b);
  } else if (oper_stack->operator== 'C') {
    res = acos(b);
  } else if (oper_stack->operator== 'S') {
    res = asin(b);
  } else if (oper_stack->operator== 'T') {
    res = atan(b);
  } else if (oper_stack->operator== 'q') {
    res = sqrt(b);
  } else if (oper_stack->operator== 'l') {
    res = log(b);
  } else if (oper_stack->operator== 'g') {
    res = log10(b);
  }
  // printf("\n calc_res = %f\n", res);
  return res;
}

double count_result(numbers **num_stack, operators **oper_stack) {
  double a = 0;
  double b = 0;
  double res = 0;
  while ((*oper_stack)->size > 1) {
    get_operands(num_stack, &a, &b, (*oper_stack)->required_num);
    res = calc(a, b, *oper_stack);
    push_numbers(num_stack, res);
    pop_operators(oper_stack);
  }
  get_operands(num_stack, &a, &b, (*oper_stack)->required_num);
  res = calc(a, b, *oper_stack);

  // pop_numbers(num_stack);
  // res = (*num_stack)->num;
  printf("\n RES = %f", res);
  return res;
}

void calc_before_push(numbers **num_stack, operators **oper_stack, int prior) {
  double a = 0;
  double b = 0;
  if (*num_stack != NULL) {
    while ((*num_stack)->size >= 1 && *oper_stack != NULL &&
           prior <= (*oper_stack)->priority) {
      get_operands(num_stack, &a, &b, (*oper_stack)->required_num);
      push_numbers(num_stack, calc(a, b, *oper_stack));
      pop_operators(oper_stack);
    }
  }
}