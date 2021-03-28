/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  intXLEN_t c;
  int32_t a, b;
  c = __rv__maxw(a, b);
  c = __rv__minw(a, b);
  return 0;
}

/* { dg-final { scan-assembler-times "maxw\t" 1 } } */
/* { dg-final { scan-assembler-times "minw\t" 1 } } */
