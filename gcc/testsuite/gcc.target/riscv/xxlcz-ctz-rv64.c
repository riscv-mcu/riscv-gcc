/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64imac_xxlczbitop -mabi=lp64 -O2 -mautogen-xxlcz" } */
/* ctz maps to xl.fl1 for DImode; SImode on rv64 deliberately does not
   use the xl path (xl.fl1 is XLEN-wide: an SImode operand's upper 32
   bits are unspecified, and fl1(0) would be 64 instead of the
   CTZ_DEFINED_VALUE_AT_ZERO-promised 32), so it is expanded through
   the zero-extended DImode form instead.  xl.ff1 must not appear.  */
long test_ctzl(long x) { return __builtin_ctzl(x); }
int test_ctz(unsigned x) { return __builtin_ctz(x); }
/* { dg-final { scan-assembler-times "xl\\.fl1" 2 } } */
/* { dg-final { scan-assembler-not "xl\\.ff1" } } */
