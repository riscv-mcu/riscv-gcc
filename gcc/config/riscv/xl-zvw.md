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

(define_c_enum "unspec" [

  ;; Complex number format convert (xxlvw)
  UNSPEC_VCPACK
  UNSPEC_VCUNPACKR
  UNSPEC_VCUNPACKI

  ;; Vector Dynamic Scaling Operation
  UNSPEC_VDS
  UNSPEC_VDS_MUL
  UNSPEC_VDS_MACINI
  UNSPEC_VDS_CMUL
  UNSPEC_VDS_CMULJ
  UNSPEC_VDS_CREDSUM
  UNSPEC_VDS_CMACO
  UNSPEC_VDS_CMACJO
  UNSPEC_VDS_CMACOR
  UNSPEC_VDS_CMACOI
  UNSPEC_VDS_CMACJOR
  UNSPEC_VDS_CMACJOI
  UNSPEC_VDS_CMULR
  UNSPEC_VDS_CMULI
  UNSPEC_VDS_CMULJR
  UNSPEC_VDS_CMULJI
  UNSPEC_VDS_REDSUM
  UNSPEC_VDS_REDSUMN

  UNSPEC_VDS_MAC
  UNSPEC_VDS_MACO
  UNSPEC_VDS_CMAC
  UNSPEC_VDS_CMACJ

  UNSPEC_VLNLP0
  UNSPEC_VLNLP1
  UNSPEC_VLSB
  UNSPEC_VCONJ
  UNSPEC_VPERM

  UNSPEC_VREDMAXI
  UNSPEC_VREDMINI

  UNSPEC_VFSL
  UNSPEC_VFSR

  UNSPEC_VNLE
  UNSPEC_VNLM

  UNSPEC_VFCVT_B2H
  UNSPEC_VFCVT_B2W
  UNSPEC_VFCVT_H2W
  UNSPEC_VFCVT_H2B
  UNSPEC_VFCVT_W2B
  UNSPEC_VFCVT_W2H
  UNSPEC_VFCVT_P2C
  UNSPEC_VFCVT_C2P
])

(define_mode_iterator XL_VI [
  RVVM8QI RVVM4QI RVVM2QI RVVM1QI RVVMF2QI RVVMF4QI RVVMF8QI
  RVVM8HI RVVM4HI RVVM2HI RVVM1HI RVVMF2HI RVVMF4HI
  RVVM8SI RVVM4SI RVVM2SI RVVM1SI RVVMF2SI
])

(define_mode_iterator XL_VLNLP [
  (RVVM8QI "TARGET_MIN_VLEN == 128")  (RVVM4QI "TARGET_MIN_VLEN == 256")
  (RVVM2QI "TARGET_MIN_VLEN == 512")  (RVVM1QI "TARGET_MIN_VLEN == 1024")
  (RVVM8HI "TARGET_MIN_VLEN == 128")  (RVVM4HI "TARGET_MIN_VLEN == 256")
  (RVVM2HI "TARGET_MIN_VLEN == 512")  (RVVM1HI "TARGET_MIN_VLEN == 1024")
  (RVVM8SI "TARGET_MIN_VLEN == 128")  (RVVM4SI "TARGET_MIN_VLEN == 256")
  (RVVM2SI "TARGET_MIN_VLEN == 512")  (RVVM1SI "TARGET_MIN_VLEN == 1024")
])

(define_mode_attr XL_ZVW [
  (RVVM8QI "RVVM8QI") (RVVM4QI "RVVM4QI") (RVVM2QI "RVVM2QI") (RVVM1QI "RVVM1QI")
  (RVVMF2QI "RVVMF2QI") (RVVMF4QI "RVVMF4QI") (RVVMF8QI "RVVMF8QI")

  (RVVM8HI "RVVM8HI") (RVVM4HI "RVVM4HI") (RVVM2HI "RVVM2HI") (RVVM1HI "RVVM1HI") (RVVMF2HI "RVVMF2HI") (RVVMF4HI "RVVMF4HI")

  (RVVM8SI "RVVM8SI") (RVVM4SI "RVVM4SI") (RVVM2SI "RVVM2SI") (RVVM1SI "RVVM1SI") (RVVMF2SI "RVVMF2SI")
])

(define_mode_attr xl_zvw [
  (RVVM8QI "rvvm8qi") (RVVM4QI "rvvm4qi") (RVVM2QI "rvvm2qi") (RVVM1QI "rvvm1qi")
  (RVVMF2QI "rvvm2qi") (RVVMF4QI "rvvmf4qi") (RVVMF8QI "rvvmf4qi")

  (RVVM8HI "rvvm8hi") (RVVM4HI "rvvm4hi") (RVVM2HI "rvvm2hi") (RVVM1HI "rvvm1hi") (RVVMF2HI "rvvmf2hi") (RVVMF4HI "rvvmf4hi")

  (RVVM8SI "rvvm8si") (RVVM4SI "rvvm4si") (RVVM2SI "rvvm2si") (RVVM1SI "rvvm1si") (RVVMF2SI "rvvmf2si")
])

(define_mode_attr ZVW_VEL[
  (RVVM8QI "QI") (RVVM4QI "QI") (RVVM2QI "QI") (RVVM1QI "QI") (RVVMF2QI "QI") (RVVMF4QI "QI") (RVVMF8QI "QI")

  (RVVM8HI "HI") (RVVM4HI "HI") (RVVM2HI "HI") (RVVM1HI "HI") (RVVMF2HI "HI") (RVVMF4HI "HI")

  (RVVM8SI "SI") (RVVM4SI "SI") (RVVM2SI "SI") (RVVM1SI "SI") (RVVMF2SI "SI")
])

(define_int_iterator ANY_VDS [
  UNSPEC_VDS_MUL UNSPEC_VDS_MACO UNSPEC_VDS_CMUL UNSPEC_VDS_CMULJ UNSPEC_VDS_CMACO UNSPEC_VDS_CMACJO UNSPEC_VDS_CMACOR UNSPEC_VDS_CMACOI UNSPEC_VDS_CMACJOR UNSPEC_VDS_CMACJOI UNSPEC_VDS_CMULR UNSPEC_VDS_CMULI UNSPEC_VDS_CMULJR  UNSPEC_VDS_CMULJI])

(define_int_iterator ANY_ZVW_OP [
  UNSPEC_VLSB UNSPEC_VCONJ UNSPEC_VDS_CREDSUM UNSPEC_VDS_REDSUM])

(define_int_iterator ZVW_BINOP [ UNSPEC_VREDMAXI UNSPEC_VREDMINI UNSPEC_VNLE UNSPEC_VNLM])

(define_int_iterator ZVW_VFSOP [ UNSPEC_VFSL UNSPEC_VFSR ])

(define_int_iterator ZVW_NOVD [ UNSPEC_VDS_MAC UNSPEC_VDS_CMAC UNSPEC_VDS_CMACJ])

(define_int_attr novd [
  (UNSPEC_VDS_MAC "mac")
  (UNSPEC_VDS_CMAC "cmac")
  (UNSPEC_VDS_CMACJ "cmacj")
])

(define_int_attr zvw_op [
  (UNSPEC_VLSB "lsb")
  (UNSPEC_VCONJ "conj")
  (UNSPEC_VDS_CREDSUM "dscredsum")
  (UNSPEC_VDS_REDSUM  "dsredsum")])

(define_int_attr vds_op [
  (UNSPEC_VDS_MUL "mul")
  (UNSPEC_VDS_MACO "maco")
  (UNSPEC_VDS_CMUL "cmul")
  (UNSPEC_VDS_CMULJ "cmulj")
  (UNSPEC_VDS_CMACO "cmaco")
  (UNSPEC_VDS_CMACJO "cmacjo")
  (UNSPEC_VDS_CMACOR "cmacor")
  (UNSPEC_VDS_CMACOI "cmacoi")
  (UNSPEC_VDS_CMACJOR "cmacjor")
  (UNSPEC_VDS_CMACJOI "cmacjoi")
  (UNSPEC_VDS_CMULR "cmulr")
  (UNSPEC_VDS_CMULI "cmuli")
  (UNSPEC_VDS_CMULJR "cmuljr")
  (UNSPEC_VDS_CMULJI "cmulji")])

(define_int_attr binop_zvw [
  (UNSPEC_VREDMAXI "redmaxi")
  (UNSPEC_VREDMINI "redmini")
  (UNSPEC_VNLE "nle")
  (UNSPEC_VNLM "nlm")])

(define_int_attr vfs_op [ (UNSPEC_VFSL "l") (UNSPEC_VFSR "r")])

(define_int_iterator XXLVW_VLNLP [ UNSPEC_VLNLP0 UNSPEC_VLNLP1 ])

(define_int_attr vlnlp_op [ (UNSPEC_VLNLP0 "0") (UNSPEC_VLNLP1 "1")])


(define_insn "@pred_vds<vds_op>_vv_<mode>"
  [(set (match_operand:XL_VI 0 "register_operand"           "=vd, vd, vr, vr")
        (if_then_else:XL_VI
          (unspec:<VM>
            [(match_operand:<VM> 1 "vector_mask_operand" " vm, vm,Wc1,Wc1")
             (match_operand 5 "vector_length_operand"    " rK, rK, rK, rK")
             (match_operand 6 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 7 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 8 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 9 "const_int_operand"        "  i,  i,  i,  i")
             (reg:SI VL_REGNUM)
             (reg:SI VTYPE_REGNUM)
             (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
          (unspec:XL_VI [
            (match_operand:<XL_ZVW> 3 "register_operand"       " vr, vr, vr, vr")
            (match_operand:<XL_ZVW> 4 "register_operand"       " vr, vr, vr, vr")]ANY_VDS)
          (match_operand:XL_VI 2 "vector_merge_operand"     " vu,  0, vu,  0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vds<vds_op>.vv\t%0,%3,%4%p1"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")
   (set (attr "frm_mode")
        (symbol_ref "riscv_vector::get_frm_mode (operands[9])"))])


(define_insn "@pred_vds<vds_op>_vs_<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:<XL_ZVW>
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 8 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:<XL_ZVW> [
             (match_operand:<XL_ZVW>     3 "register_operand"      " vr, vr, vr, vr")
             (match_operand:<XL_ZVW>     4 "register_operand"      " vr, vr, vr, vr")
           ] ANY_VDS)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0,  vu,   0")] UNSPEC_VDS))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vds<vds_op>.vs\t%0,%3,%4%p1"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])

(define_mode_attr VSI_SI [
  (RVVM8SI "RVVM8SI") (RVVM4SI "RVVM4SI") (RVVM2SI "RVVM2SI") (RVVM1SI "RVVM1SI") (RVVMF2SI "RVVMF2SI")
])

;; vcpack(vector complex packing instruction)
(define_insn "@pred_vcpack_<mode>"
  [(set (match_operand:VSI          0 "register_operand"      "=vd, vd, vr, vr")
	  (if_then_else:VSI
	    (unspec:<VM>
	      [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	       (match_operand 5 "vector_length_operand"      " rK, rK, rK, rK")
	       (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
	       (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
         (match_operand 8 "const_int_operand"          " i,  i,  i,   i")
	       (reg:SI VL_REGNUM)
	       (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:VSI
        [(match_operand:VSI     3 "register_operand"      " vr, vr, vr, vr")
         (match_operand:VSI     4 "register_operand"      " vr, vr, vr, vr")] UNSPEC_VCPACK)
	   (match_operand:VSI       2 "vector_merge_operand"  " vu,  0,  vu,   0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vcpack.vv\t%0,%3,%4%p1"
  [(set_attr "type" "vcpack")
   (set_attr "mode" "<MODE>")])

;; vcunpackr
(define_insn "@pred_vcunpackr_<mode>"
  [(set (match_operand:<VSI_SI> 0 "register_operand"       "=vd, vd, vr, vr")
	(if_then_else:<VSI_SI>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"     " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"        " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"            "  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<VSI_SI>
	     [(match_operand:VSI 3 "register_operand"     " vr, vr, vr, vr")] UNSPEC_VCUNPACKR)
	  (match_operand:<VSI_SI> 2 "vector_merge_operand" " vu,  0, vu,  0")))]
  "TARGET_VECTOR"
  "vcunpackr.v\t%0,%3%p1"
  [(set_attr "type" "vcpack")
   (set_attr "mode" "<MODE>")])

;; vcunpacki
(define_insn "@pred_vcunpacki_<mode>"
  [(set (match_operand:<VSI_SI> 0 "register_operand"       "=vd, vd, vr, vr")
	(if_then_else:<VSI_SI>
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"     " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"        " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 6 "const_int_operand"            "  i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"            "  i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (unspec:<VSI_SI>
	     [(match_operand:VSI 3 "register_operand"     " vr, vr, vr, vr")] UNSPEC_VCUNPACKI)
	  (match_operand:<VSI_SI> 2 "vector_merge_operand" " vu,  0, vu,  0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vcunpacki.v\t%0,%3%p1"
  [(set_attr "type" "vcpack")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vdsmacini_v<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	  (if_then_else:XL_VI
	    (unspec:<VM>
	      [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	       (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	       (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	       (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
         (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	       (reg:SI VL_REGNUM)
	       (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:XL_VI
        [(match_operand:XL_VI     3 "register_operand"      " vr, vr, vr, vr")] UNSPEC_VDS_MACINI)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0,  vu,   0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vdsmacini.v\t%3%p1"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vdsmacini_x<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	  (if_then_else:XL_VI
	    (unspec:<VM>
	      [(match_operand:<VM> 1 "vector_mask_operand"   " vm, Wc1,vm,Wc1")
	       (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	       (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	       (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
         (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	       (reg:SI VL_REGNUM)
	       (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:XL_VI
        [(match_operand:<ZVW_VEL>     3 "immediate_register_operand"      "r, r, K, K")] UNSPEC_VDS_MACINI)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu, vu, vu,  vu")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "@
  vdsmacini.s\t%3%p1
  vdsmacini.s\t%3
  vdsmacini.i\t%3%p1
  vdsmacini.i\t%3"
  [(set_attr "type" "vdsop,vdsop,vdsop,vdsop")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_v<zvw_op>_<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	  (if_then_else:XL_VI
	    (unspec:<VM>
	      [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	       (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	       (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	       (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
         (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	       (reg:SI VL_REGNUM)
	       (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:XL_VI
        [(match_operand:XL_VI     3 "register_operand"      " vr, vr, vr, vr")] ANY_ZVW_OP)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0,  vu,   0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "v<zvw_op>.v\t%0,%3%p1"
  [(set_attr "type" "vlsb")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vdsredsumn_vx_<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:<XL_ZVW>
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"          " i,  i,  i,  i")
       (match_operand 8 "const_int_operand"          " i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:<XL_ZVW> [
             (match_operand:<XL_ZVW>     3 "register_operand"      " vr, vr, vr, vr")
             (match_operand:<ZVW_VEL>    4 "register_operand"      "  r, r, r, r")
           ] UNSPEC_VDS_REDSUMN)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0, vu,  0")] UNSPEC_VDS))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vdsredsumn.vs\t%0,%3,%4"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vdsredsumn_vi_<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:<XL_ZVW>
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,  i")
	     (match_operand 7 "const_int_operand"          " i,  i,  i,  i")
       (match_operand 8 "const_int_operand"          " i,  i,  i,  i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:<XL_ZVW> [
             (match_operand:<XL_ZVW>     3 "register_operand"      " vr, vr, vr, vr")
             (match_operand:<ZVW_VEL>    4 "immediate_operand"     "Ds4,Ds4,Ds4,Ds4")
           ] UNSPEC_VDS_REDSUMN)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0, vu,  0")] UNSPEC_VDS))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vdsredsumn.vi\t%0,%3,%4"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_v<binop_zvw>_vv_<mode>"
  [(set (match_operand:XL_VI 0 "register_operand"           "=vd, vd, vr, vr")
        (if_then_else:XL_VI
          (unspec:<VM>
            [(match_operand:<VM> 1 "vector_mask_operand" " vm, vm,Wc1,Wc1")
             (match_operand 5 "vector_length_operand"    " rK, rK, rK, rK")
             (match_operand 6 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 7 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 8 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 9 "const_int_operand"        "  i,  i,  i,  i")
             (reg:SI VL_REGNUM)
             (reg:SI VTYPE_REGNUM)
             (reg:SI FRM_REGNUM)] UNSPEC_VPREDICATE)
          (unspec:XL_VI [
            (match_operand:<XL_ZVW> 3 "register_operand"       " vr, vr, vr, vr")
            (match_operand:<XL_ZVW> 4 "register_operand"       " vr, vr, vr, vr")]ZVW_BINOP)
          (match_operand:XL_VI 2 "vector_merge_operand"     " vu,  0, vu,  0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "v<binop_zvw>.vv\t%0,%3,%4%p1"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_v<binop_zvw>_vs_<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:<XL_ZVW>
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 8 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:<XL_ZVW> [
             (match_operand:<XL_ZVW>     3 "register_operand"      " vr, vr, vr, vr")
             (match_operand:<XL_ZVW>     4 "register_operand"      " vr, vr, vr, vr")
           ] ZVW_BINOP)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0,  vu,   0")] UNSPEC_VDS))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "v<binop_zvw>.vs\t%0,%3,%4%p1"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])


(define_insn "@pred_vperm_vi_<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	(if_then_else:XL_VI
	   (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 8 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:XL_VI [
             (match_operand:<XL_ZVW>     3 "register_operand"      " vr, vr, vr, vr")
             (match_operand:<ZVW_VEL>     4 "immediate_operand"      "Ds8,Ds8,Ds8,Ds8")
           ] UNSPEC_VPERM)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0,  vu,   0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vperm.vi\t%0,%3,%4"
  [(set_attr "type" "vperm")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vfs<vfs_op>_vv_<mode>"
  [(set (match_operand:XL_VI 0 "register_operand"           "=vd, vd, vr, vr")
        (if_then_else:XL_VI
          (unspec:<VM>
            [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
             (match_operand 5 "vector_length_operand"    " rK, rK, rK, rK")
             (match_operand 6 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 7 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 8 "const_int_operand"        "  i,  i,  i,  i")
             (reg:SI VL_REGNUM)
             (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
          (unspec:XL_VI [
            (match_operand:<XL_ZVW> 3 "register_operand"       " vr, vr, vr, vr")
            (match_operand:<XL_ZVW> 4 "register_operand"       " vr, vr, vr, vr")]ZVW_VFSOP)
          (match_operand:XL_VI 2 "vector_merge_operand"     " vu,  0, vu,  0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vfs<vfs_op>.vv\t%0,%3,%4"
  [(set_attr "type" "vfsop")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vds<novd>_vv_<mode>"
  [(set (match_operand:XL_VI 0 "register_operand"           "=vd, vd, vr, vr")
        (if_then_else:XL_VI
          (unspec:<VM>
            [(match_operand:<VM> 1 "vector_mask_operand" " vm, vm,Wc1,Wc1")
             (match_operand 5 "vector_length_operand"    " rK, rK, rK, rK")
             (match_operand 6 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 7 "const_int_operand"        "  i,  i,  i,  i")
             (match_operand 8 "const_int_operand"        "  i,  i,  i,  i")
             (reg:SI VL_REGNUM)
             (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
          (unspec:XL_VI [
            (match_operand:<XL_ZVW> 3 "register_operand"       " vr, vr, vr, vr")
            (match_operand:<XL_ZVW> 4 "register_operand"       " vr, vr, vr, vr")]ZVW_NOVD)
          (match_operand:XL_VI 2 "vector_merge_operand"     " vu,  0, vu,  0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vds<novd>.vv\t%3,%4%p1"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vds<novd>_vs_<mode>"
  [(set (match_operand:XL_VI          0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:<XL_ZVW>
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 5 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 8 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:<XL_ZVW> [
             (match_operand:<XL_ZVW>     3 "register_operand"      " vr, vr, vr, vr")
             (match_operand:<XL_ZVW>     4 "register_operand"      " vr, vr, vr, vr")
           ] ZVW_NOVD)
	   (match_operand:XL_VI       2 "vector_merge_operand"  " vu,  0,  vu,   0")] UNSPEC_VDS))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vds<novd>.vs\t%3,%4%p1"
  [(set_attr "type" "vdsop")
   (set_attr "mode" "<MODE>")])


(define_insn "@pred_vlnlp<vlnlp_op>_v<mode>"
  [(set (match_operand:XL_VLNLP          0 "register_operand"      "=vd, vd, vr, vr")
	  (if_then_else:XL_VLNLP
	    (unspec:<VM>
	      [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	       (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	       (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	       (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
         (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	       (reg:SI VL_REGNUM)
	       (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:XL_VLNLP
        [(match_operand:XL_VLNLP     3 "register_operand"      " vr, vr, vr, vr")] XXLVW_VLNLP)
	   (match_operand:XL_VLNLP       2 "vector_merge_operand"  " vu,  0,  vu,   0")))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vlnlp<vlnlp_op>.v\t%3"
  [(set_attr "type" "vlnlp")
   (set_attr "mode" "<MODE>")])

;; Format Convert Instruction

(define_mode_iterator HSI [
  RVVM8HI RVVM4HI RVVM2HI RVVM1HI RVVMF2HI RVVMF4HI
  RVVM8SI RVVM4SI RVVM2SI RVVM1SI RVVMF2SI
])

(define_mode_attr DOUBLE_TRUNC_HSI [
  (RVVM8HI "RVVM4QI")   (RVVM4HI "RVVM2QI") (RVVM2HI "RVVM1QI") (RVVM1HI "RVVMF2QI")
  (RVVMF2HI "RVVMF4QI") (RVVMF4HI "RVVMF8QI")

  (RVVM8SI "RVVM4HI")   (RVVM4SI "RVVM2HI") (RVVM2SI "RVVM1HI") (RVVM1SI "RVVMF2HI")
  (RVVMF2SI "RVVMF4HI")
])

(define_mode_attr QUAD_TRUNC_VSI [
  (RVVM8SI "RVVM2QI") (RVVM4SI "RVVM1QI") (RVVM2SI "RVVMF2QI") (RVVM1SI "RVVMF4QI") (RVVMF2SI "RVVMF8QI")
])

(define_int_iterator CONV [ UNSPEC_VFCVT_B2H UNSPEC_VFCVT_H2W UNSPEC_VFCVT_P2C ])

(define_int_attr conv_op [
  (UNSPEC_VFCVT_B2H "b2h")
  (UNSPEC_VFCVT_H2W "h2w")
  (UNSPEC_VFCVT_P2C "p2c")
])

(define_int_iterator RECONV [ UNSPEC_VFCVT_H2B UNSPEC_VFCVT_W2H UNSPEC_VFCVT_C2P])

(define_int_attr reconv_op [
  (UNSPEC_VFCVT_H2B "h2b")
  (UNSPEC_VFCVT_W2H "w2h")
  (UNSPEC_VFCVT_C2P "c2p")
])

(define_insn "@pred_vfcvt_<conv_op><mode>"
  [(set (match_operand:HSI       0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:HSI
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:HSI [
        (match_operand:<DOUBLE_TRUNC_HSI>    3 "register_operand"  "vr, vr, vr, vr")] CONV)
	   (match_operand:HSI       2 "vector_merge_operand"  " vu,  0,  vu,   0")] UNSPEC_VFCVT))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vfcvt.<conv_op>.v\t%0,%3"
  [(set_attr "type" "vconvert")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vfcvt_b2w<mode>"
  [(set (match_operand:VSI       0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:VSI
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:VSI [
        (match_operand:<QUAD_TRUNC_VSI>    3 "register_operand"  " vr, vr, vr, vr")] UNSPEC_VFCVT_B2W)
	   (match_operand:VSI       2 "vector_merge_operand"  " vu,  0,  vu,   0")] UNSPEC_VFCVT))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vfcvt.b2w.v\t%0,%3"
  [(set_attr "type" "vconvert")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vfcvt_<reconv_op><mode>"
  [(set (match_operand:<DOUBLE_TRUNC_HSI>      0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:<DOUBLE_TRUNC_HSI>
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:<DOUBLE_TRUNC_HSI> [
        (match_operand:HSI    3 "register_operand"  " vr, vr, vr, vr")] RECONV)
	   (match_operand:<DOUBLE_TRUNC_HSI>       2 "vector_merge_operand"  " vu,  0,  vu,   0")] UNSPEC_VFCVT))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vfcvt.<reconv_op>.v\t%0,%3"
  [(set_attr "type" "vconvert")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_vfcvt_w2b<mode>"
  [(set (match_operand:<QUAD_TRUNC_VSI>       0 "register_operand"      "=vd, vd, vr, vr")
	(unspec:<QUAD_TRUNC_VSI>
	  [(unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"   " vm, vm,Wc1,Wc1")
	     (match_operand 4 "vector_length_operand"      " rK, rK, rK, rK")
	     (match_operand 5 "const_int_operand"          " i,  i,  i,   i")
	     (match_operand 6 "const_int_operand"          " i,  i,  i,   i")
       (match_operand 7 "const_int_operand"          " i,  i,  i,   i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	   (unspec:<QUAD_TRUNC_VSI> [
        (match_operand:VSI    3 "register_operand"  " vr, vr, vr, vr")] UNSPEC_VFCVT_W2B)
	   (match_operand:<QUAD_TRUNC_VSI>       2 "vector_merge_operand"  " vu,  0,  vu,   0")] UNSPEC_VFCVT))]
  "TARGET_VECTOR && TARGET_XXLVW"
  "vfcvt.w2b.v\t%0,%3"
  [(set_attr "type" "vconvert")
   (set_attr "mode" "<MODE>")])
