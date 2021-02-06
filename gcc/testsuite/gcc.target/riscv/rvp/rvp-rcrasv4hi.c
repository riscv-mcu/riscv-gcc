/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2, -3, 4}, b = {-1, 2, -3, 4}, c;
  uintXLEN_t e = 0x01, f = 0x02, g;

  c = __rv__v_rcras16(a, b);
  g = __rv__rcras16(e, f);

  return 0;
}

/* { dg-final { scan-assembler-times "rcras16" 2 } } */
