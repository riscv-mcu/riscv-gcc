/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int8x4_t a = {-1, 2, -3, 4}, b = {1, -2, 3, -4}, c;
  uint8x4_t e = {0x01, 0x02, 0x03, 0x04}, f = {0x01, 0x02, 0x03, 0x04}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = a + b;
  c = __rv__sadd8(a, b);

  g = f + g;
  g = __rv__uadd8(e, f);

  j = __rv__add8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "add8" 5 } } */
