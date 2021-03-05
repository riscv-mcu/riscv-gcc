/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b = {-3, 4}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __rv__v_clrs16(a);
  j = __rv__clrs16(h);

  c = __rv__v_clz16(a);
  j = __rv__clz16(h);

  c = __rv__v_clo16(a);
  j = __rv__clo16(h);

  return 0;
}

/* { dg-final { scan-assembler-times "clrs16" 2 } } */
/* { dg-final { scan-assembler-times "clz16" 2 } } */
/* { dg-final { scan-assembler-times "clo16" 2 } } */
