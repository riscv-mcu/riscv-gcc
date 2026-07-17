/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczbitrev -mabi=ilp32 -O2" } */

int foo (unsigned int a)
{
  return __builtin_xxlcz_bitrev(a, 1, 2);
}

/* { dg-final { scan-assembler-times "xl\\.bitrev" 1 } } */
