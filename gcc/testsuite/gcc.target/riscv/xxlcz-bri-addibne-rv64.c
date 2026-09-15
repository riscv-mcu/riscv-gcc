/* { dg-do compile } */
/* { dg-require-effective-target rv64 } */
/* { dg-options "-march=rv64imac_xxlczbri -mabi=lp64 -O2 -mautogen-xxlcz" } */
/* { dg-final { scan-assembler-not "xl\\.addibne" } } */

/* The xl.addibne fusion is RV32-only: the peephole2 matches the SImode
   decrement-and-compare latch shape, and RV64 loop counters are DImode.
   Even with the xxlczbri extension and -mautogen-xxlcz enabled, the latch
   must stay a separate addi + bne pair.  */

int
loop_m1 (long n)
{
    int s = 0;
    for (long i = n; i != 0; i += 1)
        s += 1;
    return s;
}

int
loop_m2 (long n)
{
    int s = 0;
    for (long i = n; i != 0; i += 2)
        s += 2;
    return s;
}
