
CC=clang
CFLAGS=-std=c99 -pedantic -Wall -Isrc
SOURCES=src/ttt.c
TEST_SOURCES=tests/test_main.c tests/tests.c

all:

check: tests/tests

tests/tests: tests/test_main.c tests/tests.c tests/tests.h
	$(CC) $(CFLAGS) $(TEST_SOURCES) $(SOURCES) -o $@
	tests/tests

