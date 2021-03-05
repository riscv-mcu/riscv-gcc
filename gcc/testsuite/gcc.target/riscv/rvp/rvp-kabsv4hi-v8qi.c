/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2}, b = {-3, 4}, c;
  int8x8_t aa = {-1, 2}, bb = {-3, 4}, cc;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __rv__v_kabs16(a);
  j = __rv__kabs16(h);

  cc = __rv__v_kabs8(aa);
  j = __rv__kabs8(h);

  return 0;
}

/* { dg-final { scan-assembler-times "kabs16" 2 } } */
/* { dg-final { scan-assembler-times "kabs8" 2 } } */
