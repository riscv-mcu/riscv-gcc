/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x4_t a = {0x01, 0x02, 0x03, 0x04}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_srlv4qi(a, c);
  b = __rv__v_srl8(a, c);
  e = __builtin_riscv_srlv4qi(d, c);
  e = __rv__srl8(d, c);

  b = __builtin_riscv_v_srlv4qi(a, 2);
  b = __rv__v_srl8(a, 2);
  e = __builtin_riscv_srlv4qi(d, 2);
  e = __rv__srl8(d, 2);

  b = __builtin_riscv_v_srlv4qi_u(a, c);
  b = __rv__v_srl8_u(a, c);
  e = __builtin_riscv_srlv4qi_u(d, c);
  e = __rv__srl8_u(d, c);

  b = __builtin_riscv_v_srlv4qi_u(a, 2);
  b = __rv__v_srl8_u(a, 2);
  e = __builtin_riscv_srlv4qi_u(d, 2);
  e = __rv__srl8_u(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "srl8\t" 4 } } */
/* { dg-final { scan-assembler-times "srli8\t" 4 } } */
/* { dg-final { scan-assembler-times "srl8.u" 4 } } */
/* { dg-final { scan-assembler-times "srli8.u" 4 } } */
