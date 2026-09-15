/* { dg-do compile } */
/* { dg-skip-if "" { *-*-* } { "-O0" "-O1" "-O3" "-Os" "-Oz" "-Og" "-flto" } { "" } } */
/* { dg-options "-march=rv32imac_xxlczbri -mabi=ilp32 -O2 -mautogen-xxlcz" } */
/* { dg-final { scan-assembler-times "xl\\.addibne\t\[a-z0-9\]+,\[a-z0-9\]+,2," 2 } } */

/* Verify that the xl.addibne fusion also fires when the loop counter is
   compared against a variable rather than zero, in either source order.
   The peephole2 accepts both (ne counter other) and (ne other counter)
   comparison forms; ne is commutative so the fused instruction always
   compares the updated counter against the other register (rs1 = a
   named register, not zero).  */

int
loop_var_a (int n, int j)
{
    int s = 0;
    for (int i = n; i != j; i += 2)
        s += i;
    return s;
}

int
loop_var_b (int n, int j)
{
    int s = 0;
    for (int i = n; j != i; i += 2)
        s += i;
    return s;
}
