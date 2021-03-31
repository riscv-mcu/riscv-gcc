/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int64_t a, b, c;
  uint64_t ua, ub, uc;
  c = __rv__ssub64(a, b);
  uc = __rv__usub64(ua, ub);

  c = __rv__rsub64(a, b);
  uc = __rv__ursub64(a, b);

  c = __rv__ksub64(a, b);
  uc = __rv__uksub64(a, b);
  return 0;
}

/* { dg-final { scan-assembler-times "sub64\t" 2 } } */
/* { dg-final { scan-assembler-times "rsub64\t" 1 } } */
/* { dg-final { scan-assembler-times "ursub64\t" 1 } } */
/* { dg-final { scan-assembler-times "ksub64\t" 1 } } */
/* { dg-final { scan-assembler-times "uksub64\t" 1 } } */
