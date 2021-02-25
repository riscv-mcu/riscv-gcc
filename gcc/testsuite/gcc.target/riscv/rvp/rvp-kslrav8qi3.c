/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, -3, 4, -5, 6, -7, 8}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_kslrav8qi(a, c);
  b = __rv__v_kslra8(a, c);
  e = __builtin_riscv_kslrav8qi(d, c);
  e = __rv__kslra8(d, c);

  b = __builtin_riscv_v_kslrav8qi_u(a, c);
  b = __rv__v_kslra8_u(a, c);
  e = __builtin_riscv_kslrav8qi_u(d, c);
  e = __rv__kslra8_u(d, c);

  return 0;
}

/* { dg-final { scan-assembler-times "kslra8\t" 4 } } */
/* { dg-final { scan-assembler-times "kslra8.u" 4 } } */
