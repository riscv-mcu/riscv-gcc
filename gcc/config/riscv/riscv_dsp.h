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

#define __rv__cras16(a, b) __builtin_riscv_crasv2hi(a, b)
#define __rv__v_scras16(a, b) __builtin_riscv_v_scrasv2hi(a, b)
#define __rv__v_ucras16(a, b) __builtin_riscv_v_ucrasv2hi(a, b)

#define __rv__rcras16(a, b) __builtin_riscv_rcrasv2hi(a, b)
#define __rv__v_rcras16(a, b) __builtin_riscv_v_rcrasv2hi(a, b)

#define __rv__urcras16(a, b) __builtin_riscv_urcrasv2hi(a, b)
#define __rv__v_urcras16(a, b) __builtin_riscv_v_urcrasv2hi(a, b)

#define __rv__kcras16(a, b) __builtin_riscv_kcrasv2hi(a, b)
#define __rv__v_kcras16(a, b) __builtin_riscv_v_kcrasv2hi(a, b)

#define __rv__ukcras16(a, b) __builtin_riscv_ukcrasv2hi(a, b)
#define __rv__v_ukcras16(a, b) __builtin_riscv_v_ukcrasv2hi(a, b)

#define __rv__crsa16(a, b) __builtin_riscv_crsav2hi(a, b)
#define __rv__v_scrsa16(a, b) __builtin_riscv_v_scrsav2hi(a, b)
#define __rv__v_ucrsa16(a, b) __builtin_riscv_v_ucrsav2hi(a, b)

#define __rv__rcrsa16(a, b) __builtin_riscv_rcrsav2hi(a, b)
#define __rv__v_rcrsa16(a, b) __builtin_riscv_v_rcrsav2hi(a, b)

#define __rv__urcrsa16(a, b) __builtin_riscv_urcrsav2hi(a, b)
#define __rv__v_urcrsa16(a, b) __builtin_riscv_v_urcrsav2hi(a, b)

#define __rv__kcrsa16(a, b) __builtin_riscv_kcrsav2hi(a, b)
#define __rv__v_kcrsa16(a, b) __builtin_riscv_v_kcrsav2hi(a, b)

#define __rv__ukcrsa16(a, b) __builtin_riscv_ukcrsav2hi(a, b)
#define __rv__v_ukcrsa16(a, b) __builtin_riscv_v_ukcrsav2hi(a, b)

#define __rv__stas16(a, b) __builtin_riscv_stasv2hi(a, b)
#define __rv__v_sstas16(a, b) __builtin_riscv_v_sstasv2hi(a, b)
#define __rv__v_ustas16(a, b) __builtin_riscv_v_ustasv2hi(a, b)

#define __rv__rstas16(a, b) __builtin_riscv_rstasv2hi(a, b)
#define __rv__v_rstas16(a, b) __builtin_riscv_v_rstasv2hi(a, b)

#define __rv__urstas16(a, b) __builtin_riscv_urstasv2hi(a, b)
#define __rv__v_urstas16(a, b) __builtin_riscv_v_urstasv2hi(a, b)

#define __rv__kstas16(a, b) __builtin_riscv_kstasv2hi(a, b)
#define __rv__v_kstas16(a, b) __builtin_riscv_v_kstasv2hi(a, b)

#define __rv__ukstas16(a, b) __builtin_riscv_ukstasv2hi(a, b)
#define __rv__v_ukstas16(a, b) __builtin_riscv_v_ukstasv2hi(a, b)

#define __rv__stsa16(a, b) __builtin_riscv_stsav2hi(a, b)
#define __rv__v_sstsa16(a, b) __builtin_riscv_v_sstsav2hi(a, b)
#define __rv__v_ustsa16(a, b) __builtin_riscv_v_ustsav2hi(a, b)

#define __rv__rstsa16(a, b) __builtin_riscv_rstsav2hi(a, b)
#define __rv__v_rstsa16(a, b) __builtin_riscv_v_rstsav2hi(a, b)

#define __rv__urstsa16(a, b) __builtin_riscv_urstsav2hi(a, b)
#define __rv__v_urstsa16(a, b) __builtin_riscv_v_urstsav2hi(a, b)

#define __rv__kstsa16(a, b) __builtin_riscv_kstsav2hi(a, b)
#define __rv__v_kstsa16(a, b) __builtin_riscv_v_kstsav2hi(a, b)

#define __rv__ukstsa16(a, b) __builtin_riscv_ukstsav2hi(a, b)
#define __rv__v_ukstsa16(a, b) __builtin_riscv_v_ukstsav2hi(a, b)

/* 8-bit Add/Subtract */
#define __rv__add8(a, b) __builtin_riscv_addv4qi(a, b)
#define __rv__v_sadd8(a, b) __builtin_riscv_v_saddv4qi(a, b)
#define __rv__v_uadd8(a, b) __builtin_riscv_v_uaddv4qi(a, b)

#define __rv__radd8(a, b) __builtin_riscv_raddv4qi(a, b)
#define __rv__v_radd8(a, b) __builtin_riscv_v_raddv4qi(a, b)

#define __rv__uradd8(a, b) __builtin_riscv_uraddv4qi(a, b)
#define __rv__v_uradd8(a, b) __builtin_riscv_v_uraddv4qi(a, b)

#define __rv__kadd8(a, b) __builtin_riscv_kaddv4qi(a, b)
#define __rv__v_kadd8(a, b) __builtin_riscv_v_kaddv4qi(a, b)

#define __rv__ukadd8(a, b) __builtin_riscv_ukaddv4qi(a, b)
#define __rv__v_ukadd8(a, b) __builtin_riscv_v_ukaddv4qi(a, b)

#define __rv__sub8(a, b) __builtin_riscv_subv4qi(a, b)
#define __rv__v_ssub8(a, b) __builtin_riscv_v_ssubv4qi(a, b)
#define __rv__v_usub8(a, b) __builtin_riscv_v_usubv4qi(a, b)

#define __rv__rsub8(a, b) __builtin_riscv_rsubv4qi(a, b)
#define __rv__v_rsub8(a, b) __builtin_riscv_v_rsubv4qi(a, b)

#define __rv__ursub8(a, b) __builtin_riscv_ursubv4qi(a, b)
#define __rv__v_ursub8(a, b) __builtin_riscv_v_ursubv4qi(a, b)

#define __rv__ksub8(a, b) __builtin_riscv_ksubv4qi(a, b)
#define __rv__v_ksub8(a, b) __builtin_riscv_v_ksubv4qi(a, b)

#define __rv__uksub8(a, b) __builtin_riscv_uksubv4qi(a, b)
#define __rv__v_uksub8(a, b) __builtin_riscv_v_uksubv4qi(a, b)

/* 16-bit Shift operations */
#define __rv__sra16(a, b) __builtin_riscv_srav2hi(a, b)
#define __rv__v_sra16(a, b) __builtin_riscv_v_srav2hi(a, b)

#define __rv__sra16_u(a, b) __builtin_riscv_srav2hi_u(a, b)
#define __rv__v_sra16_u(a, b) __builtin_riscv_v_srav2hi_u(a, b)

#define __rv__srl16(a, b) __builtin_riscv_srlv2hi(a, b)
#define __rv__v_srl16(a, b) __builtin_riscv_v_srlv2hi(a, b)

#define __rv__srl16_u(a, b) __builtin_riscv_srlv2hi_u(a, b)
#define __rv__v_srl16_u(a, b) __builtin_riscv_v_srlv2hi_u(a, b)

#define __rv__sll16(a, b) __builtin_riscv_sllv2hi(a, b)
#define __rv__v_sll16(a, b) __builtin_riscv_v_sllv2hi(a, b)

#define __rv__ksll16(a, b) __builtin_riscv_ksllv2hi(a, b)
#define __rv__v_ksll16(a, b) __builtin_riscv_v_ksllv2hi(a, b)

#define __rv__kslra16(a, b) __builtin_riscv_kslrav2hi(a, b)
#define __rv__v_kslra16(a, b) __builtin_riscv_v_kslrav2hi(a, b)

#define __rv__kslra16_u(a, b) __builtin_riscv_kslrav2hi_u(a, b)
#define __rv__v_kslra16_u(a, b) __builtin_riscv_v_kslrav2hi_u(a, b)

/* 8-bit Shift operations */
#define __rv__sra8(a, b) __builtin_riscv_srav4qi(a, b)
#define __rv__v_sra8(a, b) __builtin_riscv_v_srav4qi(a, b)

#define __rv__sra8_u(a, b) __builtin_riscv_srav4qi_u(a, b)
#define __rv__v_sra8_u(a, b) __builtin_riscv_v_srav4qi_u(a, b)

#define __rv__srl8(a, b) __builtin_riscv_srlv4qi(a, b)
#define __rv__v_srl8(a, b) __builtin_riscv_v_srlv4qi(a, b)

#define __rv__srl8_u(a, b) __builtin_riscv_srlv4qi_u(a, b)
#define __rv__v_srl8_u(a, b) __builtin_riscv_v_srlv4qi_u(a, b)

#define __rv__sll8(a, b) __builtin_riscv_sllv4qi(a, b)
#define __rv__v_sll8(a, b) __builtin_riscv_v_sllv4qi(a, b)

#define __rv__ksll8(a, b) __builtin_riscv_ksllv4qi(a, b)
#define __rv__v_ksll8(a, b) __builtin_riscv_v_ksllv4qi(a, b)

#define __rv__kslra8(a, b) __builtin_riscv_kslrav4qi(a, b)
#define __rv__v_kslra8(a, b) __builtin_riscv_v_kslrav4qi(a, b)

#define __rv__kslra8_u(a, b) __builtin_riscv_kslrav4qi_u(a, b)
#define __rv__v_kslra8_u(a, b) __builtin_riscv_v_kslrav4qi_u(a, b)

/* 16-bit Comparison. */
#define __rv__cmpeq16(a, b) __builtin_riscv_cmpeqv2hi(a, b)
#define __rv__v_scmpeq16(a, b) __builtin_riscv_v_scmpeqv2hi(a, b)
#define __rv__v_ucmpeq16(a, b) __builtin_riscv_v_ucmpeqv2hi(a, b)

#define __rv__scmplt16(a, b) __builtin_riscv_scmpltv2hi(a, b)
#define __rv__v_scmplt16(a, b) __builtin_riscv_v_scmpltv2hi(a, b)

#define __rv__scmple16(a, b) __builtin_riscv_scmplev2hi(a, b)
#define __rv__v_scmple16(a, b) __builtin_riscv_v_scmplev2hi(a, b)

#define __rv__ucmplt16(a, b) __builtin_riscv_ucmpltv2hi(a, b)
#define __rv__v_ucmplt16(a, b) __builtin_riscv_v_ucmpltv2hi(a, b)

#define __rv__ucmple16(a, b) __builtin_riscv_ucmplev2hi(a, b)
#define __rv__v_ucmple16(a, b) __builtin_riscv_v_ucmplev2hi(a, b)

/* 8-bit Comparison. */
#define __rv__cmpeq8(a, b) __builtin_riscv_cmpeqv4qi(a, b)
#define __rv__v_scmpeq8(a, b) __builtin_riscv_v_scmpeqv4qi(a, b)
#define __rv__v_ucmpeq8(a, b) __builtin_riscv_v_ucmpeqv4qi(a, b)

#define __rv__scmplt8(a, b) __builtin_riscv_scmpltv4qi(a, b)
#define __rv__v_scmplt8(a, b) __builtin_riscv_v_scmpltv4qi(a, b)

#define __rv__scmple8(a, b) __builtin_riscv_scmplev4qi(a, b)
#define __rv__v_scmple8(a, b) __builtin_riscv_v_scmplev4qi(a, b)

#define __rv__ucmplt8(a, b) __builtin_riscv_ucmpltv4qi(a, b)
#define __rv__v_ucmplt8(a, b) __builtin_riscv_v_ucmpltv4qi(a, b)

#define __rv__ucmple8(a, b) __builtin_riscv_ucmplev4qi(a, b)
#define __rv__v_ucmple8(a, b) __builtin_riscv_v_ucmplev4qi(a, b)

/* 16-bit Multiplications */
#define __rv__smul16(a, b) __builtin_riscv_smul16_32(a, b)
#define __rv__v_smul16(a, b) __builtin_riscv_v_smul16_32(a, b)

#define __rv__smulx16(a, b) __builtin_riscv_smulx16_32(a, b)
#define __rv__v_smulx16(a, b) __builtin_riscv_v_smulx16_32(a, b)

#define __rv__khm16(a, b) __builtin_riscv_khm16v2hi(a, b)
#define __rv__v_khm16(a, b) __builtin_riscv_v_khm16v2hi(a, b)

#define __rv__khmx16(a, b) __builtin_riscv_khmx16v2hi(a, b)
#define __rv__v_khmx16(a, b) __builtin_riscv_v_khmx16v2hi(a, b)

/* 8-bit Multiplications */
#define __rv__smul8(a, b) __builtin_riscv_smul8_32(a, b)
#define __rv__v_smul8(a, b) __builtin_riscv_v_smul8_32(a, b)

#define __rv__smulx8(a, b) __builtin_riscv_smulx8_32(a, b)
#define __rv__v_smulx8(a, b) __builtin_riscv_v_smulx8_32(a, b)

#define __rv__khm8(a, b) __builtin_riscv_khm8v4qi(a, b)
#define __rv__v_khm8(a, b) __builtin_riscv_v_khm8v4qi(a, b)

#define __rv__khmx8(a, b) __builtin_riscv_khmx8v4qi(a, b)
#define __rv__v_khmx8(a, b) __builtin_riscv_v_khmx8v4qi(a, b)

#define __rv__smin16(a, b) __builtin_riscv_sminv2hi(a, b)
#define __rv__v_smin16(a, b) __builtin_riscv_v_sminv2hi(a, b)

#define __rv__smax16(a, b) __builtin_riscv_smaxv2hi(a, b)
#define __rv__v_smax16(a, b) __builtin_riscv_v_smaxv2hi(a, b)

#define __rv__umin16(a, b) __builtin_riscv_uminv2hi(a, b)
#define __rv__v_umin16(a, b) __builtin_riscv_v_uminv2hi(a, b)

#define __rv__umax16(a, b) __builtin_riscv_umaxv2hi(a, b)
#define __rv__v_umax16(a, b) __builtin_riscv_v_umaxv2hi(a, b)

#define __rv__smin8(a, b) __builtin_riscv_sminv4qi(a, b)
#define __rv__v_smin8(a, b) __builtin_riscv_v_sminv4qi(a, b)

#define __rv__smax8(a, b) __builtin_riscv_smaxv4qi(a, b)
#define __rv__v_smax8(a, b) __builtin_riscv_v_smaxv4qi(a, b)

#define __rv__umin8(a, b) __builtin_riscv_uminv4qi(a, b)
#define __rv__v_umin8(a, b) __builtin_riscv_v_uminv4qi(a, b)

#define __rv__umax8(a, b) __builtin_riscv_umaxv4qi(a, b)
#define __rv__v_umax8(a, b) __builtin_riscv_v_umaxv4qi(a, b)

#define __rv__sclip16(a, b) __builtin_riscv_sclipv2hi(a, b)
#define __rv__v_sclip16(a, b) __builtin_riscv_v_sclipv2hi(a, b)

#define __rv__uclip16(a, b) __builtin_riscv_uclipv2hi(a, b)
#define __rv__v_uclip16(a, b) __builtin_riscv_v_uclipv2hi(a, b)

#define __rv__kabs16(a) __builtin_riscv_kabsv2hi(a)
#define __rv__v_kabs16(a) __builtin_riscv_v_kabsv2hi(a)

#define __rv__clrs16(a) __builtin_riscv_clrsv2hi(a)
#define __rv__v_clrs16(a) __builtin_riscv_v_clrsv2hi(a)

#define __rv__clz16(a) __builtin_riscv_clzv2hi(a)
#define __rv__v_clz16(a) __builtin_riscv_v_clzv2hi(a)

#define __rv__clo16(a) __builtin_riscv_clov2hi(a)
#define __rv__v_clo16(a) __builtin_riscv_v_clov2hi(a)

#define __rv__sclip8(a, b) __builtin_riscv_sclipv4qi(a, b)
#define __rv__v_sclip8(a, b) __builtin_riscv_v_sclipv4qi(a, b)

#define __rv__uclip8(a, b) __builtin_riscv_uclipv4qi(a, b)
#define __rv__v_uclip8(a, b) __builtin_riscv_v_uclipv4qi(a, b)

#define __rv__kabs8(a) __builtin_riscv_kabsv4qi(a)
#define __rv__v_kabs8(a) __builtin_riscv_v_kabsv4qi(a)

#define __rv__clrs8(a) __builtin_riscv_clrsv4qi(a)
#define __rv__v_clrs8(a) __builtin_riscv_v_clrsv4qi(a)

#define __rv__clz8(a) __builtin_riscv_clzv4qi(a)
#define __rv__v_clz8(a) __builtin_riscv_v_clzv4qi(a)

#define __rv__clo8(a) __builtin_riscv_clov4qi(a)
#define __rv__v_clo8(a) __builtin_riscv_v_clov4qi(a)

#define __rv__sunpkd810(a) __builtin_riscv_sunpkd810_32(a)
#define __rv__v_sunpkd810(a) __builtin_riscv_v_sunpkd810_32(a)

#define __rv__sunpkd820(a) __builtin_riscv_sunpkd820_32(a)
#define __rv__v_sunpkd820(a) __builtin_riscv_v_sunpkd820_32(a)

#define __rv__sunpkd830(a) __builtin_riscv_sunpkd830_32(a)
#define __rv__v_sunpkd830(a) __builtin_riscv_v_sunpkd830_32(a)

#define __rv__sunpkd831(a) __builtin_riscv_sunpkd831_32(a)
#define __rv__v_sunpkd831(a) __builtin_riscv_v_sunpkd831_32(a)

#define __rv__sunpkd832(a) __builtin_riscv_sunpkd832_32(a)
#define __rv__v_sunpkd832(a) __builtin_riscv_v_sunpkd832_32(a)

#define __rv__zunpkd810(a) __builtin_riscv_zunpkd810_32(a)
#define __rv__v_zunpkd810(a) __builtin_riscv_v_zunpkd810_32(a)

#define __rv__zunpkd820(a) __builtin_riscv_zunpkd820_32(a)
#define __rv__v_zunpkd820(a) __builtin_riscv_v_zunpkd820_32(a)

#define __rv__zunpkd830(a) __builtin_riscv_zunpkd830_32(a)
#define __rv__v_zunpkd830(a) __builtin_riscv_v_zunpkd830_32(a)

#define __rv__zunpkd831(a) __builtin_riscv_zunpkd831_32(a)
#define __rv__v_zunpkd831(a) __builtin_riscv_v_zunpkd831_32(a)

#define __rv__zunpkd832(a) __builtin_riscv_zunpkd832_32(a)
#define __rv__v_zunpkd832(a) __builtin_riscv_v_zunpkd832_32(a)

#define __rv__pkbb16(a, b) __builtin_riscv_pkbbv2hi(a, b)
#define __rv__v_pkbb16(a, b) __builtin_riscv_v_pkbbv2hi(a, b)

#define __rv__pkbt16(a, b) __builtin_riscv_pkbtv2hi(a, b)
#define __rv__v_pkbt16(a, b) __builtin_riscv_v_pkbtv2hi(a, b)

#define __rv__pktb16(a, b) __builtin_riscv_pktbv2hi(a, b)
#define __rv__v_pktb16(a, b) __builtin_riscv_v_pktbv2hi(a, b)

#define __rv__pktt16(a, b) __builtin_riscv_pkttv2hi(a, b)
#define __rv__v_pktt16(a, b) __builtin_riscv_v_pkttv2hi(a, b)

#define __rv__smmul(a, b) __builtin_riscv_smulsi(a, b)

#define __rv__smmul_u(a, b) __builtin_riscv_smmulsi(a, b)

#define __rv__kmmac(a, b, c) __builtin_riscv_kmmac(a, b, c)
#define __rv__kmmac_u(a, b, c) __builtin_riscv_kmmac_round(a, b, c)

#define __rv__kmmsb(a, b, c) __builtin_riscv_kmmsb(a, b, c)
#define __rv__kmmsb_u(a, b, c) __builtin_riscv_kmmsb_round(a, b, c)

#define __rv__kwmmul(a, b) __builtin_riscv_kwmmul(a, b)
#define __rv__kwmmul_u(a, b) __builtin_riscv_kwmmul_round(a, b)

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

#define __rv__cras16(a, b) __builtin_riscv_crasv4hi(a, b)
#define __rv__v_scras16(a, b) __builtin_riscv_v_scrasv4hi(a, b)
#define __rv__v_ucras16(a, b) __builtin_riscv_v_ucrasv4hi(a, b)

#define __rv__rcras16(a, b) __builtin_riscv_rcrasv4hi(a, b)
#define __rv__v_rcras16(a, b) __builtin_riscv_v_rcrasv4hi(a, b)

#define __rv__urcras16(a, b) __builtin_riscv_urcrasv4hi(a, b)
#define __rv__v_urcras16(a, b) __builtin_riscv_v_urcrasv4hi(a, b)

#define __rv__kcras16(a, b) __builtin_riscv_kcrasv4hi(a, b)
#define __rv__v_kcras16(a, b) __builtin_riscv_v_kcrasv4hi(a, b)

#define __rv__ukcras16(a, b) __builtin_riscv_ukcrasv4hi(a, b)
#define __rv__v_ukcras16(a, b) __builtin_riscv_v_ukcrasv4hi(a, b)

#define __rv__crsa16(a, b) __builtin_riscv_crsav4hi(a, b)
#define __rv__v_scrsa16(a, b) __builtin_riscv_v_scrsav4hi(a, b)
#define __rv__v_ucrsa16(a, b) __builtin_riscv_v_ucrsav4hi(a, b)

#define __rv__rcrsa16(a, b) __builtin_riscv_rcrsav4hi(a, b)
#define __rv__v_rcrsa16(a, b) __builtin_riscv_v_rcrsav4hi(a, b)

#define __rv__urcrsa16(a, b) __builtin_riscv_urcrsav4hi(a, b)
#define __rv__v_urcrsa16(a, b) __builtin_riscv_v_urcrsav4hi(a, b)

#define __rv__kcrsa16(a, b) __builtin_riscv_kcrsav4hi(a, b)
#define __rv__v_kcrsa16(a, b) __builtin_riscv_v_kcrsav4hi(a, b)

#define __rv__ukcrsa16(a, b) __builtin_riscv_ukcrsav4hi(a, b)
#define __rv__v_ukcrsa16(a, b) __builtin_riscv_v_ukcrsav4hi(a, b)

#define __rv__stas16(a, b) __builtin_riscv_stasv4hi(a, b)
#define __rv__v_sstas16(a, b) __builtin_riscv_v_sstasv4hi(a, b)
#define __rv__v_ustas16(a, b) __builtin_riscv_v_ustasv4hi(a, b)

#define __rv__rstas16(a, b) __builtin_riscv_rstasv4hi(a, b)
#define __rv__v_rstas16(a, b) __builtin_riscv_v_rstasv4hi(a, b)

#define __rv__urstas16(a, b) __builtin_riscv_urstasv4hi(a, b)
#define __rv__v_urstas16(a, b) __builtin_riscv_v_urstasv4hi(a, b)

#define __rv__kstas16(a, b) __builtin_riscv_kstasv4hi(a, b)
#define __rv__v_kstas16(a, b) __builtin_riscv_v_kstasv4hi(a, b)

#define __rv__ukstas16(a, b) __builtin_riscv_ukstasv4hi(a, b)
#define __rv__v_ukstas16(a, b) __builtin_riscv_v_ukstasv4hi(a, b)

#define __rv__stsa16(a, b) __builtin_riscv_stsav4hi(a, b)
#define __rv__v_sstsa16(a, b) __builtin_riscv_v_sstsav4hi(a, b)
#define __rv__v_ustsa16(a, b) __builtin_riscv_v_ustsav4hi(a, b)

#define __rv__rstsa16(a, b) __builtin_riscv_rstsav4hi(a, b)
#define __rv__v_rstsa16(a, b) __builtin_riscv_v_rstsav4hi(a, b)

#define __rv__urstsa16(a, b) __builtin_riscv_urstsav4hi(a, b)
#define __rv__v_urstsa16(a, b) __builtin_riscv_v_urstsav4hi(a, b)

#define __rv__kstsa16(a, b) __builtin_riscv_kstsav4hi(a, b)
#define __rv__v_kstsa16(a, b) __builtin_riscv_v_kstsav4hi(a, b)

#define __rv__ukstsa16(a, b) __builtin_riscv_ukstsav4hi(a, b)
#define __rv__v_ukstsa16(a, b) __builtin_riscv_v_ukstsav4hi(a, b)

/* 8-bit Add/Subtract */
#define __rv__add8(a, b) __builtin_riscv_addv8qi(a, b)
#define __rv__v_sadd8(a, b) __builtin_riscv_v_saddv8qi(a, b)
#define __rv__v_uadd8(a, b) __builtin_riscv_v_uaddv8qi(a, b)

#define __rv__radd8(a, b) __builtin_riscv_raddv8qi(a, b)
#define __rv__v_radd8(a, b) __builtin_riscv_v_raddv8qi(a, b)

#define __rv__uradd8(a, b) __builtin_riscv_uraddv8qi(a, b)
#define __rv__v_uradd8(a, b) __builtin_riscv_v_uraddv8qi(a, b)

#define __rv__kadd8(a, b) __builtin_riscv_kaddv8qi(a, b)
#define __rv__v_kadd8(a, b) __builtin_riscv_v_kaddv8qi(a, b)

#define __rv__ukadd8(a, b) __builtin_riscv_ukaddv8qi(a, b)
#define __rv__v_ukadd8(a, b) __builtin_riscv_v_ukaddv8qi(a, b)

#define __rv__sub8(a, b) __builtin_riscv_subv8qi(a, b)
#define __rv__v_ssub8(a, b) __builtin_riscv_v_ssubv8qi(a, b)
#define __rv__v_usub8(a, b) __builtin_riscv_v_usubv8qi(a, b)

#define __rv__rsub8(a, b) __builtin_riscv_rsubv8qi(a, b)
#define __rv__v_rsub8(a, b) __builtin_riscv_v_rsubv8qi(a, b)

#define __rv__ursub8(a, b) __builtin_riscv_ursubv8qi(a, b)
#define __rv__v_ursub8(a, b) __builtin_riscv_v_ursubv8qi(a, b)

#define __rv__ksub8(a, b) __builtin_riscv_ksubv8qi(a, b)
#define __rv__v_ksub8(a, b) __builtin_riscv_v_ksubv8qi(a, b)

#define __rv__uksub8(a, b) __builtin_riscv_uksubv8qi(a, b)
#define __rv__v_uksub8(a, b) __builtin_riscv_v_uksubv8qi(a, b)

/* 16-bit Shift operations */
#define __rv__sra16(a, b) __builtin_riscv_srav4hi(a, b)
#define __rv__v_sra16(a, b) __builtin_riscv_v_srav4hi(a, b)

#define __rv__sra16_u(a, b) __builtin_riscv_srav4hi_u(a, b)
#define __rv__v_sra16_u(a, b) __builtin_riscv_v_srav4hi_u(a, b)

#define __rv__srl16(a, b) __builtin_riscv_srlv4hi(a, b)
#define __rv__v_srl16(a, b) __builtin_riscv_v_srlv4hi(a, b)

#define __rv__srl16_u(a, b) __builtin_riscv_srlv4hi_u(a, b)
#define __rv__v_srl16_u(a, b) __builtin_riscv_v_srlv4hi_u(a, b)

#define __rv__sll16(a, b) __builtin_riscv_sllv4hi(a, b)
#define __rv__v_sll16(a, b) __builtin_riscv_v_sllv4hi(a, b)

#define __rv__ksll16(a, b) __builtin_riscv_ksllv4hi(a, b)
#define __rv__v_ksll16(a, b) __builtin_riscv_v_ksllv4hi(a, b)

#define __rv__kslra16(a, b) __builtin_riscv_kslrav4hi(a, b)
#define __rv__v_kslra16(a, b) __builtin_riscv_v_kslrav4hi(a, b)

#define __rv__kslra16_u(a, b) __builtin_riscv_kslrav4hi_u(a, b)
#define __rv__v_kslra16_u(a, b) __builtin_riscv_v_kslrav4hi_u(a, b)

/* 8-bit Shift operations */
#define __rv__sra8(a, b) __builtin_riscv_srav8qi(a, b)
#define __rv__v_sra8(a, b) __builtin_riscv_v_srav8qi(a, b)

#define __rv__sra8_u(a, b) __builtin_riscv_srav8qi_u(a, b)
#define __rv__v_sra8_u(a, b) __builtin_riscv_v_srav8qi_u(a, b)

#define __rv__srl8(a, b) __builtin_riscv_srlv8qi(a, b)
#define __rv__v_srl8(a, b) __builtin_riscv_v_srlv8qi(a, b)

#define __rv__srl8_u(a, b) __builtin_riscv_srlv8qi_u(a, b)
#define __rv__v_srl8_u(a, b) __builtin_riscv_v_srlv8qi_u(a, b)

#define __rv__sll8(a, b) __builtin_riscv_sllv8qi(a, b)
#define __rv__v_sll8(a, b) __builtin_riscv_v_sllv8qi(a, b)

#define __rv__ksll8(a, b) __builtin_riscv_ksllv8qi(a, b)
#define __rv__v_ksll8(a, b) __builtin_riscv_v_ksllv8qi(a, b)

#define __rv__kslra8(a, b) __builtin_riscv_kslrav8qi(a, b)
#define __rv__v_kslra8(a, b) __builtin_riscv_v_kslrav8qi(a, b)

#define __rv__kslra8_u(a, b) __builtin_riscv_kslrav8qi_u(a, b)
#define __rv__v_kslra8_u(a, b) __builtin_riscv_v_kslrav8qi_u(a, b)

/* 16-bit Comparison. */
#define __rv__cmpeq16(a, b) __builtin_riscv_cmpeqv4hi(a, b)
#define __rv__v_scmpeq16(a, b) __builtin_riscv_v_scmpeqv4hi(a, b)
#define __rv__v_ucmpeq16(a, b) __builtin_riscv_v_ucmpeqv4hi(a, b)

#define __rv__scmplt16(a, b) __builtin_riscv_scmpltv4hi(a, b)
#define __rv__v_scmplt16(a, b) __builtin_riscv_v_scmpltv4hi(a, b)

#define __rv__scmple16(a, b) __builtin_riscv_scmplev4hi(a, b)
#define __rv__v_scmple16(a, b) __builtin_riscv_v_scmplev4hi(a, b)

#define __rv__ucmplt16(a, b) __builtin_riscv_ucmpltv4hi(a, b)
#define __rv__v_ucmplt16(a, b) __builtin_riscv_v_ucmpltv4hi(a, b)

#define __rv__ucmple16(a, b) __builtin_riscv_ucmplev4hi(a, b)
#define __rv__v_ucmple16(a, b) __builtin_riscv_v_ucmplev4hi(a, b)

/* 8-bit Comparison. */
#define __rv__cmpeq8(a, b) __builtin_riscv_cmpeqv8qi(a, b)
#define __rv__v_scmpeq8(a, b) __builtin_riscv_v_scmpeqv8qi(a, b)
#define __rv__v_ucmpeq8(a, b) __builtin_riscv_v_ucmpeqv8qi(a, b)

#define __rv__scmplt8(a, b) __builtin_riscv_scmpltv8qi(a, b)
#define __rv__v_scmplt8(a, b) __builtin_riscv_v_scmpltv8qi(a, b)

#define __rv__scmple8(a, b) __builtin_riscv_scmplev8qi(a, b)
#define __rv__v_scmple8(a, b) __builtin_riscv_v_scmplev8qi(a, b)

#define __rv__ucmplt8(a, b) __builtin_riscv_ucmpltv8qi(a, b)
#define __rv__v_ucmplt8(a, b) __builtin_riscv_v_ucmpltv8qi(a, b)

#define __rv__ucmple8(a, b) __builtin_riscv_ucmplev8qi(a, b)
#define __rv__v_ucmple8(a, b) __builtin_riscv_v_ucmplev8qi(a, b)

#define __rv__smin16(a, b) __builtin_riscv_sminv4hi(a, b)
#define __rv__v_smin16(a, b) __builtin_riscv_v_sminv4hi(a, b)

#define __rv__smax16(a, b) __builtin_riscv_smaxv4hi(a, b)
#define __rv__v_smax16(a, b) __builtin_riscv_v_smaxv4hi(a, b)

#define __rv__umin16(a, b) __builtin_riscv_uminv4hi(a, b)
#define __rv__v_umin16(a, b) __builtin_riscv_v_uminv4hi(a, b)

#define __rv__umax16(a, b) __builtin_riscv_umaxv4hi(a, b)
#define __rv__v_umax16(a, b) __builtin_riscv_v_umaxv4hi(a, b)

#define __rv__smin8(a, b) __builtin_riscv_sminv8qi(a, b)
#define __rv__v_smin8(a, b) __builtin_riscv_v_sminv8qi(a, b)

#define __rv__smax8(a, b) __builtin_riscv_smaxv8qi(a, b)
#define __rv__v_smax8(a, b) __builtin_riscv_v_smaxv8qi(a, b)

#define __rv__umin8(a, b) __builtin_riscv_uminv8qi(a, b)
#define __rv__v_umin8(a, b) __builtin_riscv_v_uminv8qi(a, b)

#define __rv__umax8(a, b) __builtin_riscv_umaxv8qi(a, b)
#define __rv__v_umax8(a, b) __builtin_riscv_v_umaxv8qi(a, b)

#define __rv__sclip16(a, b) __builtin_riscv_sclipv4hi(a, b)
#define __rv__v_sclip16(a, b) __builtin_riscv_v_sclipv4hi(a, b)

#define __rv__uclip16(a, b) __builtin_riscv_uclipv4hi(a, b)
#define __rv__v_uclip16(a, b) __builtin_riscv_v_uclipv4hi(a, b)

#define __rv__kabs16(a) __builtin_riscv_kabsv4hi(a)
#define __rv__v_kabs16(a) __builtin_riscv_v_kabsv4hi(a)

#define __rv__clrs16(a) __builtin_riscv_clrsv4hi(a)
#define __rv__v_clrs16(a) __builtin_riscv_v_clrsv4hi(a)

#define __rv__clz16(a) __builtin_riscv_clzv4hi(a)
#define __rv__v_clz16(a) __builtin_riscv_v_clzv4hi(a)

#define __rv__clo16(a) __builtin_riscv_clov4hi(a)
#define __rv__v_clo16(a) __builtin_riscv_v_clov4hi(a)

#define __rv__sclip8(a, b) __builtin_riscv_sclipv8qi(a, b)
#define __rv__v_sclip8(a, b) __builtin_riscv_v_sclipv8qi(a, b)

#define __rv__uclip8(a, b) __builtin_riscv_uclipv8qi(a, b)
#define __rv__v_uclip8(a, b) __builtin_riscv_v_uclipv8qi(a, b)

#define __rv__kabs8(a) __builtin_riscv_kabsv8qi(a)
#define __rv__v_kabs8(a) __builtin_riscv_v_kabsv8qi(a)

#define __rv__clrs8(a) __builtin_riscv_clrsv8qi(a)
#define __rv__v_clrs8(a) __builtin_riscv_v_clrsv8qi(a)

#define __rv__clz8(a) __builtin_riscv_clzv8qi(a)
#define __rv__v_clz8(a) __builtin_riscv_v_clzv8qi(a)

#define __rv__clo8(a) __builtin_riscv_clov8qi(a)
#define __rv__v_clo8(a) __builtin_riscv_v_clov8qi(a)

#define __rv__pkbb16(a, b) __builtin_riscv_pkbbv4hi(a, b)
#define __rv__v_pkbb16(a, b) __builtin_riscv_v_pkbbv4hi(a, b)

#define __rv__pkbt16(a, b) __builtin_riscv_pkbtv4hi(a, b)
#define __rv__v_pkbt16(a, b) __builtin_riscv_v_pkbtv4hi(a, b)

#define __rv__pktb16(a, b) __builtin_riscv_pktbv4hi(a, b)
#define __rv__v_pktb16(a, b) __builtin_riscv_v_pktbv4hi(a, b)

#define __rv__pktt16(a, b) __builtin_riscv_pkttv4hi(a, b)
#define __rv__v_pktt16(a, b) __builtin_riscv_v_pkttv4hi(a, b)

#define __rv__smmul(a, b) __builtin_riscv_smulv2si(a, b)
#define __rv__v_smmul(a, b) __builtin_riscv_v_smulv2si(a, b)
#define __rv__smmul_u(a, b) __builtin_riscv_smmulv2si(a, b)
#define __rv__v_smmul_u(a, b) __builtin_riscv_v_smmulv2si(a, b)

#define __rv__kmmac(a, b, c) __builtin_riscv_kmmac_64(a, b, c)
#define __rv__v_kmmac(a, b, c) __builtin_riscv_v_kmmac_64(a, b, c)
#define __rv__kmmac_u(a, b, c) __builtin_riscv_kmmac64_round(a, b, c)
#define __rv__v_kmmac_u(a, b, c) __builtin_riscv_v_kmmac64_round(a, b, c)

#define __rv__kmmsb(a, b, c) __builtin_riscv_kmmsb_64(a, b, c)
#define __rv__v_kmmsb(a, b, c) __builtin_riscv_v_kmmsb_64(a, b, c)
#define __rv__kmmsb_u(a, b, c) __builtin_riscv_kmmsb64_round(a, b, c)
#define __rv__v_kmmsb_u(a, b, c) __builtin_riscv_v_kmmsb64_round(a, b, c)

#define __rv__kwmmul(a, b) __builtin_riscv_kwmmul_64(a, b)
#define __rv__v_kwmmul(a, b) __builtin_riscv_v_kwmmul_64(a, b)
#define __rv__kwmmul_u(a, b) __builtin_riscv_kwmmul64_round(a, b)
#define __rv__v_kwmmul_u(a, b) __builtin_riscv_v_kwmmul64_round(a, b)

#else
#error "unknown xlen"
#endif

#endif
#endif
