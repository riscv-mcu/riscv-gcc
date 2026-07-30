/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32imac_xxlczbitop -mabi=ilp32 -O2 -mautogen-xxlcz" } */

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

/* { dg-final { scan-assembler-times "xl\\.extractu" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.extract" 2 } } */

