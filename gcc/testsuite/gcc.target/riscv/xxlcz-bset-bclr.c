/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32imac_xxlczbitop -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* Per the Nuclei spec the first immediate (uimm3) of xl.bset/xl.bclr is
   (len - 1): mask = ((1 << (uimm3 + 1)) - 1) << uimm2, so setting or
   clearing the 16-bit field at bit 8 must emit 15, 8 -- not 16, 8
   (which would touch 17 bits).  */
#include <stdint.h>
uint32_t set16(uint32_t x) { return x | 0xFFFF00u; }
uint32_t clr16(uint32_t x) { return x & ~0xFFFF00u; }
uint32_t set10high(uint32_t x) { return x | 0x3FF00000u; }
/* { dg-final { scan-assembler "xl\\.bset\\ta\[0-9\]+,a\[0-9\]+,15,8" } } */
/* { dg-final { scan-assembler "xl\\.bclr\\ta\[0-9\]+,a\[0-9\]+,15,8" } } */
/* { dg-final { scan-assembler "xl\\.bset\\ta\[0-9\]+,a\[0-9\]+,9,20" } } */
