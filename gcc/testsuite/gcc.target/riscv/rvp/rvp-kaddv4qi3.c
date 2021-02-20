/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int8x4_t a = {-1, 2, -3, 4}, b = {1, -2, 3, -4}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_kaddv4qi(a, b);
  c = __rv__v_kadd8(a, b);

  j = __builtin_riscv_kaddv4qi(h, i);
  j = __rv__kadd8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "kadd8" 4 } } */
