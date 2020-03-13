CC=gcc
CXX=g++
CFLAGS=-g -Wall -O2 -I..
CXXFLAGS=$(CFLAGS)
PROG=khashl_test kseq_test

all:$(PROG)

khashl_test:khashl_test.c ../khashl.h
		$(CC) $(CFLAGS) -o $@ khashl_test.c

kseq_test:kseq_test.c ../kseq.h
		$(CC) $(CFLAGS) -o $@ kseq_test.c -lz

clean:
	rm -fr *.dSYM $(PROG)
