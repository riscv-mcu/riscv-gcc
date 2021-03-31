/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int64_t a, b, c;
  uint64_t ua, ub, uc;
  c = __rv__sadd64(a, b);
  uc = __rv__uadd64(ua, ub);

  c = __rv__radd64(a, b);
  uc = __rv__uradd64(a, b);

  c = __rv__kadd64(a, b);
  uc = __rv__ukadd64(a, b);
  return 0;
}

/* { dg-final { scan-assembler-times "add64\t" 2 } } */
/* { dg-final { scan-assembler-times "radd64\t" 1 } } */
/* { dg-final { scan-assembler-times "uradd64\t" 1 } } */
/* { dg-final { scan-assembler-times "kadd64\t" 1 } } */
/* { dg-final { scan-assembler-times "ukadd64\t" 1 } } */
