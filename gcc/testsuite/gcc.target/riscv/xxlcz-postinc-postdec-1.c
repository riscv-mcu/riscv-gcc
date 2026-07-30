/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczpstinc -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* { dg-skip-if "" { *-*-* } { "-funroll-loops" } } */

#include <stdint.h>

//xl.lw and xl.sw inc
int32_t __attribute__((noinline))
xxlcz_load_store_si_inc (int32_t *ptr,int32_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
    return 0;
}

//xl.lw and xl.sw dec
int32_t __attribute__((noinline))
xxlcz_load_store_si_dec (int32_t *ptr,int32_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
    return 0;
}

//xl.lh and xl.sh inc
int16_t __attribute__((noinline))
xxlcz_load_store_hi_inc (int16_t *ptr, int16_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
    return 0;
}

//xl.lh and xl.sh dec
int16_t __attribute__((noinline))
xxlcz_load_store_hi_dec (int16_t *ptr, int16_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
    return 0;
}

// xl.lhu + xl.sh inc
uint16_t __attribute__((noinline))
xxlcz_load_store_uhi_inc (uint16_t *ptr, uint16_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
        //*src-- = *ptr--;
    }
    return 0;
}

// xl.lhu + xl.sh dec
uint16_t __attribute__((noinline))
xxlcz_load_store_uhi_dec (uint16_t *ptr, uint16_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
    return 0;
}

// xl.lb + xl.sb inc
int8_t __attribute__((noinline))
xxlcz_load_store_qi_inc (int8_t *ptr, int8_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
    return 0;
}

// xl.lb + xl.sb dec
int8_t __attribute__((noinline))
xxlcz_load_store_qi_dec (int8_t *ptr, int8_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
    return 0;
}

// xl.lbu + xl.sb inc
uint8_t __attribute__((noinline))
xxlcz_load_store_uqi_inc (uint8_t *ptr, uint8_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src++ = *ptr++;
    }
    return 0;
}

// xl.lbu + xl.sb dec
uint8_t __attribute__((noinline))
xxlcz_load_store_uqi_dec (uint8_t *ptr, uint8_t *src, int n)
{
    for (int i = 0; i < n; i++)
    {
        *src-- = *ptr--;
    }
    return 0;
}

/* { dg-final { scan-assembler-times "xl\\.lw\t" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lh\t" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lhu\t" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lb\t" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lbu\t" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.sw\t" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.sh\t" 4 } } */
/* { dg-final { scan-assembler-times "xl\\.sb\t" 4 } } */
