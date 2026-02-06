/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczpstinc -mabi=ilp32 -O2" } */

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

/* { dg-final { scan-assembler-times "xl\\.lw" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lh" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lhu" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lb" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.lbu" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.sw" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.sh" 4 } } */
/* { dg-final { scan-assembler-times "xl\\.sb" 4 } } */
