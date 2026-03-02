/* { dg-do compile } */
/* { dg-options "-march=rv32imac_xxlczslet -mabi=ilp32 -O2" } */

//rv32 and rv64
unsigned int test_sletu(unsigned int rs1, unsigned int rs2) {
    unsigned int rd = (rs1 <= rs2) ? 1 : 0;
    return rd;
}

int test_slet(int rs1, int rs2) {
    int rd = (rs1 <= rs2) ? 1 : 0;
    return rd;
}

/* { dg-final { scan-assembler-times "xl\\.sletu" 1 } } */
/* { dg-final { scan-assembler-times "xl\\.slet" 1 } } */
