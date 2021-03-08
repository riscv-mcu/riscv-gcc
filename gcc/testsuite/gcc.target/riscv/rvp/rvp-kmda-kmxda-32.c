/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  intXLEN_t c;
  uintXLEN_t a = 0x01, b = 0x02;
  int32_t cc;
  int16x2_t aa = { 1, 2 }, bb = { 3, 4 };

  c = __rv__kmda(a, b);
  cc = __rv__v_kmda(aa, bb);

  c = __rv__kmxda(a, b);
  cc = __rv__v_kmxda(aa, bb);

  return 0;
}

/* { dg-final { scan-assembler-times "kmda\t" 2 } } */
/* { dg-final { scan-assembler-times "kmxda\t" 2 } } */
