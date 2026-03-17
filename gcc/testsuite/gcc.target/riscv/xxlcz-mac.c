/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczmac -mabi=ilp32 -O2 -mtune=nuclei-100-series" } */

int foo (int a)
{
  return a * 7;
}

/* { dg-final { scan-assembler-times "xl\\.muli" 1 } } */
