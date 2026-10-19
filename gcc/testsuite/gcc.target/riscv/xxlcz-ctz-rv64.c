/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64imac_xxlczbitop -mabi=lp64 -O2 -mautogen-xxlcz" } */
/* ctz maps to xl.fl1 for both DImode and SImode operands; xl.ff1 must
   not appear.  */
long test_ctzl(long x) { return __builtin_ctzl(x); }
int test_ctz(unsigned x) { return __builtin_ctz(x); }
/* { dg-final { scan-assembler-times "xl\\.fl1" 2 } } */
/* { dg-final { scan-assembler-not "xl\\.ff1" } } */
