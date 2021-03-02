/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x4_t a = {0x01, 0x02, 0x04, 0x02}, b = {0x03, 0x04, 0x01, 0x02};
  uint16x4_t c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_ucmpltv4hi(h, i);
  j = __rv__ucmplt16(h, i);

  c = __builtin_riscv_v_ucmpltv4hi(a, b);
  c = __rv__v_ucmplt16(a, b);

  return 0;
}

/* { dg-final { scan-assembler-times "ucmplt16" 4 } } */
