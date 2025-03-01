/* { dg-do compile } */

#include <riscv_vector.h>
#include <stddef.h>
#include "rvv-common.h"

/* Takes the scalar type STYPE, vector class VCLASS (int or float), and
   the e and m value.  */
#define VWADDSUB(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)                     \
  void v##OP##VCLASS##EM(size_t n, STYPE *x, STYPE *y, WSTYPE *z, word_type vl) {            \
    v##VCLASST##EM##_t vx, vy;                                               \
    v##VCLASST##WEM##_t vz;                                                  \
    vx = VLOAD(VCLASS, SEW, EM, x);                                               \
    vy = VLOAD(VCLASS, SEW, EM, y);                                               \
    vz = v##OP##_vv_##VCLASS##WEM (vx, vy, vl);                                 \
    VSTORE(VCLASS, WSEW, WEM, z, vz);                                               \
  }                                                                            \
  void v##OP##VCLASS##EM##_s(size_t n, STYPE *x, STYPE y, WSTYPE *z, word_type vl) {         \
    v##VCLASST##EM##_t vx, vy;                                               \
    v##VCLASST##WEM##_t vz;                                                  \
    vx = VLOAD(VCLASS, SEW, EM, x);                                               \
    vz = v##OP##_v##STYPEC##_##VCLASS##WEM (vx, y, vl);                                  \
    VSTORE(VCLASS, WSEW, WEM, z, vz);                                               \
  }

#define VWADDSUBU(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)    \
  void v##OP##u##EM(size_t n, STYPE *x, STYPE *y, WSTYPE *z, word_type vl) {         \
    v##VCLASST##EM##_t vx, vy;                                              \
    v##VCLASST##WEM##_t vz;                                                 \
    vx = VLOAD(VCLASS, SEW, EM, x);                                              \
    vy = VLOAD(VCLASS, SEW, EM, y);                                              \
    vz = v##OP##_vv_##VCLASS##WEM (vx, vy, vl);                                \
    VSTORE(VCLASS, WSEW, WEM, z, vz);                                              \
  }                                                                            \
  void v##OP##u##EM##_s(size_t n, STYPE *x, STYPE y, WSTYPE *z, word_type vl) {      \
    v##VCLASST##EM##_t vx, vy;                                              \
    v##VCLASST##WEM##_t vz;                                                 \
    vx = VLOAD(VCLASS, SEW, EM, x);                                              \
    vz = v##OP##_v##STYPEC##_##VCLASS##WEM (vx, y, vl);                                \
    VSTORE(VCLASS, WSEW, WEM, z, vz);                                              \
  }

#define VWMULSU(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)      \
  void v##OP##VCLASS##EM(size_t n, STYPE *x, u##STYPE *y, WSTYPE *z, word_type vl) {         \
    v##VCLASST##EM##_t vx;                                                   \
    vuint##EM##_t vy;                                                  \
    v##VCLASST##WEM##_t vz;                                                  \
    vx = VLOAD(VCLASS, SEW, EM, x);                                               \
    vy = VULOAD(SEW, EM, y);                                              \
    vz = v##OP##_vv_##VCLASS##WEM (vx, vy, vl);                                 \
    VSTORE(VCLASS, WSEW, WEM, z, vz);                                               \
  }                                                                            \
  void v##OP##VCLASS##EM##_s(size_t n, STYPE *x, u##STYPE y, WSTYPE *z, word_type vl) {      \
    v##VCLASST##EM##_t vx;                                                   \
    vuint##EM##_t vy;                                                  \
    v##VCLASST##WEM##_t vz;                                                  \
    vx = VLOAD(VCLASS, SEW, EM, x);                                               \
    vz = v##OP##_v##STYPEC##_##VCLASS##WEM (vx, y, vl);                                  \
    VSTORE(VCLASS, WSEW, WEM, z, vz);                                               \
  }

RVV_WINT_TEST_ARG(VWADDSUB, wadd)
RVV_WUINT_TEST_ARG(VWADDSUBU, waddu)
RVV_WINT_TEST_ARG(VWADDSUB, wsub)
RVV_WUINT_TEST_ARG(VWADDSUBU, wsubu)
RVV_WINT_TEST_ARG(VWADDSUB, wmul)
RVV_WUINT_TEST_ARG(VWADDSUBU, wmulu)
RVV_WINT_TEST_ARG(VWMULSU, wmulsu)

RVV_WFLOAT_TEST_ARG(VWADDSUB, fwadd)
RVV_WFLOAT_TEST_ARG(VWADDSUB, fwsub)
RVV_WFLOAT_TEST_ARG(VWADDSUB, fwmul)

/* { dg-final { scan-assembler-times "vwadd.vv" 15 } } */
/* { dg-final { scan-assembler-times "vwaddu.vv" 15 } } */
/* { dg-final { scan-assembler-times "vwadd.vx" 15 } } */
/* { dg-final { scan-assembler-times "vwaddu.vx" 15 } } */
/* { dg-final { scan-assembler-times "vwsub.vv" 15 } } */
/* { dg-final { scan-assembler-times "vwsubu.vv" 15 } } */
/* { dg-final { scan-assembler-times "vwsub.vx" 15 } } */
/* { dg-final { scan-assembler-times "vwsubu.vx" 15 } } */
/* { dg-final { scan-assembler-times "vwmul.vv" 15 } } */
/* { dg-final { scan-assembler-times "vwmulu.vv" 15 } } */
/* { dg-final { scan-assembler-times "vwmul.vx" 15 } } */
/* { dg-final { scan-assembler-times "vwmulu.vx" 15 } } */
/* { dg-final { scan-assembler-times "vwmulsu.vv" 15 } } */
/* { dg-final { scan-assembler-times "vwmulsu.vx" 15 } } */
/* { dg-final { scan-assembler-times "vfwadd.vv" 9 } } */
/* { dg-final { scan-assembler-times "vfwadd.vf" 9 } } */
/* { dg-final { scan-assembler-times "vfwsub.vv" 9 } } */
/* { dg-final { scan-assembler-times "vfwsub.vf" 9 } } */
/* { dg-final { scan-assembler-times "vfwmul.vv" 9 } } */
/* { dg-final { scan-assembler-times "vfwmul.vf" 9 } } */
