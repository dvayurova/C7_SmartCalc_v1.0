.PHONY: all s21_smarcalc.a test gcov_report check rebuild clean test.o install uninstall dist dvi
CC = gcc
CFLAGS = -Wall -Werror -Wextra -std=c11 -g
GCOVFLAGS =  -fprofile-arcs -ftest-coverage 
LC = lcov -c -d .
C_FILES = ./SmartCalc/s21*.c
O_FILES = s21*.o
LIBS=-lcheck
LINUX=-lcheck -lm -lpthread -lrt
OS=$(shell uname -s)

all : s21_smarcalc.a 
clean : 
	rm -rf *.o *.gcno *.gcda *.info test.out s21_smarcalc.a
	rm -rf ./report
	rm -rf *.dSYM
rebuild : clean all

$(O_FILES) :
	$(CC) $(CFLAGS) -c $(C_FILES) ./SmartCalc/s21_smarcalc.h
test.o :
	$(CC) $(CFLAGS) -c -lcheck test.c
s21_smarcalc.a :
	$(CC) $(CFLAGS) -c $(C_FILES)
	ar r s21_smarcalc.a $(O_FILES)

test: s21_smarcalc.a test.c
ifeq ($(OS), Darwin)
	$(CC) $(CFLAGS) test.c s21_smarcalc.a -o test.out $(LIBS)
else
	$(CC) $(CFLAGS) test.c s21_smarcalc.a -o test.out $(LIBS) $(LINUX)
endif
	./test.out	

gcov_report : clean
	$(CC) $(CFLAGS) $(GCOVFLAGS) -o gcov_test -lcheck $(C_FILES) test.c
	./gcov_test 
	$(LC) -t "gcov_report" --no-external -o report.info
	genhtml -o gcov_report report.info
	rm -f *.gcno *.gcda *.info report.out *.gcov
	open ./gcov_report/index-sort-f.html

install: uninstall
	make clean
	mkdir build
	cd SmartCalc && qmake && make && make clean && rm Makefile && cd ../ && mv SmartCalc/SmartCalc.app build

uninstall:
	rm -rf build*

dist:
	rm -rf Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/
	mkdir Archive_SmartCalc_v1.0/src
	mv ./build/SmartCalc.app Archive_SmartCalc_v1.0/src/
	tar cvzf Archive_SmartCalc_v1.0.tgz Archive_SmartCalc_v1.0/
	rm -rf Archive_SmartCalc_v1.0/

dvi:
	open readme_calc.md


check:
	cp ../materials/linters/.clang-format ./
	clang-format -i ./*.c
	clang-format -i ./SmartCalc/*.cpp
	clang-format -i ./SmartCalc/*.c
	clang-format -i ./SmartCalc/*.h
