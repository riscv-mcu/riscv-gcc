/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int32_t a, b, c;
  intXLEN_t xa, xb, xc;
  uint32_t ua, ub, uc;
  uintXLEN_t uxa, uxb, uxc;
  xa = __rv__sra_u(xb, ub);
  xa = __rv__sra_u(xb, 1);
  return 0;
}

/* { dg-final { scan-assembler-times "sra.u\t" 1 } } */
/* { dg-final { scan-assembler-times "srai.u\t" 1 } } */
