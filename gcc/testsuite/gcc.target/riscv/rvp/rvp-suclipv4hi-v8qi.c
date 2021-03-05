/* { dg-do compile } */
/* { dg-options "-O0 -march=rv64gcp -mabi=lp64d" } */

#include <riscv_dsp.h>

int foo() {
  int16x4_t a = {-1, 2}, b = {-3, 4}, c;
  uint16x4_t a1 = {0x01, 0x02}, b1 = {0x03, 0x04}, c1;
  int8x8_t a2 = {1, 2}, b2 = {3, 4}, c2;
  uint8x8_t a3 = {1, 2}, b3 = {3, 4}, c3;
  uintXLEN_t h = 0x01, i = 0x02, j;

  c = __rv__v_sclip16(a, 0x01);
  j = __rv__sclip16(h, 0x02);

  c1 = __rv__v_uclip16(a1, 0x01);
  j = __rv__uclip16(h, 0x02);

  c2 = __rv__v_sclip8(a2, 0x01);
  j = __rv__sclip8(h, 0x02);

  c3 = __rv__v_uclip8(a3, 0x01);
  j = __rv__uclip8(h, 0x02);

  return 0;
}

/* { dg-final { scan-assembler-times "sclip16" 2 } } */
/* { dg-final { scan-assembler-times "uclip16" 2 } } */
/* { dg-final { scan-assembler-times "sclip8" 2 } } */
/* { dg-final { scan-assembler-times "uclip8" 2 } } */
