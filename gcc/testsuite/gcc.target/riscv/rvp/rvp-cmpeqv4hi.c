/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2, 3, -4}, b = {1, 2, -3, 4};
  uint16x4_t e = {0x01, 0x02, 0x03, 0x04}, f = {0x03, 0x04, 0x01, 0x02}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_cmpeqv4hi(h, i);
  j = __rv__cmpeq16(h, i);

  g = __builtin_riscv_v_scmpeqv4hi(a, b);
  g = __rv__v_scmpeq16(a, b);

  g = __builtin_riscv_v_ucmpeqv4hi(e, f);
  g = __rv__v_ucmpeq16(e, f);

  return 0;
}

/* { dg-final { scan-assembler-times "cmpeq16" 6 } } */
