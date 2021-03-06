/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int32x2_t a = {1, 2}, b = {1, 2}, c;
  intXLEN_t aa = 0x01, bb = 0x02, cc;
  c = __rv__v_smmul(a, b);
  cc = __rv__smmul(aa, bb);
  c = __rv__v_smmul_u(a, b);
  cc = __rv__smmul_u(aa, bb);
  return 0;
}

/* { dg-final { scan-assembler-times "smmul\t" 2 } } */
/* { dg-final { scan-assembler-times "smmul.u" 2 } } */
