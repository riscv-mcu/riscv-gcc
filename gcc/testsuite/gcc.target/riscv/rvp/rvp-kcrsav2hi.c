/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_kcrsav2hi(a, b);
  c = __rv__v_kcrsa16(a, b);
  j = __builtin_riscv_kcrsav2hi(h, i);
  j = __rv__kcrsa16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "kcrsa16" 4 } } */
