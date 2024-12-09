;; Machine description for RISC-V for GNU compiler.
;; Copyright (C) 2024 Free Software Foundation, Inc.
;; Contributed by nuclei.

;; Based on RISC-V target for GNU compiler.

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


(define_mode_iterator XL_VSI [
  RVVM8SI RVVM4SI RVVM2SI RVVM1SI
])
(define_mode_attr XL_VQMACC_QOQ [
  (RVVM8SI "RVVM2QI")
  (RVVM4SI "RVVM1QI")
  (RVVM2SI "RVVMF2QI")
  (RVVM1SI "RVVMF4QI")
])
(define_mode_attr xl_vqmacc_qoq [
  (RVVM8SI "rvvm2qi")
  (RVVM4SI "rvvm1qi")
  (RVVM2SI "rvvmf2qi")
  (RVVM1SI "rvvmf4qi")
])

(define_insn "@pred_matrix_mul_plus<u><mode>_qoq"
  [(set (match_operand:XL_VSI 0 "register_operand"                    "=&vr")
	(if_then_else:XL_VSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"             "vmWc1")
	     (match_operand 5 "vector_length_operand"                "   rK")
	     (match_operand 6 "const_int_operand"                    "    i")
	     (match_operand 7 "const_int_operand"                    "    i")
	     (match_operand 8 "const_int_operand"                    "    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (plus:XL_VSI
	    (mult:XL_VSI
	      (any_extend:XL_VSI
	        (match_operand:RVVM1QI 3 "register_operand" "   vr"))
	      (any_extend:XL_VSI
	        (match_operand:<XL_VQMACC_QOQ> 4 "register_operand" "   vr")))
	    (match_operand:XL_VSI 2 "register_operand"               "    0"))
	  (match_dup 2)))]
  "TARGET_VECTOR && TARGET_XXLVQMACC"
  "xl.vqmacc<u>.vv\t%0,%3,%4"
  [(set_attr "type" "xl_vqmacc")
   (set_attr "mode" "<MODE>")])


(define_insn "@pred_matrix_mul_plussu<mode>_qoq"
  [(set (match_operand:XL_VSI 0 "register_operand"                    "=&vr")
	(if_then_else:XL_VSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"             "vmWc1")
	     (match_operand 5 "vector_length_operand"                "   rK")
	     (match_operand 6 "const_int_operand"                    "    i")
	     (match_operand 7 "const_int_operand"                    "    i")
	     (match_operand 8 "const_int_operand"                    "    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (plus:XL_VSI
	    (mult:XL_VSI
	      (sign_extend:XL_VSI
	        (match_operand:RVVM1QI 3 "register_operand" "   vr"))
	      (zero_extend:XL_VSI
	        (match_operand:<XL_VQMACC_QOQ> 4 "register_operand" "   vr")))
	    (match_operand:XL_VSI 2 "register_operand"               "    0"))
	  (match_dup 2)))]
  "TARGET_VECTOR && TARGET_XXLVQMACC"
  "xl.vqmaccsu.vv\t%0,%3,%4"
  [(set_attr "type" "xl_vqmacc")
   (set_attr "mode" "<MODE>")])

(define_insn "@pred_matrix_mul_plusus<mode>_qoq"
  [(set (match_operand:XL_VSI 0 "register_operand"                    "=&vr")
	(if_then_else:XL_VSI
	  (unspec:<VM>
	    [(match_operand:<VM> 1 "vector_mask_operand"             "vmWc1")
	     (match_operand 5 "vector_length_operand"                "   rK")
	     (match_operand 6 "const_int_operand"                    "    i")
	     (match_operand 7 "const_int_operand"                    "    i")
	     (match_operand 8 "const_int_operand"                    "    i")
	     (reg:SI VL_REGNUM)
	     (reg:SI VTYPE_REGNUM)] UNSPEC_VPREDICATE)
	  (plus:XL_VSI
	    (mult:XL_VSI
	      (zero_extend:XL_VSI
	        (match_operand:RVVM1QI 3 "register_operand" "   vr"))
	      (sign_extend:XL_VSI
	        (match_operand:<XL_VQMACC_QOQ> 4 "register_operand" "   vr")))
	    (match_operand:XL_VSI 2 "register_operand"               "    0"))
	  (match_dup 2)))]
  "TARGET_VECTOR && TARGET_XXLVQMACC"
  "xl.vqmaccus.vv\t%0,%3,%4"
  [(set_attr "type" "xl_vqmacc")
   (set_attr "mode" "<MODE>")])
