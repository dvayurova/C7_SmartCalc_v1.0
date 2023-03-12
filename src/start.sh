#!/bin/bash

make s21_smarcalc.a
gcc -g ./test.c s21_smarcalc.a -o test.out -lcheck -lcheck -lpthread -lm -D_GNU_SOURCE -lrt
CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./test.out
