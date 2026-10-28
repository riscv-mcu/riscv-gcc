/* { dg-do compile } */
/* { dg-options "-march=rv64gcv_xxlvqmacc -mabi=lp64 -O3" } */

#include <riscv_vector.h>

vint32m1_t test_xl_vqmacc_4x4x4_i32m1(vint32m1_t vd, vint8m1_t vs1, vint8mf4_t vs2, size_t vl) {
    return __riscv_xl_vqmacc_4x4x4_i32m1(vd, vs1, vs2, vl);
}

vint32m1_t test_xl_vqmaccsu_4x4x4_i32m1(vint32m1_t vd, vint8m1_t vs1, vuint8mf4_t vs2, size_t vl) {
    return __riscv_xl_vqmaccsu_4x4x4_i32m1(vd, vs1, vs2, vl);
}

vint32m1_t test_xl_vqmaccu_4x4x4_i32m1(vint32m1_t vd, vuint8m1_t vs1, vuint8mf4_t vs2, size_t vl) {
    return __riscv_xl_vqmaccu_4x4x4_i32m1(vd, vs1, vs2, vl);
}

vint32m1_t test_xl_vqmaccus_4x4x4_i32m1(vint32m1_t vd, vuint8m1_t vs1, vint8mf4_t vs2, size_t vl) {
    return __riscv_xl_vqmaccus_4x4x4_i32m1(vd, vs1, vs2, vl);
}

/* { dg-final { scan-assembler-times {vsetvli\s+zero,\s*[a-x0-9]+,\s*e32,\s*m1,\s*t[au],\s*m[au]} 4 } } */
/* { dg-final { scan-assembler-times {xl\.vqmacc\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {xl\.vqmaccsu\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {xl\.vqmaccu\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
/* { dg-final { scan-assembler-times {xl\.vqmaccus\.vv\s+v[0-9]+,\s*v[0-9]+,\s*v[0-9]+} 1 } } */
