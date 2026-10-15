/* Verify that non-leaf interrupt handlers do not save every V register.  */
/* { dg-do compile } */
/* { dg-options "-O2 -march=rv64gcv -mabi=lp64d" { target { rv64 } } } */
/* { dg-options "-O2 -march=rv32gcv -mabi=ilp32d" { target { rv32 } } } */

extern void foo (void);

void __attribute__ ((interrupt))
handler (void)
{
  foo ();
}

/* { dg-final { scan-assembler-not {vlenb} } } */
/* { dg-final { scan-assembler-not {vs1r\.v} } } */
/* { dg-final { scan-assembler-not {vl1re[0-9]+\.v} } } */
