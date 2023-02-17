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
  // printf("\n num in stack after push = %f, size = %d", (*head)->num,
  //        (*head)->size);
}
void pop_numbers(numbers **head) {
  if (*head != NULL) {
    numbers *tmp = *head;
    (*head)->size -= 1;
    *head = (*head)->next_numbers;
    free(tmp);
    // printf("\n pop_numbers done!");
  }
}

// void destroy(numbers *head) {
//   while (head != NULL) {
//     destroy(head->next_numbers);
//     free(head);
//   }
//   head = NULL;
// }

void push_operators(operators **head, int opr, int prior, int required_nums) {
  // printf("\n operator in stack = %c", (*head)->operator);
  // printf("\n priority in stack = %d", (*head)->priority);
  // printf("\n *next_operator = %p", (*head)->next_operators);

  operators *tmp = (operators *)calloc(1, sizeof(operators));

  tmp->operator= opr;
  tmp->priority = prior;
  tmp->required_num = required_nums;
  if (*head == NULL) {
    // printf("\n check IF!!");
    tmp->next_operators = NULL;
    tmp->size = 1;
    *head = tmp;
  } else {
    // printf("\n check ELSE!!");
    tmp->size = (*head)->size + 1;
    tmp->next_operators = *head;
    *head = tmp;
  }
  // printf("\n After push");
  // printf(": operator in stack = %c", (*head)->operator);
  // printf(", priority in stack = %d, size = %d, required_nums = %d",
  //        (*head)->priority, (*head)->size, (*head)->required_num);
  // printf("\n *next_operator = %p", (*head)->next_operators);
}

// int peek_operators(operators *head) { return head->priority; }

int pop_operators(operators **head) {
  int res = 0;
  if (*head != NULL) {
    if ((*head)->next_operators == NULL) {
      free(*head);
      *head = NULL;
      // printf("\n pop_operators LAST done!");
    } else {
      operators *tmp = *head;
      (*head)->size -= 1;
      *head = (*head)->next_operators;
      free(tmp);
      // printf("\n pop_operators done!, size = %d", (*head)->size);
    }
  }

  return res;
}