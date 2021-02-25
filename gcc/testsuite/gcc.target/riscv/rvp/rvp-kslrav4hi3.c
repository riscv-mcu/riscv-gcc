/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2, -3, 4}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_kslrav4hi(a, c);
  b = __rv__v_kslra16(a, c);
  e = __builtin_riscv_kslrav4hi(d, c);
  e = __rv__kslra16(d, c);

  b = __builtin_riscv_v_kslrav4hi_u(a, c);
  b = __rv__v_kslra16_u(a, c);
  e = __builtin_riscv_kslrav4hi_u(d, c);
  e = __rv__kslra16_u(d, c);

  return 0;
}

/* { dg-final { scan-assembler-times "kslra16\t" 4 } } */
/* { dg-final { scan-assembler-times "kslra16.u" 4 } } */
