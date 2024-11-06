;; Machine description for RISC-V bfloat16 extensions.
;; Copyright (C) 2024 Free Software Foundation, Inc.

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

(define_mode_iterator VWCONVERTI_XL [
  (RVVM8SI "TARGET_XXLVFBF") (RVVM4SI "TARGET_XXLVFBF") (RVVM2SI "TARGET_XXLVFBF") (RVVM1SI "TARGET_XXLVFBF")
  (RVVMF2SI "TARGET_XXLVFBF")

  (V1SI "riscv_vector::vls_mode_valid_p (V1SImode) && TARGET_XXLVFBF")
  (V2SI "riscv_vector::vls_mode_valid_p (V2SImode) && TARGET_XXLVFBF")
  (V4SI "riscv_vector::vls_mode_valid_p (V4SImode) && TARGET_XXLVFBF")
  (V8SI "riscv_vector::vls_mode_valid_p (V8SImode) && TARGET_XXLVFBF")
  (V16SI "riscv_vector::vls_mode_valid_p (V16SImode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 64")
  (V32SI "riscv_vector::vls_mode_valid_p (V32SImode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 128")
  (V64SI "riscv_vector::vls_mode_valid_p (V64SImode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 256")
  (V128SI "riscv_vector::vls_mode_valid_p (V128SImode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 512")
  (V256SI "riscv_vector::vls_mode_valid_p (V256SImode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 1024")
  (V512SI "riscv_vector::vls_mode_valid_p (V512SImode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 2048")
  (V1024SI "riscv_vector::vls_mode_valid_p (V1024SImode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 4096")
])

(define_mode_iterator VLSF_XXLVFBF [
  (V1BF "riscv_vector::vls_mode_valid_p (V1BFmode) && TARGET_XXLVFBF")
  (V2BF "riscv_vector::vls_mode_valid_p (V2BFmode) && TARGET_XXLVFBF")
  (V4BF "riscv_vector::vls_mode_valid_p (V4BFmode) && TARGET_XXLVFBF")
  (V8BF "riscv_vector::vls_mode_valid_p (V8BFmode) && TARGET_XXLVFBF")
  (V16BF "riscv_vector::vls_mode_valid_p (V16BFmode) && TARGET_XXLVFBF")
  (V32BF "riscv_vector::vls_mode_valid_p (V32BFmode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 64")
  (V64BF "riscv_vector::vls_mode_valid_p (V64BFmode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 128")
  (V128BF "riscv_vector::vls_mode_valid_p (V128BFmode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 256")
  (V256BF "riscv_vector::vls_mode_valid_p (V256BFmode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 512")
  (V512BF "riscv_vector::vls_mode_valid_p (V512BFmode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 1024")
  (V1024BF "riscv_vector::vls_mode_valid_p (V1024BFmode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 2048")
  (V2048BF "riscv_vector::vls_mode_valid_p (V2048BFmode) && TARGET_XXLVFBF && TARGET_MIN_VLEN >= 4096")
])

(define_mode_iterator V_VLSF_XXLVFBF [VF_ZVFBF16 VLSF_XXLVFBF])

(define_mode_attr VNCONVERT_XL [
  (RVVM8SI "RVVM4BF") (RVVM4SI "RVVM2BF") (RVVM2SI "RVVM1BF") (RVVM1SI "RVVMF2BF") (RVVMF2SI "RVVMF4BF")

  (V1SI "V1BF")
  (V2SI "V2BF")
  (V4SI "V4BF")
  (V8SI "V8BF")
  (V16SI "V16BF")
  (V32SI "V32BF")
  (V64SI "V64BF")
  (V128SI "V128BF")
  (V256SI "V256BF")
  (V512SI "V512BF")
  (V1024SI "V1024BF")
])

;; Vector Widening Add/Subtract/Multiply.
(define_insn "@pred_dual_widen_xl_<optab><mode>"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                  "=&vr,  &vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"           "vmWc1,vmWc1")
	     (match_operand 5 "vector_length_operand"              "   rK,   rK")
	     (match_operand 6 "const_int_operand"                  "    i,    i")
	     (match_operand 7 "const_int_operand"                  "    i,    i")
	     (match_operand 8 "const_int_operand"                  "    i,    i")
	     (match_operand 9 "const_int_operand"                  "    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (any_widen_binop:VWEXTF_ZVFBF
	    (float_extend:VWEXTF_ZVFBF
	      (match_operand:<V_FP32TOBF16_TRUNC> 3 "register_operand" "   vr,   vr"))
	    (float_extend:VWEXTF_ZVFBF
	      (match_operand:<V_FP32TOBF16_TRUNC> 4 "register_operand" "   vr,   vr")))
	  (match_operand:VWEXTF_ZVFBF 2 "vector_merge_operand"           "   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfw<insn>.vv\t%0,%3,%4%p1"
  [(set_attr "type" "vf<widen_binop_insn_type>")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_dual_widen_xl_<optab><mode>_scalar"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                  "=&vr,  &vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"           "vmWc1,vmWc1")
	     (match_operand 5 "vector_length_operand"              "   rK,   rK")
	     (match_operand 6 "const_int_operand"                  "    i,    i")
	     (match_operand 7 "const_int_operand"                  "    i,    i")
	     (match_operand 8 "const_int_operand"                  "    i,    i")
	     (match_operand 9 "const_int_operand"                  "    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (any_widen_binop:VWEXTF_ZVFBF
	    (float_extend:VWEXTF_ZVFBF
	      (match_operand:<V_FP32TOBF16_TRUNC> 3 "register_operand" "   vr,   vr"))
	    (float_extend:VWEXTF_ZVFBF
	      (vec_duplicate:<V_FP32TOBF16_TRUNC>
		(match_operand:<VF32_SUBEL> 4 "register_operand"       "    f,    f"))))
	  (match_operand:VWEXTF_ZVFBF 2 "vector_merge_operand"           "   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfw<insn>.vf\t%0,%3,%4%p1"
  [(set_attr "type" "vf<widen_binop_insn_type>")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_single_widen_xl_add_<mode>"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                  "=&vr,  &vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"           "vmWc1,vmWc1")
	     (match_operand 5 "vector_length_operand"              "   rK,   rK")
	     (match_operand 6 "const_int_operand"                  "    i,    i")
	     (match_operand 7 "const_int_operand"                  "    i,    i")
	     (match_operand 8 "const_int_operand"                  "    i,    i")
	     (match_operand 9 "const_int_operand"                  "    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (plus:VWEXTF_ZVFBF
	    (float_extend:VWEXTF_ZVFBF
	      (match_operand:<V_FP32TOBF16_TRUNC> 4 "register_operand" "   vr,   vr"))
	    (match_operand:VWEXTF_ZVFBF 3 "register_operand"             "   vr,   vr"))
	  (match_operand:VWEXTF_ZVFBF 2 "vector_merge_operand"           "   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfwadd.wv\t%0,%3,%4%p1"
  [(set_attr "type" "vfwalu")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_single_widen_xl_sub_<mode>"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                  "=&vr,  &vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"           "vmWc1,vmWc1")
	     (match_operand 5 "vector_length_operand"              "   rK,   rK")
	     (match_operand 6 "const_int_operand"                  "    i,    i")
	     (match_operand 7 "const_int_operand"                  "    i,    i")
	     (match_operand 8 "const_int_operand"                  "    i,    i")
	     (match_operand 9 "const_int_operand"                  "    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (minus:VWEXTF_ZVFBF
	    (match_operand:VWEXTF_ZVFBF 3 "register_operand"             "   vr,   vr")
	    (float_extend:VWEXTF_ZVFBF
	      (match_operand:<V_FP32TOBF16_TRUNC> 4 "register_operand" "   vr,   vr")))
	  (match_operand:VWEXTF_ZVFBF 2 "vector_merge_operand"           "   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfwsub.wv\t%0,%3,%4%p1"
  [(set_attr "type" "vfwalu")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_single_widen_xl_<plus_minus:optab><mode>_scalar"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                "=vd, vd, vr, vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"          " vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"             " rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"                 "  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"                 "  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"                 "  i,  i,  i,  i")
	     (match_operand 9 "const_int_operand"                 "  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (plus_minus:VWEXTF_ZVFBF
	    (match_operand:VWEXTF_ZVFBF 3 "register_operand"            " vr, vr, vr, vr")
	    (float_extend:VWEXTF_ZVFBF
	      (vec_duplicate:<V_FP32TOBF16_TRUNC>
		(match_operand:<VF32_SUBEL> 4 "register_operand"      "  f,  f,  f,  f"))))
	  (match_operand:VWEXTF_ZVFBF 2 "vector_merge_operand"          " vu,  0, vu,  0")))]
  "TARGET_XXLVFBF"
  "vfw<insn>.wf\t%0,%3,%4%p1"
  [(set_attr "type" "vfwalu")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

;; -------------------------------------------------------------------------------
;; ---- Predicated widen floating-point ternary operations
;; -------------------------------------------------------------------------------
;; Includes:
;; - 13.7 Vector Widening Floating-Point Fused Multiply-Add Instructions
;; - xl_vfwmacc/xl_vfwnmacc/xl_vfwmsac/xl_vfwnmsac
;; -------------------------------------------------------------------------------

(define_insn "@pred_widen_xl_mul_<optab><mode>"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                    "=&vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"             "vmWc1")
	     (match_operand 5 "vector_length_operand"                "   rK")
	     (match_operand 6 "const_int_operand"                    "    i")
	     (match_operand 7 "const_int_operand"                    "    i")
	     (match_operand 8 "const_int_operand"                    "    i")
	     (match_operand 9 "const_int_operand"                    "    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (plus_minus:VWEXTF_ZVFBF
	    (mult:VWEXTF_ZVFBF
	      (float_extend:VWEXTF_ZVFBF
	        (match_operand:<V_FP32TOBF16_TRUNC> 3 "register_operand" "   vr"))
	      (float_extend:VWEXTF_ZVFBF
	        (match_operand:<V_FP32TOBF16_TRUNC> 4 "register_operand" "   vr")))
	    (match_operand:VWEXTF_ZVFBF 2 "register_operand"               "    0"))
	  (match_dup 2)))]
  "TARGET_XXLVFBF"
  "vfw<macc_msac>.vv\t%0,%3,%4%p1"
  [(set_attr "type" "vfwmuladd")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_widen_xl_mul_<optab><mode>_scalar"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                    "=&vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"             "vmWc1")
	     (match_operand 5 "vector_length_operand"                "   rK")
	     (match_operand 6 "const_int_operand"                    "    i")
	     (match_operand 7 "const_int_operand"                    "    i")
	     (match_operand 8 "const_int_operand"                    "    i")
	     (match_operand 9 "const_int_operand"                    "    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (plus_minus:VWEXTF_ZVFBF
	    (mult:VWEXTF_ZVFBF
	      (float_extend:VWEXTF_ZVFBF
	        (vec_duplicate:<V_FP32TOBF16_TRUNC>
	          (match_operand:<VF32_SUBEL> 3 "register_operand"       "    f")))
	      (float_extend:VWEXTF_ZVFBF
	        (match_operand:<V_FP32TOBF16_TRUNC> 4 "register_operand" "   vr")))
	    (match_operand:VWEXTF_ZVFBF 2 "register_operand"               "    0"))
	  (match_dup 2)))]
  "TARGET_XXLVFBF"
  "vfw<macc_msac>.vf\t%0,%3,%4%p1"
  [(set_attr "type" "vfwmuladd")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_widen_xl_mul_neg_<optab><mode>"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                      "=&vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"               "vmWc1")
	     (match_operand 5 "vector_length_operand"                  "   rK")
	     (match_operand 6 "const_int_operand"                      "    i")
	     (match_operand 7 "const_int_operand"                      "    i")
	     (match_operand 8 "const_int_operand"                      "    i")
	     (match_operand 9 "const_int_operand"                      "    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (plus_minus:VWEXTF_ZVFBF
	    (neg:VWEXTF_ZVFBF
	      (mult:VWEXTF_ZVFBF
	        (float_extend:VWEXTF_ZVFBF
	          (match_operand:<V_FP32TOBF16_TRUNC> 3 "register_operand" "   vr"))
	        (float_extend:VWEXTF_ZVFBF
	          (match_operand:<V_FP32TOBF16_TRUNC> 4 "register_operand" "   vr"))))
	      (match_operand:VWEXTF_ZVFBF 2 "register_operand"               "    0"))
	  (match_dup 2)))]
  "TARGET_XXLVFBF"
  "vfw<nmsac_nmacc>.vv\t%0,%3,%4%p1"
  [(set_attr "type" "vfwmuladd")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

(define_insn "@pred_widen_xl_mul_neg_<optab><mode>_scalar"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                      "=&vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"               "vmWc1")
	     (match_operand 5 "vector_length_operand"                  "   rK")
	     (match_operand 6 "const_int_operand"                      "    i")
	     (match_operand 7 "const_int_operand"                      "    i")
	     (match_operand 8 "const_int_operand"                      "    i")
	     (match_operand 9 "const_int_operand"                      "    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (plus_minus:VWEXTF_ZVFBF
	    (neg:VWEXTF_ZVFBF
	      (mult:VWEXTF_ZVFBF
	        (float_extend:VWEXTF_ZVFBF
	          (vec_duplicate:<V_FP32TOBF16_TRUNC>
	            (match_operand:<VF32_SUBEL> 3 "register_operand"       "    f")))
	        (float_extend:VWEXTF_ZVFBF
	          (match_operand:<V_FP32TOBF16_TRUNC> 4 "register_operand" "   vr"))))
	    (match_operand:VWEXTF_ZVFBF 2 "register_operand"                 "    0"))
	  (match_dup 2)))]
  "TARGET_XXLVFBF"
  "vfw<nmsac_nmacc>.vf\t%0,%3,%4%p1"
  [(set_attr "type" "vfwmuladd")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])

;; -------------------------------------------------------------------------------
;; ---- Predicated floating-point conversions
;; -------------------------------------------------------------------------------
;; Includes:
;; - 13.17 Single-Width Floating-Point/Integer Type-Convert Instructions
;; -------------------------------------------------------------------------------

(define_insn "@pred_xl_fcvt_x<v_su>_f<mode>"
  [(set (match_operand:<VCONVERT> 0 "register_operand"       "=vd, vd, vr, vr")
	(if_then_else:<VCONVERT>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"     " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"        " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 8 "const_int_operand"            "  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<VCONVERT>
	     [(match_operand:V_VLSF_XXLVFBF 3 "register_operand"     " vr, vr, vr, vr")] VFCVTS)
	  (match_operand:<VCONVERT> 2 "vector_merge_operand" " vu,  0, vu,  0")))]
  "TARGET_XXLVFBF"
  "vfcvt.x<v_su>.f.v\t%0,%3%p1"
  [(set_attr "type" "vfcvtftoi")
   (set_attr "mode" "<MODE>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

(define_insn "@pred_xl_<fix_cvt><mode>"
  [(set (match_operand:<VCONVERT> 0 "register_operand"       "=vd, vd, vr, vr")
	(if_then_else:<VCONVERT>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"     " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"        " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"            "  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (any_fix:<VCONVERT>
	     (match_operand:V_VLSF_XXLVFBF 3 "register_operand"          " vr, vr, vr, vr"))
	  (match_operand:<VCONVERT> 2 "vector_merge_operand" " vu,  0, vu,  0")))]
  "TARGET_XXLVFBF"
  "vfcvt.rtz.x<u>.f.v\t%0,%3%p1"
  [(set_attr "type" "vfcvtftoi")
   (set_attr "mode" "<MODE>")])

;; -------------------------------------------------------------------------------
;; ---- Predicated floating-point widen conversions
;; -------------------------------------------------------------------------------
;; Includes:
;; - 13.18 Widening Floating-Point/Integer Type-Convert Instructions
;; -------------------------------------------------------------------------------

(define_insn "@pred_widen_xl_fcvt_x<v_su>_f<mode>"
  [(set (match_operand:VWCONVERTI_XL 0 "register_operand"         "=&vr,  &vr")
	(if_then_else:VWCONVERTI_XL
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"      "vmWc1,vmWc1")
	     (match_operand 4 "vector_length_operand"         "   rK,   rK")
	     (match_operand 5 "const_int_operand"             "    i,    i")
	     (match_operand 6 "const_int_operand"             "    i,    i")
	     (match_operand 7 "const_int_operand"             "    i,    i")
	     (match_operand 8 "const_int_operand"             "    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:VWCONVERTI_XL
	     [(match_operand:<VNCONVERT_XL> 3 "register_operand" "   vr,   vr")] VFCVTS)
	  (match_operand:VWCONVERTI_XL 2 "vector_merge_operand"  "   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfwcvt.x<v_su>.f.v\t%0,%3%p1"
  [(set_attr "type" "vfwcvtftoi")
   (set_attr "mode" "<VNCONVERT_XL>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))])

(define_insn "@pred_widen_xl_<fix_cvt><mode>"
  [(set (match_operand:VWCONVERTI_XL 0 "register_operand"        "=&vr,  &vr")
	(if_then_else:VWCONVERTI_XL
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"     "vmWc1,vmWc1")
	     (match_operand 4 "vector_length_operand"        "   rK,   rK")
	     (match_operand 5 "const_int_operand"            "    i,    i")
	     (match_operand 6 "const_int_operand"            "    i,    i")
	     (match_operand 7 "const_int_operand"            "    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (any_fix:VWCONVERTI_XL
	     (match_operand:<VNCONVERT_XL> 3 "register_operand" "   vr,   vr"))
	  (match_operand:VWCONVERTI_XL 2 "vector_merge_operand" "   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfwcvt.rtz.x<u>.f.v\t%0,%3%p1"
  [(set_attr "type" "vfwcvtftoi")
   (set_attr "mode" "<VNCONVERT_XL>")])

(define_insn "@pred_xl_extend<mode>"
  [(set (match_operand:VWEXTF_ZVFBF 0 "register_operand"                 "=&vr,  &vr")
	(if_then_else:VWEXTF_ZVFBF
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"          "vmWc1,vmWc1")
	     (match_operand 4 "vector_length_operand"             "   rK,   rK")
	     (match_operand 5 "const_int_operand"                 "    i,    i")
	     (match_operand 6 "const_int_operand"                 "    i,    i")
	     (match_operand 7 "const_int_operand"                 "    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (float_extend:VWEXTF_ZVFBF
	     (match_operand:<V_FP32TOBF16_TRUNC> 3 "register_operand" "   vr,   vr"))
	  (match_operand:VWEXTF_ZVFBF 2 "vector_merge_operand"          "   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfwcvt.f.f.v\t%0,%3%p1"
  [(set_attr "type" "vfwcvtftof")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")])

(define_insn "@pred_xl_trunc<mode>"
  [(set (match_operand:<V_FP32TOBF16_TRUNC> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
	(if_then_else:<V_FP32TOBF16_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"           " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
	     (match_operand 4 "vector_length_operand"              " rK, rK, rK, rK,   rK,   rK")
	     (match_operand 5 "const_int_operand"                  "  i,  i,  i,  i,    i,    i")
	     (match_operand 6 "const_int_operand"                  "  i,  i,  i,  i,    i,    i")
	     (match_operand 7 "const_int_operand"                  "  i,  i,  i,  i,    i,    i")
	     (match_operand 8 "const_int_operand"                  "  i,  i,  i,  i,    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (float_truncate:<V_FP32TOBF16_TRUNC>
	     (match_operand:VWEXTF_ZVFBF 3 "register_operand"            "  0,  0,  0,  0,   vr,   vr"))
	  (match_operand:<V_FP32TOBF16_TRUNC> 2 "vector_merge_operand" " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfncvt.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))
   (set_attr "spec_restriction" "none,none,thv,thv,none,none")])

(define_insn "@pred_xl_rod_trunc<mode>"
  [(set (match_operand:<V_FP32TOBF16_TRUNC> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
	(if_then_else:<V_FP32TOBF16_TRUNC>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"           " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
	     (match_operand 4 "vector_length_operand"              " rK, rK, rK, rK,   rK,   rK")
	     (match_operand 5 "const_int_operand"                  "  i,  i,  i,  i,    i,    i")
	     (match_operand 6 "const_int_operand"                  "  i,  i,  i,  i,    i,    i")
	     (match_operand 7 "const_int_operand"                  "  i,  i,  i,  i,    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<V_FP32TOBF16_TRUNC>
	    [(float_truncate:<V_FP32TOBF16_TRUNC>
	       (match_operand:VWEXTF_ZVFBF 3 "register_operand"          "  0,  0,  0,  0,   vr,   vr"))] UNSPEC_ROD)
	  (match_operand:<V_FP32TOBF16_TRUNC> 2 "vector_merge_operand" " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfncvt.rod.f.f.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtftof")
   (set_attr "mode" "<V_FP32TOBF16_TRUNC>")])

(define_insn "@pred_xl_narrow_<float_cvt><mode>"
  [(set (match_operand:<VNCONVERT_XL> 0 "register_operand"       "=vd, vd, vr, vr,  &vr,  &vr")
	(if_then_else:<VNCONVERT_XL>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"      " vm, vm,Wc1,Wc1,vmWc1,vmWc1")
	     (match_operand 4 "vector_length_operand"         " rK, rK, rK, rK,   rK,   rK")
	     (match_operand 5 "const_int_operand"             "  i,  i,  i,  i,    i,    i")
	     (match_operand 6 "const_int_operand"             "  i,  i,  i,  i,    i,    i")
	     (match_operand 7 "const_int_operand"             "  i,  i,  i,  i,    i,    i")
	     (match_operand 8 "const_int_operand"             "  i,  i,  i,  i,    i,    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)
	     (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
	  (any_float:<VNCONVERT_XL>
	     (match_operand:VWCONVERTI_XL 3 "register_operand"   "  0,  0,  0,  0,   vr,   vr"))
	  (match_operand:<VNCONVERT_XL> 2 "vector_merge_operand" " vu,  0, vu,  0,   vu,    0")))]
  "TARGET_XXLVFBF"
  "vfncvt.f.x<u>.w\t%0,%3%p1"
  [(set_attr "type" "vfncvtitof")
   (set_attr "mode" "<VNCONVERT_XL>")
   (set (attr "frm_mode")
	(symbol_ref "riscv_vector::get_frm_mode (operands[8])"))
   (set_attr "spec_restriction" "none,none,thv,thv,none,none")])
