/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64imac_xxlczbitop -mabi=lp64 -O2 -mautogen-xxlcz" } */
/* clz maps to xl.ff1 plus an xor of XLEN-1, for both DImode and
   (via the clzdi2 wrapper) SImode operands; xl.fl1 must not appear.  */
long test_clzl(long x) { return __builtin_clzl(x); }
int test_clz(unsigned x) { return __builtin_clz(x); }
/* { dg-final { scan-assembler-times "xl\\.ff1" 2 } } */
/* { dg-final { scan-assembler-not "xl\\.fl1" } } */
/* { dg-final { scan-assembler-times "xori" 2 } } */
