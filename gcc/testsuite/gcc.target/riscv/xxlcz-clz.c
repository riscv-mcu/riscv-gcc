/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32imac_xxlczbitop -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* xl.ff1 (find the first '1' seen from the MSB) returns the bit index
   of the most significant set bit for nonzero inputs and XLEN for a
   zero input, so clz compiles to xl.ff1 plus an xor with the
   correction term (XLEN - 1) * (x != 0): the identity is untouched for
   x != 0, and the xl.ff1 result passes through unchanged for x == 0
   (clz(0) == XLEN, as promised by CLZ_DEFINED_VALUE_AT_ZERO).  xl.fl1
   (which finds the last '1' seen from the MSB, i.e. the ctz value)
   must not appear.  */
int test_clz(unsigned x) { return __builtin_clz(x); }
/* { dg-final { scan-assembler-times "xl\\.ff1" 1 } } */
/* { dg-final { scan-assembler-not "xl\\.fl1" } } */
/* { dg-final { scan-assembler-not "xori" } } */
/* { dg-final { scan-assembler-times "snez" 1 } } */
/* { dg-final { scan-assembler-times "xor" 1 } } */
