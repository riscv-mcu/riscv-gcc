/* { dg-do compile } */
/* { dg-options "-O0 -march=rv32gcp -mabi=ilp32d" } */

#include <riscv_dsp.h>

int foo() {
  uintXLEN_t a = 0x01, b;
  int8x4_t aa = { 1, 2 };
  int16x2_t bb = { 1, 3 };
  uint8x4_t aaa = { 0x01, 0x02 };
  uint16x2_t bbb = { 0x02, 0x03 };

  b = __rv__sunpkd810(a);
  b = __rv__sunpkd820(a);
  b = __rv__sunpkd830(a);
  b = __rv__sunpkd831(a);
  b = __rv__sunpkd832(a);

  bb = __rv__v_sunpkd810(aa);
  bb = __rv__v_sunpkd820(aa);
  bb = __rv__v_sunpkd830(aa);
  bb = __rv__v_sunpkd831(aa);
  bb = __rv__v_sunpkd832(aa);

  b = __rv__zunpkd810(a);
  b = __rv__zunpkd820(a);
  b = __rv__zunpkd830(a);
  b = __rv__zunpkd831(a);
  b = __rv__zunpkd832(a);

  bbb = __rv__v_zunpkd810(aaa);
  bbb = __rv__v_zunpkd820(aaa);
  bbb = __rv__v_zunpkd830(aaa);
  bbb = __rv__v_zunpkd831(aaa);
  bbb = __rv__v_zunpkd832(aaa);

  return 0;
}

/* { dg-final { scan-assembler-times "sunpkd810" 2 } } */
/* { dg-final { scan-assembler-times "sunpkd820" 2 } } */
/* { dg-final { scan-assembler-times "sunpkd830" 2 } } */
/* { dg-final { scan-assembler-times "sunpkd831" 2 } } */
/* { dg-final { scan-assembler-times "sunpkd832" 2 } } */

/* { dg-final { scan-assembler-times "zunpkd810" 2 } } */
/* { dg-final { scan-assembler-times "zunpkd820" 2 } } */
/* { dg-final { scan-assembler-times "zunpkd830" 2 } } */
/* { dg-final { scan-assembler-times "zunpkd831" 2 } } */
/* { dg-final { scan-assembler-times "zunpkd832" 2 } } */
