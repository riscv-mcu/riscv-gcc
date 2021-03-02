/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4};
  uint16x2_t e = {0x01, 0x02}, f = {0x01, 0x02}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_cmpeqv2hi(h, i);
  j = __rv__cmpeq16(h, i);

  g = __builtin_riscv_v_scmpeqv2hi(a, b);
  g = __rv__v_scmpeq16(a, b);

  g = __builtin_riscv_v_ucmpeqv2hi(e, f);
  g = __rv__v_ucmpeq16(e, f);

  return 0;
}

/* { dg-final { scan-assembler-times "cmpeq16" 6 } } */
