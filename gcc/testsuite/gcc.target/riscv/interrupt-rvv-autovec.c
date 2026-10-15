/* Verify that interrupt handlers do not use RVV auto-vectorization.  */
/* { dg-do compile } */
/* { dg-options "-O3 -fno-vect-cost-model -march=rv64gcv -mabi=lp64d" { target { rv64 } } } */
/* { dg-options "-O3 -fno-vect-cost-model -march=rv32gcv -mabi=ilp32d" { target { rv32 } } } */

extern int a[256];
extern int b[256];
extern int c[256];

void __attribute__ ((interrupt))
handler (void)
{
  for (int i = 0; i < 256; ++i)
    a[i] = b[i] + c[i];
}

/* Exercise basic-block SLP separately from loop vectorization.  */
void __attribute__ ((interrupt))
handler_slp (void)
{
  a[0] = b[0] + c[0];
  a[1] = b[1] + c[1];
  a[2] = b[2] + c[2];
  a[3] = b[3] + c[3];
}

/* { dg-final { scan-assembler-not {vsetvli|vsetivli} } } */
/* { dg-final { scan-assembler-not {vle[0-9]+\.v} } } */
/* { dg-final { scan-assembler-not {vse[0-9]+\.v} } } */
/* { dg-final { scan-assembler-not {vs[0-9]+r\.v} } } */
/* { dg-final { scan-assembler-not {vlenb} } } */
