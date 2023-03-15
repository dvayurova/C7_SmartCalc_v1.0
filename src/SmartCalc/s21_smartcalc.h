#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

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
  DIFFER = 20,
  WITHCAPITAL = 30,
  WITHOUTCAPITAL = 40,
  DAILY = 50,
  MONTHLY = 60
};

typedef struct struct_num {
  double num;
  struct struct_num *next_numbers;
  int size;
} numbers;

typedef struct struct_opr {
  int operations;
  struct struct_opr *next_operators;
  int priority;
  int size;
  int required_num;
} operators;

typedef struct struct_credit {
  double monthlyPayment;
  double monthlyPaymentFirst;
  double monthlyPaymentLast;
  double overPayment;
  double totalPayment;
} creditValues;

typedef struct struct_deposit {
  double totalInterestAmount;
  double taxAmount;
  double finalAmount;
} depositValues;

typedef struct amountChangeStruct {
  int day;
  int month;
  int year;
  double summ;
} replenishmentsListValues;

typedef struct date_struct {
  int day;
  int month;
  int year;
} dateStruct;

// validation
int validation(char *str);
int divide_zero(int divide, double num);
int correct_dot(char *str);
int incorrect_brackets(char *str);
int incorrect_function(char *str);
int missed_numbers(char *str);

double s21_calculator(char *str, double x);
// stack
void push_numbers(numbers **head, double x);
void pop_numbers(numbers **head);
void push_operators(operators **head, int opr, int prior, int required_nums);
int pop_operators(operators **head);

// parcer
void parcer(char *str, double x, numbers **num_stack, operators **oper_stack);
int is_number(char c);
void to_number(char *str, double *num);
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
creditValues credit_calc(double amount, int term, double rate, int type);

// deposit calc
depositValues deposit_calc(double amount, int term, double rate, double taxRate,
                           int paymentPeriod, int capitalization,
                           char *replenishmentsList);
int replenishmentsListParcer(char *replenishmentsList,
                             replenishmentsListValues *amountList);
double dailyInterest(double currentSumm, double rate, int year);
void countCurrentSumm(double *summ, replenishmentsListValues *amountList,
                      int replenishmentsNumber, dateStruct today);
void getDay(dateStruct *today, int term);
int leapYear(int year);
void capitalizationFunc(int capitalization, double *summ,
                        double dailyInterestSumm);
double monthlyInterest(double currentSumm, double rate, int year,
                       int daysInMonth);

#endif  // SRC_S21_SMARTCALC_H_