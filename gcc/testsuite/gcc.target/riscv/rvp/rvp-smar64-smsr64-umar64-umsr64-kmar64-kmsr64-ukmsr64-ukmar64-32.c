/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int64_t a64, b64, c64;
  uint64_t ua64, ub64, uc64;
  intXLEN_t a, b, c;
  uintXLEN_t ua, ub, uc;
  c64 = __rv__smar64(a64, b, a64);
  c64 = __rv__smsr64(a64, b, a64);
  uc64 = __rv__umar64(ua64, ub, ua64);
  uc64 = __rv__umsr64(ua64, ub, ua64);
  c64 = __rv__kmar64(a64, b, a64);
  c64 = __rv__kmsr64(a64, b, a64);
  uc64 = __rv__ukmsr64(ua64, ub, ua64);
  uc64 = __rv__ukmar64(ua64, ub, ua64);
  return 0;
}

/* { dg-final { scan-assembler-times "smar64\t" 1 } } */
/* { dg-final { scan-assembler-times "smsr64\t" 1 } } */
/* { dg-final { scan-assembler-times "umar64\t" 1 } } */
/* { dg-final { scan-assembler-times "umsr64\t" 1 } } */
/* { dg-final { scan-assembler-times "kmar64\t" 1 } } */
/* { dg-final { scan-assembler-times "kmsr64\t" 1 } } */
/* { dg-final { scan-assembler-times "ukmar64\t" 1 } } */
/* { dg-final { scan-assembler-times "ukmsr64\t" 1 } } */
