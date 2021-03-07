/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t a = 0x01, b = 0x02;
  intXLEN_t c;
  int16x2_t aa = { 1, 2 }, bb = { 3, 4 };
  int32_t cc;

  c = __rv__smbb16(a, b);
  cc = __rv__v_smbb16(aa, bb);

  c = __rv__smbt16(a, b);
  cc = __rv__v_smbt16(aa, bb);

  c = __rv__smtt16(a, b);
  cc = __rv__v_smtt16(aa, bb);

  return 0;
}

/* { dg-final { scan-assembler-times "smbb16" 2 } } */
/* { dg-final { scan-assembler-times "smbt16" 2 } } */
/* { dg-final { scan-assembler-times "smtt16" 2 } } */
