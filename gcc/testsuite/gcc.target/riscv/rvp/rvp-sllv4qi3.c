/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x4_t a = {0x01, 0x02, 0x03, 0x04}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_sllv4qi(a, c);
  b = __rv__v_sll8(a, c);
  e = __builtin_riscv_sllv4qi(d, c);
  e = __rv__sll8(d, c);

  b = __builtin_riscv_v_sllv4qi(a, 2);
  b = __rv__v_sll8(a, 2);
  e = __builtin_riscv_sllv4qi(d, 2);
  e = __rv__sll8(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "sll8\t" 4 } } */
/* { dg-final { scan-assembler-times "slli8\t" 4 } } */
