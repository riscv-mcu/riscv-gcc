/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x4_t a = {0x01, 0x02, 0x03, 0x04}, b = {0x01, 0x02, 0x03, 0x04}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_urcrsav4hi(a, b);
  c = __rv__v_urcrsa16(a, b);
  j = __builtin_riscv_urcrsav4hi(h, i);
  j = __rv__urcrsa16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "urcrsa16" 4 } } */
