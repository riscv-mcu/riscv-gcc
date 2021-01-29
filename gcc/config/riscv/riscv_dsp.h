#ifndef _GCC_RISCV_DSP_H
#define _GCC_RISCV_DSP_H 1

#include <stddef.h>
#include <stdint.h>

#ifndef __riscv_dsp
#error "Vector intrinsics require the p-extension."
#else

typedef signed char int8x4_t __attribute__((vector_size(4)));
typedef signed char int8x8_t __attribute__((vector_size(8)));
typedef short int16x2_t __attribute__((vector_size(4)));
typedef short int16x4_t __attribute__((vector_size (8)));
typedef short int16x8_t __attribute__((vector_size (16)));
typedef int int32x2_t __attribute__((vector_size(8)));
typedef int int32x4_t __attribute__((vector_size(16)));
typedef unsigned char uint8x4_t __attribute__((vector_size (4)));
typedef unsigned char uint8x8_t __attribute__((vector_size (8)));
typedef unsigned short uint16x2_t __attribute__((vector_size (4)));
typedef unsigned short uint16x4_t __attribute__((vector_size (8)));
typedef unsigned short uint16x8_t __attribute__((vector_size (16)));
typedef unsigned int uint32x2_t __attribute__((vector_size(8)));
typedef unsigned int uint32x4_t __attribute__((vector_size(16)));

#if __riscv_xlen == 32
/* 16-bit Add/Subtract */
#define __rv__add16(a, b) __builtin_riscv_addv2hi(a, b)
#define __rv__v_sadd16(a, b) __builtin_riscv_v_saddv2hi(a, b)
#define __rv__v_uadd16(a, b) __builtin_riscv_v_uaddv2hi(a, b)

#define __rv__radd16(a, b) __builtin_riscv_raddv2hi(a, b)
#define __rv__v_radd16(a, b) __builtin_riscv_v_raddv2hi(a, b)

#define __rv__uradd16(a, b) __builtin_riscv_uraddv2hi(a, b)
#define __rv__v_uradd16(a, b) __builtin_riscv_v_uraddv2hi(a, b)

#define __rv__kadd16(a, b) __builtin_riscv_kaddv2hi(a, b)
#define __rv__v_kadd16(a, b) __builtin_riscv_v_kaddv2hi(a, b)

#define __rv__ukadd16(a, b) __builtin_riscv_ukaddv2hi(a, b)
#define __rv__v_ukadd16(a, b) __builtin_riscv_v_ukaddv2hi(a, b)

#define __rv__sub16(a, b) __builtin_riscv_subv2hi(a, b)
#define __rv__v_usub16(a, b) __builtin_riscv_v_usubv2hi(a, b)
#define __rv__v_ssub16(a, b) __builtin_riscv_v_ssubv2hi(a, b)

#define __rv__rsub16(a, b) __builtin_riscv_rsubv2hi(a, b)
#define __rv__v_rsub16(a, b) __builtin_riscv_v_rsubv2hi(a, b)

#define __rv__ursub16(a, b) __builtin_riscv_ursubv2hi(a, b)
#define __rv__v_ursub16(a, b) __builtin_riscv_v_ursubv2hi(a, b)

#define __rv__ksub16(a, b) __builtin_riscv_ksubv2hi(a, b)
#define __rv__v_ksub16(a, b) __builtin_riscv_v_ksubv2hi(a, b)

#define __rv__uksub16(a, b) __builtin_riscv_uksubv2hi(a, b)
#define __rv__v_uksub16(a, b) __builtin_riscv_v_uksubv2hi(a, b)

/* 8-bit Add/Subtract */
#define __rv__add8(a, b) __builtin_riscv_addv4qi(a, b)
#define __rv__v_sadd8(a, b) __builtin_riscv_v_saddv4qi(a, b)
#define __rv__v_uadd8(a, b) __builtin_riscv_v_uaddv4qi(a, b)

#elif __riscv_xlen == 64
/* 16-bit Add/Subtract */
#define __rv__add16(a, b) __builtin_riscv_addv4hi(a, b)
#define __rv__v_sadd16(a, b) __builtin_riscv_v_saddv4hi(a, b)
#define __rv__v_uadd16(a, b) __builtin_riscv_v_uaddv4hi(a, b)

#define __rv__radd16(a, b) __builtin_riscv_raddv4hi(a, b)
#define __rv__v_radd16(a, b) __builtin_riscv_v_raddv4hi(a, b)

#define __rv__uradd16(a, b) __builtin_riscv_uraddv4hi(a, b)
#define __rv__v_uradd16(a, b) __builtin_riscv_v_uraddv4hi(a, b)

#define __rv__kadd16(a, b) __builtin_riscv_kaddv4hi(a, b)
#define __rv__v_kadd16(a, b) __builtin_riscv_v_kaddv4hi(a, b)

#define __rv__ukadd16(a, b) __builtin_riscv_ukaddv4hi(a, b)
#define __rv__v_ukadd16(a, b) __builtin_riscv_v_ukaddv4hi(a, b)

#define __rv__sub16(a, b) __builtin_riscv_subv4hi(a, b)
#define __rv__v_usub16(a, b) __builtin_riscv_v_usubv4hi(a, b)
#define __rv__v_ssub16(a, b) __builtin_riscv_v_ssubv4hi(a, b)

#define __rv__rsub16(a, b) __builtin_riscv_rsubv4hi(a, b)
#define __rv__v_rsub16(a, b) __builtin_riscv_v_rsubv4hi(a, b)

#define __rv__ursub16(a, b) __builtin_riscv_ursubv4hi(a, b)
#define __rv__v_ursub16(a, b) __builtin_riscv_v_ursubv4hi(a, b)

#define __rv__ksub16(a, b) __builtin_riscv_ksubv4hi(a, b)
#define __rv__v_ksub16(a, b) __builtin_riscv_v_ksubv4hi(a, b)

#define __rv__uksub16(a, b) __builtin_riscv_uksubv4hi(a, b)
#define __rv__v_uksub16(a, b) __builtin_riscv_v_uksubv4hi(a, b)

/* 8-bit Add/Subtract */
#define __rv__add8(a, b) __builtin_riscv_addv8qi(a, b)
#define __rv__v_sadd8(a, b) __builtin_riscv_v_saddv8qi(a, b)
#define __rv__v_uadd8(a, b) __builtin_riscv_v_uaddv8qi(a, b)

#else
#error "unknown xlen"
#endif

#endif
#endif
