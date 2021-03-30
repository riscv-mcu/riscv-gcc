/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t ua, ub, uc;
  uc = __rv__umul8(ua, ub);
  uc = __rv__umulx8(ua, ub);
  uc = __rv__umul16(ua, ub);
  uc = __rv__umulx16(ua, ub);
  return 0;
}

/* { dg-final { scan-assembler-times "umul8\t" 1 } } */
/* { dg-final { scan-assembler-times "umulx8\t" 1 } } */
/* { dg-final { scan-assembler-times "umul16\t" 1 } } */
/* { dg-final { scan-assembler-times "umulx16\t" 1 } } */
