/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t ua, ub, uc;
  intXLEN_t a, b, c;

  a = __rv__smaqa(a, b, c);
  ua = __rv__umaqa(ua, ub, uc);
  a = __rv__smaqa_su(a, b, c);
}

/* { dg-final { scan-assembler-times "smaqa\t" 1 } } */
/* { dg-final { scan-assembler-times "umaqa\t" 1 } } */
/* { dg-final { scan-assembler-times "smaqa.su\t" 1 } } */
