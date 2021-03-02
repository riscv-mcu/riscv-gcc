/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2, 4, 2}, b = {-3, 4, 1, 2};
  uint16x4_t c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_scmplev4hi(h, i);
  j = __rv__scmple16(h, i);

  c = __builtin_riscv_v_scmplev4hi(a, b);
  c = __rv__v_scmple16(a, b);

  return 0;
}

/* { dg-final { scan-assembler-times "scmple16" 4 } } */
