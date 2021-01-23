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
/* 8-bit Add/Subtract */
#define __rv__add8(a, b) __builtin_riscv_addv4qi(a, b)
#define __rv__sadd8(a, b) __builtin_riscv_saddv4qi(a, b)
#define __rv__uadd8(a, b) __builtin_riscv_uaddv4qi(a, b)

#elif __riscv_xlen == 64
/* 8-bit Add/Subtract */
#define __rv__add8(a, b) __builtin_riscv_addv8qi(a, b)
#define __rv__sadd8(a, b) __builtin_riscv_saddv8qi(a, b)
#define __rv__uadd8(a, b) __builtin_riscv_uaddv8qi(a, b)

#else
#error "unknown xlen"
#endif

#endif
#endif
