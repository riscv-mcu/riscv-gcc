/* RISC-V-specific code for C family languages.
   Copyright (C) 2011-2020 Free Software Foundation, Inc.
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

#define IN_TARGET_CODE 1

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "c-family/c-common.h"
#include "cpplib.h"

#define builtin_define(TXT) cpp_define (pfile, TXT)

/* Implement TARGET_CPU_CPP_BUILTINS.  */

void
riscv_cpu_cpp_builtins (cpp_reader *pfile)
{
  builtin_define ("__riscv");

  if (TARGET_RVC)
    builtin_define ("__riscv_compressed");

  if (TARGET_RVE)
    builtin_define ("__riscv_32e");

  if (TARGET_ATOMIC)
    builtin_define ("__riscv_atomic");

  if (TARGET_MUL)
    builtin_define ("__riscv_mul");
  if (TARGET_DIV)
    builtin_define ("__riscv_div");
  if (TARGET_DIV && TARGET_MUL)
    builtin_define ("__riscv_muldiv");

  builtin_define_with_int_value ("__riscv_xlen", UNITS_PER_WORD * 8);
  if (TARGET_HARD_FLOAT)
    builtin_define_with_int_value ("__riscv_flen", UNITS_PER_FP_REG * 8);

  if (TARGET_FP16)
    builtin_define ("__riscv_zfh");

  if (TARGET_HARD_FLOAT && TARGET_FDIV)
    {
      builtin_define ("__riscv_fdiv");
      builtin_define ("__riscv_fsqrt");
    }

  switch (riscv_abi)
    {
    case ABI_ILP32E:
      builtin_define ("__riscv_abi_rve");
      gcc_fallthrough ();

    case ABI_ILP32:
    case ABI_LP64:
      builtin_define ("__riscv_float_abi_soft");
      break;

    case ABI_ILP32F:
    case ABI_LP64F:
      builtin_define ("__riscv_float_abi_single");
      break;

    case ABI_ILP32D:
    case ABI_LP64D:
      builtin_define ("__riscv_float_abi_double");
      break;
    }

  switch (riscv_cmodel)
    {
    case CM_MEDLOW:
      builtin_define ("__riscv_cmodel_medlow");
      break;

    case CM_PIC:
      /* __riscv_cmodel_pic is deprecated, and will removed in next GCC release.
	 see https://github.com/riscv/riscv-c-api-doc/pull/11  */
      builtin_define ("__riscv_cmodel_pic");
      /* FALLTHROUGH. */

    case CM_MEDANY:
      builtin_define ("__riscv_cmodel_medany");
      break;
    }

  if (TARGET_VECTOR)
  {
    builtin_define ("__riscv_vector");
    builtin_define ("__riscv_v");
  }

  if (TARGET_ZPN)
  {
    builtin_define ("__riscv_zpn");
    builtin_define ("__riscv_dsp");
  }
    
  if (TARGET_ZPRV)
    builtin_define ("__riscv_zprv");

  if (TARGET_ZPSF)
    builtin_define ("__riscv_zpsf");

  if (TARGET_ZBA)
  {
    builtin_define ("__riscv_zba");
    builtin_define ("__riscv_bitmanip");
    builtin_define ("__riscv_b");
  }

  if (TARGET_ZBB)
    builtin_define ("__riscv_zbb");

  if (TARGET_ZBC)
    builtin_define ("__riscv_zbc");

  if (TARGET_ZBS)
    builtin_define ("__riscv_zbs");

  if (TARGET_ZBKB)
    builtin_define ("__riscv_zbkb");

  if (TARGET_ZBKC)
    builtin_define ("__riscv_zbkc");

  if (TARGET_ZBKX)
    builtin_define ("__riscv_zbkx");

  if (TARGET_ZKNE)
    builtin_define ("__riscv_zkne");

  if (TARGET_ZKND)
    builtin_define ("__riscv_zknd");
  
  if (TARGET_ZKNH)
    builtin_define ("__riscv_zknh");

  if (TARGET_ZKR)
    builtin_define ("__riscv_zkr");

  if (TARGET_ZKSED)
    builtin_define ("__riscv_zksed");

  if (TARGET_ZKSH)
    builtin_define ("__riscv_zksh");

  if (TARGET_ZKT)
    builtin_define ("__riscv_zkt");
}
