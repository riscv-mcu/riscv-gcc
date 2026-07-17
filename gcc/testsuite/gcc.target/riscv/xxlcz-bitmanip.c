/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32imac_xxlczbitop -mabi=ilp32 -O2" } */
/* { dg-final { scan-assembler-times "xl\\.extractu" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.extract" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.bset" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.bclr" 2 } } */
/* { dg-final { scan-assembler-times "xl\\.ff1" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.fl1" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.ff0" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.fl0" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.clb" 1 } } */

#include <stdint.h>

/* ------------ extract ------------ */
unsigned int extract_5bits(unsigned int x)
{
        return (x >> 3) & 0x1F;  // 0x1F = (1 << 5) - 1
}

int extract_5bits_signed(unsigned int x)
{
        return (int)(((x >> 3) & 0x1F) << (32 - 5)) >> (32 - 5);
}

struct S {
        int field1: 5;
        int field2: 10;
};
int get_field2(struct S s) {
        return s.field2;
}

/* ------------ bset/bclr ------------ */
uint32_t test_bset_16bits(uint32_t x)
{
        // 16 bits at offset 8 -> xl.bset
        return x | (((1 << 16) - 1) << 8);
}

uint32_t test_bclr_12bits(uint32_t x)
{
        // 12 bits at offset 10 -> xl.bclr
        return x & ~(((1 << 12) - 1) << 10);
}

uint32_t test_bset_large(uint32_t x)
{
        // 10 bits at offset 5 -> xl.bset
        return x | (((1 << 10) - 1) << 5);
}

uint32_t test_bclr_large(uint32_t x)
{
        // 10 bits at offset 5 -> xl.bclr
        return x & ~(((1 << 10) - 1) << 5);
}


uint32_t test_bset_7bits(uint32_t x) {
    return x | (((1 << 7) - 1) << 10);
}

uint32_t test_bclr_5bits(uint32_t x) {
    return x & ~(((1 << 5) - 1) << 20);
}


/* ------------ find bits ------------ */
int test_ff1(uint32_t x)
{
        // __builtin_clz -> xl.ff1
        return __builtin_clz(x);
}

int test_fl1(uint32_t x)
{
        // __builtin_ctz -> xl.fl1
        return __builtin_ctz(x);
}

int test_ff0(uint32_t x)
{
        // explicit builtin -> xl.ff0
        return __builtin_xxlcz_ff0(x);
}

int test_fl0(uint32_t x)
{
        // explicit builtin -> xl.fl0
        return __builtin_xxlcz_fl0(x);
}

/* ------------ count leading bits ------------ */
int test_clb(uint32_t x)
{
        // explicit builtin -> xl.clb
        return __builtin_xxlcz_clb(x);
}
