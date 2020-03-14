// Copyright attractivechaos - http://attractivechaos.github.io/klib/

#include <stdio.h>
#include <stdint.h>
#include <zlib.h>

#include "kseq.h"
KSEQ_INIT(gzFile, gzread)

//////////////////////////////////////////////////////
//
//	Parameters in the above macro -->
//
//	gzFile = type_t in the following data structure
//	gzread = zlib function to read from file (default buffer size 16384)
//	https://refspecs.linuxbase.org/LSB_3.0.0/LSB-Core-generic/LSB-Core-generic/zlib-gzread-1.html
//
//	The above macro declaration gives you -
//
//	1. data structures -->
//
//      typedef struct __kstream_t {
//              unsigned char *buf;
//              int begin, end, is_eof;
//              type_t f;
//      } kstream_t;
//
//      typedef struct { 
//              kstring_t name, comment, seq, qual;
//              int last_char;
//              kstream_t *f;
//      } kseq_t;
//
//	2. functions --> 
//
//      static kseq_t *kseq_init(gzFile fd)
//	static int kseq_read(kseq_t *seq)
//	static void kseq_destroy(kseq_t *ks)
//
//	The following code shows how they are used.
//
//////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
	gzFile fp;
	kseq_t *seq;
	int l;
	fp = gzopen(argv[1], "r");
	seq = kseq_init(fp);
	while ((l = kseq_read(seq)) >= 0) {
	     printf("name: %s\n", seq->name.s);
	     if (seq->comment.l) printf("comment: %s\n", seq->comment.s);
	     printf("seq: %s\n", seq->seq.s);
	     if (seq->qual.l) printf("qual: %s\n", seq->qual.s);
	}
	printf("return value: %d\n", l);
	kseq_destroy(seq);
	gzclose(fp);
	return 0;
}
