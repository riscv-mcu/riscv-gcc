/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2, -3, 4}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_ksllv4hi(a, c);
  b = __rv__v_ksll16(a, c);
  e = __builtin_riscv_ksllv4hi(d, c);
  e = __rv__ksll16(d, c);

  b = __builtin_riscv_v_ksllv4hi(a, 2);
  b = __rv__v_ksll16(a, 2);
  e = __builtin_riscv_ksllv4hi(d, 2);
  e = __rv__ksll16(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "ksll16\t" 4 } } */
/* { dg-final { scan-assembler-times "kslli16\t" 4 } } */
