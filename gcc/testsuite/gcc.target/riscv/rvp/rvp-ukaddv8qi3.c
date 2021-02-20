/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x8_t e = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	    f = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	    g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  g = __builtin_riscv_v_ukaddv8qi(e, f);
  g = __rv__v_ukadd8(e, f);

  j = __builtin_riscv_ukaddv8qi(h, i);
  j = __rv__ukadd8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "ukadd8" 4 } } */
