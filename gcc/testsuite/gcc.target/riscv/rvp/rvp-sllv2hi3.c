/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x2_t a = {0x01, 0x02}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_sllv2hi(a, c);
  b = __rv__v_sll16(a, c);
  e = __builtin_riscv_sllv2hi(d, c);
  e = __rv__sll16(d, c);

  b = __builtin_riscv_v_sllv2hi(a, 2);
  b = __rv__v_sll16(a, 2);
  e = __builtin_riscv_sllv2hi(d, 2);
  e = __rv__sll16(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "sll16\t" 4 } } */
/* { dg-final { scan-assembler-times "slli16\t" 4 } } */
