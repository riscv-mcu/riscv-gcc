/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int16x2_t a = {-1, 2}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_srav2hi(a, c);
  b = __rv__v_sra16(a, c);
  e = __builtin_riscv_srav2hi(d, c);
  e = __rv__sra16(d, c);

  b = __builtin_riscv_v_srav2hi(a, 2);
  b = __rv__v_sra16(a, 2);
  e = __builtin_riscv_srav2hi(d, 2);
  e = __rv__sra16(d, 2);

  b = __builtin_riscv_v_srav2hi_u(a, c);
  b = __rv__v_sra16_u(a, c);
  e = __builtin_riscv_srav2hi_u(d, c);
  e = __rv__sra16_u(d, c);

  b = __builtin_riscv_v_srav2hi_u(a, 2);
  b = __rv__v_sra16_u(a, 2);
  e = __builtin_riscv_srav2hi_u(d, 2);
  e = __rv__sra16_u(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "sra16\t" 4 } } */
/* { dg-final { scan-assembler-times "srai16\t" 4 } } */
/* { dg-final { scan-assembler-times "sra16.u" 4 } } */
/* { dg-final { scan-assembler-times "srai16.u" 4 } } */
