/* { dg-do compile } */
/* { dg-options "-march=rv64imafdc_xxlczpstinc -mabi=lp64d -O2" } */
/* { dg-skip-if "" { *-*-* } { "-funroll-loops" } } */

#include <stdint.h>

// xl.ld + xl.sd inc
int64_t __attribute__((noinline))
xxlcz_load_store_di_inc (int64_t *ptr,int64_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

// xl.ld + xl.sd dec
int64_t __attribute__((noinline))
xxlcz_load_store_di_dec (int64_t *ptr,int64_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
}

//xl.fld + xl.fsd inc
int64_t __attribute__((noinline))
xxlcz_load_store_df_inc (double *ptr,double *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

//xl.fld + xl.fsd dec
int64_t __attribute__((noinline))
xxlcz_load_store_df_dec (double *ptr,double *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
}

//xl.flw + xl.fsw inc
int64_t __attribute__((noinline))
xxlcz_load_store_sf_inc (float *ptr,float *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

//xl.flw + xl.fsw dec
int64_t __attribute__((noinline))
xxlcz_load_store_sf_dec (float *ptr,float *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
}

// xl.lwu + xl.sd
int64_t __attribute__((noinline))
xxlcz_load_store_lwu_inc (uint32_t *ptr,uint64_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

// xl.lwu + xl.sd 
int64_t __attribute__((noinline))
xxlcz_load_store_lwu_dec (uint32_t *ptr,uint64_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
}

/* { dg-final { scan-assembler-times "xl\\.ld" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.sd" 4 } } */
/* { dg-final { scan-assembler-times "xl\\.fld" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.fsd" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.flw" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.fsw" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lwu" 2 } } */
