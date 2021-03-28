/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint32_t a, b;
  uint64_t c;
  int32_t sa, sb;
  int64_t sc;
  c = __rv__mulr64(a, b);
  sc = __rv__mulsr64(sa, sb);
  return 0;
}

/* { dg-final { scan-assembler-times "mulr64\t" 1 } } */
/* { dg-final { scan-assembler-times "mulsr64\t" 1 } } */
