/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x8_t a = {0x01, 0x02, 0x03, 0x04, 0x05, 0x04, 0x02, 0x01},
	    b = {0x03, 0x04, 0x01, 0x02, 0x03, 0x05, 0x02, 0x01};
  uint8x8_t c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  j = __builtin_riscv_ucmplev8qi(h, i);
  j = __rv__ucmple8(h, i);

  c = __builtin_riscv_v_ucmplev8qi(a, b);
  c = __rv__v_ucmple8(a, b);

  return 0;
}

/* { dg-final { scan-assembler-times "ucmple8" 4 } } */
