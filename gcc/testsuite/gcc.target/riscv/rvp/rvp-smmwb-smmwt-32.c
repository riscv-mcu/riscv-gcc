/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  intXLEN_t a = 1, c;
  uintXLEN_t b = 0x01;
  int32_t aa = 1, cc;
  int16x2_t bb = { 1, 2 };
  c = __rv__smmwb(a, b);
  c = __rv__smmwb_u(a, b);
  c = __rv__smmwt(a, b);
  c = __rv__smmwt_u(a, b);
  cc = __rv__v_smmwb(aa, bb);
  cc = __rv__v_smmwb_u(aa, bb);
  cc = __rv__v_smmwt(aa, bb);
  cc = __rv__v_smmwt_u(aa, bb);
  return 0;
}

/* { dg-final { scan-assembler-times "smmwb\t" 2 } } */
/* { dg-final { scan-assembler-times "smmwb.u\t" 2 } } */
/* { dg-final { scan-assembler-times "smmwt\t" 2 } } */
/* { dg-final { scan-assembler-times "smmwt.u\t" 2 } } */
