#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { PLUS = 1, MULT, MINUS = 1, DIV, MOD = 2, EXP, FUNCS };

typedef struct struct_num {
  double num;
  struct struct_num *next_numbers;
  int size;
} numbers;

typedef struct struct_opr {
  int operator;
  struct struct_opr *next_operators;
  int priority;
  int size;
} operators;

// stack
void push_numbers(numbers **head, double x);
void pop_numbers(numbers **head);
// void destroy(numbers *head);
void push_operators(operators **head, int opr, int prior, numbers **num_stack);
// int peek_operators(operators *head);
int pop_operators(operators **head);

// parcer
void parcer(char *str);
int is_number(char c);
int to_number(char *str, double *num);
int parse_operator(char *str, int *i, operators **oper_stack,
                   numbers **num_stack);

// calc
void get_operands(numbers **num_stack, double *a, double *b);
double calc(double a, double b, operators *oper_stack);
double count_result(numbers **num_stack, operators **oper_stack);

#endif // SRC_S21_SMARTCALC_H_