// #include "s21_smartcalc.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void delete_space(char *str) {
//   int space = 0;
//   char tmp[strlen(str)];
//   while (str[i] != '\0') {
//     if (str[i] == ' ' && str[i + 1] != ' ') {
//       space = i;
//     }
//     s21_strcpy(str + space, tmp);
//     i++;
//   }
// }

int validation(char *str) {
  int i = 0;
  int stop = 0;
  int dot = 0;
  const char first_char[] = "cstal0123456789(x+- ";
  if (strlen(str) > 255)
    stop = 1;
  while (str[i] != '\0' && !stop) {
    // check first symbol e.g. it's '^' or ')'
    if (strchr(first_char, str[0]) == NULL) {
      stop = 1;
      printf("stop1.");
    }
    if (str[i] >= '0' &&
        str[i] <= '9') { // С 32 ПО 47 СТРОКИ  - ПРОВЕРКА НА ТОЧКУ. НАВЕРНОЕ В
                         // ОТДЕЛЬНУЮ ФУНКИЦЮ ВЫНЕСТИ
      if (str[i + 1] == '.')
        dot++;
    } else {
      if (str[i + 1] == '.') {
        stop = 1;
        printf("stop2.");
      }
    }
    if (strchr("+-*/^ m)", str[i]) != NULL) {
      dot = 0;
    }
    if (dot > 1) {
      stop = 1;
      printf("stop3.");
    }
    i++;
  }
  return stop ? 0 : 1;
}

int main() {
  char str[] = " -5.0 + ^";
  validation(str);
  return 0;
}
