/* Interrupt restrictions must not affect neighboring ordinary functions
   or the layout of shared GNU vector types.  */
/* { dg-do compile } */
/* { dg-options "-O3 -fno-vect-cost-model -march=rv64gcv -mabi=lp64d" { target { rv64 } } } */
/* { dg-options "-O3 -fno-vect-cost-model -march=rv32gcv -mabi=ilp32d" { target { rv32 } } } */

typedef int v4si __attribute__ ((vector_size (16)));
extern v4si va, vb, vc;
extern int a[256], b[256], c[256];
extern char dst[128], src[128];

void __attribute__ ((noinline, noclone))
ordinary_before (void)
{
  for (int i = 0; i < 256; ++i)
    a[i] = b[i] + c[i];
}

void __attribute__ ((interrupt))
handler (void)
{
  for (int i = 0; i < 256; ++i)
    a[i] = b[i] + c[i];
}

void __attribute__ ((noinline, noclone))
ordinary_after (void)
{
  for (int i = 0; i < 256; ++i)
    a[i] = b[i] - c[i];
}

void __attribute__ ((noinline, noclone))
ordinary_vector (void)
{
  va = vb + vc;
}

void __attribute__ ((noinline, noclone))
ordinary_copy (void)
{
  __builtin_memcpy (dst, src, 64);
}

/* { dg-final { scan-assembler {vadd\.vv} } } */
/* { dg-final { scan-assembler {vsub\.vv} } } */
/* { dg-final { scan-assembler {vle8\.v} } } */
/* { dg-final { scan-assembler-not {handler:(?:(?!\.size\s+handler).)*\t(?:v[a-z0-9]+\.[a-z0-9]+|vsetvli|vsetivli|vsetvl)\t} } } */
/* { dg-final { scan-assembler-not {vlenb} } } */
