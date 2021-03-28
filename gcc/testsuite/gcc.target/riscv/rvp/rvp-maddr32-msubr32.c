/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int32_t a, b, c;
  c = __rv__maddr32(a, b);
  c = __rv__msubr32(a, b);
  return 0;
}

/* { dg-final { scan-assembler-times "maddr32\t" 1 } } */
/* { dg-final { scan-assembler-times "msubr32\t" 1 } } */
