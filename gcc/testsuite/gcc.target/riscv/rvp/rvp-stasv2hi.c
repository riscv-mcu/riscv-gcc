/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4}, c;
  uint16x2_t e = {0x01, 0x02}, f = {0x01, 0x02}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_sstasv2hi(a, b);
  c = __rv__v_sstas16(a, b);
  g = __builtin_riscv_v_ustasv2hi(e, f);
  g = __rv__v_ustas16(e, f);
  j = __builtin_riscv_stasv2hi(h, i);
  j = __rv__stas16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "stas16" 6 } } */
