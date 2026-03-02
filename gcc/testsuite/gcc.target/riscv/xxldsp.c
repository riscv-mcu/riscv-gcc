/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxldsp -mabi=ilp32 -O2" } */

#include <stdint.h>

//rv32 or rv64 maddr32
int xxldsp_maddr32(int a, int b, int c) 
{
    return a * b + c;
}

//rv32 or rv64 msubr32
int xxldsp_msubr32(int a, int b, int c) 
{
    return c - a * b;
}

uint64_t xxldsp_mulr64(uint32_t a, uint32_t b) {
    return (uint64_t)a * b;
}


int64_t xxldsp_mulsr64(int32_t a, int32_t b) {
    return (int64_t)a * (int64_t)b;
}

// -Os -O2 -Ofast
int64_t test_smar64(int64_t t, int32_t a, int32_t b) {
    return t + (int64_t)a * b;
}

//-Os -O2 -Ofast
int64_t test_smsr64(int64_t t, int32_t a, int32_t b) {
return t - (int64_t)a * b;
}

//-Os -O2 -Ofast
uint64_t test_umar64(int64_t t, uint32_t a, uint32_t b) {
    return t + (uint64_t)a * b;
}

// -Os -O2 -Ofast
uint64_t test_umsr64(uint64_t t, uint32_t a, uint32_t b) {
    return t - (uint64_t)a * b;
}

/* { dg-final { scan-assembler-times "maddr32" 1 } } */
/* { dg-final { scan-assembler-times "msubr32" 1 } } */
/* { dg-final { scan-assembler-times "mulr64" 1 } } */
/* { dg-final { scan-assembler-times "mulsr64" 1 } } */
/* { dg-final { scan-assembler-times "smar64" 1 } } */
/* { dg-final { scan-assembler-times "smsr64" 1 } } */
/* { dg-final { scan-assembler-times "umar64" 1 } } */
/* { dg-final { scan-assembler-times "umsr64" 1 } } */
