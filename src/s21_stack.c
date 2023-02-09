#include "s21_smartcalc.h"

void push_numbers(numbers **head, double x) {
  numbers *tmp = (numbers *)calloc(1, sizeof(numbers));
  tmp->num = x;
  if (*head == NULL) {
    tmp->size = 1;
    tmp->next_numbers = NULL;
    *head = tmp;
  } else {
    tmp->size = (*head)->size + 1;
    tmp->next_numbers = *head;
    *head = tmp;
  }
  printf("\n num in stack after push = %f, size = %d", (*head)->num,
         (*head)->size);
}
void pop_numbers(numbers **head) {
  if (*head != NULL) {
    numbers *tmp = *head;
    (*head)->size -= 1;
    *head = (*head)->next_numbers;
    free(tmp);
    printf("\n pop_numbers done!");
  }
}

// void destroy(numbers *head) {
//   while (head != NULL) {
//     destroy(head->next_numbers);
//     free(head);
//   }
//   head = NULL;
// }

void push_operators(operators **head, int opr, int prior, numbers **num_stack) {
  // printf("\n operator in stack = %c", (*head)->operator);
  // printf("\n priority in stack = %d", (*head)->priority);
  // printf("\n *next_operator = %p", (*head)->next_operators);
  double a = 0;
  double b = 0;
  operators *tmp = (operators *)calloc(1, sizeof(operators));
  while ((*num_stack)->size > 1 && prior <= (*head)->priority) {
    get_operands(num_stack, &a, &b);
    push_numbers(num_stack, calc(a, b, *head));
    pop_operators(head);
  }
  tmp->operator= opr;
  tmp->priority = prior;
  if (*head == NULL) {
    *head = tmp;
    tmp->size = 1;
  } else {
    tmp->size = (*head)->size + 1;
    tmp->next_operators = *head;
    *head = tmp;
  }
  printf("\n After push");
  printf("\n operator in stack = %c", (*head)->operator);
  printf("\n priority in stack = %d, size = %d", (*head)->priority,
         (*head)->size);
  // printf("\n *next_operator = %p", (*head)->next_operators);
}

// int peek_operators(operators *head) { return head->priority; }

int pop_operators(operators **head) {
  int res = 0;
  if (*head != NULL) {
    operators *tmp = *head;
    (*head)->size -= 1;
    *head = (*head)->next_operators;
    free(tmp);
    printf("\n pop_operators done!");
  }
  return res;
}