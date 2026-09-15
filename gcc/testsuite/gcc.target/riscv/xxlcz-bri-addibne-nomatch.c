/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczbri -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* { dg-final { scan-assembler-not "xl\\.addibne" } } */

/* Verify that loop latches the xl.addibne peephole must not fuse stay as
   separate addi + bne instructions:
     - loop_m4:  xl.addibne only increments (rd = rd + scale), so a
		 decrementing latch is not supported
     - loop_p3:  scale 3 is not one of the power-of-two steps 1/2/4/8
     - loop_p16: scale 16 exceeds the 2-bit SCALE encoding (max 8)
   Each still uses the plain two-instruction sequence.  This holds at every
   optimization level (at -O0 the peephole is simply not run).  */

int
loop_m4 (int n)
{
    int s = 0;
    for (int i = n; i != 0; i -= 4)
        s += i;
    return s;
}

int
loop_p3 (int n)
{
    int s = 0;
    for (int i = n; i != 0; i += 3)
        s += i;
    return s;
}

int
loop_p16 (int n)
{
    int s = 0;
    for (int i = n; i != 0; i += 16)
        s += i;
    return s;
}
