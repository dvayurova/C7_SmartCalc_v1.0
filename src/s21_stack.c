#include "s21_smartcalc.h"

// функции которые писала на басике, надо проверить еще и на нулл проверки
// добавить и тд тп
node *init(int x) {
  node *head = (node *)calloc(sizeof(node));
  head->value = x;
  head->next = NULL;
  return head;
}

void push(node **head, int x) {
  node *tmp = (node *)calloc(sizeof(node));
  tmp->value = x;
  tmp->next = *head;
  *head = tmp;
}
void pop(node **head) {
  node *tmp = *head;
  *head = (*head)->next;
  free(tmp);
}

void destroy(node *head) {
  while (head != NULL) {
    destroy(head->next);
    free(head);
  }
  head = NULL;
}
