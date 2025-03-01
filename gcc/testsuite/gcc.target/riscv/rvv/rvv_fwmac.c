/* { dg-do compile } */

#include <riscv_vector.h>
#include <stddef.h>
#include "rvv-common.h"

/* Takes the scalar type STYPE, vector class VCLASS (int or float), and
   the e and m value.  */
#define VWMAC_VV(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)		\
  void v##OP##VCLASS##EM(size_t n, STYPE *op1, STYPE *op2, WSTYPE * op0, word_type vl)\
  {									\
    v##VCLASST##EM##_t vop1;						\
    v##VCLASST##EM##_t vop2;						\
    v##VCLASST##WEM##_t vop0;						\
    vop0 = VLOAD(VCLASS, WSEW, WEM, op0);					\
    vop1 = VLOAD(VCLASS, SEW, EM, op1);					\
    vop2 = VLOAD(VCLASS, SEW, EM, op2);					\
    vop0 = v##OP##_vv_##VCLASS##WEM (vop0, vop1, vop2, vl);		\
    VSTORE(VCLASS, WSEW, WEM, op0, vop0);					\
  }

#define VWMAC_VX(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)		\
  void x##OP##VCLASS##EM(size_t n, STYPE  op1, STYPE *op2, WSTYPE * op0, word_type vl)\
  {									\
    v##VCLASST##EM##_t vop2;						\
    v##VCLASST##WEM##_t vop0;						\
    vop0 = VLOAD(VCLASS, WSEW, WEM, op0);					\
    vop2 = VLOAD(VCLASS, SEW, EM, op2);					\
    vop0 = v##OP##_vf_##VCLASS##WEM (vop0, op1, vop2, vl);		\
    VSTORE(VCLASS, WSEW, WEM, op0, vop0);					\
  }

#define VWMAC(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)   \
  VWMAC_VV(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)      \
  VWMAC_VX(STYPE, VCLASST, VCLASS, EM, MLEN, WSTYPE, WEM, STYPEC, SEW, WSEW, OP)

RVV_WFLOAT_TEST_ARG(VWMAC, fwmacc)
RVV_WFLOAT_TEST_ARG(VWMAC, fwnmacc)
RVV_WFLOAT_TEST_ARG(VWMAC, fwmsac)
RVV_WFLOAT_TEST_ARG(VWMAC, fwnmsac)

/* { dg-final { scan-assembler-times "vfwmacc.vv" 9 } } */
/* { dg-final { scan-assembler-times "vfwmacc.vf" 9 } } */
/* { dg-final { scan-assembler-times "vfwnmacc.vv" 9 } } */
/* { dg-final { scan-assembler-times "vfwnmacc.vf" 9 } } */
/* { dg-final { scan-assembler-times "vfwmsac.vv" 9 } } */
/* { dg-final { scan-assembler-times "vfwmsac.vf" 9 } } */
/* { dg-final { scan-assembler-times "vfwnmsac.vv" 9 } } */
/* { dg-final { scan-assembler-times "vfwnmsac.vf" 9 } } */
