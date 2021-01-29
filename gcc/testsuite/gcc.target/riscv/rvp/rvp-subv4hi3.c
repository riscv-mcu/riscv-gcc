/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2, -3, 4}, b = {1, -2, 3, -4}, c;
  uint16x4_t e = {0x01, 0x02, 0x03, 0x04}, f = {0x01, 0x02, 0x03, 0x04}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = a - b;
  c = __rv__v_ssub16(a, b);

  g = f - g;
  g = __rv__v_usub16(e, f);

  j = __rv__sub16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "sub16" 5 } } */
