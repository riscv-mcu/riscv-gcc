/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uint16x2_t a = {0x01, 0x02}, b = {0x01, 0x02}, c;
  uintXLEN_t d = 0x01, e = 0x02, f;

  f = __rv__pkbb16(d, e);
  c = __rv__v_pkbb16(a, b);

  f = __rv__pktb16(d, e);
  c = __rv__v_pktb16(a, b);

  f = __rv__pkbt16(d, e);
  c = __rv__v_pkbt16(a, b);

  f = __rv__pktt16(d, e);
  c = __rv__v_pktt16(a, b);

  return 0;
}

/* { dg-final { scan-assembler-times "pkbb16" 2 } } */
/* { dg-final { scan-assembler-times "pktb16" 2 } } */
/* { dg-final { scan-assembler-times "pkbt16" 2 } } */
/* { dg-final { scan-assembler-times "pktt16" 2 } } */
