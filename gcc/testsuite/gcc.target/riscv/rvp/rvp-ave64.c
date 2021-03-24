/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int32_t a, b, c;
  intXLEN_t xa, xb, xc;
  uint32_t ua, ub, uc;
  uintXLEN_t uxa, uxb, uxc;
  xa = __rv__ave(xb, xc);
  return 0;
}

/* { dg-final { scan-assembler-times "ave\t" 1 } } */
