/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64imac_xxlczbitop -mabi=lp64 -O2 -mautogen-xxlcz" } */
/* { dg-final { scan-assembler-times "xl\\.extractu" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.extract" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.bset" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.bclr" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.ff1" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.fl1" 1 } } */

#include <stdint.h>

uint64_t extract_10bits(uint64_t x)
{
        return (x >> 10) & 0x3FF;
}

int64_t extract_12bits_signed(uint64_t x)
{
        return (int64_t)(((x >> 20) & ((1LL << 12) - 1)) << (64 - 12)) >> (64 - 12);
}

uint64_t test_bset_20bits(uint64_t x)
{
        // 20 bits at offset 12
        return x | (((1LL << 20) - 1) << 12);
}

uint64_t test_bclr_20bits(uint64_t x)
{
        // 20 bits at offset 12
        return x & ~(((1LL << 20) - 1) << 12);
}

int test_clz_64(uint64_t x)
{
        // __builtin_clzll -> xl.ff1 + xori (ff1 = MSB set bit index, clz = 63 - index)
        return __builtin_clzll(x);
}

int test_ctz_64(uint64_t x)
{
        // __builtin_ctzll -> xl.fl1 (fl1 = lowest set bit index)
        return __builtin_ctzll(x);
}
