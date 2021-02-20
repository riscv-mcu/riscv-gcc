/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x4_t a = { 0x01, 0x02, 0x03, 0x04 }, b = { 0x01, 0x02, 0x03, 0x04 }, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_ursubv4qi(a, b);
  c = __rv__v_ursub8(a, b);

  j = __builtin_riscv_ursubv4qi(h, i);
  j = __rv__ursub8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "ursub8" 4 } } */
