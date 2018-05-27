CC=gcc
FLAGS=-Wall -Werror -Wextra -Wpedantic
COMPILE=$(CC) $(FLAGS)

.PHONY: all	clean	memcheck

all:	vector_test

memcheck:	vector_test
	valgrind --leak-check=full ./vector_test

vector_test:	vector_test.o	vector.o
	$(COMPILE) vector_test.o vector.o -o vector_test

vector.o:	vector.c
	$(COMPILE) -c vector.c

vector_test.o:	vector_test.c
	$(COMPILE) -c vector_test.c

clean:
	rm -rf *.o *.gch vector_test