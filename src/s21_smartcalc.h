#ifndef SRC_S21_SMARTCALC_H_
#define SRC_S21_SMARTCALC_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
  NUMBER = 1, X = 2, PLUS = 3; MINUS, MULT, DIVIDE, POW, MOD, SUM, SUB
} // ПОДУМАТЬ НАД ЭТИМ

typedef struct node_struct { // ПОДУМАТЬ НАД СТРУКТУРОЙ
  double value;
  node *next;
  int priority;
  type_t type;
} node;

node *init(int x);
void push(node **head, int x);
void pop(node **head);
void destroy(node *head);

#endif // SRC_S21_SMARTCALC_H_