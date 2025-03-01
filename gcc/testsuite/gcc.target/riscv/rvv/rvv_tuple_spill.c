/* { dg-do compile } */

#include <riscv_vector.h>

void foo(){

  vint32m1x2_t x;
  asm volatile ("#%0":"=vr"(x));
  asm volatile ("###":::"v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v8", "v9", "v10", "v11", "v12", "v13", "v14", "v15", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23", "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31", "memory");
  asm volatile ("#%0"::"vr"(x));
}

/* { dg-final { scan-assembler-times "vlseg" 0 } } */
/* { dg-final { scan-assembler-times "vsseg" 0 } } */
/* { dg-final { scan-assembler "\[ |\t\]vs1r.v\[ |\t\].*\n\[ |\t\]add.*\n\[ |\t\]vs1r.v.*" } } */
/* { dg-final { scan-assembler "\[ |\t\]vl1r.v\[ |\t\].*\n\[ |\t\]add.*\n\[ |\t\]vl1r.v.*" } } */

