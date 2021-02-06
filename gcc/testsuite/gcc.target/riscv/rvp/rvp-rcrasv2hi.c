/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4}, c;
  uintXLEN_t d = 0x01, e = 0x02, f;

  c = __rv__v_rcras16(a, b);
  f = __rv__rcras16(d, e);

  return 0;
}

/* { dg-final { scan-assembler-times "rcras16" 2 } } */
