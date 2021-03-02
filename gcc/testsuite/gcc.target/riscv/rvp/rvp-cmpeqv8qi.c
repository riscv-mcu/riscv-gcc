/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, -3, 4, 5, 6, 7, 8}, b = {1, 2, 3, 4, 1, -2, -3, 4};
  uint8x8_t e = {0x01, 0x02, 0x03, 0x04, 0x04, 0x03, 0x02, 0x01},
	    f = {0x01, 0x02, 0x03, 0x04, 0x01, 0x02, 0x03, 0x01}, g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_cmpeqv8qi(h, i);
  j = __rv__cmpeq8(h, i);

  g = __builtin_riscv_v_scmpeqv8qi(a, b);
  g = __rv__v_scmpeq8(a, b);

  g = __builtin_riscv_v_ucmpeqv8qi(e, f);
  g = __rv__v_ucmpeq8(e, f);

  return 0;
}

/* { dg-final { scan-assembler-times "cmpeq8" 6 } } */
