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

template<int UNSPEC>
class vds_binop : public function_base
{
public:
  bool may_require_frm_p () const override { return true; }

  rtx expand (function_expander &e) const override
  {
    if (e.op_info->op == OP_TYPE_vv)
      return e.use_exact_insn (code_for_pred_vds_vv (UNSPEC, e.vector_mode ()));
    if (e.op_info->op == OP_TYPE_vs)
      return e.use_exact_insn (code_for_pred_vds_vs (UNSPEC, e.vector_mode ()));
    gcc_unreachable ();
  }
};

class vcpack : public function_base
{
public:
  bool may_require_frm_p () const override { return true; }
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vcpack (e.vector_mode ()));
  }
};

class vcunpackr : public function_base
{
public:
  bool may_require_frm_p () const override { return true; }
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vcunpackr (e.vector_mode ()));
  }
};

class vcunpacki : public function_base
{
public:
  bool may_require_frm_p () const override { return true; }
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vcunpacki (e.vector_mode ()));
  }
};

/* Implements  vdsmacini.v/vdsmacini.s/vdsmacini.i */
class vdsmacini : public function_base
{
public:
  bool can_be_overloaded_p (enum predication_type_index pred) const override
  {
    return false;
  }
  rtx expand (function_expander &e) const override
  {
    switch (e.op_info->op)
      {
      case OP_TYPE_v:
	return e.use_exact_insn (code_for_pred_vdsmacini_v (e.vector_mode ()));
      case OP_TYPE_x:
	return e.use_exact_insn (code_for_pred_vdsmacini_x (e.vector_mode ()));
      default:
	gcc_unreachable ();
      }
  }
};

template<int UNSPEC>
class xxlvw_uniop : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_v (UNSPEC, e.vector_mode ()));
  }
};

class vdsredsumn : public function_base
{
public:
  bool can_be_overloaded_p (enum predication_type_index pred) const override
  {
    return false;
  }
  rtx expand (function_expander &e) const override
  {
    switch (e.op_info->op)
    {
      case OP_TYPE_vx:
	      return e.use_exact_insn (code_for_pred_vdsredsumn_vx (e.vector_mode ()));
      case OP_TYPE_vi:
	      return e.use_exact_insn (code_for_pred_vdsredsumn_vi (e.vector_mode ()));
      default:
	      gcc_unreachable ();
    }
  }
};

template<int UNSPEC>
class xxlvw_binop : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
    switch (e.op_info->op)
    {
      case OP_TYPE_vv:
	      return e.use_exact_insn (code_for_pred_v_vv (UNSPEC, e.vector_mode ()));
      case OP_TYPE_vs:
	      return e.use_exact_insn (code_for_pred_v_vs (UNSPEC, e.vector_mode ()));
      default:
	      gcc_unreachable ();
    }
  }
};

class vperm : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vperm_vi (e.vector_mode ()));
  }
};

template<int UNSPEC>
class vlnlp : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vlnlp_v (UNSPEC,e.vector_mode ()));
  }
};
template<int UNSPEC>
class xxlvw_vfs : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vfs_vv (UNSPEC, e.vector_mode ()));
  }
};

template<int UNSPEC>
class xxlvw_vfcvt : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vfcvt (UNSPEC, e.vector_mode ()));
  }
};

class vfcvt_b2w : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vfcvt_b2w (e.vector_mode ()));
  }
};

class xl_vfcvt_w2b : public function_base
{
public:
  rtx expand (function_expander &e) const override
  {
      return e.use_exact_insn (code_for_pred_vfcvt_w2b (e.vector_mode ()));
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
static CONSTEXPR const vds_binop<UNSPEC_VDS_MUL> vdsmul_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_MACO> vdsmaco_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMUL> vdscmul_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMULJ> vdscmulj_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMACO> vdscmaco_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMACJO> vdscmacjo_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMACOR> vdscmacor_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMACOI> vdscmacoi_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMACJOR> vdscmacjor_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMACJOI> vdscmacjoi_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMULR> vdscmulr_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMULI> vdscmuli_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMULJR> vdscmuljr_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMULJI> vdscmulji_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_MAC> vdsmac_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMAC> vdscmac_obj;
static CONSTEXPR const vds_binop<UNSPEC_VDS_CMACJ> vdscmacj_obj;
static CONSTEXPR const vcpack vcpack_obj;
static CONSTEXPR const vcunpackr vcunpackr_obj;
static CONSTEXPR const vcunpacki vcunpacki_obj;
static CONSTEXPR const vdsmacini vdsmacini_obj;
static CONSTEXPR const xxlvw_uniop<UNSPEC_VLSB> xl_vlsb_obj;
static CONSTEXPR const xxlvw_uniop<UNSPEC_VCONJ> vconj_obj;
static CONSTEXPR const xxlvw_uniop<UNSPEC_VDS_CREDSUM> vdscredsum_obj;
static CONSTEXPR const xxlvw_uniop<UNSPEC_VDS_REDSUM> vdsredsum_obj;
static CONSTEXPR const vdsredsumn vdsredsumn_obj;
static CONSTEXPR const xxlvw_binop<UNSPEC_VREDMAXI> vredmaxi_obj;
static CONSTEXPR const xxlvw_binop<UNSPEC_VREDMINI> vredmini_obj;
static CONSTEXPR const xxlvw_binop<UNSPEC_VNLE> vnle_obj;
static CONSTEXPR const xxlvw_binop<UNSPEC_VNLM> vnlm_obj;
static CONSTEXPR const vperm vperm_obj;
static CONSTEXPR const xxlvw_vfs<UNSPEC_VFSL> vfsl_obj;
static CONSTEXPR const xxlvw_vfs<UNSPEC_VFSR> vfsr_obj;
static CONSTEXPR const vlnlp<UNSPEC_VLNLP0> vlnlp0_obj;
static CONSTEXPR const vlnlp<UNSPEC_VLNLP1> vlnlp1_obj;
static CONSTEXPR const xxlvw_vfcvt<UNSPEC_VFCVT_B2H> vfcvt_b2h_obj;
static CONSTEXPR const vfcvt_b2w vfcvt_b2w_obj;
static CONSTEXPR const xxlvw_vfcvt<UNSPEC_VFCVT_H2W> vfcvt_h2w_obj;
static CONSTEXPR const xxlvw_vfcvt<UNSPEC_VFCVT_H2B> xl_vfcvt_h2b_obj;
static CONSTEXPR const xl_vfcvt_w2b xl_vfcvt_w2b_obj;
static CONSTEXPR const xxlvw_vfcvt<UNSPEC_VFCVT_W2H> xl_vfcvt_w2h_obj;
static CONSTEXPR const xxlvw_vfcvt<UNSPEC_VFCVT_P2C> vfcvt_p2c_obj;
static CONSTEXPR const xxlvw_vfcvt<UNSPEC_VFCVT_C2P> xl_vfcvt_c2p_obj;

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
/*xxlvw extension*/
BASE (vdsmul)
BASE (vcpack)
BASE (vcunpackr)
BASE (vcunpacki)
BASE (vdsmacini)
BASE (xl_vlsb)
BASE (vconj)
BASE (vdscmul)
BASE (vdscmulj)
BASE (vdscredsum)
BASE (vdscmaco)
BASE (vdscmacjo)
BASE (vdscmacor)
BASE (vdscmacoi)
BASE (vdscmacjor)
BASE (vdscmacjoi)
BASE (vdscmulr)
BASE (vdscmuli)
BASE (vdscmuljr)
BASE (vdscmulji)
BASE (vdsredsum)
BASE (vdsredsumn)
BASE (vredmaxi)
BASE (vredmini)
BASE (vperm)
BASE (vfsl)
BASE (vfsr)
BASE (vlnlp0)
BASE (vlnlp1)
BASE (vnle)
BASE (vnlm)
BASE (vdsmac)
BASE (vdscmac)
BASE (vdscmacj)
BASE (vdsmaco)
BASE (vfcvt_b2h)
BASE (vfcvt_b2w)
BASE (vfcvt_h2w)
BASE (xl_vfcvt_h2b)
BASE (xl_vfcvt_w2b)
BASE (xl_vfcvt_w2h)
BASE (vfcvt_p2c)
BASE (xl_vfcvt_c2p)
} // end namespace riscv_vector
