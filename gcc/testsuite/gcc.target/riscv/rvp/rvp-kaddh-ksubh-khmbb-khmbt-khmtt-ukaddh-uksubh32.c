/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  int32_t a32, b32, c32;
  uint32_t ua32, ub32, uc32;
  uintXLEN_t ua, ub, uc;
  intXLEN_t a, b, c;
  a = __rv__kaddh(a32, b32);
  a = __rv__ksubh(a32, b32);
  a = __rv__khmbb(ua32, ub32);
  a = __rv__khmbt(ua32, ub32);
  a = __rv__khmtt(ua32, ub32);
  ua = __rv__ukaddh(ua32, ub32);
  ua = __rv__uksubh(ua32, ub32);
  return 0;
}

/* { dg-final { scan-assembler-times "kaddh\t" 1 } } */
/* { dg-final { scan-assembler-times "ksubh\t" 1 } } */
/* { dg-final { scan-assembler-times "khmbb\t" 1 } } */
/* { dg-final { scan-assembler-times "khmbt\t" 1 } } */
/* { dg-final { scan-assembler-times "khmtt\t" 1 } } */
/* { dg-final { scan-assembler-times "ukaddh\t" 1 } } */
/* { dg-final { scan-assembler-times "uksubh\t" 1 } } */
