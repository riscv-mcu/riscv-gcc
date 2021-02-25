/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int8x4_t a = {1, 2, 3, 4}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_ksllv4qi(a, c);
  b = __rv__v_ksll8(a, c);
  e = __builtin_riscv_ksllv4qi(d, c);
  e = __rv__ksll8(d, c);

  b = __builtin_riscv_v_ksllv4qi(a, 2);
  b = __rv__v_ksll8(a, 2);
  e = __builtin_riscv_ksllv4qi(d, 2);
  e = __rv__ksll8(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "ksll8\t" 4 } } */
/* { dg-final { scan-assembler-times "kslli8\t" 4 } } */
