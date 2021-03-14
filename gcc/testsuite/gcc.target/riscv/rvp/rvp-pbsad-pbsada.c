/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t a, b, c;
  c = __rv__pbsad(a, b);
  c = __builtin_riscv_pbsadasi(a, a, b);
  return 0;
}

/* { dg-final { scan-assembler-times "pbsad\t" 1 } } */
/* { dg-final { scan-assembler-times "pbsada\t" 1 } } */
