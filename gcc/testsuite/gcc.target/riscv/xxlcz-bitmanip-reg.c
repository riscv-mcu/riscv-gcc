/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczbitop -mabi=ilp32 -O2" } */
/* { dg-final { scan-assembler-times "xl\\.bsetr" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.bclrr" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.insertr" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.extractr" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.extractur" 1 } } */

#include <stdint.h>

/* Register version tests - all use explicit builtins */

uint32_t test_bsetr(uint32_t x, uint32_t pos_len)
{
        return __builtin_xxlcz_bset_r(x, pos_len);
}

uint32_t test_bclrr(uint32_t x, uint32_t pos_len)
{
        return __builtin_xxlcz_bclr_r(x, pos_len);
}

uint32_t test_insertr(uint32_t dst, uint32_t pos_len)
{
        return __builtin_xxlcz_insert_r(dst, pos_len);
}

int32_t test_extractr(uint32_t x, uint32_t pos_len)
{
        return __builtin_xxlcz_extract_r(x, pos_len);
}

uint32_t test_extractur(uint32_t x, uint32_t pos_len)
{
        return __builtin_xxlcz_extractu_r(x, pos_len);
}
