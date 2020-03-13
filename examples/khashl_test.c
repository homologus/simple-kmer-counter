#include <stdio.h>
#include <stdint.h>
#include <zlib.h>

#include "khashl.h" // hash table
KHASHL_MAP_INIT(, kc_c1_t, kc_c1, uint64_t, uint32_t, kh_hash_uint64, kh_eq_generic)

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
