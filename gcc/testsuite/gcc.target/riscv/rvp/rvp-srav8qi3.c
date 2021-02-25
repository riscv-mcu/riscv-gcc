/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int8x8_t a = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_srav8qi(a, c);
  b = __rv__v_sra8(a, c);
  e = __builtin_riscv_srav8qi(d, c);
  e = __rv__sra8(d, c);

  b = __builtin_riscv_v_srav8qi(a, 2);
  b = __rv__v_sra8(a, 2);
  e = __builtin_riscv_srav8qi(d, 2);
  e = __rv__sra8(d, 2);

  b = __builtin_riscv_v_srav8qi_u(a, c);
  b = __rv__v_sra8_u(a, c);
  e = __builtin_riscv_srav8qi_u(d, c);
  e = __rv__sra8_u(d, c);

  b = __builtin_riscv_v_srav8qi_u(a, 2);
  b = __rv__v_sra8_u(a, 2);
  e = __builtin_riscv_srav8qi_u(d, 2);
  e = __rv__sra8_u(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "sra8\t" 4 } } */
/* { dg-final { scan-assembler-times "srai8\t" 4 } } */
/* { dg-final { scan-assembler-times "sra8.u" 4 } } */
/* { dg-final { scan-assembler-times "srai8.u" 4 } } */
