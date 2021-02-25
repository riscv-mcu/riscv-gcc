/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  uint8x8_t a = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08}, b;
  int c = 2;
  uintXLEN_t d = 0x01, e;

  b = __builtin_riscv_v_sllv8qi(a, c);
  b = __rv__v_sll8(a, c);
  e = __builtin_riscv_sllv8qi(d, c);
  e = __rv__sll8(d, c);

  b = __builtin_riscv_v_sllv8qi(a, 2);
  b = __rv__v_sll8(a, 2);
  e = __builtin_riscv_sllv8qi(d, 2);
  e = __rv__sll8(d, 2);

  return 0;
}

/* { dg-final { scan-assembler-times "sll8\t" 4 } } */
/* { dg-final { scan-assembler-times "slli8\t" 4 } } */
