/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4}, c;
  uint16x2_t e = {0x01, 0x02}, f = {0x01, 0x02}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __rv__v_scras16(a, b);
  g = __rv__v_ucras16(e, f);
  j = __rv__cras16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "cras16" 3 } } */
