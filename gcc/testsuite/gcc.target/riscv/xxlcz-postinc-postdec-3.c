/* { dg-do compile } */
/* { dg-options "-march=rv64imafdc_zfhmin_xxlczpstinc -mabi=lp64d -O2 -mautogen-xxlcz" } */
/* { dg-skip-if "" { *-*-* } { "-funroll-loops" } } */

#include <stdint.h>

int64_t __attribute__((noinline))
xxlcz_load_store_hf_inc (_Float16 *ptr,_Float16 *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

int64_t __attribute__((noinline))
xxlcz_load_store_hf_dec (_Float16 *ptr,_Float16 *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
}

/* { dg-final { scan-assembler-times "xl\\.flh" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.fsh" 2 } } */