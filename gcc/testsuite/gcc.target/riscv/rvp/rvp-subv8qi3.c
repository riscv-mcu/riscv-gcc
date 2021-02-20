/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, -3, 4, 5, 6, 7, 8}, b = {1, -2, 3, -4, 5, 6, -7, 8}, c;
  uint8x8_t e = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	    f = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08},
	    g;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = a - b;
  c = __builtin_riscv_v_ssubv8qi(a, b);
  c = __rv__v_ssub8(a, b);

  g = f - g;
  g = __builtin_riscv_v_usubv8qi(e, f);
  g = __rv__v_usub8(e, f);

  j = __builtin_riscv_subv8qi(h, i);
  j = __rv__sub8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "sub8" 8 } } */
