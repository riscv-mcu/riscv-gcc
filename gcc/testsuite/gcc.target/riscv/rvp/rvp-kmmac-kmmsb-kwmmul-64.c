/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  intXLEN_t a = 0x01, b = 0x02, c = 0x03, d;
  int32x2_t aa = { 1, 2 }, bb = { 1, 2 }, cc = { 1, 2 }, dd;
  d = __rv__kmmac(a, b, c);
  dd = __rv__v_kmmac(aa, bb, cc);
  d = __rv__kmmac_u(a, b, c);
  dd = __rv__v_kmmac_u(aa, bb, cc);
  d = __rv__kmmsb(a, b, c);
  dd = __rv__v_kmmsb(aa, bb, cc);
  d = __rv__kmmsb_u(a, b, c);
  dd = __rv__v_kmmsb_u(aa, bb, cc);
  d = __rv__kwmmul(a, b);
  dd = __rv__v_kwmmul(aa, bb);
  d = __rv__kwmmul_u(a, b);
  dd = __rv__v_kwmmul_u(aa, bb);
  return 0;
}

/* { dg-final { scan-assembler-times "kmmac\t" 2 } } */
/* { dg-final { scan-assembler-times "kmmac.u\t" 2 } } */
/* { dg-final { scan-assembler-times "kmmsb\t" 2 } } */
/* { dg-final { scan-assembler-times "kmmsb.u\t" 2 } } */
/* { dg-final { scan-assembler-times "kwmmul\t" 2 } } */
/* { dg-final { scan-assembler-times "kwmmul.u\t" 2 } } */
