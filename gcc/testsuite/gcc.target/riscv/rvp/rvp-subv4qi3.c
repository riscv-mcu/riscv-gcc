/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int8x4_t a = {-1, 2, -3, 4}, b = {1, -2, 3, -4}, c;
  uint8x4_t e = {0x01, 0x02, 0x03, 0x04}, f = {0x01, 0x02, 0x03, 0x04}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = a - b;
  c = __builtin_riscv_v_ssubv4qi(a, b);
  c = __rv__v_ssub8(a, b);

  g = f - g;
  g = __builtin_riscv_v_usubv4qi(e, f);
  g = __rv__v_usub8(e, f);

  j = __builtin_riscv_subv4qi(h, i);
  j = __rv__sub8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "sub8" 8 } } */
