/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_xxlvfbf -mabi=lp64 -O3" } */

#include "riscv_vector.h"

typedef _Float16 bfloat16_t;

vbfloat16mf4_t test_vfadd_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfadd_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfadd_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfadd_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfsub_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfsub_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfsub_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfsub_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfrsub_vf_bf16mf4(vbfloat16mf4_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfrsub_vf_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfrsub_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfrsub_vf_bf16m8(op1, op2, vl);
}

vfloat32mf2_t test_vfwadd_vv_f32mf2(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfwadd_vv_f32mf2(op1, op2, vl);
}

vfloat32m8_t test_vfwadd_vv_f32m8(vbfloat16m4_t op1, vbfloat16m4_t op2, size_t vl) {
  return __riscv_xl_vfwadd_vv_f32m8(op1, op2, vl);
}

vfloat32mf2_t test_vfwadd_wv_f32mf2(vfloat32mf2_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfwadd_wv_f32mf2(op1, op2, vl);
}

vfloat32m8_t test_vfwadd_wv_f32m8(vfloat32m8_t op1, vbfloat16m4_t op2, size_t vl) {
  return __riscv_xl_vfwadd_wv_f32m8(op1, op2, vl);
}

vfloat32mf2_t test_vfwadd_wf_f32mf2(vfloat32mf2_t op1, __bf16 op2, size_t vl) {
  return __riscv_xl_vfwadd_wf_f32mf2(op1, op2, vl);
}

vfloat32m8_t test_vfwadd_wf_f32m8(vfloat32m8_t op1, __bf16 op2, size_t vl) {
  return __riscv_xl_vfwadd_wf_f32m8(op1, op2, vl);
}

vfloat32mf2_t test_vfwsub_vv_f32mf2(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfwsub_vv_f32mf2(op1, op2, vl);
}

vfloat32m8_t test_vfwsub_vv_f32m8(vbfloat16m4_t op1, vbfloat16m4_t op2, size_t vl) {
  return __riscv_xl_vfwsub_vv_f32m8(op1, op2, vl);
}

vfloat32mf2_t test_vfwsub_wv_f32mf2(vfloat32mf2_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfwsub_wv_f32mf2(op1, op2, vl);
}

vfloat32m8_t test_vfwsub_wv_f32m8(vfloat32m8_t op1, vbfloat16m4_t op2, size_t vl) {
  return __riscv_xl_vfwsub_wv_f32m8(op1, op2, vl);
}

vfloat32mf2_t test_vfwsub_wf_f32mf2(vfloat32mf2_t op1, __bf16 op2, size_t vl) {
  return __riscv_xl_vfwsub_wf_f32mf2(op1, op2, vl);
}

vfloat32m8_t test_vfwsub_wf_f32m8(vfloat32m8_t op1, __bf16 op2, size_t vl) {
  return __riscv_xl_vfwsub_wf_f32m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfmul_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfmul_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfmul_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfmul_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfdiv_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfdiv_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfdiv_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfdiv_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfrdiv_vf_bf16mf4(vbfloat16mf4_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfrdiv_vf_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfrdiv_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfrdiv_vf_bf16m8(op1, op2, vl);
}

vfloat32mf2_t test_vfwmul_vv_f32mf2(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfwmul_vv_f32mf2(op1, op2, vl);
}

vfloat32m8_t test_vfwmul_vf_f32m8(vbfloat16m4_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfwmul_vf_f32m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfmacc_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfmacc_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfmacc_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfmacc_vf_bf16m8(vd, rs1, vs2, vl);
}

vbfloat16mf4_t test_vfnmacc_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfnmacc_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfnmacc_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfnmacc_vf_bf16m8(vd, rs1, vs2, vl);
}

vbfloat16mf4_t test_vfmsac_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfmsac_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfmsac_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfmsac_vf_bf16m8(vd, rs1, vs2, vl);
}

vbfloat16mf4_t test_vfnmsac_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfnmsac_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfnmsac_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfnmsac_vf_bf16m8(vd, rs1, vs2, vl);
}

vbfloat16mf4_t test_vfmadd_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfmadd_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfmadd_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfmadd_vf_bf16m8(vd, rs1, vs2, vl);
}

vbfloat16mf4_t test_vfnmadd_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfnmadd_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfnmadd_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfnmadd_vf_bf16m8(vd, rs1, vs2, vl);
}

vbfloat16mf4_t test_vfmsub_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfmsub_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfmsub_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfmsub_vf_bf16m8(vd, rs1, vs2, vl);
}

vbfloat16mf4_t test_vfnmsub_vv_bf16mf4(vbfloat16mf4_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfnmsub_vv_bf16mf4(vd, vs1, vs2, vl);
}

vbfloat16m8_t test_vfnmsub_vf_bf16m8(vbfloat16m8_t vd, bfloat16_t rs1, vbfloat16m8_t vs2, size_t vl) {
  return __riscv_xl_vfnmsub_vf_bf16m8(vd, rs1, vs2, vl);
}

vfloat32mf2_t test_vfwmacc_vv_f32mf2(vfloat32mf2_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfwmacc_vv_f32mf2(vd, vs1, vs2, vl);
}

vfloat32m8_t test_vfwmacc_vf_f32m8(vfloat32m8_t vd, bfloat16_t vs1, vbfloat16m4_t vs2, size_t vl) {
  return __riscv_xl_vfwmacc_vf_f32m8(vd, vs1, vs2, vl);
}

vfloat32mf2_t test_vfwnmacc_vv_f32mf2(vfloat32mf2_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfwnmacc_vv_f32mf2(vd, vs1, vs2, vl);
}

vfloat32m8_t test_vfwnmacc_vf_f32m8(vfloat32m8_t vd, bfloat16_t vs1, vbfloat16m4_t vs2, size_t vl) {
  return __riscv_xl_vfwnmacc_vf_f32m8(vd, vs1, vs2, vl);
}

vfloat32mf2_t test_vfwmsac_vv_f32mf2(vfloat32mf2_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfwmsac_vv_f32mf2(vd, vs1, vs2, vl);
}

vfloat32m8_t test_vfwmsac_vf_f32m8(vfloat32m8_t vd, bfloat16_t vs1, vbfloat16m4_t vs2, size_t vl) {
  return __riscv_xl_vfwmsac_vf_f32m8(vd, vs1, vs2, vl);
}

vfloat32mf2_t test_vfwnmsac_vv_f32mf2(vfloat32mf2_t vd, vbfloat16mf4_t vs1, vbfloat16mf4_t vs2, size_t vl) {
  return __riscv_xl_vfwnmsac_vv_f32mf2(vd, vs1, vs2, vl);
}

vfloat32m8_t test_vfwnmsac_vf_f32m8(vfloat32m8_t vd, bfloat16_t vs1, vbfloat16m4_t vs2, size_t vl) {
  return __riscv_xl_vfwnmsac_vf_f32m8(vd, vs1, vs2, vl);
}

vbfloat16mf4_t test_vfsqrt_v_bf16mf4(vbfloat16mf4_t op1, size_t vl) {
  return __riscv_xl_vfsqrt_v_bf16mf4(op1, vl);
}

vbfloat16m8_t test_vfsqrt_v_bf16m8(vbfloat16m8_t op1, size_t vl) {
  return __riscv_xl_vfsqrt_v_bf16m8(op1, vl);
}

vbfloat16mf4_t test_vfrsqrt7_v_bf16mf4(vbfloat16mf4_t op1, size_t vl) {
  return __riscv_xl_vfrsqrt7_v_bf16mf4(op1, vl);
}

vbfloat16m8_t test_vfrsqrt7_v_bf16m8(vbfloat16m8_t op1, size_t vl) {
  return __riscv_xl_vfrsqrt7_v_bf16m8(op1, vl);
}

vbfloat16mf4_t test_vfrec7_v_bf16mf4(vbfloat16mf4_t op1, size_t vl) {
  return __riscv_xl_vfrec7_v_bf16mf4(op1, vl);
}

vbfloat16m8_t test_vfrec7_v_bf16m8(vbfloat16m8_t op1, size_t vl) {
  return __riscv_xl_vfrec7_v_bf16m8(op1, vl);
}

vbfloat16mf4_t test_vfmin_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfmin_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfmin_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfmin_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfmax_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfmax_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfmax_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfmax_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfsgnj_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfsgnj_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfsgnj_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfsgnj_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfsgnjn_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfsgnjn_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfsgnjn_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfsgnjn_vf_bf16m8(op1, op2, vl);
}

vbfloat16mf4_t test_vfsgnjx_vv_bf16mf4(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vfsgnjx_vv_bf16mf4(op1, op2, vl);
}

vbfloat16m8_t test_vfsgnjx_vf_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vfsgnjx_vf_bf16m8(op1, op2, vl);
}

vbool64_t test_vmfeq_vv_bf16mf4_b64(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vmfeq_vv_bf16mf4_b64(op1, op2, vl);
}

vbool2_t test_vmfeq_vf_bf16m8_b2(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vmfeq_vf_bf16m8_b2(op1, op2, vl);
}

vbool64_t test_vmfne_vv_bf16mf4_b64(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vmfne_vv_bf16mf4_b64(op1, op2, vl);
}

vbool2_t test_vmfne_vf_bf16m8_b2(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vmfne_vf_bf16m8_b2(op1, op2, vl);
}

vbool64_t test_vmflt_vv_bf16mf4_b64(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vmflt_vv_bf16mf4_b64(op1, op2, vl);
}

vbool2_t test_vmflt_vf_bf16m8_b2(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vmflt_vf_bf16m8_b2(op1, op2, vl);
}

vbool64_t test_vmfle_vv_bf16mf4_b64(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vmfle_vv_bf16mf4_b64(op1, op2, vl);
}

vbool2_t test_vmfle_vf_bf16m8_b2(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vmfle_vf_bf16m8_b2(op1, op2, vl);
}

vbool64_t test_vmfgt_vv_bf16mf4_b64(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vmfgt_vv_bf16mf4_b64(op1, op2, vl);
}

vbool2_t test_vmfgt_vf_bf16m8_b2(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vmfgt_vf_bf16m8_b2(op1, op2, vl);
}

vbool64_t test_vmfge_vv_bf16mf4_b64(vbfloat16mf4_t op1, vbfloat16mf4_t op2, size_t vl) {
  return __riscv_xl_vmfge_vv_bf16mf4_b64(op1, op2, vl);
}

vbool2_t test_vmfge_vf_bf16m8_b2(vbfloat16m8_t op1, bfloat16_t op2, size_t vl) {
  return __riscv_xl_vmfge_vf_bf16m8_b2(op1, op2, vl);
}

vuint16mf4_t test_vfclass_v_u16mf4(vbfloat16mf4_t op1, size_t vl) {
  return __riscv_xl_vfclass_v_u16mf4(op1, vl);
}

vuint16m8_t test_vfclass_v_u16m8(vbfloat16m8_t op1, size_t vl) {
  return __riscv_xl_vfclass_v_u16m8(op1, vl);
}

vbfloat16mf4_t test_vfmerge_vfm_bf16mf4(vbfloat16mf4_t op1, bfloat16_t op2, vbool64_t mask, size_t vl) {
  return __riscv_xl_vfmerge_vfm_bf16mf4(op1, op2, mask, vl);
}

vbfloat16m8_t test_vfmerge_vfm_bf16m8(vbfloat16m8_t op1, bfloat16_t op2, vbool2_t mask, size_t vl) {
  return __riscv_xl_vfmerge_vfm_bf16m8(op1, op2, mask, vl);
}

vbfloat16mf4_t test_vfmv_v_f_bf16mf4(bfloat16_t src, size_t vl) {
  return __riscv_xl_vfmv_v_f_bf16mf4(src, vl);
}

vbfloat16m8_t test_vfmv_v_f_bf16m8(bfloat16_t src, size_t vl) {
  return __riscv_xl_vfmv_v_f_bf16m8(src, vl);
}

vint16mf4_t test_vfcvt_x_f_v_i16mf4(vbfloat16mf4_t src, size_t vl) {
  return __riscv_xl_vfcvt_x_f_v_i16mf4(src, vl);
}

vuint16m8_t test_vfcvt_xu_f_v_u16m8(vbfloat16m8_t src, size_t vl) {
  return __riscv_xl_vfcvt_xu_f_v_u16m8(src, vl);
}

vbfloat16mf4_t test_vfcvt_f_x_v_bf16mf4(vint16mf4_t src, size_t vl) {
  return __riscv_xl_vfcvt_f_x_v_bf16mf4(src, vl);
}

vbfloat16m8_t test_vfcvt_f_xu_v_bf16m8(vuint16m8_t src, size_t vl) {
  return __riscv_xl_vfcvt_f_xu_v_bf16m8(src, vl);
}

vint16mf4_t test_vfcvt_rtz_x_f_v_i16mf4(vbfloat16mf4_t src, size_t vl) {
  return __riscv_xl_vfcvt_rtz_x_f_v_i16mf4(src, vl);
}

vuint16m8_t test_vfcvt_rtz_xu_f_v_u16m8(vbfloat16m8_t src, size_t vl) {
  return __riscv_xl_vfcvt_rtz_xu_f_v_u16m8(src, vl);
}

vbfloat16mf4_t test_vfwcvt_f_x_v_bf16mf4(vint8mf8_t src, size_t vl) {
  return __riscv_xl_vfwcvt_f_x_v_bf16mf4(src, vl);
}

vuint32m8_t test_vfwcvt_xu_f_v_u32m8(vbfloat16m4_t src, size_t vl) {
  return __riscv_xl_vfwcvt_xu_f_v_u32m8(src, vl);
}

vint8mf8_t test_vfncvt_x_f_w_i8mf8(vbfloat16mf4_t src, size_t vl) {
  return __riscv_xl_vfncvt_x_f_w_i8mf8(src, vl);
}

vbfloat16m4_t test_vfncvt_f_xu_w_bf16m4(vuint32m8_t src, size_t vl) {
  return __riscv_xl_vfncvt_f_xu_w_bf16m4(src, vl);
}

vbfloat16m1_t test_vfredosum_vs_bf16mf4_bf16m1(vbfloat16mf4_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredosum_vs_bf16mf4_bf16m1(vector, scalar, vl);
}

vbfloat16m1_t test_vfredosum_vs_bf16m8_bf16m1(vbfloat16m8_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredosum_vs_bf16m8_bf16m1(vector, scalar, vl);
}

vbfloat16m1_t test_vfredusum_vs_bf16mf4_bf16m1(vbfloat16mf4_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredusum_vs_bf16mf4_bf16m1(vector, scalar, vl);
}

vbfloat16m1_t test_vfredusum_vs_bf16m8_bf16m1(vbfloat16m8_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredusum_vs_bf16m8_bf16m1(vector, scalar, vl);
}

vbfloat16m1_t test_vfredmax_vs_bf16mf4_bf16m1(vbfloat16mf4_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredmax_vs_bf16mf4_bf16m1(vector, scalar, vl);
}

vbfloat16m1_t test_vfredmax_vs_bf16m8_bf16m1(vbfloat16m8_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredmax_vs_bf16m8_bf16m1(vector, scalar, vl);
}

vbfloat16m1_t test_vfredmin_vs_bf16mf4_bf16m1(vbfloat16mf4_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredmin_vs_bf16mf4_bf16m1(vector, scalar, vl);
}

vbfloat16m1_t test_vfredmin_vs_bf16m8_bf16m1(vbfloat16m8_t vector, vbfloat16m1_t scalar, size_t vl) {
  return __riscv_xl_vfredmin_vs_bf16m8_bf16m1(vector, scalar, vl);
}

vfloat32m1_t test_vfwredosum_vs_bf16mf4_f32m1(vbfloat16mf4_t vector, vfloat32m1_t scalar, size_t vl) {
  return __riscv_xl_vfwredosum_vs_bf16mf4_f32m1(vector, scalar, vl);
}

vfloat32m1_t test_vfwredosum_vs_bf16m8_f32m1(vbfloat16m8_t vector, vfloat32m1_t scalar, size_t vl) {
  return __riscv_xl_vfwredosum_vs_bf16m8_f32m1(vector, scalar, vl);
}

vfloat32m1_t test_vfwredusum_vs_bf16mf4_f32m1(vbfloat16mf4_t vector, vfloat32m1_t scalar, size_t vl) {
  return __riscv_xl_vfwredusum_vs_bf16mf4_f32m1(vector, scalar, vl);
}

vfloat32m1_t test_vfwredusum_vs_bf16m8_f32m1(vbfloat16m8_t vector, vfloat32m1_t scalar, size_t vl) {
  return __riscv_xl_vfwredusum_vs_bf16m8_f32m1(vector, scalar, vl);
}

vbfloat16mf4_t test_vfslide1up_vf_bf16mf4(vbfloat16mf4_t src, bfloat16_t value, size_t vl) {
  return __riscv_xl_vfslide1up_vf_bf16mf4(src, value, vl);
}

vbfloat16m8_t test_vfslide1up_vf_bf16m8(vbfloat16m8_t src, bfloat16_t value, size_t vl) {
  return __riscv_xl_vfslide1up_vf_bf16m8(src, value, vl);
}

vbfloat16mf4_t test_vfslide1down_vf_bf16mf4(vbfloat16mf4_t src, bfloat16_t value, size_t vl) {
  return __riscv_xl_vfslide1down_vf_bf16mf4(src, value, vl);
}

vbfloat16m8_t test_vfslide1down_vf_bf16m8(vbfloat16m8_t src, bfloat16_t value, size_t vl) {
  return __riscv_xl_vfslide1down_vf_bf16m8(src, value, vl);
}

vbfloat16mf4_t test_vrgather_vv_bf16mf4(vbfloat16mf4_t src, vuint16mf4_t value, size_t vl) {
  return __riscv_xl_vrgather_vv_bf16mf4(src, value, vl);
}

vbfloat16mf4_t test_vrgather_vx_bf16mf4(vbfloat16mf4_t src, size_t value, size_t vl) {
  return __riscv_xl_vrgather_vx_bf16mf4(src, value, vl);
}

vbfloat16mf4_t test_vrgatherei16_vv_bf16mf4(vbfloat16mf4_t src, vuint16mf4_t value, size_t vl) {
  return __riscv_xl_vrgatherei16_vv_bf16mf4(src, value, vl);
}

vbfloat16mf4_t test_vcompress_vm_bf16mf4(vbfloat16mf4_t src, vbool64_t mask, size_t vl) {
  return __riscv_xl_vcompress_vm_bf16mf4(src, mask, vl);
}

vbfloat16mf4_t test_vmv_v_v_bf16mf4(vbfloat16mf4_t src, size_t vl) {
  return __riscv_xl_vmv_v_v_bf16mf4(src, vl);
}

/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,\s*mf4,\s*t[au],\s*m[au]} 58 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,\s*m4,\s*t[au],\s*m[au]} 13 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,\s*m8,\s*t[au],\s*m[au]} 42 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e8,\s*mf8,\s*t[au],\s*m[au]} 2 } } */
/* { dg-final { scan-assembler-times {vfadd\.v[fv]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfsub\.v[fv]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfrsub\.vf\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwadd\.[wv]v\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 6 } } */
/* { dg-final { scan-assembler-times {vfwsub\.[wv]v\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 4 } } */
/* { dg-final { scan-assembler-times {vfwsub\.wf\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmul\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfdiv\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfrdiv\.vf\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwmul\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmacc\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfnmacc\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmsac\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfnmsac\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmadd\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfnmadd\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmsub\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfnmsub\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwmaccbf16\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwnmacc\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwmsac\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwnmsac\.v[vf]\s+v[0-9]+,\s*[vfa]+[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfsqrt\.v\s+v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfrsqrt7\.v\s+v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfrec7\.v\s+v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmin\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmax\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfsgnj\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfsgnjn\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfsgnjx\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vmfeq\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vmfne\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vmflt\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vmfle\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vmfgt\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vmfge\.v[vf]\s+v[0-9]+,\s*v[0-9]+,\s*[vfa]+[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfclass\.v\s+v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfmerge\.vfm\s+v[0-9]+,\s*v[0-9]+,\s*fa[0-9]+,\s*v0} 2 } } */
/* { dg-final { scan-assembler-times {vfmv\.v\.f\s+v[0-9]+,\s*fa[0-9]+} 4 } } */
/* { dg-final { scan-assembler-times {vmv\.v\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.x\.f\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.xu\.f\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.f\.x\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.f\.xu\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.rtz\.x\.f\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.rtz\.xu\.f\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfwcvt\.f\.x\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfwcvt\.xu\.f\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfncvt\.x\.f\.w\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfncvt\.f\.xu\.w\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfredosum\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfredusum\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfredmax\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfredmin\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwredosum\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfwredusum\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfslide1up\.vf\s+v[0-9]+,\s*v[0-9]+,\s*fa[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vfslide1down\.vf\s+v[0-9]+,\s*v[0-9]+,\s*fa[0-9]+} 2 } } */
/* { dg-final { scan-assembler-times {vrgather\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vrgather\.vx\s+v[0-9]+,\s*v[0-9]+,\s*[a-x0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vrgatherei16\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vcompress\.vm\s+v[0-9]+,\s*v[0-9]+,\s*v0} 1 } } */
