/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, -3, 4, -5, 6, -7, 8}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_ksllv8qi(a, c);
  b = __rv__v_ksll8(a, c);
  e = __builtin_riscv_ksllv8qi(d, c);
  e = __rv__ksll8(d, c);

  b = __builtin_riscv_v_ksllv8qi(a, 2);
  b = __rv__v_ksll8(a, 2);
  e = __builtin_riscv_ksllv8qi(d, 2);
  e = __rv__ksll8(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "ksll8\t" 4 } } */
/* { dg-final { scan-assembler-times "kslli8\t" 4 } } */
