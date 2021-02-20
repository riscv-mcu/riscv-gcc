/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, -3, 4, 5, 6, 7, 8}, b = {1, -2, 3, -4, 5, 6, -7, 8}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_rsubv8qi(a, b);
  c = __rv__v_rsub8(a, b);

  j = __builtin_riscv_rsubv8qi(h, i);
  j = __rv__rsub8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "rsub8" 4 } } */
