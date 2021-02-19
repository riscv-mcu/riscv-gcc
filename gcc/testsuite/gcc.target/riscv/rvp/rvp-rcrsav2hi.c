/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_rcrsav2hi(a, b);
  c = __rv__v_rcrsa16(a, b);
  j = __builtin_riscv_rcrsav2hi(h, i);
  j = __rv__rcrsa16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "rcrsa16" 4 } } */
