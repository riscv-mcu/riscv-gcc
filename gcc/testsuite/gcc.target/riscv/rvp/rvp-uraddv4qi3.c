/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x4_t a = { 0x01, 0x02, 0x03, 0x04 }, b = { 0x01, 0x02, 0x03, 0x04 }, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_uraddv4qi(a, b);
  c = __rv__v_uradd8(a, b);

  j = __builtin_riscv_uraddv4qi(h, i);
  j = __rv__uradd8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "uradd8" 4 } } */
