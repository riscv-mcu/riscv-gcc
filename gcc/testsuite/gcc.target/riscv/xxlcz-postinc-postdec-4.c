/* { dg-do compile } */
/* { dg-options "-march=rv32imafdc_zfhmin_xxlczpstinc -mabi=ilp32d -O2" } */
/* { dg-skip-if "" { *-*-* } { "-funroll-loops" } } */

#include <stdint.h>

// xl.fld + xl.fsd
int64_t __attribute__((noinline))
xxlcz_load_store_df_inc (double *ptr,double *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

// xl.fld + xl.fsd
int64_t __attribute__((noinline))
xxlcz_load_store_df_dec (double *ptr,double *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
}

// xl.flw + xl.fsw
int64_t __attribute__((noinline))
xxlcz_load_store_sf_inc (float *ptr,float *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

// xl.flw + xl.fsw
int64_t __attribute__((noinline))
xxlcz_load_store_sf_dec (float *ptr,float *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
}

// xl.flh + xl.fsh
int64_t __attribute__((noinline))
xxlcz_load_store_hf_inc (_Float16 *ptr,_Float16 *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
}

// xl.flh + xl.fsh
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
/* { dg-final { scan-assembler-times "xl\\.flw" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.fsw" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.fld" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.fsd" 2 } } */
