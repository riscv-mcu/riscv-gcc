/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int32_t a, b;
  intXLEN_t c;
  uint32_t ua, ub;
  uintXLEN_t uc;
  c = __rv__kaddw(a, b);
  c = __rv__ksubw(a, b);
  uc = __rv__ukaddw(ua, ub);
  uc = __rv__uksubw(ua, ub);
  return 0;
}

/* { dg-final { scan-assembler-times "kaddw\t" 1 } } */
/* { dg-final { scan-assembler-times "ksubw\t" 1 } } */
/* { dg-final { scan-assembler-times "ukaddw\t" 1 } } */
/* { dg-final { scan-assembler-times "uksubw\t" 1 } } */
