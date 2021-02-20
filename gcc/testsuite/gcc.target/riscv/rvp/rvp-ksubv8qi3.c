/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2, -3, 4, 5, 6, 7, 8}, b = {1, -2, 3, -4, 5, 6, -7, 8}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __builtin_riscv_v_ksubv8qi(a, b);
  c = __rv__v_ksub8(a, b);

  j = __builtin_riscv_ksubv8qi(h, i);
  j = __rv__ksub8(h, i);

  return 0;
}

/* { dg-final { scan-assembler-times "ksub8" 4 } } */
