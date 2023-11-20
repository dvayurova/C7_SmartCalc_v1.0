#include "s21_smartcalc.h"

numbers *init_numbers(double x) {
  numbers *head = (numbers *)calloc(1, sizeof(numbers));
  head->num = x;
  head->next_numbers = NULL;
  return head;
}

void push_numbers(numbers **head, double x) {
  numbers *tmp = (numbers *)calloc(1, sizeof(numbers));
  tmp->num = x;
  tmp->next_numbers = *head;
  *head = tmp;
}
void pop_numbers(numbers **head) {
  if ((*head)->next_numbers != NULL) {
    numbers *tmp = *head;
    *head = (*head)->next_numbers;
    free(tmp);
  }
}

// void destroy(numbers *head) {
//   while (head != NULL) {
//     destroy(head->next_numbers);
//     free(head);
//   }
//   head = NULL;
// }

operators *init_operators(int opr, int prior) {
  operators *head = (operators *)calloc(1, sizeof(operators));
  head->operator= opr;
  head->priority = prior;
  head->next_operators = NULL;
  return head;
}

void push_operators(operators **head, int opr, int prior) {
  // printf("\n operator in stack = %c", (*head)->operator);
  // printf("\n priority in stack = %d", (*head)->priority);
  // printf("\n *next_operator = %p", (*head)->next_operators);
  operators *tmp = (operators *)calloc(1, sizeof(operators));
  tmp->operator= opr;
  tmp->priority = prior;
  tmp->next_operators = *head;
  *head = tmp;
  printf("\n After push");
  printf("\n operator in stack = %c", (*head)->operator);
  printf("\n priority in stack = %d", (*head)->priority);
  // printf("\n *next_operator = %p", (*head)->next_operators);
}

int peek_operators(operators *head) { return head->priority; }

void pop_operators(operators **head) {
  if ((*head)->next_operators != NULL) {
    operators *tmp = *head;
    *head = (*head)->next_operators;
    free(tmp);
  }
}