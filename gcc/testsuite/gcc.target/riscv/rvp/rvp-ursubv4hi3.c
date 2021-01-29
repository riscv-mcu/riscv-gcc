/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x4_t a = {1, 2, 3, 4}, b = {1, 2, 3, 4}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __rv__v_ursub16(a, b);

  j = __rv__ursub16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "ursub16" 2 } } */
