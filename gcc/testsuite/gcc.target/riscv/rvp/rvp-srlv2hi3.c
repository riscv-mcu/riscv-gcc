/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x2_t a = {0x01, 0x02}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_srlv2hi(a, c);
  b = __rv__v_srl16(a, c);
  e = __builtin_riscv_srlv2hi(d, c);
  e = __rv__srl16(d, c);

  b = __builtin_riscv_v_srlv2hi(a, 2);
  b = __rv__v_srl16(a, 2);
  e = __builtin_riscv_srlv2hi(d, 2);
  e = __rv__srl16(d, 2);

  b = __builtin_riscv_v_srlv2hi_u(a, c);
  b = __rv__v_srl16_u(a, c);
  e = __builtin_riscv_srlv2hi_u(d, c);
  e = __rv__srl16_u(d, c);

  b = __builtin_riscv_v_srlv2hi_u(a, 2);
  b = __rv__v_srl16_u(a, 2);
  e = __builtin_riscv_srlv2hi_u(d, 2);
  e = __rv__srl16_u(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "srl16\t" 4 } } */
/* { dg-final { scan-assembler-times "srli16\t" 4 } } */
/* { dg-final { scan-assembler-times "srl16.u" 4 } } */
/* { dg-final { scan-assembler-times "srli16.u" 4 } } */
