/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  intXLEN_t c;
  intXLEN_t a = 0x02;
  uintXLEN_t ua = 0x01;
  uint32_t b = 0x03;

  c = __rv__sclip32(a, 0x02);
  c = __rv__uclip32(ua, 0x02);

  ua = __rv__clrs32(ua);
  ua = __rv__clz32(ua);
  ua = __rv__clo32(ua);

  return 0;
}

/* { dg-final { scan-assembler-times "sclip32" 1 } } */
/* { dg-final { scan-assembler-times "uclip32" 1 } } */
/* { dg-final { scan-assembler-times "clrs32" 1 } } */
/* { dg-final { scan-assembler-times "clz32" 1 } } */
/* { dg-final { scan-assembler-times "clo32" 1 } } */
