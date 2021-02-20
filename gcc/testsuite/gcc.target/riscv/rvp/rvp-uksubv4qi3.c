/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x4_t a = { 0x01, 0x02, 0x03, 0x04 }, b = { 0x01, 0x02, 0x03, 0x04 }, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_uksubv4qi(a, b);
  c = __rv__v_uksub8(a, b);

  j = __builtin_riscv_uksubv4qi(h, i);
  j = __rv__uksub8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "uksub8" 4 } } */
