/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64imac_xxlczbitop -mabi=lp64 -O2 -mautogen-xxlcz" } */
/* clz maps to xl.ff1 plus an xor with the correction term
   (XLEN - 1) * (x != 0) -- which passes the xl.ff1 result through for
   a zero input, so clz(0) == XLEN as promised by
   CLZ_DEFINED_VALUE_AT_ZERO -- for both DImode and (via the clzdi2
   wrapper) SImode operands; xl.fl1 must not appear.  */
long test_clzl(long x) { return __builtin_clzl(x); }
int test_clz(unsigned x) { return __builtin_clz(x); }
/* { dg-final { scan-assembler-times "xl\\.ff1" 2 } } */
/* { dg-final { scan-assembler-not "xl\\.fl1" } } */
/* { dg-final { scan-assembler-not "xori" } } */
/* { dg-final { scan-assembler-times "snez" 2 } } */
/* { dg-final { scan-assembler-times "xor" 2 } } */
