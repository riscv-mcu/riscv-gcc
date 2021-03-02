/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, 3, -4, 5, -4, 2, 1},
	   b = {-3, 4, 1, 2, 3, 5, 2, 1};
  uint8x8_t c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_scmplev8qi(h, i);
  j = __rv__scmple8(h, i);

  c = __builtin_riscv_v_scmplev8qi(a, b);
  c = __rv__v_scmple8(a, b);

  return 0;
}

/* { dg-final { scan-assembler-times "scmple8" 4 } } */
