/* Definition of RISC-V target for GNU compiler.
   Copyright (C) 2016-2020 Free Software Foundation, Inc.
   Contributed by Andrew Waterman (andrew@sifive.com).

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.

GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef GCC_RISCV_OPTS_H
#define GCC_RISCV_OPTS_H

enum riscv_abi_type {
  ABI_ILP32,
  ABI_ILP32E,
  ABI_ILP32F,
  ABI_ILP32D,
  ABI_LP64,
  ABI_LP64F,
  ABI_LP64D
};
extern enum riscv_abi_type riscv_abi;

enum riscv_code_model {
  CM_MEDLOW,
  CM_MEDANY,
  CM_PIC
};
extern enum riscv_code_model riscv_cmodel;

enum riscv_isa_spec_class {
  ISA_SPEC_CLASS_NONE,

  ISA_SPEC_CLASS_2P2,
  ISA_SPEC_CLASS_20190608,
  ISA_SPEC_CLASS_20191213
};

extern enum riscv_isa_spec_class riscv_isa_spec;

/* Keep this list in sync with define_attr "tune" in riscv.md.  */
enum riscv_microarchitecture_type {
  generic,
  sifive_7,
  nuclei_200,
  nuclei_300,
  nuclei_600,
  nuclei_900
};
extern enum riscv_microarchitecture_type riscv_microarchitecture;

enum riscv_align_data {
  riscv_align_data_type_xlen,
  riscv_align_data_type_natural
};

/* RVV vector register sizes.  */
enum riscv_rvv_vector_bits_enum {
  RVV_SCALABLE,
  RVV_NOT_IMPLEMENTED = RVV_SCALABLE,
  RVV_64 = 64,
  RVV_128 = 128,
  RVV_256 = 256,
  RVV_512 = 512,
  RVV_1024 = 1024
};

#define MASK_ZICSR    (1 << 0)
#define MASK_ZIFENCEI (1 << 1)

#define MASK_ZFH (1 << 2)

#define MASK_ZBA (1 << 0)
#define MASK_ZBB (1 << 1)
#define MASK_ZBC (1 << 2)
#define MASK_ZBS (1 << 3)

#define MASK_ZBKB     (1 << 0)
#define MASK_ZBKC     (1 << 1)
#define MASK_ZBKX     (1 << 2)
#define MASK_ZKNE     (1 << 3)
#define MASK_ZKND     (1 << 4)
#define MASK_ZKNH     (1 << 5)
#define MASK_ZKR      (1 << 6)
#define MASK_ZKSED    (1 << 7)
#define MASK_ZKSH     (1 << 8)
#define MASK_ZKT      (1 << 9)

#define MASK_ZICBOZ   (1 << 0)
#define MASK_ZICBOM   (1 << 1)
#define MASK_ZICBOP   (1 << 2)

/* P extension subset */
#define MASK_ZPN  (1 << 0)
#define MASK_ZPRV (1 << 1)
#define MASK_ZPSF (1 << 2)

/* V extension subset */
#define MASK_ZVAMO   (1 << 0)
#define MASK_ZVLSSEG (1 << 1)

#define TARGET_ZICSR    ((riscv_zi_subext & MASK_ZICSR) != 0)
#define TARGET_ZIFENCEI ((riscv_zi_subext & MASK_ZIFENCEI) != 0)

#define TARGET_ZFH ((riscv_zfh_subext & MASK_ZFH) != 0)

#define TARGET_ZBA ((riscv_bitmanip_subext & MASK_ZBA) != 0)
#define TARGET_ZBB ((riscv_bitmanip_subext & MASK_ZBB) != 0)
#define TARGET_ZBC ((riscv_bitmanip_subext & MASK_ZBC) != 0)
#define TARGET_ZBS ((riscv_bitmanip_subext & MASK_ZBS) != 0)

#define TARGET_ZBKB  ((riscv_crypto_subext & MASK_ZBKB) != 0)
#define TARGET_ZBKC  ((riscv_crypto_subext & MASK_ZBKC) != 0)
#define TARGET_ZBKX  ((riscv_crypto_subext & MASK_ZBKX) != 0)
#define TARGET_ZKNE  ((riscv_crypto_subext & MASK_ZKNE) != 0)
#define TARGET_ZKND  ((riscv_crypto_subext & MASK_ZKND) != 0)
#define TARGET_ZKNH  ((riscv_crypto_subext & MASK_ZKNH) != 0)
#define TARGET_ZKR   ((riscv_crypto_subext & MASK_ZKR) != 0)
#define TARGET_ZKSED ((riscv_crypto_subext & MASK_ZKSED) != 0)
#define TARGET_ZKSH  ((riscv_crypto_subext & MASK_ZKSH) != 0)
#define TARGET_ZKT   ((riscv_crypto_subext & MASK_ZKT) != 0)

#define TARGET_ZICBOZ ((riscv_zicmo_subext & MASK_ZICBOZ) != 0)
#define TARGET_ZICBOM ((riscv_zicmo_subext & MASK_ZICBOM) != 0)
#define TARGET_ZICBOP ((riscv_zicmo_subext & MASK_ZICBOP) != 0)

#define TARGET_ZPN ((riscv_rvp_subext & MASK_ZPN) != 0)
#define TARGET_ZPRV ((riscv_rvp_subext & MASK_ZPRV) != 0)
#define TARGET_ZPSF ((riscv_rvp_subext & MASK_ZPSF) != 0)

#define TARGET_VECTOR   (((riscv_rvv_subext & MASK_ZVAMO) != 0) && ((riscv_rvv_subext & MASK_ZVLSSEG) != 0))

#endif /* ! GCC_RISCV_OPTS_H */
