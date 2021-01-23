/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, -3, 4, 5, 6, 7, 8}, b = {1, -2, 3, -4, 5, 6, -7, 8}, c;
  uint8x8_t e = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	    f = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	    g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = a + b;
  c = __rv__sadd8(a, b);

  g = f + g;
  g = __rv__uadd8(e, f);

  j = __rv__add8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "add8" 5 } } */
