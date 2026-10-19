/* { dg-do compile } */
/* { dg-require-effective-target rv32 } */
/* { dg-options "-march=rv32imac_xxlczbitop -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* xl.fl1 (find the last '1' seen from the MSB) returns the bit index
   of the least significant set bit, which is exactly ctz; xl.ff1 must
   not be used (it finds the first '1' from the MSB, i.e. the MSB set
   bit index).  */
int test_ctz(unsigned x) { return __builtin_ctz(x); }
/* { dg-final { scan-assembler-times "xl\\.fl1" 1 } } */
/* { dg-final { scan-assembler-not "xl\\.ff1" } } */
