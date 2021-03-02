/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x2_t a = {0x01, 0x02}, b = {0x03, 0x04};
  uint16x2_t c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_ucmpltv2hi(h, i);
  j = __rv__ucmplt16(h, i);

  c = __builtin_riscv_v_ucmpltv2hi(a, b);
  c = __rv__v_ucmplt16(a, b);

  return 0;
}

/* { dg-final { scan-assembler-times "ucmplt16" 4 } } */
