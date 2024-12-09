/* function_base implementation for nuclei custom 'V' Extension for GNU compiler.
   Copyright (C) 2024 Free Software Foundation, Inc.
   Contributed by Nuclei.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "tm.h"
#include "tree.h"
#include "rtl.h"
#include "tm_p.h"
#include "memmodel.h"
#include "insn-codes.h"
#include "optabs.h"
#include "recog.h"
#include "expr.h"
#include "basic-block.h"
#include "function.h"
#include "fold-const.h"
#include "gimple.h"
#include "gimple-iterator.h"
#include "gimplify.h"
#include "explow.h"
#include "emit-rtl.h"
#include "tree-vector-builder.h"
#include "rtx-vector-builder.h"
#include "riscv-vector-builtins.h"
#include "riscv-vector-builtins-shapes.h"
#include "nuclei-vector-builtins-bases.h"

using namespace riscv_vector;

namespace riscv_vector {

/* Implements xl_vqmacc.  */
class xl_vqmacc : public function_base
{
public:
  bool has_merge_operand_p () const override { return false; }
  bool apply_mask_policy_p () const override { return false; }
  bool use_mask_predication_p () const override { return false; }

  bool can_be_overloaded_p (enum predication_type_index pred) const override
  {
    return pred == PRED_TYPE_tu;
  }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_4x4x4)
    {
      return e.use_widen_ternop_insn (code_for_pred_matrix_mul_plus_qoq (SIGN_EXTEND, e.vector_mode ()));
    }
    gcc_unreachable ();
  }
};

/* Implements xl_vqmaccu.  */
class xl_vqmaccu : public function_base
{
public:
  bool has_merge_operand_p () const override { return false; }
  bool apply_mask_policy_p () const override { return false; }
  bool use_mask_predication_p () const override { return false; }
  bool can_be_overloaded_p (enum predication_type_index pred) const override
  {
    return pred == PRED_TYPE_tu;
  }
  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_4x4x4)
      return e.use_widen_ternop_insn (code_for_pred_matrix_mul_plus_qoq (ZERO_EXTEND, e.vector_mode ()));
    gcc_unreachable ();
  }
};

// /* Implements xl_vqmaccsu.  */
class xl_vqmaccsu : public function_base
{
public:
  bool has_merge_operand_p () const override { return false; }
  bool apply_mask_policy_p () const override { return false; }
  bool use_mask_predication_p () const override { return false; }

  bool can_be_overloaded_p (enum predication_type_index pred) const override
  {
    return pred == PRED_TYPE_tu;
  }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_4x4x4)
      return e.use_widen_ternop_insn (code_for_pred_matrix_mul_plussu_qoq (e.vector_mode ()));
    gcc_unreachable ();
  }
};

/* Implements xl_vqmaccus.  */
class xl_vqmaccus : public function_base
{
public:
  bool has_merge_operand_p () const override { return false; }
  bool apply_mask_policy_p () const override { return false; }
  bool use_mask_predication_p () const override { return false; }
  bool can_be_overloaded_p (enum predication_type_index pred) const override
  {
    return pred == PRED_TYPE_tu;
  }
  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_4x4x4)
      return e.use_widen_ternop_insn (code_for_pred_matrix_mul_plusus_qoq (e.vector_mode ()));
    gcc_unreachable ();
  }
};

static CONSTEXPR const xl_vqmacc xl_vqmacc_obj;
static CONSTEXPR const xl_vqmaccu xl_vqmaccu_obj;
static CONSTEXPR const xl_vqmaccsu xl_vqmaccsu_obj;
static CONSTEXPR const xl_vqmaccus xl_vqmaccus_obj;


/* Declare the function base NAME, pointing it to an instance
   of class <NAME>_obj.  */
#define BASE(NAME) \
  namespace bases { const function_base *const NAME = &NAME##_obj; }


BASE (xl_vqmacc)
BASE (xl_vqmaccu)
BASE (xl_vqmaccsu)
BASE (xl_vqmaccus)

}
