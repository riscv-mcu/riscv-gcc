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

enum frm_op_type
{
  NO_FRM,
  HAS_FRM,
};

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

/* Implements xl_vfwadd/xl_vfwsub/xl_vfwmul. */
template <rtx_code CODE, enum frm_op_type FRM_OP = NO_FRM>
class xl_widen_binop_fp : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  rtx expand (function_expander &e) const override
  {
    switch(e.op_info->op)
      {
	case OP_TYPE_vv:
	  return e.use_exact_insn (code_for_pred_dual_widen_xl(CODE, e.vector_mode()));
	case OP_TYPE_vf:
	  return e.use_exact_insn (code_for_pred_dual_widen_xl_scalar(CODE, e.vector_mode()));
	case OP_TYPE_wv:
	  if(CODE == PLUS)
	    return e.use_exact_insn (code_for_pred_single_widen_xl_add(e.vector_mode()));
	  else
	    return e.use_exact_insn (code_for_pred_single_widen_xl_sub(e.vector_mode()));
	case OP_TYPE_wf:
	    return e.use_exact_insn (code_for_pred_single_widen_xl_scalar(CODE, e.vector_mode ()));
	default:
	  gcc_unreachable ();
      }
  }
};

/* Implements xl_vfwmacc */
template<enum frm_op_type FRM_OP = NO_FRM>
class xl_vfwmacc : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  bool has_merge_operand_p () const override { return false; }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_vf)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul_scalar (PLUS, e.vector_mode ()));
    if (e.op_info->op == OP_TYPE_vv)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul (PLUS, e.vector_mode ()));
    gcc_unreachable ();
  }
};

/* Implements xl_vfwnmacc */
template<enum frm_op_type FRM_OP = NO_FRM>
class xl_vfwnmacc : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  bool has_merge_operand_p () const override { return false; }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_vf)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul_neg_scalar (MINUS, e.vector_mode ()));
    if (e.op_info->op == OP_TYPE_vv)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul_neg (MINUS, e.vector_mode ()));
    gcc_unreachable ();
  }
};

/* Implements xl_vfwmsac */
template<enum frm_op_type FRM_OP = NO_FRM>
class xl_vfwmsac : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  bool has_merge_operand_p () const override { return false; }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_vf)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul_scalar (MINUS, e.vector_mode ()));
    if (e.op_info->op == OP_TYPE_vv)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul (MINUS, e.vector_mode ()));
    gcc_unreachable ();
  }
};

/* Implements xl_vfwnmsac */
template<enum frm_op_type FRM_OP = NO_FRM>
class xl_vfwnmsac : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  bool has_merge_operand_p () const override { return false; }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_vf)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul_neg_scalar (PLUS, e.vector_mode ()));
    if (e.op_info->op == OP_TYPE_vv)
      return e.use_widen_ternop_insn (code_for_pred_widen_xl_mul_neg (PLUS, e.vector_mode ()));
    gcc_unreachable ();
  }
};

/* Implements xl_vfclass.  */
class xl_vfclass : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
    return e.use_exact_insn (code_for_pred_class (e.arg_mode (0)));
  }
};

/* Implements xl_vfcvt.x.  */
template<int UNSPEC, enum frm_op_type FRM_OP = NO_FRM>
class xl_vfcvt_x : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  rtx expand (function_expander &e) const override
  {
    return e.use_exact_insn (code_for_pred_xl_fcvt_x_f (UNSPEC, e.arg_mode (0)));
  }
};

/* Implements xl_vfcvt.rtz.x.  */
template<rtx_code CODE>
class xl_vfcvt_rtz_x : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
    return e.use_exact_insn (code_for_pred_xl (CODE, e.arg_mode (0)));
  }
};

/* Implements xl_vfwcvt.x.  */
template<int UNSPEC, enum frm_op_type FRM_OP = NO_FRM>
class xl_vfwcvt_x : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  rtx expand (function_expander &e) const override
  {
    return e.use_exact_insn (
      code_for_pred_widen_xl_fcvt_x_f (UNSPEC, e.vector_mode ()));
  }
};

/* Implements xl_vfwcvt.rtz.x.  */
template<rtx_code CODE>
class xl_vfwcvt_rtz_x : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
    return e.use_exact_insn (code_for_pred_widen_xl (CODE, e.vector_mode ()));
  }
};

/* Implements xl_vfcvt.f */
class xl_vfwcvt_f : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_f_v)
      return e.use_exact_insn (code_for_pred_xl_extend (e.vector_mode ()));
    gcc_unreachable ();
  }
};

/* Implements xl_vfncvt.f */
template<enum frm_op_type FRM_OP = NO_FRM>
class xl_vfncvt_f : public function_base
{
public:
  bool has_rounding_mode_operand_p () const override
  {
    return FRM_OP == HAS_FRM;
  }

  bool may_require_frm_p () const override { return true; }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_f_w)
      return e.use_exact_insn (code_for_pred_xl_trunc (e.vector_mode ()));
    if (e.op_info->op == OP_TYPE_x_w)
      return e.use_exact_insn (code_for_pred_xl_narrow (FLOAT, e.arg_mode (0)));
    if (e.op_info->op == OP_TYPE_xu_w)
      return e.use_exact_insn (code_for_pred_xl_narrow (UNSIGNED_FLOAT, e.arg_mode (0)));
    gcc_unreachable ();
  }
};

/* Implements xl_vfcvt.rod.f */
class xl_vfncvt_rod_f : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
    return e.use_exact_insn (code_for_pred_xl_rod_trunc (e.vector_mode ()));
  }
};

static CONSTEXPR const xl_vqmacc xl_vqmacc_obj;
static CONSTEXPR const xl_vqmaccu xl_vqmaccu_obj;
static CONSTEXPR const xl_vqmaccsu xl_vqmaccsu_obj;
static CONSTEXPR const xl_vqmaccus xl_vqmaccus_obj;
/* Xxlvfbf */
static CONSTEXPR const xl_widen_binop_fp<PLUS> xl_vfwadd_obj;
static CONSTEXPR const xl_widen_binop_fp<PLUS, HAS_FRM> xl_vfwadd_frm_obj;
static CONSTEXPR const xl_widen_binop_fp<MINUS> xl_vfwsub_obj;
static CONSTEXPR const xl_widen_binop_fp<MINUS, HAS_FRM> xl_vfwsub_frm_obj;
static CONSTEXPR const xl_widen_binop_fp<MULT> xl_vfwmul_obj;
static CONSTEXPR const xl_widen_binop_fp<MULT, HAS_FRM> xl_vfwmul_frm_obj;
static CONSTEXPR const xl_vfwmacc<NO_FRM> xl_vfwmacc_obj;
static CONSTEXPR const xl_vfwmacc<HAS_FRM> xl_vfwmacc_frm_obj;
static CONSTEXPR const xl_vfwnmacc<NO_FRM> xl_vfwnmacc_obj;
static CONSTEXPR const xl_vfwnmacc<HAS_FRM> xl_vfwnmacc_frm_obj;
static CONSTEXPR const xl_vfwmsac<NO_FRM> xl_vfwmsac_obj;
static CONSTEXPR const xl_vfwmsac<HAS_FRM> xl_vfwmsac_frm_obj;
static CONSTEXPR const xl_vfwnmsac<NO_FRM> xl_vfwnmsac_obj;
static CONSTEXPR const xl_vfwnmsac<HAS_FRM> xl_vfwnmsac_frm_obj;
static CONSTEXPR const xl_vfclass xl_vfclass_obj;
static CONSTEXPR const xl_vfcvt_x<UNSPEC_VFCVT> xl_vfcvt_x_obj;
static CONSTEXPR const xl_vfcvt_x<UNSPEC_VFCVT, HAS_FRM> xl_vfcvt_x_frm_obj;
static CONSTEXPR const xl_vfcvt_x<UNSPEC_UNSIGNED_VFCVT> xl_vfcvt_xu_obj;
static CONSTEXPR const xl_vfcvt_x<UNSPEC_UNSIGNED_VFCVT, HAS_FRM> xl_vfcvt_xu_frm_obj;
static CONSTEXPR const xl_vfcvt_rtz_x<FIX> xl_vfcvt_rtz_x_obj;
static CONSTEXPR const xl_vfcvt_rtz_x<UNSIGNED_FIX> xl_vfcvt_rtz_xu_obj;
static CONSTEXPR const xl_vfwcvt_x<UNSPEC_VFCVT> xl_vfwcvt_x_obj;
static CONSTEXPR const xl_vfwcvt_x<UNSPEC_VFCVT, HAS_FRM> xl_vfwcvt_x_frm_obj;
static CONSTEXPR const xl_vfwcvt_x<UNSPEC_UNSIGNED_VFCVT> xl_vfwcvt_xu_obj;
static CONSTEXPR const xl_vfwcvt_x<UNSPEC_UNSIGNED_VFCVT, HAS_FRM> xl_vfwcvt_xu_frm_obj;
static CONSTEXPR const xl_vfwcvt_rtz_x<FIX> xl_vfwcvt_rtz_x_obj;
static CONSTEXPR const xl_vfwcvt_rtz_x<UNSIGNED_FIX> xl_vfwcvt_rtz_xu_obj;
static CONSTEXPR const xl_vfwcvt_f xl_vfwcvt_f_obj;
static CONSTEXPR const xl_vfncvt_f<NO_FRM> xl_vfncvt_f_obj;
static CONSTEXPR const xl_vfncvt_f<HAS_FRM> xl_vfncvt_f_frm_obj;
static CONSTEXPR const xl_vfncvt_rod_f xl_vfncvt_rod_f_obj;


/* Declare the function base NAME, pointing it to an instance
   of class <NAME>_obj.  */
#define BASE(NAME) \
  namespace bases { const function_base *const NAME = &NAME##_obj; }


BASE (xl_vqmacc)
BASE (xl_vqmaccu)
BASE (xl_vqmaccsu)
BASE (xl_vqmaccus)
/* Xxlvfbf */
BASE (xl_vfwadd)
BASE (xl_vfwadd_frm)
BASE (xl_vfwsub)
BASE (xl_vfwsub_frm)
BASE (xl_vfwmul)
BASE (xl_vfwmul_frm)
BASE (xl_vfwmacc)
BASE (xl_vfwmacc_frm)
BASE (xl_vfwnmacc)
BASE (xl_vfwnmacc_frm)
BASE (xl_vfwmsac)
BASE (xl_vfwmsac_frm)
BASE (xl_vfwnmsac)
BASE (xl_vfwnmsac_frm)
BASE (xl_vfclass)
BASE (xl_vfcvt_x)
BASE (xl_vfcvt_x_frm)
BASE (xl_vfcvt_xu)
BASE (xl_vfcvt_xu_frm)
BASE (xl_vfcvt_rtz_x)
BASE (xl_vfcvt_rtz_xu)
BASE (xl_vfwcvt_x)
BASE (xl_vfwcvt_x_frm)
BASE (xl_vfwcvt_xu)
BASE (xl_vfwcvt_xu_frm)
BASE (xl_vfwcvt_rtz_x)
BASE (xl_vfwcvt_rtz_xu)
BASE (xl_vfwcvt_f)
BASE (xl_vfncvt_f)
BASE (xl_vfncvt_f_frm)
BASE (xl_vfncvt_rod_f)

} // end namespace riscv_vector
