/* { dg-do compile } */
/* { dg-options "-march=rv32imafdc_xxlfbf -mabi=ilp32d -mcmodel=medany -O" { target { rv32 } } } */
/* { dg-options "-march=rv64imafdc_xxlfbf -mabi=lp64d -mcmodel=medany -O" { target { rv64 } } } */

extern __bf16 bf;
extern __bf16 bf1;
extern __bf16 bf2;
extern   _Float16  hf;
extern      float  sf;
extern      double df;
extern   signed int        si;
extern unsigned int       usi;
extern   signed long long  di;
extern unsigned long long udi;


/* Nuclei bf16_arithmetic */
void bf_add_bf () { bf = bf1 + bf2; }

void bf_sub_bf () { bf = bf1 - bf2; }

void bf_mul_bf () { bf = bf1 * bf2; }

void bf_div_bf () { bf = bf1 / bf2; }

void bf_add_const () { bf = bf1 + 3.14f; }

void const_sub_bf () { bf = 3.14f - bf2; }

void bf_mul_const () { bf = bf1 * 3.14f; }

void const_div_bf () { bf = 3.14f / bf2; }

void bf_inc () { ++bf; }

void bf_dec () { --bf; }

/*Nuclei bf16_comparison */

void bf_lt_bf () { bf = (bf1 < bf2) ? bf1 : bf2; }

void bf_le_bf () { bf = (bf1 <= bf2) ? bf1 : bf2; }

void bf_gt_bf () { bf = (bf1 > bf2) ? bf1 : bf2; }

void bf_ge_bf () { bf = (bf1 >= bf2) ? bf1 : bf2; }

void bf_eq_bf () { bf = (bf1 == bf2) ? bf1 : bf2; }

void bf_lt_const () { bf = (bf1 < 3.14f) ? bf1 : bf2; }

void bf_le_const () { bf = (bf1 <= 3.14f) ? bf1 : bf2; }

void const_gt_bf () { bf = (3.14f > bf2) ? bf1 : bf2; }

void const_ge_bf () { bf = (3.14f >= bf2) ? bf1 : bf2; }

void bf_eq_const () { bf = (bf1 == 3.14f) ? bf1 : bf2; }

/* Nuclei bf16_float_conversion */

void hf_to_bf () { bf = hf; }
void bf_to_hf () { hf = bf; }

void sf_to_bf () { bf = sf; }
void bf_to_sf () { sf = bf; }

void df_to_bf () { bf = df; } 
void bf_to_df () { df = bf; }

/* Nuclei bf16_interger_conversion */

void si_to_bf ()  { bf = si; }
void usi_to_bf () { bf = usi; }
void bf_to_si ()  { si = bf; }
void bf_to_usi () { usi = bf; }

void di_to_bf ()  { bf = di; }
void udi_to_bf () { bf = udi; }
void bf_to_di ()  { di = bf; }
void bf_to_udi () { udi = bf; }

/* Nuclei bf16_arithmetic */
/* { dg-final { scan-assembler-times "fadd.h" 2 } } */
/* { dg-final { scan-assembler-times "fsub.h" 2 } } */
/* { dg-final { scan-assembler-times "fmul.h" 1 } } */
/* { dg-final { scan-assembler-times "fdiv.h" 1 } } */


/* Nuclei bf16_comparison */
/* { dg-final { scan-assembler-times "flt.h" 1 } } */
/* { dg-final { scan-assembler-times "fle.h" 1 } } */
/* { dg-final { scan-assembler-times "fgt.h" 1 } } */
/* { dg-final { scan-assembler-times "fge.h" 1 } } */
/* { dg-final { scan-assembler-times "feq.h" 1 } } */
/* { dg-final { scan-assembler-times "flt.s" 2 } } */
/* { dg-final { scan-assembler-times "fle.s" 2 } } */
/* { dg-final { scan-assembler-times "feq.s" 1 } } */

/* Nuclei bf16_float_conversion */
/* { dg-final { scan-assembler-times "fcvt.bf16.s" 6 } } */
/* { dg-final { scan-assembler-times "fcvt.s.h" 1 } } */
/* { dg-final { scan-assembler-times "fcvt.h.s" 1 } } */
/* { dg-final { scan-assembler-times "fcvt.h.d" 1 } } */
/* { dg-final { scan-assembler-times "fcvt.d.h" 1 } } */

/* Nuclei bf16_interger_conversion */
/* { dg-final { scan-assembler-times "fcvt.h.w\t" 1 } } */
/* { dg-final { scan-assembler-times "fcvt.h.wu" 1 } } */
/* { dg-final { scan-assembler-times "fcvt.w.h" 1 } } */
/* { dg-final { scan-assembler-times "fcvt.wu.h" 1 } } */
/* { dg-final { scan-assembler-times "fcvt.h.l\t" 1 { target { rv64 } } } } */
/* { dg-final { scan-assembler-times "fcvt.h.lu" 1 { target { rv64 } } } } */
/* { dg-final { scan-assembler-times "fcvt.l.h" 1 { target { rv64 } } } } */
/* { dg-final { scan-assembler-times "fcvt.lu.h" 1 { target { rv64 } } } } */

/* { dg-final { scan-assembler-times "fcvt.s.bf16" 13 { target { rv32 } } } } */
/* { dg-final { scan-assembler-times "fcvt.s.bf16" 11 { target { rv64 } } } } */

/* rv32: 64-bit integer conversions fall back to libgcc calls */
/* { dg-final { scan-assembler-times "call\t__floatdibf" 1 { target { rv32 } } } } */
/* { dg-final { scan-assembler-times "call\t__floatundibf" 1 { target { rv32 } } } } */
/* { dg-final { scan-assembler-times "call\t__fixsfdi" 1 { target { rv32 } } } } */
/* { dg-final { scan-assembler-times "call\t__fixunssfdi" 1 { target { rv32 } } } } */
/* rv64: all conversions are done by hardware instructions */
/* { dg-final { scan-assembler-not "call" { target { rv64 } } } } */
