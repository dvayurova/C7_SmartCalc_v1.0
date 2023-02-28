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
}
void pop_numbers(numbers **head) {
  if (*head != NULL) {
    numbers *tmp = *head;
    (*head)->size -= 1;
    *head = (*head)->next_numbers;
    free(tmp);
  }
}

void push_operators(operators **head, int opr, int prior, int required_nums) {
  operators *tmp = (operators *)calloc(1, sizeof(operators));
  tmp->operations = opr;
  tmp->priority = prior;
  tmp->required_num = required_nums;
  if (*head == NULL) {
    tmp->next_operators = NULL;
    tmp->size = 1;
    *head = tmp;
  } else {
    tmp->size = (*head)->size + 1;
    tmp->next_operators = *head;
    *head = tmp;
  }
}

int pop_operators(operators **head) {
  int res = 0;
  if (*head != NULL) {
    if ((*head)->next_operators == NULL) {
      free(*head);
      *head = NULL;
    } else {
      operators *tmp = *head;
      (*head)->size -= 1;
      *head = (*head)->next_operators;
      free(tmp);
    }
  }
  return res;
}