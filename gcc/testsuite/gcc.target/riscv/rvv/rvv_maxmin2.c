/* { dg-do compile } */

#include <riscv_vector.h>
#include <stddef.h>
#include "rvv-common.h"

/* Takes the scalar type STYPE, vector class VCLASS (int or float), and
   the e and m value.  */
#define VMAXMIN(STYPE, VCLASST, VCLASS, EM, MLEN, STYPEC, SEW)                                       \
  void vmaxmin##VCLASS##EM(size_t n, STYPE *x, STYPE *y, STYPE z, word_type vl) {            \
    v##VCLASST##EM##_t vx, vy;                                                \
    vbool##MLEN##_t mask;                                                    \
    vx = VLOAD(VCLASS, SEW, EM, x);                                                 \
    vy = VLOAD(VCLASS, SEW, EM, y);                                                 \
    mask = MSET (MLEN);                                             \
    vy = vfmax_vv_##VCLASS##EM##_m(mask, vy, vx, vy, vl);                     \
    vy = vfmax_vf_##VCLASS##EM##_m(mask, vy, vy, z, vl);                      \
    vy = vfmin_vv_##VCLASS##EM##_m(mask, vy, vx, vy, vl);                     \
    vy = vfmin_vf_##VCLASS##EM##_m(mask, vy, vy, z, vl);                      \
    VSTORE(VCLASS, SEW, EM, y, vy);                                                  \
  }

RVV_FLOAT_TEST(VMAXMIN)

/* { dg-final { scan-assembler-times "vfmax.vv" 15 } } */
/* { dg-final { scan-assembler-times "vfmax.vf" 15 } } */
/* { dg-final { scan-assembler-times "vfmin.vv" 15 } } */
/* { dg-final { scan-assembler-times "vfmin.vf" 15 } } */
