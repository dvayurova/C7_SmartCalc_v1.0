#ifndef SRC_SMARTCALC_H_
#define SRC_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  PLUS = 1,
  MULT,
  MINUS = 1,
  DIV,
  MOD = 2,
  EXP,
  FUNCS,
  BRAC_OPEN = -10,
  BRAC_CLOSE = -20,
  ANNUITY = 10,
  DIFFER = 20
};

typedef struct struct_num {
  double num;
  struct struct_num *next_numbers;
  int size;
} numbers;

typedef struct struct_opr {
  int oper;
  struct struct_opr *next_operators;
  int priority;
  int size;
  int required_num;
} operators;

double s21_calculator(char *str, char *str_x);
// stack
void push_numbers(numbers **head, double x);
void pop_numbers(numbers **head);
// void destroy(numbers *head);
void push_operators(operators **head, int opr, int prior, int required_nums);
// int peek_operators(operators *head);
int pop_operators(operators **head);

// parcer
void parcer(char *str, double x, numbers **num_stack, operators **oper_stack);
int is_number(char c);
int to_number(char *str, double *num);
int parse_operator(char *str, int *i, operators **oper_stack,
                   numbers **num_stack);
void push_operators(operators **head, int opr, int prior, int required_nums);
void push_logic(int *i, operators **oper_stack, numbers **num_stack, int n,
                int opr, int prior, int required_nums);
int is_sign(int i, char *str);
// calc
void get_operands(numbers **num_stack, double *a, double *b, int required_num);
double calc(double a, double b, operators *oper_stack);
double count_result(numbers **num_stack, operators **oper_stack);
void calc_before_push(numbers **num_stack, operators **oper_stack, int prior);

// credit calc
void credit_calc(double amount, int term, double rate, int type);

#endif // SRC_SMARTCALC_H_
