/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_kstsav2hi(a, b);
  c = __rv__v_kstsa16(a, b);
  j = __builtin_riscv_kstsav2hi(h, i);
  j = __rv__kstsa16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "kstsa16" 4 } } */
