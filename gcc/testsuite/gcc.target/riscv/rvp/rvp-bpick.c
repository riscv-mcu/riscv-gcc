/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t a, b, c, d;
  a = __rv__bpick(b, c, d);
  return 0;
}

/* { dg-final { scan-assembler-times "bpick" 1 } } */
