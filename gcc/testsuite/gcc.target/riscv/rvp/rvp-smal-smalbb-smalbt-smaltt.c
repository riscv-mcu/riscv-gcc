/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int64_t a, b, c;
  uintXLEN_t ua, ub, uc;
  c = __rv__smal(a, b);
  c = __rv__smalbb(a, ua, ub);
  c = __rv__smalbt(a, ua, ub);
  c = __rv__smaltt(a, ua, ub);
  return 0;
}

/* { dg-final { scan-assembler-times "smal\t" 1 } } */
/* { dg-final { scan-assembler-times "smalbb\t" 1 } } */
/* { dg-final { scan-assembler-times "smalbt\t" 1 } } */
/* { dg-final { scan-assembler-times "smaltt\t" 1 } } */
