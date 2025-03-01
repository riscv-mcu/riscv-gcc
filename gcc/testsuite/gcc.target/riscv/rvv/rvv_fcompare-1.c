/* { dg-do compile } */

#include <riscv_vector.h>
#include <stddef.h>
#include "rvv-common.h"

/* Takes the scalar type STYPE, vector class VCLASS (int or float), and
   the e and m value.  */
#define VCOMPARE_VV(STYPE, VCLASST, VCLASS, EM, MLEN, STYPEC, SEW, OP)                               \
  void v##OP##VCLASS##EM##_vv(size_t n, STYPE *x, STYPE *y, STYPE z, word_type vl) {         \
    v##VCLASST##EM##_t vx, vy;                                               \
    vbool##MLEN##_t mask;                                                   \
    vx = VLOAD(VCLASS, SEW, EM, x);                                               \
    vy = VLOAD(VCLASS, SEW, EM, y);                                               \
    mask = vmf##OP##_vv_##VCLASS##EM##_b##MLEN(vx, vy, vl);                           \
    vx = vfadd_vv_##VCLASS##EM##_m (mask, vy, vx, vy, vl);                    \
    VSTORE(VCLASS, SEW, EM, x, vx);                                                \
  }

#define VCOMPARE_VF(STYPE, VCLASST, VCLASS, EM, MLEN, STYPEC, SEW, OP)                               \
  void v##OP##VCLASS##EM##_vx(size_t n, STYPE *x, STYPE *y, STYPE z, word_type vl) {         \
    v##VCLASST##EM##_t vx, vy;                                               \
    vbool##MLEN##_t mask;                                                   \
    vx = VLOAD(VCLASS, SEW, EM, x);                                               \
    vy = VLOAD(VCLASS, SEW, EM, y);                                               \
    mask = vmf##OP##_vf_##VCLASS##EM##_b##MLEN(vx, z, vl);                                 \
    vx = vfadd_vv_##VCLASS##EM##_m (mask, vy, vx, vy, vl);                    \
    VSTORE(VCLASS, SEW, EM, x, vx);                                                \
  }

#define TEST_COMPARE(STYPE, VCLASST, VCLASS, EM, MLEN, STYPEC, SEW, OP)		\
  VCOMPARE_VV (STYPE, VCLASST, VCLASS, EM, MLEN, STYPEC, SEW, OP)			\
  VCOMPARE_VF (STYPE, VCLASST, VCLASS, EM, MLEN, STYPEC, SEW, OP)

RVV_FLOAT_TEST_ARG(TEST_COMPARE, eq)
/* { dg-final { scan-assembler-times "vmfeq.vv" 15 } } */
/* { dg-final { scan-assembler-times "vmfeq.vf" 15 } } */
RVV_FLOAT_TEST_ARG(TEST_COMPARE, ne)
/* { dg-final { scan-assembler-times "vmfne.vv" 15 } } */
/* { dg-final { scan-assembler-times "vmfne.vf" 15 } } */
RVV_FLOAT_TEST_ARG(TEST_COMPARE, lt)
/* { dg-final { scan-assembler-times "vmflt.vv" 15 } } */
/* { dg-final { scan-assembler-times "vmflt.vf" 15 } } */
RVV_FLOAT_TEST_ARG(TEST_COMPARE, le)
/* { dg-final { scan-assembler-times "vmfle.vv" 15 } } */
/* { dg-final { scan-assembler-times "vmfle.vf" 15 } } */
RVV_FLOAT_TEST_ARG(VCOMPARE_VF, gt)
/* { dg-final { scan-assembler-times "vmfgt.vf" 15 } } */
RVV_FLOAT_TEST_ARG(VCOMPARE_VF, ge)
/* { dg-final { scan-assembler-times "vmfge.vf" 15 } } */
