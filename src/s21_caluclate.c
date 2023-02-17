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
  return res;
}

double count_result(numbers **num_stack, operators **oper_stack) {
  double a = 0;
  double b = 0;
  double res = 0;
  while ((*oper_stack)->size != 1) {
    if ((*oper_stack)->priority == BRAC_OPEN) {
      pop_operators(oper_stack);
    }
    get_operands(num_stack, &a, &b, (*oper_stack)->required_num);
    res = calc(a, b, *oper_stack);
    push_numbers(num_stack, res);
    if ((*oper_stack) != NULL)
      pop_operators(oper_stack);
  }

  if ((*oper_stack)->size == 1) {
    // printf("\n ------if-----");
    get_operands(num_stack, &a, &b, (*oper_stack)->required_num);
    res = calc(a, b, *oper_stack);
  } else
    res = (*num_stack)->num;

  // pop_numbers(num_stack);
  // res = (*num_stack)->num;
  // printf("\n RES = %f", res);
  return res;
}

void calc_before_push(numbers **num_stack, operators **oper_stack, int prior) {
  double a = 0;
  double b = 0;
  int stop = 0;
  if (*num_stack != NULL && prior != BRAC_OPEN) {
    while ((*num_stack)->size >= 1 && *oper_stack != NULL &&
           prior <= (*oper_stack)->priority && !stop) {
      // printf("\n prior = %d, (*oper_stack)->priority = %d", prior,
      //        (*oper_stack)->priority);
      if (prior == BRAC_CLOSE && (*oper_stack)->priority == BRAC_OPEN) {
        pop_operators(oper_stack);
        stop = 1;
        // printf("\n stop = %d", stop);
      }
      if ((*oper_stack) != NULL && !stop) {
        // printf("\n ==================check=====================\n");
        get_operands(num_stack, &a, &b, (*oper_stack)->required_num);
        push_numbers(num_stack, calc(a, b, *oper_stack));
        pop_operators(oper_stack);
      }
    }
  }
}