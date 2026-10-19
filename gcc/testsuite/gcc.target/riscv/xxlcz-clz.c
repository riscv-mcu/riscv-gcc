/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32imac_xxlczbitop -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* xl.ff1 (find the first '1' seen from the MSB) returns the bit index
   of the most significant set bit, so clz must compile to xl.ff1 plus
   an xor of XLEN-1, and must not use xl.fl1 (which finds the last
   '1' seen from the MSB, i.e. the ctz value).  */
int test_clz(unsigned x) { return __builtin_clz(x); }
/* { dg-final { scan-assembler-times "xl\\.ff1" 1 } } */
/* { dg-final { scan-assembler-not "xl\\.fl1" } } */
/* { dg-final { scan-assembler-times "xori" 1 } } */
