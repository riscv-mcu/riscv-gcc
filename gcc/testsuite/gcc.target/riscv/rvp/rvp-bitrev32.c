/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t a, b, c;
  a = __rv__bitrev(b, c);
  return 0;
}

/* { dg-final { scan-assembler-times "bitrev\t" 1 } } */
