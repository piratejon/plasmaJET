
CC=clang
CFLAGS=-std=c99 -pedantic -Wall

all:

check: tests/tests

tests/tests: tests/test_main.c tests/tests.c tests/tests.h
	$(CC) $(CFLAGS) tests/test_main.c tests/tests.c -o $@
	tests/tests

