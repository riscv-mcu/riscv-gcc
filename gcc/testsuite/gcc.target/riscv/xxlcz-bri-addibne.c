/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Oz" "-Og" "-flto" } { "" } } */
/* { dg-options "-march=rv32imac_xxlczbri -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* { dg-final { scan-assembler-times "xl\\.addibne\t\[a-z0-9\]+,zero,1," 1 } } */
/* { dg-final { scan-assembler-times "xl\\.addibne\t\[a-z0-9\]+,zero,2," 1 } } */
/* { dg-final { scan-assembler-times "xl\\.addibne\t\[a-z0-9\]+,zero,4," 1 } } */
/* { dg-final { scan-assembler-times "xl\\.addibne\t\[a-z0-9\]+,zero,8," 1 } } */

/* Verify that the xl.addibne fusion (addi rd,rd,-N + bne -> xl.addibne) fires
   for the legal scales {1,2,4,8}.  Each loop below increments its counter
   by one of the legal scales and branches back while non-zero, which the
   peephole2 fuses into a single xl.addibne instruction.

   The fusion is gated by TARGET_XXLCZBRI && TARGET_NUCLEI_XXLCZ_AUTOGEN and is
   RV32-only.  It is verified at -O2 where peephole2 reliably sees the adjacent
   addi+bne at the loop latch.  */

int loop_m1(int n)
{
    int s = 0;
    for (int i = n; i != 0; i += 1)
        s += i;
    return s;
}

int loop_m2(int n)
{
    int s = 0;
    for (int i = n; i != 0; i += 2)
        s += i;
    return s;
}

int loop_m4(int n)
{
    int s = 0;
    for (int i = n; i != 0; i += 4)
        s += i;
    return s;
}

int loop_m8(int n)
{
    int s = 0;
    for (int i = n; i != 0; i += 8)
        s += i;
    return s;
}
