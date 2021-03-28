/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int64_t a, b, c;
  uintXLEN_t ua, ub, uc;
  c = __rv__smalda(a, ua, ub);
  c = __rv__smalxda(a, ua, ub);
  c = __rv__smalds(a, ua, ub);
  c = __rv__smaldrs(a, ua, ub);
  c = __rv__smalxds(a, ua, ub);
  return 0;
}

/* { dg-final { scan-assembler-times "smalda\t" 1 } } */
/* { dg-final { scan-assembler-times "smalxda\t" 1 } } */
/* { dg-final { scan-assembler-times "smalds\t" 1 } } */
/* { dg-final { scan-assembler-times "smaldrs\t" 1 } } */
/* { dg-final { scan-assembler-times "smalxds\t" 1 } } */
