/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int8x4_t a = {-1, 2, 3, -4}, b = {-3, 4, 1, 2};
  uint8x4_t c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_scmplev4qi(h, i);
  j = __rv__scmple8(h, i);

  c = __builtin_riscv_v_scmplev4qi(a, b);
  c = __rv__v_scmple8(a, b);

  return 0;
}

/* { dg-final { scan-assembler-times "scmple8" 4 } } */
