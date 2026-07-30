/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlcz -mabi=ilp32 -O2" } */
/* { dg-final { scan-assembler-not "xl\\." } } */

/* With the default (-mno-autogen-xxlcz), none of the plain-C constructs below
   may auto-generate any xxlcz instruction.  Every xxlcz auto-generation path is
   gated by TARGET_NUCLEI_XXLCZ_AUTOGEN, which is off unless -mautogen-xxlcz is
   passed.  The builtin (UNSPEC) xl_* patterns are irrelevant here since no
   __builtin_xl_* is used.  */

#include <stdint.h>

unsigned int extract_5bits(unsigned int x) { return (x >> 3) & 0x1F; }            /* xl.extractu */
unsigned int bset_16bits(unsigned int x) { return x | (((1U << 16) - 1) << 8); }  /* xl.bset */
unsigned int bclr_12bits(unsigned int x) { return x & ~(((1U << 12) - 1) << 10); }/* xl.bclr */
int clz_val(unsigned int x) { return __builtin_clz(x); }                          /* xl.ff1 */
int ctz_val(unsigned int x) { return __builtin_ctz(x); }                          /* xl.fl1 */
unsigned int slet_val(unsigned int a, unsigned int b) { return (a <= b) ? 1 : 0; } /* xl.slet */
int muli_val(int a) { return a * 7; }                                             /* xl.muli */
int postinc_load(int *p, int n) { int s = 0; for (int i = 0; i < n; i++) s += *p++; return s; } /* xl.lw */
int branch_eq_neg1(int a, int b, int c) { if (a == -1) return b - c; return c - b; } /* xl.beqi */
