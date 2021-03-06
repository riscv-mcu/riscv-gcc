/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  intXLEN_t a = 0x01, b = 0x02, c;
  c = __rv__smmul(a, b);
  c = __rv__smmul_u(a, b);
  return 0;
}

/* { dg-final { scan-assembler-times "smmul.u" 1 } } */
