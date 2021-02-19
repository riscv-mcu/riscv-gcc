/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x2_t a = {0x01, 0x02}, b = {0x03, 0x04}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_urcrsav2hi(a, b);
  c = __rv__v_urcrsa16(a, b);
  j = __builtin_riscv_urcrsav2hi(h, i);
  j = __rv__urcrsa16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "urcrsa16" 4 } } */
