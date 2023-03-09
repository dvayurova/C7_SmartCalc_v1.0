#include "s21_smartcalc.h"

int main() {
  //   numbers *n1 = NULL;
  //   n1 = init_numbers(1.5);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);
  //   push_numbers(&n1, 2.5);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);
  //   push_numbers(&n1, 3.5);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);
  //   push_numbers(&n1, 4.5);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);
  //   printf("\n ====pop====");
  //   pop_numbers(&n1);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);
  //   pop_numbers(&n1);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);
  //   pop_numbers(&n1);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);
  //   pop_numbers(&n1);
  //   printf("\n num = %f", n1->num);
  //   printf("\n *next_numbers = %p", n1->next_numbers);

  //   operators *op1 = NULL;
  //   op1 = init_operators('+', 1);
  //   printf("\n operator = %c", op1->operator);
  //   printf("\n priority = %d", op1->priority);
  //   printf("\n *next_operator = %p", op1->next_operators);
  //   push_operators(&op1, '-', 1);
  //   printf("\n operator = %c", op1->operator);
  //   printf("\n priority = %d", op1->priority);
  //   printf("\n *next_operator = %p", op1->next_operators);
  //   push_operators(&op1, '*', 2);
  //   printf("\n operator = %c", op1->operator);
  //   printf("\n priority = %d", op1->priority);
  //   printf("\n *next_operator = %p", op1->next_operators);
  //   push_operators(&op1, '^', 3);
  //   printf("\n operator = %c", op1->operator);
  //   printf("\n priority = %d", op1->priority);
  //   printf("\n *next_operator = %p", op1->next_operators);
  //   printf("\n ----peek----");
  //   printf("\n priority = %d", peek_operators(op1));
  //   printf("\n ====pop====");
  //   pop_operators(&op1);
  //   printf("\n operator = %c", op1->operator);
  //   printf("\n priority = %d", op1->priority);
  //   printf("\n *next_operator = %p", op1->next_operators);
  //   printf("\n ----peek----");
  //   printf("\n priority = %d", peek_operators(op1));
  //   pop_operators(&op1);
  //   printf("\n operator = %c", op1->operator);
  //   printf("\n priority = %d", op1->priority);
  //   printf("\n *next_operator = %p", op1->next_operators);
  //   printf("\n ----peek----");
  //   printf("\n priority = %d", peek_operators(op1));

  // char str[] = "sin(cos(-5.42423*(-2^(-1*(10.3242342-15) + sin(4)))))";
  // char str[] = "-1*sin(cos(tan(-x^2)^3)^4)";
  char str[] = "sin(X)^2+cos(X)^2";
  int valid = validation(str, 5);
  if (valid == 1) {
    printf("\n correct!");
  } else {
    printf("\n incorrect!");
  }
  printf("\n res= %f ", s21_calculator(str, 5));

  // credit_calc(125555.0, 24, 0.24, ANNUITY);
}
