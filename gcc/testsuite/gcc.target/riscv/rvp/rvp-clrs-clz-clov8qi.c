/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {-1, 2}, b = {-3, 4}, c;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __rv__v_clrs8(a);
  j = __rv__clrs8(h);

  c = __rv__v_clz8(a);
  j = __rv__clz8(h);

  c = __rv__v_clo8(a);
  j = __rv__clo8(h);

  return 0;
}

/* { dg-final { scan-assembler-times "clrs8" 2 } } */
/* { dg-final { scan-assembler-times "clz8" 2 } } */
/* { dg-final { scan-assembler-times "clo8" 2 } } */
