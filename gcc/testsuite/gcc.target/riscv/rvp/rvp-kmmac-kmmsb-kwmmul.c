/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  intXLEN_t a = 0x01, b = 0x02, c = 0x03, d;
  d = __rv__kmmac(a, b, c);
  d = __rv__kmmac_u(a, b, c);
  d = __rv__kmmsb(a, b, c);
  d = __rv__kmmsb_u(a, b, c);
  d = __rv__kwmmul(a, b);
  d = __rv__kwmmul_u(a, b);
  return 0;
}

/* { dg-final { scan-assembler-times "kmmac\t" 1 } } */
/* { dg-final { scan-assembler-times "kmmac.u\t" 1 } } */
/* { dg-final { scan-assembler-times "kmmsb\t" 1 } } */
/* { dg-final { scan-assembler-times "kmmsb.u\t" 1 } } */
/* { dg-final { scan-assembler-times "kwmmul\t" 1 } } */
/* { dg-final { scan-assembler-times "kwmmul.u\t" 1 } } */
