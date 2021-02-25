/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int8x4_t a = {-1, 2, -3, 4}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_srav4qi(a, c);
  b = __rv__v_sra8(a, c);
  e = __builtin_riscv_srav4qi(d, c);
  e = __rv__sra8(d, c);

  b = __builtin_riscv_v_srav4qi(a, 2);
  b = __rv__v_sra8(a, 2);
  e = __builtin_riscv_srav4qi(d, 2);
  e = __rv__sra8(d, 2);

  b = __builtin_riscv_v_srav4qi_u(a, c);
  b = __rv__v_sra8_u(a, c);
  e = __builtin_riscv_srav4qi_u(d, c);
  e = __rv__sra8_u(d, c);

  b = __builtin_riscv_v_srav4qi_u(a, 2);
  b = __rv__v_sra8_u(a, 2);
  e = __builtin_riscv_srav4qi_u(d, 2);
  e = __rv__sra8_u(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "sra8\t" 4 } } */
/* { dg-final { scan-assembler-times "srai8\t" 4 } } */
/* { dg-final { scan-assembler-times "sra8.u" 4 } } */
/* { dg-final { scan-assembler-times "srai8.u" 4 } } */
