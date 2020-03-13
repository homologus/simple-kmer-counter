CFLAGS=-g -Wall -O2
CXXFLAGS=$(CFLAGS) -std=c++11
LIBS=-lz
PROG=kmer-counter

ifneq ($(asan),)
	CFLAGS+=-fsanitize=address
	LIBS+=-fsanitize=address
endif

.PHONY:all clean

all:$(PROG)

kmer-counter:kmer-counter.c khashl.h kseq.h
	$(CC) $(CFLAGS) -o $@ $< $(LIBS)

clean:
	rm -fr *.dSYM $(PROG)
