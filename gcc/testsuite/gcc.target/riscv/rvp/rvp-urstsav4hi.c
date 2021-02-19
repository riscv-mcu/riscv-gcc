/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x4_t a = {0x01, 0x02, 0x03, 0x04}, b = {0x01, 0x02, 0x03, 0x04}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_urstsav4hi(a, b);
  c = __rv__v_urstsa16(a, b);
  j = __builtin_riscv_urstsav4hi(h, i);
  j = __rv__urstsa16(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "urstsa16" 4 } } */
