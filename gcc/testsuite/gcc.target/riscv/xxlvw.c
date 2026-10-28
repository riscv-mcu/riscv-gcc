/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_xxlvw -mabi=lp64 -O3" } */

#include <riscv_vector.h>

vint32m2_t test_vconj_v_i32m2(vint32m2_t vs, size_t vl){
    return __riscv_xl_vconj_v_i32m2(vs, vl);
}

vint32m2_t test_vcpack_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vcpack_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vcunpacki_v_i32m2(vint32m2_t vs2, size_t vl){
    return __riscv_xl_vcunpacki_v_i32m2(vs2, vl);
}

vint32m2_t test_vcunpackr_v_i32m2(vint32m2_t vs2, size_t vl){
    return __riscv_xl_vcunpackr_v_i32m2(vs2, vl);
}

vint32m2_t test_vdscmac_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmac_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmac_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmac_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacj_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacj_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacj_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacj_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacjo_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacjo_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacjo_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacjo_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacjoi_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacjoi_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacjoi_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacjoi_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacjor_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacjor_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacjor_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacjor_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmaco_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmaco_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmaco_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmaco_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacoi_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacoi_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacoi_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacoi_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacor_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacor_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmacor_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmacor_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmul_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmul_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmul_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmul_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmuli_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmuli_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmuli_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmuli_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmulj_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmulj_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmulj_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmulj_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmulji_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmulji_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmulji_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmulji_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmuljr_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmuljr_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmuljr_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmuljr_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmulr_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmulr_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscmulr_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdscmulr_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdscredsum_v_i32m2(vint32m2_t vs2, size_t vl){
    return __riscv_xl_vdscredsum_v_i32m2(vs2, vl);
}

vint32m2_t test_vdsmac_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdsmac_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdsmac_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdsmac_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdsmacini_v_i32m2(vint32m2_t vs2, size_t vl){
    return __riscv_xl_vdsmacini_v_i32m2(vs2, vl);
}

vint32m2_t test_vdsmacini_x_i32m2(int32_t rs1, size_t vl){
    return __riscv_xl_vdsmacini_x_i32m2(rs1, vl);
}

vint32m2_t test_vdsmaco_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdsmaco_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdsmaco_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdsmaco_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdsmul_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdsmul_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdsmul_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vdsmul_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vdsredsum_v_i32m2(vint32m2_t vs, size_t vl){
    return __riscv_xl_vdsredsum_v_i32m2(vs, vl);
}

vint32m2_t test_vdsredsumn_vi_i32m2(vint32m2_t vs2, int32_t rs1, size_t vl){
    return __riscv_xl_vdsredsumn_vi_i32m2(vs2, 3, vl);
}

vint32m2_t test_vdsredsumn_vx_i32m2(vint32m2_t vs2, int32_t rs1, size_t vl){
    return __riscv_xl_vdsredsumn_vx_i32m2(vs2, rs1, vl);
}

vint16m2_t test_vfcvt_b2h_v_i16m2(vint8m1_t vs2, size_t vl){
    return __riscv_xl_vfcvt_b2h_v_i16m2(vs2, vl);
}

vint32m2_t test_vfcvt_b2w_v_i32m2(vint8mf2_t vs2, size_t vl){
    return __riscv_xl_vfcvt_b2w_v_i32m2(vs2, vl);
}

vint16m2_t test_vfcvt_c2p_v_i16m2(vint32m4_t vs2, size_t vl){
    return __riscv_xl_vfcvt_c2p_v_i16m2(vs2, vl);
}

vint8m2_t test_vfcvt_h2b_v_i8m2(vint16m4_t vs2, size_t vl){
    return __riscv_xl_vfcvt_h2b_v_i8m2(vs2, vl);
}

vint32m2_t test_vfcvt_h2w_v_i32m2(vint16m1_t vs2, size_t vl){
    return __riscv_xl_vfcvt_h2w_v_i32m2(vs2, vl);
}

vint32m2_t test_vfcvt_p2c_v_i32m2(vint16m1_t vs2, size_t vl){
    return __riscv_xl_vfcvt_p2c_v_i32m2(vs2, vl);
}

vint8m2_t test_vfcvt_w2b_v_i8m2(vint32m8_t vs2, size_t vl){
    return __riscv_xl_vfcvt_w2b_v_i8m2(vs2, vl);
}

vint16m2_t test_vfcvt_w2h_v_i16m2(vint32m4_t vs2, size_t vl){
    return __riscv_xl_vfcvt_w2h_v_i16m2(vs2, vl);
}

vint32m2_t test_vfsl_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vfsl_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vfsr_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vfsr_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vlsb_v_i32m2(vint32m2_t vs2, size_t vl){
    return __riscv_xl_vlsb_v_i32m2(vs2, vl);
}

vint32m2_t test_vnle_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vnle_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vnle_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vnle_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vnlm_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vnlm_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vnlm_vs_i32m2_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vnlm_vs_i32m2_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vperm_vi_i32m2(vint32m2_t vs2, int32_t rs1, size_t vl){
    return __riscv_xl_vperm_vi_i32m2(vs2, 3, vl);
}

vint32m2_t test_vredmaxi_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vredmaxi_vv_i32m2(vs2, vs1, vl);
}

vint32m2_t test_vredmini_vv_i32m2(vint32m2_t vs2, vint32m2_t vs1, size_t vl){
    return __riscv_xl_vredmini_vv_i32m2(vs2, vs1, vl);
}

/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,\s*m2,\s*t[au],\s*m[au]} 57 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,\s*m4,\s*t[au],\s*m[au]} 2 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,\s*m8,\s*t[au],\s*m[au]} 1 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,\s*m2,\s*t[au],\s*m[au]} 1 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e16,\s*m4,\s*t[au],\s*m[au]} 1 } } */
/* { dg-final { scan-assembler-times {vsetvli\s+[a-x0-9]+,\s*zero,\s*e8,\s*mf2,\s*t[au],\s*m[au]} 1 } } */
/* { dg-final { scan-assembler-times {vconj\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vcpack\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vcunpacki\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vcunpackr\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmac\.vv\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmac\.vs\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacj\.vv\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacj\.vs\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacjo\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacjo\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacjoi\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacjoi\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacjor\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacjor\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmaco\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmaco\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacoi\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacoi\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacor\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmacor\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmul\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmul\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmuli\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmuli\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmulj\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmulj\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmulji\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmulji\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmuljr\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmuljr\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmulr\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscmulr\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdscredsum\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsmac\.vv\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsmac\.vs\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsmacini\.v\s+v[0-9]+,\s*v0\.t} 1 } } */
/* { dg-final { scan-assembler-times {vdsmacini\.s\s+[a-x0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsmaco\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsmaco\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsmul\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsmul\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsredsum\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsredsumn\.vi\s+v[0-9]+,\s*v[0-9]+,\s*[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vdsredsumn\.vs\s+v[0-9]+,\s*v[0-9]+,\s*[a-x0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.b2h\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.b2w\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.c2p\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.h2b\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.h2w\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.p2c\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.w2b\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfcvt\.w2h\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfsl\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vfsr\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vlsb\.v\s+v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vnle\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vnle\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vnlm\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vnlm\.vs\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vperm\.vi\s+v[0-9]+,\s*v[0-9]+,\s*[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vredmaxi\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vredmini\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {vmset\.m\s+v0} 1 } } */
