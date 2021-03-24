/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int32_t a, b, c;
  intXLEN_t xa, xb, xc;
  uint32_t ua, ub, uc;
  uintXLEN_t uxa, uxb, uxc;
  xa = __rv__raddw(a, b);
  xa = __rv__rsubw(a, b);
  uxa = __rv__uraddw(ua, ub);
  uxa = __rv__ursubw(ua, ub);
  return 0;
}

/* { dg-final { scan-assembler-times "raddw\t" 1 } } */
/* { dg-final { scan-assembler-times "rsubw\t" 1 } } */
/* { dg-final { scan-assembler-times "uraddw\t" 1 } } */
/* { dg-final { scan-assembler-times "ursubw\t" 1 } } */
