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
  char str[] = "6/2 + 1";
  parcer(str);
}