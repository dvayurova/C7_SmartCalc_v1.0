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
} numbers;

typedef struct struct_opr {
  int operator;
  struct struct_opr *next_operators;
  int priority;
} operators;

// stack
numbers *init_numbers(double x);
void push_numbers(numbers **head, double x);
void pop_numbers(numbers **head);
// void destroy(numbers *head);
operators *init_operators(int opr, int prior);
void push_operators(operators **head, int opr, int prior);
int peek_operators(operators *head);
void pop_operators(operators **head);

// parcer
void parcer(char *str);
int is_number(char c);
int to_number(char *str, double *num);
int parse_operator(char *str, int *i, operators **oper_stack);

#endif // SRC_S21_SMARTCALC_H_