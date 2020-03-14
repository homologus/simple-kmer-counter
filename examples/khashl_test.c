#include <stdio.h>
#include <stdint.h>
#include <zlib.h>

#include "khashl.h" // hash table
KHASHL_MAP_INIT(, kc_c1_t, kc_c1, uint64_t, uint32_t, kh_hash_uint64, kh_eq_generic)

//////////////////////////////////////////////////////
//
//	The parameters in the above macro -->
//
//	ignored first parameter = SCOPE for functions (e.g. static)
//	kc_c1_t = name for data structures
//	kc_c1 = prefix for functions
//	uint64_t = khkey_t (hash key type)
//	uint32_t = kh_val_t(hash value type)
//	kh_hash_uint64 = see below
//	kh_eq_generic = see below
//
//	kh_eq_generic = kh_eq_generic(a, b) ((a) == (b))
//
//	static kh_inline khint_t kh_hash_uint64(khint64_t key) {
//		key = ~key + (key << 21);
//		key = key ^ key >> 24;
//        	key = (key + (key << 3)) + (key << 8);
//        	key = key ^ key >> 14;
//        	key = (key + (key << 2)) + (key << 4);
//        	key = key ^ key >> 28;
//        	key = key + (key << 31);
//        	return (khint_t)key;
//	}
//
//      The macro declaration gives you -
//
//      1. data structures -->
//
//        	typedef struct { \
//                	khint_t bits, count; \
//                	khint32_t *used; \
//                	khkey_t *keys; \
//        	} kc_c1_t;

//
//      2. functions -->
//
//      extern kc_c1_t *kc_c1_init(void); \
//      extern void kc_c1_destroy(kc_c1_t *h); \
//      extern void kc_c1_clear(kc_c1_t *h); \
//      extern khint_t kc_c1_getp(const kc_c1_t *h, const khkey_t *key); \
//      extern int kc_c1_resize(kc_c1_t *h, khint_t new_n_buckets); \
//      extern khint_t kc_c1_putp(kc_c1_t *h, const khkey_t *key, int *absent); \
//      extern void kc_c1_del(kc_c1_t *h, khint_t k);
//
//	kh_bucket(h, x)
//	kh_size(h)
//	kh_capacity(h)
//	kh_end(h)
//	kh_key(h, x)
//	kh_val(h, x)
//////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
        int i, absent;
        khint_t itr, kh;

	kc_c1_t *h=kc_c1_init();

        itr = kc_c1_put(h, 17345623, &absent);
        if (absent) kh_val(h, itr) = 0;
        ++kh_val(h, itr);

        itr = kc_c1_put(h, 17345623, &absent);
        if (absent) kh_val(h, itr) = 0;
        ++kh_val(h, itr);

        uint64_t cnt[256];

        for (i = 0; i < 256; ++i) cnt[i] = 0;
        for (kh = 0; kh < kh_end(h); ++kh)
                if (kh_exist(h, kh))
                        ++cnt[kh_val(h, kh) < 256? kh_val(h, kh) : 255];

        for (i = 1; i < 10; ++i)
                printf("%d\t%ld\n", i, (long)cnt[i]);

	kc_c1_destroy(h);
	return 0;
}

