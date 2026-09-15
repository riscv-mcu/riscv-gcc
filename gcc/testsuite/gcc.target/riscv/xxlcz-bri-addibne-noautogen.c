/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczbri -mabi=ilp32 -O2" } */
/* { dg-final { scan-assembler-not "xl\\.addibne" } } */

/* Without -mautogen-xxlcz, the xl.addibne fusion must NOT fire even though the
   loop shapes are fusible.  The fusion is gated by TARGET_NUCLEI_XXLCZ_AUTOGEN,
   which is off unless -mautogen-xxlcz is passed.  */

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
