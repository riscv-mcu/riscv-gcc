/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t ua, ub, uc;
  ua = __rv__swap8(ub);
  ua = __rv__swap16(ub);
  return 0;
}

/* { dg-final { scan-assembler-times "swap8\t" 1 } } */
/* { dg-final { scan-assembler-times "swap16\t" 1 } } */
