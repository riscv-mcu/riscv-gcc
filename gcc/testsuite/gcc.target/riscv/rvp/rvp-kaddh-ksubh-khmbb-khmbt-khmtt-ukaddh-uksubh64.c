/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int64_t a64, b64, c64;
  uint64_t ua64, ub64, uc64;
  uintXLEN_t ua, ub, uc;
  intXLEN_t a, b, c;
  a = __rv__kaddh(a64, b64);
  a = __rv__ksubh(a64, b64);
  a = __rv__khmbb(ua64, ub64);
  a = __rv__khmbt(ua64, ub64);
  a = __rv__khmtt(ua64, ub64);
  ua = __rv__ukaddh(ua64, ub64);
  ua = __rv__uksubh(ua64, ub64);
  return 0;
}

/* { dg-final { scan-assembler-times "kaddh\t" 1 } } */
/* { dg-final { scan-assembler-times "ksubh\t" 1 } } */
/* { dg-final { scan-assembler-times "khmbb\t" 1 } } */
/* { dg-final { scan-assembler-times "khmbt\t" 1 } } */
/* { dg-final { scan-assembler-times "khmtt\t" 1 } } */
/* { dg-final { scan-assembler-times "ukaddh\t" 1 } } */
/* { dg-final { scan-assembler-times "uksubh\t" 1 } } */
