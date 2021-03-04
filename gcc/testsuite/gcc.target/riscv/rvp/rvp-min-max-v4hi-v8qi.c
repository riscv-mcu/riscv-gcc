/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2}, b = {-3, 4}, c;
  uint16x4_t e = {0x01, 0x02}, f = {0x01, 0x02}, g;
  int8x8_t h = {1, 2, 3, 4}, i = {4, 3, 2, 1}, j;
  uint8x8_t k = {0x01, 0x02, 0x03, 0x04}, l = {0x04, 0x03, 0x02, 0x01}, m;
  uintXLEN_t n = 0x01, o = 0x02, p;

  c = __rv__v_smin16(a, b);
  p = __rv__smin16(n, o);

  g = __rv__v_umin16(e, f);
  p = __rv__umin16(n, o);

  c = __rv__v_smax16(a, b);
  p = __rv__smax16(n, o);

  g = __rv__v_umax16(e, f);
  p = __rv__umax16(n, o);

  j = __rv__v_smin8(h, i);
  p = __rv__smin8(n, o);

  m = __rv__v_umin8(k, l);
  p = __rv__umin8(n, o);

  j = __rv__v_smax8(h, i);
  p = __rv__smax8(n, o);

  m = __rv__v_umax8(k, l);
  p = __rv__umax8(n, o);

  return 0;
}

/* { dg-final { scan-assembler-times "smin16" 2 } } */
/* { dg-final { scan-assembler-times "umin16" 2 } } */
/* { dg-final { scan-assembler-times "smax16" 2 } } */
/* { dg-final { scan-assembler-times "umax16" 2 } } */

/* { dg-final { scan-assembler-times "smin8" 2 } } */
/* { dg-final { scan-assembler-times "umin8" 2 } } */
/* { dg-final { scan-assembler-times "smax8" 2 } } */
/* { dg-final { scan-assembler-times "umax8" 2 } } */
