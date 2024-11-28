;; Machine description for P extension.
;; Copyright (C) 2021 Free Software Foundation, Inc.

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

;; A list of the modes that are up to one word long vector.
(define_mode_iterator VECI [(RVPV4QI "!TARGET_64BIT") (RVPV2HI "!TARGET_64BIT")
                            (RVPV8QI "TARGET_64BIT") (RVPV4HI "TARGET_64BIT")
			                      (RVPV2SI "TARGET_64BIT")])
;; rvpv2hi is also used in rv64p
(define_mode_iterator VPMOVE [(RVPV4QI "") (RVPV2HI "")
                             (RVPV8QI "TARGET_64BIT")  (RVPV4HI "TARGET_64BIT")])
(define_mode_iterator VQIHI [(RVPV4QI "!TARGET_64BIT") (RVPV2HI "!TARGET_64BIT")
                             (RVPV8QI "TARGET_64BIT")  (RVPV4HI "TARGET_64BIT")])
(define_mode_iterator VSHI [(RVPV2HI "!TARGET_64BIT") (RVPV2SI "TARGET_64BIT")])
(define_mode_iterator VHIX  [(RVPV2HI "!TARGET_64BIT") (RVPV4HI "TARGET_64BIT")])
(define_mode_iterator VQIX [(RVPV4QI "!TARGET_64BIT") (RVPV8QI "TARGET_64BIT")])
(define_mode_iterator VD_SI [(SI "!TARGET_64BIT") (RVPV2SI "TARGET_64BIT")])

(define_mode_attr VNHALF [(RVPV2SI "SI") (RVPV2HI "HI")])
(define_mode_attr VSH_EXT [(RVPV2SI "DI") (RVPV2HI "HI")])
(define_mode_attr VECI_scalar [(RVPV2SI "SI") (RVPV2HI "HI") (RVPV4HI "HI")
                            (RVPV4QI "QI") (RVPV8QI "QI")])
(define_mode_attr VEXT [(RVPV4QI "RVPV4HI") (RVPV2HI "RVPV2SI") (RVPV8QI "RVPV8HI") (RVPV4HI "RVPV4SI")
			(RVPV2SI "RVPV2DI")])
(define_code_attr shift [(ashift "ashl") (ashiftrt "ashr") (lshiftrt "lshr")])

;; <uk> expands to (un)signed (saturating) arithmetic operations
(define_code_attr uk
  [(plus "") (ss_plus "k") (us_plus "uk")
   (minus "") (ss_minus "k") (us_minus "uk")])

;; <bits> for specific bit number in 'simd' type instruction
(define_mode_attr bits [(RVPV8QI "8") (RVPV4QI "8") (QI "8") (RVPV4HI "16") (RVPV2HI "16")
			            (HI "16") (RVPV2SI "32") (DI "64")])

;; <all_plus> and <all_minus> for all types of addtion and subtraction
(define_code_iterator all_plus [plus ss_plus us_plus])
(define_code_iterator all_minus [minus ss_minus us_minus])
;;(define_code_iterator plus_minus [plus minus])
(define_code_iterator sumax [smax umax])
(define_code_iterator sumin [smin umin])
(define_code_iterator ssat_op [ss_plus ss_minus])
(define_code_iterator usat_op [us_plus us_minus])

(define_code_attr ph [(plus "") (minus "")])
(define_code_attr add_sub [(plus "a")
  (ss_plus "a")
  (us_plus "a")
  (ss_minus "s")
  (us_minus "s")
  (minus "s")])

;; clz and clrs
(define_code_iterator unop [clrsb clz])

(define_code_attr zs
  [(sign_extend "s") (zero_extend "z")])

;; <rvp_optab> expands to the name of the optab for a particular code.
(define_code_attr rvp_optab [(clrsb "clrsb")
	(clz "clz")
	(ashift "ashl")
	(ashiftrt "ashr")
	(lshiftrt "lshr")])

;; <rvp_insn> expands to the name of the insn that implements a particular code.
(define_code_attr rvp_insn [(clrsb "clrs")
			(clz "clz")
			(ashift "sll")
			(ashiftrt "sra")
			(lshiftrt "srl")])

(define_code_attr opcode [(plus "add")
   (minus "sub")
   (ss_plus "add")
   (us_plus "add")
   (ss_minus "sub")
   (us_minus "sub")
   (smax "smax")
   (umax "umax")
   (smin "smin")
   (umin "umin")])

;; k|(uk)|? add
;; zpn is a mandatory subset for p extension, thus add32 (zprv subset) can also be matched
(define_insn "<uk>add<mode>3"
  [(set (match_operand:VECI 0 "register_operand"                "=r")
	(all_plus:VECI (match_operand:VECI 1 "register_operand" " r")
		       (match_operand:VECI 2 "register_operand" " r")))]
  "TARGET_ZPN"
  "<uk>add<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; 64-bit
(define_insn "rvp_<uk>adddi3"
  [(set (match_operand:DI 0 "register_operand"              "=r")
	(all_plus:DI (match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")))]
  "TARGET_ZPSF"
  "<uk>add64 %0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; k|(uk)|? sub
(define_insn "<uk>sub<mode>3"
  [(set (match_operand:VECI 0 "register_operand"                  "=r")
	(all_minus:VECI (match_operand:VECI 1 "register_operand" " r")
			(match_operand:VECI 2 "register_operand" " r")))]
  "TARGET_ZPN"
  "<uk>sub<bits> %0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; 64-bit
(define_insn "rvp_<uk>subdi3"
  [(set (match_operand:DI 0 "register_operand"               "=r")
	(all_minus:DI (match_operand:DI 1 "register_operand" " r")
		      (match_operand:DI 2 "register_operand" " r")))]
  "TARGET_ZPSF"
  "<uk>sub64 %0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; uk|k add|sub w|h
(define_insn "kaddw"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KADDW))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kaddw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "kaddw64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KADDW)))]
  "TARGET_ZPN && TARGET_64BIT"
  "kaddw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "ksubw"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KSUBW))]
  "TARGET_ZPN && !TARGET_64BIT"
  "ksubw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "ksubw64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				(match_operand:SI 2 "register_operand" "r")] UNSPEC_KSUBW)))]
  "TARGET_ZPN && TARGET_64BIT"
  "ksubw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "kaddh"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(sign_extend:SI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KADDH)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kaddh\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "kaddh_64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KADDH)))]
  "TARGET_ZPN && TARGET_64BIT"
  "kaddh\t%0, %1, %2"
 [(set_attr "type" "dsp64")
  (set_attr "mode" "DI")])

(define_insn "ksubh"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(sign_extend:SI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KSUBH)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "ksubh\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "ksubh_64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KSUBH)))]
  "TARGET_ZPN && TARGET_64BIT"
  "ksubh\t%0, %1, %2"
 [(set_attr "type" "dsp64")
  (set_attr "mode" "DI")])

(define_insn "ukaddw"
  [(set (match_operand:SI 0 "register_operand"             "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKADDW))]
  "TARGET_ZPN && !TARGET_64BIT"
  "ukaddw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "ukaddw64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKADDW)))]
  "TARGET_ZPN && TARGET_64BIT"
  "ukaddw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "uksubw"
  [(set (match_operand:SI 0 "register_operand"             "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKSUBW))]
  "TARGET_ZPN && !TARGET_64BIT"
  "uksubw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "uksubw64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKSUBW)))]
  "TARGET_ZPN && TARGET_64BIT"
  "uksubw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "ukaddh"
  [(set (match_operand:SI 0 "register_operand"             "=r")
	(sign_extend:SI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKADDH)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "ukaddh\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "ukaddh64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKADDH)))]
  "TARGET_ZPN && TARGET_64BIT"
  "ukaddh\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "uksubh"
  [(set (match_operand:SI 0 "register_operand"             "=r")
	(sign_extend:SI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKSUBH)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "uksubh\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "uksubh64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(sign_extend:DI (unspec:SI [(match_operand:SI 1 "register_operand" "r")
				    (match_operand:SI 2 "register_operand" "r")] UNSPEC_UKSUBH)))]
  "TARGET_ZPN && TARGET_64BIT"
  "uksubh\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

;; kabs
(define_insn "kabsw"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_KABS))]
  "TARGET_ZPN"
  "kabsw\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "kabs<mode>2"
  [(set (match_operand:VECI 0 "register_operand"              "=r")
	(ss_abs:VECI (match_operand:VECI 1 "register_operand" " r")))]
  "TARGET_ZPN"
  "kabs<bits>\t%0, %1"
  [(set_attr "type"   "simd")
   (set_attr "mode" "<MODE>")])

;; ave
(define_insn "ave"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(truncate:SI
	  (ashiftrt:DI
	    (plus:DI
	      (plus:DI
		(sign_extend:DI (match_operand:SI 1 "register_operand" "r"))
		(sign_extend:DI (match_operand:SI 2 "register_operand" "r")))
	      (const_int 1))
	  (const_int 1))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "ave\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "avedi"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(truncate:DI
	  (ashiftrt:TI
	    (plus:TI
	      (plus:TI
		(sign_extend:TI (match_operand:DI 1 "register_operand" "r"))
		(sign_extend:TI (match_operand:DI 2 "register_operand" "r")))
	      (const_int 1))
	  (const_int 1))))]
  "TARGET_ZPN && TARGET_64BIT"
  "ave\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

;; bitrev
(define_insn "bitrev"
  [(set (match_operand:SI 0 "register_operand"             "=r,   r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r,   r")
		    (match_operand:SI 2 "rimm5u_operand"   " r, u05")]
		   UNSPEC_BITREV))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
   bitrev\t%0, %1, %2
   bitrevi\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "mode"   "SI")])

(define_insn "bitrev64"
  [(set (match_operand:DI 0 "register_operand"             "=r,   r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r,   r")
		    (match_operand:SI 2 "rimm6u_operand"   " r, u06")]
		   UNSPEC_BITREV))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
   bitrev\t%0, %1, %2
   bitrevi\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "mode"   "SI")])

;; bpick
(define_insn "bpick<X:mode>"
  [(set (match_operand:X 0 "register_operand"       "=r")
	  (ior:X
	    (and:X
	      (match_operand:X 1 "register_operand" " r")
	      (match_operand:X 3 "register_operand" " r"))
	    (and:X
	      (match_operand:X 2 "register_operand" " r")
	      (not:X (match_dup 3)))))]
  "TARGET_ZPN"
  "bpick\t%0, %1, %2, %3"
  [(set_attr "type"   "dsp")
   (set_attr "mode"   "<MODE>")])

;; clrov
(define_insn "clrov<X:mode>"
  [(unspec_volatile:X [(const_int 0)] UNSPEC_CLROV)]
  "TARGET_ZPN"
  "csrrci\tzero,ucode,1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "<MODE>")])

;; clrs, clz
(define_insn "<rvp_optab><mode>2"
  [(set (match_operand:VECI 0 "register_operand" "=r")
        (unop:VECI (match_operand:VECI 1 "register_operand" "r")))]
  "TARGET_ZPN"
  "<rvp_insn><bits>\t%0, %1"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "p<rvp_optab>si2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unop:SI (match_operand:SI 1 "register_operand" "r")))]
  "TARGET_ZPN && !(TARGET_64BIT || TARGET_ZBB)"
  "<rvp_insn>32\t%0, %1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

;; clo
(define_insn "clo<mode>2"
  [(set (match_operand:VECI 0 "register_operand"               "=r")
	(unspec:VECI [(match_operand:VECI 1 "register_operand" " r")]
		      UNSPEC_CLO))]
  "TARGET_ZPN"
  "clo<bits>\t%0, %1"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "closi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")]
		    UNSPEC_CLO))]
  "TARGET_ZPN && !TARGET_64BIT"
  "clo32\t%0, %1"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

;; simd integer compare equal
(define_insn "cmpeq<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(eq:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				 (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_ZPN"
  "cmpeq<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; cras, crsa
;; cras32 is in zprv subset, but zpn is a mandatory subset for p ext, thus
;; target_zpn constraint should be fine for matching cras32
(define_expand "cras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_cras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "cras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 1)]))))
	  (vec_duplicate:VSHI
	    (plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "cras<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "cras16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_cras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "cras16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (minus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				     (parallel [(const_int 0)]))
		      (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				     (parallel [(const_int 1)])))
	    (plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
		     (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:RVPV2HI
	    (minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "cras16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_expand "crsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_crsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "crsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "crsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "crsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_crsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "crsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (plus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				    (parallel [(const_int 0)]))
		     (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 1)])))
	    (minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:RVPV2HI
	    (plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
		     (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
		       (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "crsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; kcras, kcrsa
(define_expand "kcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kcras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (ss_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 1)]))))
	  (vec_duplicate:VSHI
	    (ss_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "kcras<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "kcras16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kcras16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (ss_minus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
					(parallel [(const_int 1)])))
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:RVPV2HI
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (ss_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kcras16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_expand "kcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kcrsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (ss_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (ss_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "kcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "kcrsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kcrsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (ss_plus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				       (parallel [(const_int 1)])))
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:RVPV2HI
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (ss_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kcrsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; ukcras ukcrsa
(define_expand "ukcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_ukcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukcras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (us_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 1)]))))
	  (vec_duplicate:VSHI
	    (us_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "ukcras<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "ukcras16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_ukcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukcras16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (us_minus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
					(parallel [(const_int 1)])))
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:RVPV2HI
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (us_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "ukcras16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_expand "ukcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_ukcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukcrsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (us_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (us_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "ukcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "ukcrsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_ukcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukcrsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (us_plus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				       (parallel [(const_int 1)])))
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:RVPV2HI
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (us_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "ukcrsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; rcras rcrsa
(define_expand "rcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_rcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rcras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
		(minus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 0)])))
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 0)])))
		  (sign_extend:SI
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "rcras<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "rcras16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_rcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rcras16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "rcras16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_expand "rcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_rcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rcrsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
	        (minus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 1)])))
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 0)])))
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "rcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "rcrsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_rcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rcrsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "rcrsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; urcras urcrsa
(define_expand "urcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_urcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urcras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
		(minus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 0)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 0)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "urcras<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "urcras16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_urcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urcras16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "urcras16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_expand "urcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_urcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urcrsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
	        (minus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 1)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 0)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "urcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "urcrsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_urcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urcrsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "urcrsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; insb
(define_expand "insb"
  [(match_operand:RVPV4QI 0 "register_operand" "")
   (match_operand:RVPV4QI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:SI 3 "const_int_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  if (INTVAL (operands[3]) > 3 || INTVAL (operands[3]) < 0)
    gcc_unreachable ();

  rtx src = gen_reg_rtx (QImode);

  convert_move (src, operands[2], false);

  HOST_WIDE_INT selector_index;
  selector_index = INTVAL (operands[3]);
  rtx selector = gen_int_mode (1 << selector_index, SImode);
  emit_insn (gen_vec_setRVPV4QI_internal (operands[0], src,
				       operands[1], selector));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "vec_setRVPV4QI_internal"
  [(set (match_operand:RVPV4QI 0 "register_operand"    "=   r,    r,    r,    r")
	(vec_merge:RVPV4QI
	  (vec_duplicate:RVPV4QI
	    (match_operand:QI 1 "register_operand"  "    r,    r,    r,    r"))
	  (match_operand:RVPV4QI 2 "register_operand"  "    0,    0,    0,    0")
	  (match_operand:SI 3 "imm_1_2_4_8_operand" " c01, c02, c04, c08")))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
   insb\t%0, %1, 0
   insb\t%0, %1, 1
   insb\t%0, %1, 2
   insb\t%0, %1, 3"
  [(set_attr "type" "dsp")
   (set_attr "mode" "RVPV4QI")])

(define_insn "insb64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:DI 2 "register_operand" " r")
			(match_operand:DI 3 "immediate_operand" " i")]
		    UNSPEC_INSB))]
  "TARGET_ZPN && TARGET_64BIT"
  "insb\t%0, %2, %3";
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; KDMBB, KDMBT, KDMTT (32 (*) (xlen, xlen) for vector mode & 32 (*) (32, 32) for non-vector mode)
(define_expand "kdmbb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV2HI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kdm_internal (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "kdmbt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV2HI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kdm_internal (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "kdmtt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV2HI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kdm_internal (operands[0], operands[1], operands[2],
				GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "kdm_internal"
  [(set (match_operand:SI 0 "register_operand"                      "=   r,   r,   r,   r")
	(ashift:SI
	  (mult:SI
	    (sign_extend:SI
	  (vec_select:HI
		(match_operand:RVPV2HI 1 "register_operand"          "   r,   r,   r,   r")
		(parallel [(match_operand:SI 3 "imm_0_1_operand"  " c00, c00, c01, c01")])))
	    (sign_extend:SI
	  (vec_select:HI
		(match_operand:RVPV2HI 2 "register_operand"          "   r,   r,   r,   r")
		(parallel [(match_operand:SI 4 "imm_0_1_operand"  " c00, c01, c01, c00")]))))
	(const_int 1)))]
  "TARGET_ZPN"
  "@
   kdmbb\t%0, %1, %2
   kdmbt\t%0, %1, %2
   kdmtt\t%0, %1, %2
   kdmbt\t%0, %2, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

;; for RV64 vector intrinsic
;; in RV64, int32_t __rv__v_kdmtt(int16x4_t a, int16x4_t b);
(define_expand "kdmbb64"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kdm64_internal (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "kdmbt64"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kdm64_internal (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "kdmtt64"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kdm64_internal (operands[0], operands[1], operands[2],
				GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "kdm64_internal"
  [(set (match_operand:SI 0 "register_operand"                      "=   r,   r,   r,   r")
	(ashift:SI
	  (mult:SI
	    (sign_extend:SI
	  (vec_select:HI
		(match_operand:RVPV4HI 1 "register_operand"          "   r,   r,   r,   r")
		(parallel [(match_operand:SI 3 "imm_0_1_operand"  " c00, c00, c01, c01")])))
	    (sign_extend:SI
	  (vec_select:HI
		(match_operand:RVPV4HI 2 "register_operand"          "   r,   r,   r,   r")
		(parallel [(match_operand:SI 4 "imm_0_1_operand"  " c00, c01, c01, c00")]))))
	  (const_int 1)))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
   kdmbb\t%0, %1, %2
   kdmbt\t%0, %1, %2
   kdmtt\t%0, %1, %2
   kdmbt\t%0, %2, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

;; KDMABB, KDMABT, KDMATT (32 (*) (32, 32))
(define_expand "kdmabb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kdma_internal (operands[0], operands[2], operands[3],
				GEN_INT (0), GEN_INT (0), operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "kdmabt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kdma_internal (operands[0], operands[2], operands[3],
				GEN_INT (0), GEN_INT (1), operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "kdmatt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kdma_internal (operands[0], operands[2], operands[3],
				GEN_INT (1), GEN_INT (1), operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "kdma_internal"
  [(set (match_operand:SI 0 "register_operand"                      "=   r,   r,   r,   r")
	(ss_plus:SI
	  (ashift:SI
	    (mult:SI
	      (sign_extend:SI
		(vec_select:HI
		  (match_operand:RVPV2HI 1 "register_operand"          "   r,   r,   r,   r")
		  (parallel [(match_operand:SI 3 "imm_0_1_operand"  " c00, c00, c01, c01")])))
	      (sign_extend:SI
		(vec_select:HI
		  (match_operand:RVPV2HI 2 "register_operand"          "   r,   r,   r,   r")
		  (parallel [(match_operand:SI 4 "imm_0_1_operand"  " c00, c01, c01, c00")]))))
	    (const_int 1))
	  (match_operand:SI 5 "register_operand"                    "   0,   0,   0,   0")))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
   kdmabb\t%0, %1, %2
   kdmabt\t%0, %1, %2
   kdmatt\t%0, %1, %2
   kdmabt\t%0, %2, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "kdmabb_64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:DI 2 "register_operand" " r")
			(match_operand:DI 3 "register_operand" " r")]
		    UNSPEC_KDMABB))]
 "TARGET_ZPN && TARGET_64BIT"
 "kdmabb\t%0, %1, %2"
 [(set_attr "type" "dsp64")
  (set_attr "mode" "DI")])

(define_insn "kdmabt_64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:DI 2 "register_operand" " r")
			(match_operand:DI 3 "register_operand" " r")]
		    UNSPEC_KDMABT))]
 "TARGET_ZPN && TARGET_64BIT"
 "kdmabt\t%0, %1, %2"
 [(set_attr "type" "dsp64")
  (set_attr "mode" "DI")])

(define_insn "kdmatt_64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:DI 2 "register_operand" " r")
			(match_operand:DI 3 "register_operand" " r")]
		    UNSPEC_KDMATT))]
 "TARGET_ZPN && TARGET_64BIT"
 "kdmatt\t%0, %1, %2"
 [(set_attr "type" "dsp64")
  (set_attr "mode" "DI")])

;; KHMBB, KHMBT, KHMTT (xlen (*) (xlen, xlen) for vector mode, xlen (*) (32, 32) for non-vector mode)
(define_insn "khmbb<mode>"
  [(set (match_operand:VHIX 0 "register_operand" "=r")
	(unspec:VHIX [(match_operand:VHIX 1 "register_operand" "r")
		     (match_operand:VHIX 2 "register_operand" "r")] UNSPEC_KHMBB))]
  "TARGET_ZPN"
  "khmbb\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "<MODE>")])

(define_insn "khmbt<mode>"
  [(set (match_operand:VHIX 0 "register_operand" "=r")
	(unspec:VHIX [(match_operand:VHIX 1 "register_operand" "r")
		     (match_operand:VHIX 2 "register_operand" "r")] UNSPEC_KHMBT))]
  "TARGET_ZPN"
  "khmbt\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "<MODE>")])

(define_insn "khmtt<mode>"
  [(set (match_operand:VHIX 0 "register_operand" "=r")
	(unspec:VHIX [(match_operand:VHIX 1 "register_operand" "r")
		     (match_operand:VHIX 2 "register_operand" "r")] UNSPEC_KHMTT))]
  "TARGET_ZPN"
  "khmtt\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "<MODE>")])

(define_insn "khmbb64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (unspec:SI [(match_operand:SI 1 "register_operand" "r")
		      (match_operand:SI 2 "register_operand" "r")] UNSPEC_KHMBB)))]
  "TARGET_ZPN && TARGET_64BIT"
  "khmbb\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "khmbt64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (unspec:SI [(match_operand:SI 1 "register_operand" "r")
		      (match_operand:SI 2 "register_operand" "r")] UNSPEC_KHMBT)))]
  "TARGET_ZPN && TARGET_64BIT"
  "khmbt\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "khmtt64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (unspec:SI [(match_operand:SI 1 "register_operand" "r")
		      (match_operand:SI 2 "register_operand" "r")] UNSPEC_KHMTT)))]
  "TARGET_ZPN && TARGET_64BIT"
  "khmtt\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

;; KMABB, KMABT, KMATT (xlen (*) (xlen, xlen))
(define_expand "kmabb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kma_internal (operands[0], operands[2], operands[3],
			       GEN_INT (0), GEN_INT (0),
			       operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmabt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kma_internal (operands[0], operands[2], operands[3],
			       GEN_INT (0), GEN_INT (1),
			       operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmatt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kma_internal (operands[0], operands[2], operands[3],
			       GEN_INT (1), GEN_INT (1),
			       operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kma_internal"
  [(set (match_operand:SI 0 "register_operand"                   "=   r,   r,   r,   r")
	(ss_plus:SI
	  (mult:SI
	    (sign_extend:SI
	      (vec_select:HI
		(match_operand:RVPV2HI 1 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 3 "imm_0_1_operand" " c00, c00, c01, c01")])))
	    (sign_extend:SI
	      (vec_select:HI
	        (match_operand:RVPV2HI 2 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 4 "imm_0_1_operand" " c00, c01, c01, c00")]))))
	  (match_operand:SI 5 "register_operand"                 "   0,   0,   0,   0")))]
  "TARGET_ZPN && !TARGET_64BIT"
{
  const char *pats[] = { "kmabb\t%0, %1, %2",
			 "kmabt\t%0, %1, %2",
			 "kmatt\t%0, %1, %2",
			 "kmabt\t%0, %2, %1" };
  return pats[which_alternative];
}
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_expand "kmabb64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kma64_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (2), GEN_INT (0),
				 GEN_INT (2), operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmabt64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kma64_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (2), GEN_INT (1),
				 GEN_INT (3), operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmatt64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kma64_internal (operands[0], operands[2], operands[3],
				 GEN_INT (1), GEN_INT (3), GEN_INT (1),
				 GEN_INT (3), operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kma64_internal"
  [(set (match_operand:RVPV2SI 0 "register_operand"                 "=   r,   r,   r,   r")
	(ss_plus:RVPV2SI
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI
	      (vec_select:RVPV2HI
		(match_operand:RVPV4HI 1 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 3 "imm_0_1_operand" " c00, c00, c01, c01")
			   (match_operand:SI 4 "imm_2_3_operand" " c02, c02, c03, c03")])))
	    (sign_extend:RVPV2SI
	      (vec_select:RVPV2HI
	        (match_operand:RVPV4HI 2 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 5 "imm_0_1_operand" " c00, c01, c01, c00")
			   (match_operand:SI 6 "imm_2_3_operand" " c02, c03, c03, c02")]))))
	  (match_operand:RVPV2SI 7 "register_operand"               "   0,   0,   0,   0")))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
  kmabb\t%0, %1, %2
  kmabt\t%0, %1, %2
  kmatt\t%0, %1, %2
  kmabt\t%0, %2, %1"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV2SI")])

;; KHM8, KHMX8, KHM16, KHMX16
(define_insn "khm8<mode>"
  [(set (match_operand:VQIX 0 "register_operand"              "=r")
	(unspec:VQIX [(match_operand:VQIX 1 "register_operand" " r")
		     (match_operand:VQIX 2 "register_operand" " r")]
		     UNSPEC_KHM))]
  "TARGET_ZPN"
  "khm8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "khmx8<mode>"
  [(set (match_operand:VQIX 0 "register_operand"              "=r")
	(unspec:VQIX [(match_operand:VQIX 1 "register_operand" " r")
		     (match_operand:VQIX 2 "register_operand" " r")]
		     UNSPEC_KHMX))]
  "TARGET_ZPN"
  "khmx8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "khm16<mode>"
  [(set (match_operand:VHIX 0 "register_operand"              "=r")
	(unspec:VHIX [(match_operand:VHIX 1 "register_operand" " r")
		     (match_operand:VHIX 2 "register_operand" " r")]
		     UNSPEC_KHM))]
  "TARGET_ZPN"
  "khm16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "khmx16<mode>"
  [(set (match_operand:VHIX 0 "register_operand"              "=r")
	(unspec:VHIX [(match_operand:VHIX 1 "register_operand" " r")
		     (match_operand:VHIX 2 "register_operand" " r")]
		     UNSPEC_KHMX))]
  "TARGET_ZPN"
  "khmx16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; KMADA, KMAXDA
(define_insn "kmada"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_plus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmada\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmada64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_plus:RVPV2SI
	  (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (ss_plus:RVPV2SI
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 3 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)]))))
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 3)
				(parallel [(const_int 0) (const_int 2)])))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmada\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmaxda"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_plus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmaxda\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmaxda64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_plus:RVPV2SI
	  (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (ss_plus:RVPV2SI
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmaxda\t%0, %2, %3"
  [(set_attr "type" "simd")])

;; KMADS, KMADRS, KMAXDS
(define_insn "kmads"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmads\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmads64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_plus:RVPV2SI
	  (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (ss_minus:RVPV2SI
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 3 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)]))))
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 3)
				(parallel [(const_int 0) (const_int 2)])))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmads\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmadrs"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 2 "register_operand" " r")
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmadrs\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmadrs64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_plus:RVPV2SI
	  (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (ss_minus:RVPV2SI
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmadrs\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmaxds"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmaxds\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmaxds64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_plus:RVPV2SI
	  (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (ss_minus:RVPV2SI
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmaxds\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "rvp_kmar64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_KMAR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "kmar64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; RV64P KMAR64
(define_insn "vkmar64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(ss_plus:DI (match_operand:DI 1 "register_operand"    " 0")
	  (plus:DI
	    (mult:DI
	      (sign_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 2 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (sign_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 3 "register_operand" " r")
		  (parallel [(const_int 0)]))))
	    (mult:DI
	      (sign_extend:DI
		(vec_select:SI (match_dup 2) (parallel [(const_int 1)])))
	      (sign_extend:DI
		(vec_select:SI (match_dup 3) (parallel [(const_int 1)])))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "kmar64\t%0, %2, %3"
  [(set_attr "type"   "dsp64")
   (set_attr "mode" "DI")])

;; KMDA, KMXDA
(define_insn "kmda"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(ss_plus:SI
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 1 "register_operand" "r")
			      (parallel [(const_int 1)])))
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 2 "register_operand" "r")
			      (parallel [(const_int 1)]))))
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:SI (vec_select:HI
			      (match_dup 2)
			      (parallel [(const_int 0)]))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmda\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "kmxda"
  [(set (match_operand:SI 0 "register_operand"                        "=r")
	(ss_plus:SI
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 1 "register_operand" "r")
			      (parallel [(const_int 1)])))
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 2 "register_operand" "r")
			      (parallel [(const_int 0)]))))
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:SI (vec_select:HI
			      (match_dup 2)
			      (parallel [(const_int 1)]))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmxda\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "kmxda64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                      "=r")
	(ss_plus:RVPV2SI
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 1 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" "r")
				(parallel [(const_int 0) (const_int 2)]))))
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 1)
				(parallel [(const_int 0) (const_int 2)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 1) (const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmxda\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "kmda64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                      "=r")
	(ss_plus:RVPV2SI
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 1 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)]))))
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 1)
				(parallel [(const_int 0) (const_int 2)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmda\t%0, %1, %2"
  [(set_attr "type" "simd")])

;; KMMAC, KMMAC.u
(define_insn "kmmac"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(ss_plus:SI (match_operand:SI 1 "register_operand"             " 0")
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI (match_operand:SI 2 "register_operand" " r"))
		(sign_extend:DI (match_operand:SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmmac\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmmac_64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_plus:RVPV2SI (match_operand:RVPV2SI 1 "register_operand"             " 0")
	  (truncate:RVPV2SI
	    (lshiftrt:RVPV2DI
	      (mult:RVPV2DI
		(sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r"))
		(sign_extend:RVPV2DI (match_operand:RVPV2SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmmac\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmmac_round"
  [(set (match_operand:SI 0 "register_operand"                                     "=r")
	(ss_plus:SI (match_operand:SI 1 "register_operand"                         " 0")
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI [(mult:DI
			    (sign_extend:DI (match_operand:SI 2 "register_operand" " r"))
			    (sign_extend:DI (match_operand:SI 3 "register_operand" " r")))]
			 UNSPEC_ROUND)
	      (const_int 32)))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmmac.u\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmmac64_round"
  [(set (match_operand:RVPV2SI 0 "register_operand"                                     "=r")
	(ss_plus:RVPV2SI (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (truncate:RVPV2SI
	    (lshiftrt:RVPV2DI
	      (unspec:RVPV2DI [(mult:RVPV2DI
			    (sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r"))
			    (sign_extend:RVPV2DI (match_operand:RVPV2SI 3 "register_operand" " r")))]
			 UNSPEC_ROUND)
	      (const_int 32)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmmac.u\t%0, %2, %3"
  [(set_attr "type" "simd")])

;; KMMAWB, KMMAWB.u, KMMAWB2, KMMAWB2.u, KMMAWT2, KMMAWT2.u
(define_insn "kmmaw_internal"
  [(set (match_operand:SI 0 "register_operand"                         "=  r,   r,   r,   r")
	(ss_plus:SI
	  (match_operand:SI 4 "register_operand"                       "   0,   0,   0,   0")
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI (match_operand:SI 1 "register_operand" "   r,   r,   r,   r"))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_operand:RVPV2HI 2 "register_operand"         "   r,   r,   r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand" " c00, c01, c00, c01")]))))
	      (match_operand:SI 5 "imm_15_16_operand"                  " c16, c16, c15, c15" )))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
  kmmawb\t%0, %1, %2
  kmmawt\t%0, %1, %2
  kmmawb2\t%0, %1, %2
  kmmawt2\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_expand "kmmawb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), operands[1], GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_internal (operands[0], operands[2], operands[3],
				 GEN_INT (1), operands[1], GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawb2"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), operands[1], GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt2"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_internal (operands[0], operands[2], operands[3],
				 GEN_INT (1), operands[1], GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kmmaw_round_internal"
  [(set (match_operand:SI 0 "register_operand"                            "=  r,   r,   r,   r")
	(ss_plus:SI
	  (match_operand:SI 4 "register_operand"                          "   0,   0,   0,   0")
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
		[(mult:DI
		   (sign_extend:DI (match_operand:SI 1 "register_operand" "   r,   r,   r,   r"))
		   (sign_extend:DI
		     (vec_select:HI
		       (match_operand:RVPV2HI 2 "register_operand"           "   r,   r,   r,   r")
		       (parallel [(match_operand:SI 3 "imm_0_1_operand"   " c00, c01, c00, c01")]))))]
		UNSPEC_ROUND)
	      (match_operand:SI 5 "imm_15_16_operand"                     " c16, c16, c15, c15")))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
  kmmawb.u\t%0, %1, %2
  kmmawt.u\t%0, %1, %2
  kmmawb2.u\t%0, %1, %2
  kmmawt2.u\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_expand "kmmawb_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_round_internal (operands[0], operands[2], operands[3],
				       GEN_INT (0), operands[1], GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_round_internal (operands[0], operands[2], operands[3],
				       GEN_INT (1), operands[1], GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawb2_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_round_internal (operands[0], operands[2], operands[3],
				       GEN_INT (0), operands[1], GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt2_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:SI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmaw_round_internal (operands[0], operands[2], operands[3],
				       GEN_INT (1), operands[1], GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kmmaw64_internal"
[(set (match_operand:RVPV2SI 0 "register_operand" "=r, r, r, r")
      (ss_plus:RVPV2SI
	(match_operand:RVPV2SI 5 "register_operand" "0, 0, 0, 0")
	(vec_concat:RVPV2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI
		  (vec_select:SI
		    (match_operand:RVPV2SI 1 "register_operand" "r, r, r, r")
		      (parallel [(const_int 0)])))
		(sign_extend:DI
		  (vec_select:HI
		    (match_operand:RVPV4HI 2 "register_operand"           "  r,   r,   r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand" "c00, c01, c00, c01")]))))
	      (match_operand:SI 6 "imm_15_16_operand"                  "c16, c16, c15, c15")))
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI
		  (vec_select:SI
		    (match_dup 1)
		      (parallel [(const_int 1)])))
		(sign_extend:DI
		  (vec_select:HI
		    (match_dup 2)
		      (parallel [(match_operand:SI 4 "imm_2_3_operand" "c02, c03, c02, c03")]))))
	      (match_dup 6))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
  kmmawb\t%0, %1, %2
  kmmawt\t%0, %1, %2
  kmmawb2\t%0, %1, %2
  kmmawt2\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_expand "kmmawb64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_internal (operands[0], operands[2], operands[3],
				   GEN_INT (0), GEN_INT (2), operands[1],
				   GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_internal (operands[0], operands[2], operands[3],
				   GEN_INT (1), GEN_INT (3), operands[1],
				   GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawb2_64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_internal (operands[0], operands[2], operands[3],
				   GEN_INT (0), GEN_INT (2), operands[1],
				   GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt2_64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_internal (operands[0], operands[2], operands[3],
				   GEN_INT (1), GEN_INT (3), operands[1],
				   GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kmmaw64_round_internal"
[(set (match_operand:RVPV2SI 0 "register_operand"                           "=r,    r,   r,   r")
      (ss_plus:RVPV2SI
	(match_operand:RVPV2SI 5 "register_operand"                         "  0,   0,   0,   0")
	(vec_concat:RVPV2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
		[(mult:DI
		  (sign_extend:DI
		    (vec_select:SI
		      (match_operand:RVPV2SI 1 "register_operand"           "  r,   r,   r,   r")
			(parallel [(const_int 0)])))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_operand:RVPV4HI 2 "register_operand"           "  r,   r,   r,   r")
			(parallel [(match_operand:SI 3 "imm_0_1_operand" "c00, c01, c00, c01")]))))]
		UNSPEC_ROUND)
	      (const_int 16)))
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
		[(mult:DI
		  (sign_extend:DI
		    (vec_select:SI
		      (match_dup 1)
			(parallel [(const_int 1)])))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_dup 2)
			(parallel [(match_operand:SI 4 "imm_2_3_operand" "c02, c03, c02, c03")]))))]
		  UNSPEC_ROUND)
	      (match_operand:SI 6 "imm_15_16_operand"                    "c16, c16, c15, c15"))))))]
"TARGET_ZPN && TARGET_64BIT"
  "@
  kmmawb.u\t%0, %1, %2
  kmmawt.u\t%0, %1, %2
  kmmawb2.u\t%0, %1, %2
  kmmawt2.u\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_expand "kmmawb64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_round_internal (operands[0], operands[2], operands[3],
					 GEN_INT (0), GEN_INT (2), operands[1],
					 GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_round_internal (operands[0], operands[2], operands[3],
					 GEN_INT (1), GEN_INT (3), operands[1],
					 GEN_INT (16)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawb2_64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_round_internal (operands[0], operands[2], operands[3],
					 GEN_INT (0), GEN_INT (2), operands[1],
					 GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmawt2_64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmaw64_round_internal (operands[0], operands[2], operands[3],
					 GEN_INT (1), GEN_INT (3), operands[1],
					 GEN_INT (15)));
  DONE;
}
[(set_attr "type" "simd")])

;; KMMSB, KMMSB.u
(define_insn "kmmsb"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(ss_minus:SI (match_operand:SI 1 "register_operand"            " 0")
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI (match_operand:SI 2 "register_operand" " r"))
		(sign_extend:DI (match_operand:SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmmsb\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmmsb_64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_minus:RVPV2SI (match_operand:RVPV2SI 1 "register_operand"             " 0")
	  (truncate:RVPV2SI
	    (lshiftrt:RVPV2DI
	      (mult:RVPV2DI
		(sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r"))
		(sign_extend:RVPV2DI (match_operand:RVPV2SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmmsb\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmmsb_round"
  [(set (match_operand:SI 0 "register_operand"                                     "=r")
	(ss_minus:SI (match_operand:SI 1 "register_operand"                        " 0")
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI [(mult:DI
			    (sign_extend:DI (match_operand:SI 2 "register_operand" " r"))
			    (sign_extend:DI (match_operand:SI 3 "register_operand" " r")))]
			 UNSPEC_ROUND)
	      (const_int 32)))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmmsb.u\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmmsb64_round"
  [(set (match_operand:RVPV2SI 0 "register_operand"                                     "=r")
	(ss_minus:RVPV2SI (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (truncate:RVPV2SI
	    (lshiftrt:RVPV2DI
	      (unspec:RVPV2DI [(mult:RVPV2DI
			    (sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r"))
			    (sign_extend:RVPV2DI (match_operand:RVPV2SI 3 "register_operand" " r")))]
			 UNSPEC_ROUND)
	      (const_int 32)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmmsb.u\t%0, %2, %3"
  [(set_attr "type" "simd")])

;; KMMWB2, KMMWB2.u, KMMWT2, KMMWT2.u
(define_insn "kmmw2_round_internal"
  [(set (match_operand:SI 0 "register_operand"                          "=   r,    r")
	(truncate:SI
	  (lshiftrt:DI
	    (unspec:DI
	      [(ss_mult:DI
		 (sign_extend:DI (match_operand:SI 1 "register_operand" "    r,    r"))
		 (sign_extend:DI
		   (vec_select:HI
		     (match_operand:RVPV2HI 2 "register_operand"           "    r,    r")
		     (parallel [(match_operand:SI 3 "imm_0_1_operand"   "  c00,  c01")]))))]
	      UNSPEC_KMMWU)
	    (const_int 15))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
   kmmwb2.u\t%0, %1, %2
   kmmwt2.u\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_expand "kmmwb2_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmw2_round_internal (operands[0], operands[1],
				       operands[2], GEN_INT (0)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmwt2_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmw2_round_internal (operands[0], operands[1],
				       operands[2], GEN_INT (1)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kmmw64_round"
  [(set (match_operand:RVPV2SI 0 "register_operand"                       "=r,    r")
	(vec_concat:RVPV2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
		[(mult:DI
		  (sign_extend:DI
		    (vec_select:SI
		      (match_operand:RVPV2SI 1 "register_operand"           "  r,   r")
		      (parallel [(const_int 0)])))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_operand:RVPV4HI 2 "register_operand"           "  r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand"   "c00, c01")]))))]
		UNSPEC_KMMWU)
	      (const_int 15)))
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
		[(mult:DI
		  (sign_extend:DI
		    (vec_select:SI
		      (match_dup 1)
		      (parallel [(const_int 1)])))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_dup 2)
		      (parallel [(match_operand:SI 4 "imm_2_3_operand"   "c02, c03")]))))]
		UNSPEC_KMMWU)
	      (const_int 15)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
   kmmwb2.u\t%0, %1, %2
   kmmwt2.u\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_expand "kmmwb64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmw64_round (operands[0], operands[1], operands[2],
			       GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmwt64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmw64_round (operands[0], operands[1], operands[2],
			       GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "simd")])

;; KMSDA, KMSXDA
(define_insn "kmsda"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_minus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmsda\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmsda64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_minus:RVPV2SI
	  (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (ss_minus:RVPV2SI
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 3 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)]))))
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 3)
				(parallel [(const_int 0) (const_int 2)])))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmsda\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmsxda"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_minus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:RVPV2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kmsxda\t%0, %2, %3"
  [(set_attr "type" "simd")])

(define_insn "kmsxda64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                         "=r")
	(ss_minus:RVPV2SI
	  (match_operand:RVPV2SI 1 "register_operand"                       " 0")
	  (ss_minus:RVPV2SI
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:RVPV2SI
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmsxda\t%0, %2, %3"
  [(set_attr "type" "simd")])


(define_insn "rvp_kmsr64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_KMSR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "kmsr64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; RV64P KMSR64
(define_insn "vkmsr64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(ss_minus:DI
	  (minus:DI
	  (match_operand:DI 1 "register_operand"    " 0")
	    (mult:DI
	      (sign_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 2 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (sign_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 3 "register_operand" " r")
		  (parallel [(const_int 0)])))))
	    (mult:DI
	      (sign_extend:DI
		(vec_select:SI (match_dup 2) (parallel [(const_int 1)])))
	      (sign_extend:DI
		(vec_select:SI (match_dup 3) (parallel [(const_int 1)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kmsr64\t%0, %2, %3"
  [(set_attr "type"  "dsp64")
   (set_attr "mode"  "DI")])

(define_expand "kmmwb64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmw64 (operands[0], operands[1], operands[2],
			  GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmwt64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kmmw64 (operands[0], operands[1], operands[2],
			 GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kmmw64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                       "=r,    r")
	(vec_concat:RVPV2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI [(mult:DI
		(sign_extend:DI
		  (vec_select:SI
		    (match_operand:RVPV2SI 1 "register_operand"           "  r,   r")
		      (parallel [(const_int 0)])))
		(sign_extend:DI
		  (vec_select:HI
		    (match_operand:RVPV4HI 2 "register_operand"           "  r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand"   "c00, c01")]))))]
	      UNSPEC_KMMW)
	      (const_int 15)))
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI [(mult:DI
		(sign_extend:DI
		  (vec_select:SI
		    (match_dup 1)
		      (parallel [(const_int 1)])))
		(sign_extend:DI
		  (vec_select:HI
		    (match_dup 2)
		      (parallel [(match_operand:SI 4 "imm_2_3_operand"   "c02, c03")]))))]
	      UNSPEC_KMMW)
	      (const_int 15)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
   kmmwb2\t%0, %1, %2
   kmmwt2\t%0, %1, %2"
[(set_attr "type" "simd")])

(define_expand "kmmwb2"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmw2_internal (operands[0], operands[1], operands[2], GEN_INT (0)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmmwt2"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_kmmw2_internal (operands[0], operands[1], operands[2], GEN_INT (1)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kmmw2_internal"
  [(set (match_operand:SI 0 "register_operand"                       "=   r,    r")
	(truncate:SI
	  (lshiftrt:DI
	    (unspec:DI [(mult:DI
	      (sign_extend:DI (match_operand:SI 1 "register_operand" "    r,    r"))
	      (sign_extend:DI
		(vec_select:HI
		  (match_operand:RVPV2HI 2 "register_operand"           "    r,    r")
		  (parallel [(match_operand:SI 3 "imm_0_1_operand"   "  c00,  c01")]))))]
	    UNSPEC_KMMW)
	    (const_int 15))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
   kmmwb2\t%0, %1, %2
   kmmwt2\t%0, %1, %2"
  [(set_attr "type" "simd")])
;; KSLLW
(define_insn "ksll"
  [(set (match_operand:SI 0 "register_operand"               "=   r, r")
	(ss_ashift:SI (match_operand:SI 1 "register_operand" "    r, r")
		      (match_operand:SI 2 "rimm5u_operand"   " Iu05, r")))]
  "TARGET_ZPN"
  "@
   kslliw\t%0, %1, %2
   ksllw\t%0, %1, %2"
  [(set_attr "type"  "dsp")
   (set_attr "mode"  "SI")])

;; KSLL8
(define_insn "kslli8<VQIX:mode><X:mode>"
  [(set (match_operand:VQIX 0 "register_operand"                "=  r, r")
	(ss_ashift:VQIX (match_operand:VQIX 1 "register_operand" "   r, r")
		       (match_operand:X 2   "rimm3u_operand"   " u03, r")))]
  "TARGET_ZPN"
  "@
   kslli8\t%0, %1, %2
   ksll8\t%0, %1, %2"
  [(set_attr "type"  "simd, simd")
   (set_attr "mode"  "<VQIX:MODE>, <VQIX:MODE>")])

;; KSLL16
(define_insn "kslli16<mode>"
  [(set (match_operand:VHIX 0 "register_operand"                "=  r, r")
	(ss_ashift:VHIX (match_operand:VHIX 1 "register_operand" "   r, r")
		       (match_operand:SI 2  "rimm4u_operand"   " u04, r")))]
  "TARGET_ZPN"
  "@
   kslli16\t%0, %1, %2
   ksll16\t%0, %1, %2"
  [(set_attr "type"  "simd, simd")
   (set_attr "mode"  "<MODE>, <MODE>")])

;; KSLRA 8|16|32
(define_insn "kslra<VECI:mode><X:mode>"
  [(set (match_operand:VECI 0 "register_operand"                  "=r")
	(if_then_else:VECI
	  (lt:X
	    (sign_extend:SI
		  (truncate:<VECI_scalar>
		    (match_operand:SI 2 "register_operand"              " r")))
		(const_int 0))
	  (ashiftrt:VECI (match_operand:VECI 1 "register_operand" " r")
			 (neg:X (match_dup 2)))
	  (ss_ashift:VECI (match_dup 1)
			  (match_dup 2))))]
  "TARGET_ZPN"
  "kslra<VECI:bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<VECI:MODE>")])

;; kslra32.u kslrarvpv2sidi_round
(define_insn "kslra<VECI:mode><X:mode>_round"
  [(set (match_operand:VECI 0 "register_operand"                  "=r")
	(if_then_else:VECI
	  (lt:X
	    (sign_extend:SI
		  (truncate:<VECI_scalar>
		    (match_operand:SI 2 "register_operand"                     " r")))
		(const_int 0))
	  (unspec:VECI [(ashiftrt:VECI (match_operand:VECI 1 "register_operand" " r")
				       (neg:X (match_dup 2)))]
		        UNSPEC_ROUND)
	  (ss_ashift:VECI (match_dup 1)
			  (match_dup 2))))]
  "TARGET_ZPN"
  "kslra<VECI:bits>.u\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<VECI:MODE>")])

;; kslraw
(define_insn "kslraw"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KSLRAW))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kslraw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "kslraw64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (unspec:SI [(match_operand:SI 1 "register_operand" "r")
		      (match_operand:SI 2 "register_operand" "r")] UNSPEC_KSLRAW)))]
  "TARGET_ZPN && TARGET_64BIT"
  "kslraw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "kslrawu"
  [(set (match_operand:SI 0 "register_operand" "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "r")
		    (match_operand:SI 2 "register_operand" "r")] UNSPEC_KSLRAWU))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kslraw.u\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "kslrawu64"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(sign_extend:DI
	  (unspec:SI [(match_operand:SI 1 "register_operand" "r")
		      (match_operand:SI 2 "register_operand" "r")] UNSPEC_KSLRAWU)))]
  "TARGET_ZPN && TARGET_64BIT"
  "kslraw.u\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

;; KSTAS16|32, KSTSA16|32
(define_expand "kstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kstas<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (ss_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (ss_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "kstas<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

;; rv64
(define_expand "kstas16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kstas16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (ss_minus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
					(parallel [(const_int 0)])))
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:RVPV2HI
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (ss_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kstas16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_expand "kstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_kstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kstsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (ss_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (ss_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "kstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "kstsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_kstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kstsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (ss_plus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				       (parallel [(const_int 0)])))
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:RVPV2HI
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (ss_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kstsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; KWMMUL[.u]
(define_insn "kwmmul"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (lshiftrt:DI
	    (ss_mult:DI
	      (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" " r")) (const_int 2))
	      (mult:DI (sign_extend:DI (match_operand:SI 2 "register_operand" " r")) (const_int 2)))
	    (const_int 32))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kwmmul\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "kwmmul_64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                       "=r")
	(truncate:RVPV2SI
	  (lshiftrt:RVPV2DI
	    (ss_mult:RVPV2DI
	      (mult:RVPV2DI (sign_extend:RVPV2DI (match_operand:RVPV2SI 1 "register_operand" " r")) (const_int 2))
	      (mult:RVPV2DI (sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r")) (const_int 2)))
	    (const_int 32))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kwmmul\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "kwmmul_round"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (lshiftrt:DI
	    (unspec:DI [
	      (ss_mult:DI
		(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" " r")) (const_int 2))
		(mult:DI (sign_extend:DI (match_operand:SI 2 "register_operand" " r")) (const_int 2)))]
	      UNSPEC_ROUND)
	    (const_int 32))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "kwmmul.u\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "kwmmul64_round"
  [(set (match_operand:RVPV2SI 0 "register_operand"                       "=r")
	(truncate:RVPV2SI
	  (lshiftrt:RVPV2DI
	    (unspec:RVPV2DI [
	      (ss_mult:RVPV2DI
		(mult:RVPV2DI (sign_extend:RVPV2DI (match_operand:RVPV2SI 1 "register_operand" " r")) (const_int 2))
		(mult:RVPV2DI (sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r")) (const_int 2)))]
	      UNSPEC_ROUND)
	    (const_int 32))))]
  "TARGET_ZPN && TARGET_64BIT"
  "kwmmul.u\t%0, %1, %2"
  [(set_attr "type" "simd")])

;; MADDR32, MSUBR32
(define_insn "*maddr32_vec"
  [(set (match_operand:SI 0 "register_operand"                   "=r")
	(plus:SI (mult:SI (match_operand:SI 1 "register_operand" " r")
			  (match_operand:SI 2 "register_operand" " r"))
		 (match_operand:SI 3 "register_operand"          " 0")))]
  "TARGET_ZPN && riscv_rvp_autovec_enable() && TARGET_NUCLEI_DSP_AUTOVEC"
  "maddr32\t%0, %1, %2"
  [(set_attr "type"   "mac")
   (set_attr "length"   "4")])

(define_insn "maddr32<mode>"
  [(set (match_operand:VSHI 0 "register_operand"                   "=r")
	(plus:VSHI (mult:VSHI (match_operand:VSHI 1 "register_operand" " r")
			  (match_operand:VSHI 2 "register_operand" " r"))
		 (match_operand:VSHI 3 "register_operand"          " 0")))]
  "TARGET_ZPN"
  "maddr32\t%0, %1, %2"
  [(set_attr "type"   "mac")
   (set_attr "length"   "4")
   (set_attr "mode" "<MODE>")])

(define_insn "msubr32<mode>"
  [(set (match_operand:VSHI 0 "register_operand"                    "=r")
	(minus:VSHI (match_operand:VSHI 3 "register_operand"          " 0")
		  (mult:VSHI (match_operand:VSHI 1 "register_operand" " r")
			   (match_operand:VSHI 2 "register_operand" " r"))))]
  "TARGET_ZPN"
  "msubr32\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "mode" "<MODE>")])

(define_insn "*msubr32_vec"
  [(set (match_operand:SI 0 "register_operand"                    "=r")
	(minus:SI (match_operand:SI 3 "register_operand"          " 0")
		  (mult:SI (match_operand:SI 1 "register_operand" " r")
			   (match_operand:SI 2 "register_operand" " r"))))]
  "TARGET_ZPN && riscv_rvp_autovec_enable() && TARGET_NUCLEI_DSP_AUTOVEC"
  "msubr32\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "length"   "4")])

;; MAXW, MINW
(define_insn "psmaxsi3"
  [(set (match_operand:SI 0 "register_operand"          "=r")
	(smax:SI (match_operand:SI 1 "register_operand" " r")
		 (match_operand:SI 2 "register_operand" " r")))]
  "TARGET_ZPN && !TARGET_ZBB && !TARGET_64BIT"
  "maxw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "psminsi3"
  [(set (match_operand:SI 0 "register_operand"          "=r")
	(smin:SI (match_operand:SI 1 "register_operand" " r")
		 (match_operand:SI 2 "register_operand" " r")))]
  "TARGET_ZPN && !TARGET_ZBB && !TARGET_64BIT"
  "minw\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "psmaxsi3_64"
  [(set (match_operand:DI 0 "register_operand"          "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		 (match_operand:SI 2 "register_operand" " r")]
		 UNSPEC_MAXW))]
  "TARGET_ZPN && !TARGET_ZBB && TARGET_64BIT"
  "maxw\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "psminsi3_64"
  [(set (match_operand:DI 0 "register_operand"          "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		 (match_operand:SI 2 "register_operand" " r")]
		 UNSPEC_MINW))]
  "TARGET_ZPN && !TARGET_ZBB && TARGET_64BIT"
  "minw\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; MULR64, MULSR64
(define_insn "rvp_umulsidi3"
  [(set (match_operand:DI 0 "register_operand"                          "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		      (match_operand:SI 2 "register_operand" " r")]
			  UNSPEC_MULR64))]
  "TARGET_ZPSF && TARGET_64BIT"
  "mulr64\t%0, %1, %2"
  [(set_attr "type"   "dsp")])
			 
(define_insn "*umulsidi3_vec"
  [(set (match_operand:DI 0 "register_operand"                          "=r")
	(mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
		 (zero_extend:DI (match_operand:SI 2 "register_operand" " r"))))]
  "TARGET_ZPSF && TARGET_64BIT && riscv_rvp_autovec_enable() &&TARGET_NUCLEI_DSP_AUTOVEC"
  "mulr64\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "mode"   "DI")])

(define_insn "rvp_mulsidi3"
  [(set (match_operand:DI 0 "register_operand"                          "=r")
	(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
		 (sign_extend:DI (match_operand:SI 2 "register_operand" " r"))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "mulsr64\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "mode"   "DI")])

;; PBSAD, PBSADA
(define_insn "pbsad<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_PBSAD))]
  "TARGET_ZPN"
  "pbsad\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "<MODE>")])

(define_insn "pbsada<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_PBSADA))]
  "TARGET_ZPN"
  "pbsada\t%0, %2, %3"
  [(set_attr "type" "dsp")
   (set_attr "mode" "<MODE>")])

;; PKBB[16|32], PKBT[16|32], PKTT[16|32], PKTB[16|32]
(define_insn "vec_merge<mode>"
  [(set (match_operand:VSHI 0 "register_operand"               "= r,   r,   r,   r,   r,   r,   r,   r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (vec_select:<VNHALF>
	      (match_operand:VSHI 1 "register_operand"         "  r,   r,   r,   r,   r,   r,   r,   r")
	      (parallel [(match_operand:SI 4 "imm_0_1_operand" "c00, c00, c01, c01, c00, c00, c01, c01")])))
	  (vec_duplicate:VSHI
	    (vec_select:<VNHALF>
	      (match_operand:VSHI 2 "register_operand"         "  r,   r,   r,   r,   r,   r,   r,   r")
	      (parallel [(match_operand:SI 5 "imm_0_1_operand" "c00, c01, c01, c00, c00, c01, c01, c00")])))
	  (match_operand:SI 3 "imm_1_2_operand"                "c01, c01, c01, c01, c02, c02, c02, c02")))]
  "TARGET_ZPN"
  "@
   pkbb<bits>\t%0, %2, %1
   pktb<bits>\t%0, %2, %1
   pktt<bits>\t%0, %2, %1
   pkbt<bits>\t%0, %2, %1
   pkbb<bits>\t%0, %1, %2
   pkbt<bits>\t%0, %1, %2
   pktt<bits>\t%0, %1, %2
   pktb<bits>\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "<MODE>")])

;; pk**32 (e.g. pkbbrvpv2si) belongs to zprv subset, but zpn subset is a mandatory
;; subset for RVP, and the availability will be checked in riscv-builtin.c
(define_expand "pkbb<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_ZPN"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "pkbt<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_ZPN"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "pktt<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_ZPN"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "pktb<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_ZPN"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (1), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dsp")])

;; pkbb16 rv64p
(define_expand "pkbb64"
  [(match_operand:RVPV4HI 0 "register_operand")
   (match_operand:RVPV4HI 1 "register_operand")
   (match_operand:RVPV4HI 2 "register_operand")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_vec_pkbb64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "vec_pkbb64"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(vec_select:RVPV4HI
	 (vec_concat:RVPV8HI (match_operand:RVPV4HI 1 "register_operand" "r")
			  (match_operand:RVPV4HI 2 "register_operand" "r"))
	 (parallel [(const_int 0) (const_int 4)
		    (const_int 2) (const_int 6)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "pkbb16\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "RVPV4HI")])

(define_expand "pkbt64"
  [(match_operand:RVPV4HI 0 "register_operand")
   (match_operand:RVPV4HI 1 "register_operand")
   (match_operand:RVPV4HI 2 "register_operand")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_vec_pkbt64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "vec_pkbt64"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(vec_select:RVPV4HI
	 (vec_concat:RVPV8HI (match_operand:RVPV4HI 1 "register_operand" "r")
			  (match_operand:RVPV4HI 2 "register_operand" "r"))
	 (parallel [(const_int 0) (const_int 5)
		    (const_int 2) (const_int 7)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "pkbt16\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "RVPV4HI")])

(define_expand "pktt64"
  [(match_operand:RVPV4HI 0 "register_operand")
   (match_operand:RVPV4HI 1 "register_operand")
   (match_operand:RVPV4HI 2 "register_operand")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_vec_pktt64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "vec_pktt64"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(vec_select:RVPV4HI
	 (vec_concat:RVPV8HI (match_operand:RVPV4HI 1 "register_operand" "r")
			  (match_operand:RVPV4HI 2 "register_operand" "r"))
	 (parallel [(const_int 1) (const_int 5)
		    (const_int 3) (const_int 7)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "pktt16\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "RVPV4HI")])

(define_expand "pktb64"
  [(match_operand:RVPV4HI 0 "register_operand")
   (match_operand:RVPV4HI 1 "register_operand")
   (match_operand:RVPV4HI 2 "register_operand")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_vec_pktb64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "vec_pktb64"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(vec_select:RVPV4HI
	 (vec_concat:RVPV8HI (match_operand:RVPV4HI 1 "register_operand" "r")
			  (match_operand:RVPV4HI 2 "register_operand" "r"))
	 (parallel [(const_int 1) (const_int 4)
		    (const_int 3) (const_int 6)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "pktb16\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "RVPV4HI")])

;; [U]RADD[8|16|32|64|W], [U]RSUB[8|16|32|64|W]
(define_insn "radd<mode>3"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(truncate:VECI
	  (ashiftrt:<VEXT>
	    (plus:<VEXT> (sign_extend:<VEXT> (match_operand:VECI 1 "register_operand" " r"))
			 (sign_extend:<VEXT> (match_operand:VECI 2 "register_operand" " r")))
	    (const_int 1))))]
  "TARGET_ZPN"
  "radd<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; radd64
(define_insn "radddi3"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(truncate:DI
	  (ashiftrt:TI
	    (plus:TI (sign_extend:TI (match_operand:DI 1 "register_operand" " r"))
		     (sign_extend:TI (match_operand:DI 2 "register_operand" " r")))
	  (const_int 1))))]
  "TARGET_ZPSF"
  "radd64\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "uradd<mode>3"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(truncate:VECI
	  (lshiftrt:<VEXT>
	    (plus:<VEXT> (zero_extend:<VEXT> (match_operand:VECI 1 "register_operand" " r"))
			 (zero_extend:<VEXT> (match_operand:VECI 2 "register_operand" " r")))
	    (const_int 1))))]
  "TARGET_ZPN"
  "uradd<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; uradd64
(define_insn "uradddi3"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(truncate:DI
	  (lshiftrt:TI
	    (plus:TI (zero_extend:TI (match_operand:DI 1 "register_operand" " r"))
		     (zero_extend:TI (match_operand:DI 2 "register_operand" " r")))
	  (const_int 1))))]
  "TARGET_ZPSF"
  "uradd64\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "rsub<mode>3"
  [(set (match_operand:VECI 0 "register_operand"                                   "=r")
	(truncate:VECI
	  (ashiftrt:<VEXT>
	    (minus:<VEXT> (sign_extend:<VEXT> (match_operand:VECI 1 "register_operand" " r"))
			  (sign_extend:<VEXT> (match_operand:VECI 2 "register_operand" " r")))
	    (const_int 1))))]
  "TARGET_ZPN"
  "rsub<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "ursub<mode>3"
  [(set (match_operand:VECI 0 "register_operand"                                   "=r")
	(truncate:VECI
	  (ashiftrt:<VEXT>
	    (minus:<VEXT> (zero_extend:<VEXT> (match_operand:VECI 1 "register_operand" " r"))
			  (zero_extend:<VEXT> (match_operand:VECI 2 "register_operand" " r")))
	    (const_int 1))))]
  "TARGET_ZPN"
  "ursub<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; rsub64
(define_insn "rsubdi3"
  [(set (match_operand:DI 0 "register_operand"                   "=r")
	(truncate:DI
	  (ashiftrt:TI
	    (minus:TI (sign_extend:TI (match_operand:DI 1 "register_operand" " r"))
		      (sign_extend:TI (match_operand:DI 2 "register_operand" " r")))
	  (const_int 1))))]
  "TARGET_ZPSF"
  "rsub64\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; ursub64
(define_insn "ursubdi3"
  [(set (match_operand:DI 0 "register_operand"                   "=r")
	(truncate:DI
	  (lshiftrt:TI
	    (minus:TI (zero_extend:TI (match_operand:DI 1 "register_operand" " r"))
		      (zero_extend:TI (match_operand:DI 2 "register_operand" " r")))
	  (const_int 1))))]
  "TARGET_ZPSF"
  "ursub64\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; 32-bit add/sub instruction: raddw and rsubw.
(define_insn "r<opcode>si3"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (ashiftrt:DI
	    (plus_minus:DI
	      (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
	      (sign_extend:DI (match_operand:SI 2 "register_operand" " r")))
	    (const_int 1))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "r<opcode>w\t%0, %1, %2"
  [(set_attr "type" "dsp")])

;; 64-bit add/sub instruction: raddw and rsubw.
(define_insn "r<opcode>disi3"
  [(set (match_operand:DI 0 "register_operand"                       "=r")
	(sign_extend:DI
	  (truncate:SI
	    (ashiftrt:DI
	      (plus_minus:DI
		(sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
		(sign_extend:DI (match_operand:SI 2 "register_operand" " r")))
	      (const_int 1)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "r<opcode>w\t%0, %1, %2"
  [(set_attr "type" "dsp")])

;; 32-bit add/sub instruction: uraddw and ursubw.
(define_insn "ur<opcode>si3"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (lshiftrt:DI
	    (plus_minus:DI
	      (zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
	      (zero_extend:DI (match_operand:SI 2 "register_operand" " r")))
	    (const_int 1))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "ur<opcode>w\t%0, %1, %2"
  [(set_attr "type" "dsp")])

;; 64-bit add/sub instruction: uraddw and ursubw.
(define_insn "ur<opcode>disi3"
  [(set (match_operand:DI 0 "register_operand"                       "=r")
	(sign_extend:DI
	  (truncate:SI
	    (lshiftrt:DI
	      (plus_minus:DI
		(zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
		(zero_extend:DI (match_operand:SI 2 "register_operand" " r")))
	      (const_int 1)))))]
  "TARGET_ZPN && TARGET_64BIT"
  "ur<opcode>w\t%0, %1, %2"
  [(set_attr "type" "dsp")])

;; RDOV
(define_insn "rdov<X:mode>"
  [(set (match_operand:X 0 "register_operand" "=r")
	(unspec_volatile:X [(const_int 0)] UNSPEC_RDOV))]
  "TARGET_ZPN"
  "csrrs \t%0, ucode, zero"
  [(set_attr "type" "dsp")
   (set_attr "mode" "<MODE>")])

;; RSTAS[16|32], RSTSA[16|32]
;; RSTSA32 => rstsarvpv2si
(define_expand "rstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_rstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rstas<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
		(minus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 0)])))
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 1)])))
		  (sign_extend:SI
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "rstas<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "rstas16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_rstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rstas16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "rstas16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_expand "rstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_rstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rstsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
	        (minus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 0)])))
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 1)])))
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "rstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "rstsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_rstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "rstsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "rstsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; SCLIP8, SCLIP16
(define_insn "sclip8<mode>"
  [(set (match_operand:VQIX 0 "register_operand"              "=  r")
	(unspec:VQIX [(match_operand:VQIX 1 "register_operand" "   r")
		      (match_operand:SI 2 "imm3u_operand"    " u03")]
		     UNSPEC_CLIPS))]
  "TARGET_ZPN"
  "sclip8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "sclip16<mode>"
  [(set (match_operand:VHIX 0 "register_operand"              "=   r")
	(unspec:VHIX [(match_operand:VHIX 1 "register_operand" "    r")
		     (match_operand:SI 2 "imm4u_operand"     " u04")]
		     UNSPEC_CLIPS))]
  "TARGET_ZPN"
  "sclip16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "sclip32<VD_SI:mode><X:mode>"
  [(set (match_operand:VD_SI 0 "register_operand" "=r")
	(unspec:VD_SI [(match_operand:VD_SI 1 "register_operand" "r")
		       (match_operand:X 2 "immediate_operand" "i")] UNSPEC_CLIPS_OV))]
  "TARGET_ZPN"
  "sclip32\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "mode" "<VD_SI:MODE>")])

;; SCMPLE8, SCMPLE16
(define_insn "scmple<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(le:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				 (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_ZPN"
  "scmple<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; SCMPLT8, SCMPLT16
(define_insn "scmplt<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(lt:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				 (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_ZPN"
  "scmplt<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; SMAL
(define_insn "smal"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(plus:DI (match_operand:DI 1 "register_operand"    " r")
	  (sign_extend:DI
	    (mult:SI
	      (sign_extend:SI
		(vec_select:HI
		  (match_operand:RVPV2HI 2 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (sign_extend:SI
		(vec_select:HI
		  (match_dup 2)
		  (parallel [(const_int 1)])))))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smal\t%0, %1, %2"
  [(set_attr "type" "psimd")
   (set_attr "mode" "DI")])

(define_insn "smal_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(plus:DI (match_operand:DI 1 "register_operand"    " r")
	  (plus:DI
	    (sign_extend:DI
	      (mult:SI
		(sign_extend:SI
		  (vec_select:HI
		    (match_operand:RVPV4HI 2 "register_operand" " r")
		    (parallel [(const_int 0)])))
		(sign_extend:SI
		  (vec_select:HI (match_dup 2) (parallel [(const_int 1)])))))
	    (sign_extend:DI
	      (mult:SI
		(sign_extend:SI
		  (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
		(sign_extend:SI
		  (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "smal\t%0, %1, %2"
  [(set_attr "type" "psimd")
   (set_attr "mode" "DI")])

;; SMALBB, SMALBT, SMALTT
(define_expand "smalbb"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smaddhidi (operands[0], operands[2],
			    operands[3], operands[1],
			    GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_expand "smalbt"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smaddhidi (operands[0], operands[2],
			    operands[3], operands[1],
			    GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_expand "smaltt"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")
   (match_operand:RVPV2HI 3 "register_operand" "")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smaddhidi (operands[0], operands[2],
			    operands[3], operands[1],
			    GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_insn "smaddhidi"
  [(set (match_operand:DI 0 "register_operand"                   "=  r,   r,   r,   r")
	(plus:DI
	  (match_operand:DI 3 "register_operand"                 "   0,   0,   0,   0")
	  (mult:DI
	    (sign_extend:DI
	      (vec_select:HI
		(match_operand:RVPV2HI 1 "register_operand"         "   r,   r,   r,   r")
		(parallel [(match_operand:SI 4 "imm_0_1_operand" " c00, c00, c01, c01")])))
	    (sign_extend:DI
	      (vec_select:HI
		(match_operand:RVPV2HI 2 "register_operand"         "   r,   r,   r,   r")
		(parallel [(match_operand:SI 5 "imm_0_1_operand" " c00, c01, c01, c00")]))))))]
  "TARGET_ZPSF && !TARGET_64BIT"
{
    const char *pats[] = { "smalbb\t%0, %1, %2",
			   "smalbt\t%0, %1, %2",
			   "smaltt\t%0, %1, %2",
			   "smalbt\t%0, %2, %1" };
    return pats[which_alternative];
}
[(set_attr "type" "dsp64")])

;; 64 Bit
(define_expand "smalbb64"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPSF && TARGET_64BIT"
{
  emit_insn (gen_smaddhidi64 (operands[0], operands[2],
			      operands[3], operands[1],
			      GEN_INT (0), GEN_INT (0),
			      GEN_INT (2), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_expand "smalbt64"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPSF && TARGET_64BIT"
{
  emit_insn (gen_smaddhidi64 (operands[0], operands[2],
			      operands[3], operands[1],
			      GEN_INT (0), GEN_INT (1),
			      GEN_INT (2), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_expand "smaltt64"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPSF && TARGET_64BIT"
{
  emit_insn (gen_smaddhidi64 (operands[0], operands[2],
			      operands[3], operands[1],
			      GEN_INT (1), GEN_INT (1),
			      GEN_INT (3), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_insn "smaddhidi64"
  [(set (match_operand:DI 0 "register_operand"                   "=  r,   r,   r,   r")
	(plus:DI
	  (match_operand:DI 3 "register_operand"                 "   0,   0,   0,   0")
	  (plus:DI
	    (mult:DI
	      (sign_extend:DI
		(vec_select:HI
		  (match_operand:RVPV4HI 1 "register_operand"         "   r,   r,   r,   r")
		  (parallel [(match_operand:SI 4 "imm_0_1_operand" " c00, c00, c01, c01")])))
	      (sign_extend:DI
		(vec_select:HI
		  (match_operand:RVPV4HI 2 "register_operand"         "   r,   r,   r,   r")
		  (parallel [(match_operand:SI 5 "imm_0_1_operand" " c00, c01, c01, c00")]))))
	    (mult:DI
	      (sign_extend:DI
		(vec_select:HI
		  (match_dup 1)
		  (parallel [(match_operand:SI 6 "imm_2_3_operand" " c02, c02, c03, c03")])))
	      (sign_extend:DI
		(vec_select:HI
		  (match_dup 2)
		  (parallel [(match_operand:SI 7 "imm_2_3_operand" " c02, c03, c03, c02")])))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "@
   smalbb\t%0, %1, %2
   smalbt\t%0, %1, %2
   smaltt\t%0, %1, %2
   smalbt\t%0, %2, %1"
  [(set_attr "type" "dsp64")])

;; SMALDA
(define_expand "smalda1"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" " r")
   (match_operand:RVPV2HI 3 "register_operand" " r")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smalda1_le (operands[0], operands[1], operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_insn "smalda1_le"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (sign_extend:DI
	    (plus:SI
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 2 "register_operand" " r")
				  (parallel [(const_int 1)])))
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 3 "register_operand" " r")
				  (parallel [(const_int 1)]))))
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_dup 2)
				  (parallel [(const_int 0)])))
		(sign_extend:SI (vec_select:HI
				  (match_dup 3)
				  (parallel [(const_int 0)]))))))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smalda\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; 64 Bit v_smalda
(define_insn "smalda64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (plus:DI
	    (sign_extend:DI
	      (plus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 3 "register_operand" " r")
				    (parallel [(const_int 0)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 1)]))))))
	    (sign_extend:DI
	      (plus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 2)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 3)])))))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "smalda\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; SMALXDA, SMALXDS
(define_expand "smalxda1"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" " r")
   (match_operand:RVPV2HI 3 "register_operand" " r")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smalxda1_le (operands[0], operands[1], operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_expand "smalxds1"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" " r")
   (match_operand:RVPV2HI 3 "register_operand" " r")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smalxds1_le (operands[0], operands[1], operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_insn "smalxd<add_sub>1_le"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (sign_extend:DI
	    (plus_minus:SI
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 2 "register_operand" " r")
				  (parallel [(const_int 1)])))
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 3 "register_operand" " r")
				  (parallel [(const_int 0)]))))
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_dup 2)
				  (parallel [(const_int 0)])))
		(sign_extend:SI (vec_select:HI
				  (match_dup 3)
				  (parallel [(const_int 1)]))))))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smalxd<add_sub>\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

(define_insn "smalxd<add_sub>64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (plus:DI
	    (sign_extend:DI
	      (plus_minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 3 "register_operand" " r")
				    (parallel [(const_int 0)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 1)]))))))
	    (sign_extend:DI
	      (plus_minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 2)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 3)])))))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "smalxd<add_sub>\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; SMALDS
(define_expand "smalds1"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" " r")
   (match_operand:RVPV2HI 3 "register_operand" " r")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smalds1_le (operands[0], operands[1], operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_insn "smalds1_le"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (sign_extend:DI
	    (minus:SI
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 2 "register_operand" " r")
				  (parallel [(const_int 1)])))
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 3 "register_operand" " r")
				  (parallel [(const_int 1)]))))
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_dup 2)
				  (parallel [(const_int 0)])))
		(sign_extend:SI (vec_select:HI
				  (match_dup 3)
				  (parallel [(const_int 0)]))))))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smalds\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

(define_insn "smalds64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (plus:DI
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 3 "register_operand" " r")
				    (parallel [(const_int 1)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 0)]))))))
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 3)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 2)])))))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "smalds\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; SMALDRS
(define_expand "smaldrs3"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" " r")
   (match_operand:RVPV2HI 3 "register_operand" " r")]
  "TARGET_ZPSF && !TARGET_64BIT"
{
  emit_insn (gen_smaldrs3_le (operands[0], operands[1], operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp64")])

(define_insn "smaldrs3_le"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (sign_extend:DI
	    (minus:SI
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 2 "register_operand" " r")
				  (parallel [(const_int 0)])))
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 3 "register_operand" " r")
				  (parallel [(const_int 0)]))))
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_dup 2)
				  (parallel [(const_int 1)])))
		(sign_extend:SI (vec_select:HI
				  (match_dup 3)
				  (parallel [(const_int 1)]))))))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smaldrs\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

(define_insn "smaldrs64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(plus:DI
	  (match_operand:DI 1 "register_operand"                           " 0")
	  (plus:DI
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 3 "register_operand" " r")
				    (parallel [(const_int 0)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 1)]))))))
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 2)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 3)])))))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "smaldrs\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; RV32P KMAR64, KMSR64
(define_insn "ssm<opcode>sidi4"
  [(set (match_operand:DI 0 "register_operand"       "=r")
	(ssat_op:DI
	  (mult:DI
	    (sign_extend:DI
	      (match_operand:SI 1 "register_operand" " r"))
	    (sign_extend:DI
	      (match_operand:SI 2 "register_operand"  " r")))
	  (match_operand:DI 3 "register_operand"      " 0")))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "km<add_sub>r64\t%0, %1, %2"
  [(set_attr "type"   "dsp64")
   (set_attr "mode"   "DI")])

;; RV32P UKMSR64, UKMAR64
(define_insn "usm<opcode>sidi4"
  [(set (match_operand:DI 0 "register_operand"       "=r")
	(usat_op:DI
	  (mult:DI
	    (zero_extend:DI
	      (match_operand:SI 1 "register_operand" " r"))
	    (zero_extend:DI
	      (match_operand:SI 2 "register_operand"  " r")))
	  (match_operand:DI 3 "register_operand"      " 0")))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "ukm<add_sub>r64\t%0, %1, %2"
  [(set_attr "type"   "dsp64")
   (set_attr "mode"   "DI")])

;; RV32P KMSR64, KMAR64
(define_insn "<u>m<opcode>sidi4"
  [(set (match_operand:DI 0 "register_operand"       "=r")
	(plus_minus:DI
	  (mult:DI
	    (any_extend:DI
	      (match_operand:SI 1 "register_operand" " r"))
	    (any_extend:DI
	      (match_operand:SI 2 "register_operand"  " r")))
	  (match_operand:DI 3 "register_operand"      " 0")))]
  "TARGET_ZPSF && !TARGET_64BIT && riscv_rvp_autovec_enable() &&TARGET_NUCLEI_DSP_AUTOVEC"
  "<su>m<add_sub>r64\t%0, %1, %2"
  [(set_attr "type"   "dsp64")
   (set_attr "mode"   "DI")])

(define_insn "rvp_smar64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_SMAR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smar64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "rvp_umar64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_UMAR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "umar64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; SMAR64, UMAR64
(define_insn "v<su>mar64_1"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(plus:DI (match_operand:DI 1 "register_operand"    " 0")
	  (plus:DI
	    (mult:DI
	      (any_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 2 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (any_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 3 "register_operand" " r")
		  (parallel [(const_int 0)]))))
	    (mult:DI
	      (any_extend:DI
		(vec_select:SI (match_dup 2) (parallel [(const_int 1)])))
	      (any_extend:DI
		(vec_select:SI (match_dup 3) (parallel [(const_int 1)])))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "<su>mar64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; [U]SMAX 8|16|32  and [U]SMIN 8|16|32
;; smax 8|16|32 and umax 8|16|32
(define_insn "<opcode><mode>3"
  [(set (match_operand:VECI 0 "register_operand"             "=r")
	(sumax:VECI (match_operand:VECI 1 "register_operand" " r")
		    (match_operand:VECI 2 "register_operand" " r")))]
  "TARGET_ZPN"
  "<opcode><bits>\t%0, %1, %2"
  [(set_attr "type" "simd")])

;; smin 8|16|32 and umin 8|16|32
(define_insn "<opcode><mode>3"
  [(set (match_operand:VECI 0 "register_operand"             "=r")
	(sumin:VECI (match_operand:VECI 1 "register_operand" " r")
		    (match_operand:VECI 2 "register_operand" " r")))]
  "TARGET_ZPN"
  "<opcode><bits>\t%0, %1, %2"
  [(set_attr "type" "simd")])

;; SMAQA, SMAQA.SU, UMAQA, UMAQA.SU
(define_expand "smaqa"
  [(match_operand:SI 0 "register_operand")
   (match_operand:SI 1 "register_operand")
   (match_operand:RVPV4QI 2 "register_operand")
   (match_operand:RVPV4QI 3 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_smaqaRVPV4QI (operands[0], operands[1],
			    operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "umaqa"
  [(match_operand:SI 0 "register_operand")
   (match_operand:SI 1 "register_operand")
   (match_operand:RVPV4QI 2 "register_operand")
   (match_operand:RVPV4QI 3 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_umaqaRVPV4QI (operands[0], operands[1],
			    operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "<su>maqaRVPV4QI"
  [(set (match_operand:SI 0 "register_operand"             "=r")
	(plus:SI (match_operand:SI 1 "register_operand"    " 0")
	  (plus:SI (plus:SI
	    (sign_extend:SI
	      (mult:HI
		(any_extend:HI
		  (vec_select:QI
		    (match_operand:RVPV4QI 2 "register_operand" "r")
		    (parallel [(const_int 0)])))
		(any_extend:HI
		  (vec_select:QI
		    (match_operand:RVPV4QI 3 "register_operand" "r")
		    (parallel [(const_int 0)])))))
	    (sign_extend:SI
	      (mult:HI
		(any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 1)])))
		(any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 1)]))))))
	  (plus:SI
	    (sign_extend:SI
	      (mult:HI
		(any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 2)])))
		(any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 2)])))))
	    (sign_extend:SI
	      (mult:HI
		(any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 3)])))
		(any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 3)])))))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "<su>maqa\t%0, %2, %3"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_expand "smaqa64"
  [(match_operand:RVPV2SI 0 "register_operand")
   (match_operand:RVPV2SI 1 "register_operand")
   (match_operand:RVPV8QI 2 "register_operand")
   (match_operand:RVPV8QI 3 "register_operand")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_smaqarvpv8qi (operands[0], operands[1],
			    operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "umaqa64"
  [(match_operand:RVPV2SI 0 "register_operand")
   (match_operand:RVPV2SI 1 "register_operand")
   (match_operand:RVPV8QI 2 "register_operand")
   (match_operand:RVPV8QI 3 "register_operand")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_umaqarvpv8qi (operands[0], operands[1],
			    operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "<su>maqarvpv8qi"
  [(set (match_operand:RVPV2SI 0 "register_operand"             "=r")
	(plus:RVPV2SI (match_operand:RVPV2SI 1 "register_operand"  " 0")
	  (vec_concat:RVPV2SI
	    (plus:SI
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI
		      (vec_select:QI
			(match_operand:RVPV8QI 2 "register_operand" "r")
			(parallel [(const_int 0)])))
		    (any_extend:HI
		      (vec_select:QI
			(match_operand:RVPV8QI 3 "register_operand" "r")
			(parallel [(const_int 0)])))))
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 1)])))
		    (any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 1)]))))))
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 2)])))
		    (any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 2)])))))
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 3)])))
		    (any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 3)])))))))
	    (plus:SI
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 4)])))
		    (any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 4)])))))
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 5)])))
		    (any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 5)]))))))
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 6)])))
		    (any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 6)])))))
		(sign_extend:SI
		  (mult:HI
		    (any_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 7)])))
		    (any_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 7)]))))))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "<su>maqa\t%0, %2, %3"
  [(set_attr "type" "dsp")
   (set_attr "mode" "RVPV2SI")])

(define_expand "sumaqa"
  [(match_operand:SI 0 "register_operand")
   (match_operand:SI 1 "register_operand")
   (match_operand:RVPV4QI 2 "register_operand")
   (match_operand:RVPV4QI 3 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_sumaqaRVPV4QI (operands[0], operands[1],
			     operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "sumaqaRVPV4QI"
  [(set (match_operand:SI 0 "register_operand"             "=r")
	(plus:SI (match_operand:SI 1 "register_operand"    " 0")
	  (plus:SI (plus:SI
	    (sign_extend:SI
	      (mult:HI
		(sign_extend:HI
		  (vec_select:QI
		    (match_operand:RVPV4QI 2 "register_operand" "r")
		    (parallel [(const_int 0)])))
		(zero_extend:HI
		  (vec_select:QI
		    (match_operand:RVPV4QI 3 "register_operand" "r")
		    (parallel [(const_int 0)])))))
	    (sign_extend:SI
	      (mult:HI
		(sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 1)])))
		(zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 1)]))))))

	  (plus:SI
	    (sign_extend:SI
	      (mult:HI
		(sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 2)])))
		(zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 2)])))))
	    (sign_extend:SI
	      (mult:HI
		(sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 3)])))
		(zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 3)])))))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "smaqa.su\t%0, %2, %3"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_expand "sumaqa64"
  [(match_operand:RVPV2SI 0 "register_operand")
   (match_operand:RVPV2SI 1 "register_operand")
   (match_operand:RVPV8QI 2 "register_operand")
   (match_operand:RVPV8QI 3 "register_operand")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_sumaqarvpv8qi (operands[0], operands[1],
			     operands[2], operands[3]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "sumaqarvpv8qi"
  [(set (match_operand:RVPV2SI 0 "register_operand"             "=r")
	(plus:RVPV2SI (match_operand:RVPV2SI 1 "register_operand"  " 0")
	  (vec_concat:RVPV2SI
	    (plus:SI
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI
		      (vec_select:QI
			(match_operand:RVPV8QI 2 "register_operand" "r")
			(parallel [(const_int 0)])))
		    (zero_extend:HI
		      (vec_select:QI
			(match_operand:RVPV8QI 3 "register_operand" "r")
			(parallel [(const_int 0)])))))
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 1)])))
		    (zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 1)]))))))
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 2)])))
		    (zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 2)])))))
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 3)])))
		    (zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 3)])))))))
	    (plus:SI
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 4)])))
		    (zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 4)])))))
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 5)])))
		    (zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 5)]))))))
	      (plus:SI
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 6)])))
		    (zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 6)])))))
		(sign_extend:SI
		  (mult:HI
		    (sign_extend:HI (vec_select:QI (match_dup 2) (parallel [(const_int 7)])))
		    (zero_extend:HI (vec_select:QI (match_dup 3) (parallel [(const_int 7)]))))))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smaqa.su\t%0, %2, %3"
  [(set_attr "type" "dsp")
   (set_attr "mode" "RVPV2SI")])

;; SMBB16, SMBT16, SMTT16
;; 32 BIT smbb16
(define_expand "smbb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV2HI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_mulhisi3v (operands[0], operands[1], operands[2],
			    GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smbt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV2HI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_mulhisi3v (operands[0], operands[1], operands[2],
			    GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smtt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:RVPV2HI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_mulhisi3v (operands[0], operands[1], operands[2],
			    GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "mulhisi3v"
  [(set (match_operand:SI 0 "register_operand"                  "=  r,   r,   r,   r")
	(mult:SI
	  (sign_extend:SI
	     (vec_select:HI
	       (match_operand:RVPV2HI 1 "register_operand"         "   r,   r,   r,   r")
	       (parallel [(match_operand:SI 3 "imm_0_1_operand" " c00, c00, c01, c01")])))
	  (sign_extend:SI (vec_select:HI
	       (match_operand:RVPV2HI 2 "register_operand"         "   r,   r,   r,   r")
	       (parallel [(match_operand:SI 4 "imm_0_1_operand" " c00, c01, c01, c00")])))))]
  "TARGET_ZPN && !TARGET_64BIT"
{
  const char *pats[] = { "smbb16\t%0, %1, %2",
			 "smbt16\t%0, %1, %2",
			 "smtt16\t%0, %1, %2",
			 "smbt16\t%0, %2, %1" };
  return pats[which_alternative];
}
  [(set_attr "type"   "simd")
   (set_attr "mode"   "SI")])

;; 64 Bit smbb16
(define_expand "smbb64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_mulrvpv2hirvpv2si3v (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (2), GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smbt64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_mulrvpv2hirvpv2si3v (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (2), GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smtt64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_mulrvpv2hirvpv2si3v (operands[0], operands[1], operands[2],
				GEN_INT (1), GEN_INT (3), GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "mulrvpv2hirvpv2si3v"
  [(set (match_operand:RVPV2SI 0 "register_operand" "=r, r, r")
        (mult:RVPV2SI
	 (sign_extend:RVPV2SI
	  (vec_select:RVPV2HI
	   (match_operand:RVPV4HI 1 "register_operand" "r, r, r")
	   (parallel [(match_operand:SI 3 "imm2u_operand" " c00, c00, c01")
		      (match_operand:SI 4 "imm2u_operand" " c02, c02, c03")])))
	 (sign_extend:RVPV2SI
	  (vec_select:RVPV2HI
	   (match_operand:RVPV4HI 2 "register_operand" "r, r, r")
	   (parallel [(match_operand:SI 5 "imm2u_operand" " c00, c01, c01")
		      (match_operand:SI 6 "imm2u_operand" " c02, c03, c03")])))))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
   smbb16\t%0, %1, %2
   smbt16\t%0, %1, %2
   smtt16\t%0, %1, %2"
  [(set_attr "type"   "simd")
   (set_attr "mode"   "DI")])

;; SMBB32, SMBT32, SMTT32
(define_expand "smbb32"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_mulsidi3v (operands[0], operands[1], operands[2],
			    GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "smbt32"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_mulsidi3v (operands[0], operands[1], operands[2],
			    GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "smtt32"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_mulsidi3v (operands[0], operands[1], operands[2],
			    GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "mulsidi3v"
  [(set (match_operand:DI 0 "register_operand"                  "=  r,   r,   r,   r")
	(mult:DI
	  (sign_extend:DI
	     (vec_select:SI
	       (match_operand:RVPV2SI 1 "register_operand"         "   r,   r,   r,   r")
	       (parallel [(match_operand:SI 3 "imm_0_1_operand" " c00, c00, c01, c01")])))
	  (sign_extend:DI (vec_select:SI
	       (match_operand:RVPV2SI 2 "register_operand"         "   r,   r,   r,   r")
	       (parallel [(match_operand:SI 4 "imm_0_1_operand" " c00, c01, c01, c00")])))))]
  "TARGET_ZPRV && TARGET_64BIT"
{
  const char *pats[] = { "smbb32\t%0, %1, %2",
			 "smbt32\t%0, %1, %2",
			 "smtt32\t%0, %1, %2",
			 "smbt32\t%0, %2, %1" };
  return pats[which_alternative];
}
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

;; SMDS, SMDRS, SMXDS
(define_insn "smds"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(minus:SI
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 1 "register_operand" " r")
			      (parallel [(const_int 1)])))
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 2 "register_operand" " r")
			      (parallel [(const_int 1)]))))
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:SI (vec_select:HI
			      (match_dup 2)
			      (parallel [(const_int 0)]))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "smds\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "smds64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                      "=r")
	(minus:RVPV2SI
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 1 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)]))))
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 1)
				(parallel [(const_int 0) (const_int 2)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smds\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "smdrs"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(minus:SI
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 1 "register_operand" " r")
			      (parallel [(const_int 0)])))
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 2 "register_operand" " r")
			      (parallel [(const_int 0)]))))
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_dup 1)
			      (parallel [(const_int 1)])))
	    (sign_extend:SI (vec_select:HI
			      (match_dup 2)
			      (parallel [(const_int 1)]))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "smdrs\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "smdrs64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                      "=r")
	(minus:RVPV2SI
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 1 "register_operand" "r")
				(parallel [(const_int 0) (const_int 2)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" "r")
				(parallel [(const_int 0) (const_int 2)]))))
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 1)
				(parallel [(const_int 1) (const_int 3)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 1) (const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smdrs\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "smxdsv"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(minus:SI
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 1 "register_operand" " r")
			      (parallel [(const_int 1)])))
	    (sign_extend:SI (vec_select:HI
			      (match_operand:RVPV2HI 2 "register_operand" " r")
			      (parallel [(const_int 0)]))))
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:SI (vec_select:HI
			      (match_dup 2)
			      (parallel [(const_int 1)]))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "smxds\t%0, %1, %2"
  [(set_attr "type" "simd")])

(define_insn "smxds64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                      "=r")
	(minus:RVPV2SI
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 1 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_operand:RVPV4HI 2 "register_operand" "r")
				(parallel [(const_int 0) (const_int 2)]))))
	  (mult:RVPV2SI
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 1)
				(parallel [(const_int 0) (const_int 2)])))
	    (sign_extend:RVPV2SI (vec_select:RVPV2HI
				(match_dup 2)
				(parallel [(const_int 1) (const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smxds\t%0, %1, %2"
  [(set_attr "type" "simd")])

;; SMDS32, SMDRS32, SMXDS32
(define_insn "smxds32"
  [(set (match_operand:DI 0 "register_operand"                         "=r")
	(minus:DI
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 1 "register_operand" " r")
			      (parallel [(const_int 1)])))
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 2 "register_operand" " r")
			      (parallel [(const_int 0)]))))
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:DI (vec_select:SI
			      (match_dup 2)
			      (parallel [(const_int 1)]))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "smxds32\t%0, %1, %2"
  [(set_attr "type" "dsp")])

(define_insn "smds32"
  [(set (match_operand:DI 0 "register_operand"                         "=r")
	(minus:DI
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 1 "register_operand" " r")
			      (parallel [(const_int 1)])))
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 2 "register_operand" " r")
			      (parallel [(const_int 1)]))))
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:DI (vec_select:SI
			      (match_dup 2)
			      (parallel [(const_int 0)]))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "smds32\t%0, %1, %2"
  [(set_attr "type" "dsp")])

(define_insn "smdrs32"
  [(set (match_operand:DI 0 "register_operand"                         "=r")
	(minus:DI
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 1 "register_operand" " r")
			      (parallel [(const_int 0)])))
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 2 "register_operand" " r")
			      (parallel [(const_int 0)]))))
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_dup 1)
			      (parallel [(const_int 1)])))
	    (sign_extend:DI (vec_select:SI
			      (match_dup 2)
			      (parallel [(const_int 1)]))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "smdrs32\t%0, %1, %2"
  [(set_attr "type" "dsp")])

;; SMMUL, SMMUL.u
;; RV32P smmul
;;(define_insn "smulsi3_highpart"
;;  [(set (match_operand:SI 0 "register_operand"                       "=r")
;;	(truncate:SI
;;	  (lshiftrt:DI
;;	    (mult:DI
;;	      (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
;;	      (sign_extend:DI (match_operand:SI 2 "register_operand" " r")))
;;	    (const_int 32))))]
;;  "TARGET_ZPN && !TARGET_64BIT"
;;  "smmul\t%0, %1, %2"
;;  [(set_attr "type" "simd")
;;   (set_attr "mode" "HI")])

(define_insn "smmul_round"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (lshiftrt:DI
	    (unspec:DI [(mult:DI
		  	  (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
			  (sign_extend:DI (match_operand:SI 2 "register_operand" " r")))]
		       UNSPEC_ROUND)
	    (const_int 32))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "smmul.u\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "HI")])

;; RV64P smmul
(define_insn "smulrvpv2si3_highpart"
  [(set (match_operand:RVPV2SI 0 "register_operand" "=r")
	(truncate:RVPV2SI
	  (lshiftrt:RVPV2DI
	    (mult:RVPV2DI (sign_extend:RVPV2DI (match_operand:RVPV2SI 1 "register_operand" " r"))
		       (sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r")))
	    (const_int 32))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smmul\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV2SI")])

(define_insn "smmulrvpv2si3_round"
  [(set (match_operand:RVPV2SI 0 "register_operand" "=r")
	(truncate:RVPV2SI
	  (lshiftrt:RVPV2DI
	    (unspec:RVPV2DI [(mult:RVPV2DI
			    (sign_extend:RVPV2DI (match_operand:RVPV2SI 1 "register_operand" " r"))
			    (sign_extend:RVPV2DI (match_operand:RVPV2SI 2 "register_operand" " r")))]
			  UNSPEC_ROUND)
	    (const_int 32))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smmul.u\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

;; SMMWB, SMMWT
(define_expand "smmwb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_1 (operands[0], operands[1], operands[2], GEN_INT (0)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smmwt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_1 (operands[0], operands[1], operands[2], GEN_INT (1)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "smulhisi3_highpart_1"
  [(set (match_operand:SI 0 "register_operand"                       "= r,   r")
	(truncate:SI
	  (lshiftrt:DI
	    (mult:DI
	      (sign_extend:DI (match_operand:SI 1 "register_operand" "  r,   r"))
	      (sign_extend:DI
	        (vec_select:HI
		  (match_operand:RVPV2HI 2 "register_operand"           "  r,   r")
		  (parallel [(match_operand:SI 3 "imm_0_1_operand"   "c00, c01")]))))
	    (const_int 16))))]
  "TARGET_ZPN && !TARGET_64BIT"
{
  const char *pats[] = { "smmwb\t%0, %1, %2",
			 "smmwt\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "simd")])

;; RV64P smmwb
(define_expand "smmwb64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_64 (operands[0], operands[1], operands[2],
					GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smmwt64"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_64 (operands[0], operands[1], operands[2],
					GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "smulhisi3_highpart_64"
  [(set (match_operand:RVPV2SI 0 "register_operand"                       "=r,    r")
	(vec_concat:RVPV2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI
		  (vec_select:SI
		    (match_operand:RVPV2SI 1 "register_operand"           "  r,   r")
		      (parallel [(const_int 0)])))
		(sign_extend:DI
		  (vec_select:HI
		    (match_operand:RVPV4HI 2 "register_operand"           "  r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand"   "c00, c01")]))))
	      (const_int 16)))
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI
		  (vec_select:SI
		    (match_dup 1)
		      (parallel [(const_int 1)])))
		(sign_extend:DI
		  (vec_select:HI
		    (match_dup 2)
		      (parallel [(match_operand:SI 4 "imm_2_3_operand"   "c02, c03")]))))
	      (const_int 16)))))]
  "TARGET_ZPN && TARGET_64BIT"
{
  const char *pats[] = { "smmwb\t%0, %1, %2",
			 "smmwt\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "simd")])

;; SMMWB.u, SMMWT.u
(define_expand "smmwb_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_smmw_round_internal (operands[0], operands[1], operands[2], GEN_INT (0)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smmwt_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:RVPV2HI 2 "register_operand" "")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_smmw_round_internal (operands[0], operands[1], operands[2], GEN_INT (1)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "smmw_round_internal"
  [(set (match_operand:SI 0 "register_operand"                          "=  r,   r")
	(truncate:SI
	  (lshiftrt:DI
	    (unspec:DI
	      [(mult:DI
		 (sign_extend:DI (match_operand:SI 1 "register_operand" "   r,   r"))
		 (sign_extend:DI
		   (vec_select:HI
		     (match_operand:RVPV2HI 2 "register_operand"           "   r,   r")
		     (parallel [(match_operand:SI 3 "imm_0_1_operand"   " c00, c01")]))))]
	      UNSPEC_ROUND)
	    (const_int 16))))]
  "TARGET_ZPN && !TARGET_64BIT"
{
  const char *pats[] = { "smmwb.u\t%0, %1, %2",
			 "smmwt.u\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "simd")])

(define_expand "smmwb64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_smmw64_round_internal (operands[0], operands[1], operands[2],
					GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "smmwt64_round"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_smmw64_round_internal (operands[0], operands[1], operands[2],
					GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "smmw64_round_internal"
  [(set (match_operand:RVPV2SI 0 "register_operand"                       "=r,    r")
	(vec_concat:RVPV2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
	        [(mult:DI
		  (sign_extend:DI
		    (vec_select:SI
		      (match_operand:RVPV2SI 1 "register_operand"           "  r,   r")
		      (parallel [(const_int 0)])))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_operand:RVPV4HI 2 "register_operand"           "  r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand"   "c00, c01")]))))]
	        UNSPEC_ROUND)
	      (const_int 16)))
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
		[(mult:DI
		  (sign_extend:DI
		    (vec_select:SI
		      (match_dup 1)
		      (parallel [(const_int 1)])))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_dup 2)
		      (parallel [(match_operand:SI 4 "imm_2_3_operand"   "c02, c03")]))))]
	        UNSPEC_ROUND)
	      (const_int 16)))))]
  "TARGET_ZPN && TARGET_64BIT"
{
  const char *pats[] = { "smmwb.u\t%0, %1, %2",
			 "smmwt.u\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "simd")])

;; SMSLDA, SMSLXDA
;; RV32P smslda
(define_insn "smslda1"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_operand"                         " 0")
	    (sign_extend:DI
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 2 "register_operand" " r")
				  (parallel [(const_int 1)])))
		(sign_extend:SI (vec_select:HI
				  (match_operand:RVPV2HI 3 "register_operand" " r")
				  (parallel [(const_int 1)]))))))
	  (sign_extend:DI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smslda\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; RV64P smslda
(define_insn "smslda64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_operand"                           " 0")
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 3 "register_operand" " r")
				    (parallel [(const_int 0)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 1)])))))))
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 2)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 3)]))))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smslda\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; RV32P smslxda
(define_insn "smslxda1"
  [(set (match_operand:DI 0 "register_operand"                               "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_operand"                           " 0")
	      (sign_extend:DI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV2HI 2 "register_operand" " r")
				    (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV2HI 3 "register_operand" " r")
				    (parallel [(const_int 0)]))))))
	  (sign_extend:DI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPN && !TARGET_64BIT"
  "smslxda\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

;; RV64P smslxda
(define_insn "smslxda64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_operand"                           " 0")
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:RVPV4HI 3 "register_operand" " r")
				    (parallel [(const_int 1)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 0)])))))))
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 3)]))))
		(mult:SI
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
		  (sign_extend:SI (vec_select:HI (match_dup 3) (parallel [(const_int 2)]))))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "smslxda\t%0, %2, %3"
  [(set_attr "type" "dsp64")])

(define_insn "rvp_smsr64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_SMSR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "smsr64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "rvp_umsr64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_UMSR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "umsr64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; SMSR64, UMSR64

(define_insn "v<su>msr64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(minus:DI
	  (minus:DI
	  (match_operand:DI 1 "register_operand"    " 0")
	    (mult:DI
	      (any_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 2 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (any_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 3 "register_operand" " r")
		  (parallel [(const_int 0)])))))
	    (mult:DI
	      (any_extend:DI
		(vec_select:SI (match_dup 2) (parallel [(const_int 1)])))
	      (any_extend:DI
		(vec_select:SI (match_dup 3) (parallel [(const_int 1)]))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "<su>msr64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; SMUL 8|16, SMULX 8|16, UMUL 8|16, UMULX 8|16
;; SMUL8
(define_insn "smul8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMUL8))]
  "TARGET_ZPSF"
  "smul8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; SMULX8
(define_insn "smulx8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMULX8))]
  "TARGET_ZPSF"
  "smulx8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; UMUL8
(define_insn "umul8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMUL8))]
  "TARGET_ZPSF"
  "umul8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; UMULX8
(define_insn "umulx8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMULX8))]
  "TARGET_ZPSF"
  "umulx8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; S|U MUL16
(define_insn "<su>mul16"
  [(set (match_operand:RVPV2SI 0 "register_operand"                             "=r")
	(mult:RVPV2SI (any_extend:RVPV2SI (match_operand:RVPV2HI 1 "register_operand" "%r"))
		   (any_extend:RVPV2SI (match_operand:RVPV2HI 2 "register_operand" " r"))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "<su>mul16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV2SI")])

(define_insn "smul16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMUL16))]
  "TARGET_ZPSF && TARGET_64BIT"
  "smul16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "umul16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMUL16))]
  "TARGET_ZPSF && TARGET_64BIT"
  "umul16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

;; S|U MULX16
(define_insn "<su>mulx16"
  [(set (match_operand:RVPV2SI 0 "register_operand"         "=r")
	(vec_merge:RVPV2SI
	  (vec_duplicate:RVPV2SI
	    (mult:SI
	      (any_extend:SI
		(vec_select:HI
		  (match_operand:RVPV2HI 1 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (any_extend:SI
		(vec_select:HI
		  (match_operand:RVPV2HI 2 "register_operand" " r")
		  (parallel [(const_int 1)])))))
	  (vec_duplicate:RVPV2SI
	    (mult:SI
	      (any_extend:SI
		(vec_select:HI
		  (match_dup 1)
		  (parallel [(const_int 1)])))
	      (any_extend:SI
		(vec_select:HI
		  (match_dup 2)
		  (parallel [(const_int 0)])))))
	  (const_int 1)))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "<su>mulx16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV2SI")])

;; RV64P
(define_insn "smulx16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMULX16))]
  "TARGET_ZPSF && TARGET_64BIT"
  "smulx16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

(define_insn "umulx16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMULX16))]
  "TARGET_ZPSF && TARGET_64BIT"
  "umulx16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

;; SRA[I] 8|16|32, SRL[I] 8|16|32, SLL[I] 8|16|32
;; SRA32, SRL32, SLL32
(define_insn "<rvp_optab>rvpv2si3"
  [(set (match_operand:RVPV2SI 0 "register_operand"                 "=  r, r")
	(any_shift:RVPV2SI (match_operand:RVPV2SI 1 "register_operand" "   r, r")
			(match_operand:SI   2  "rimm5u_operand"  " u05, r")))]
  "TARGET_ZPRV && TARGET_64BIT"
  "@
   <rvp_insn>i32\t%0, %1, %2
   <rvp_insn>32\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "RVPV2SI,  RVPV2SI")])

(define_expand "<shift><mode>3"
  [(set (match_operand:VHIX 0 "register_operand"                "")
	(any_shift:VHIX (match_operand:VHIX 1 "register_operand" "")
		       (match_operand:SI   2 "rimm4u_operand"  "")))]
  "TARGET_ZPN"
{
  if (operands[2] == const0_rtx)
    {
      emit_move_insn (operands[0], operands[1]);
      DONE;
    }
})

(define_insn "*riscv_lshr<mode>3"
  [(set (match_operand:VHIX 0 "register_operand"               "=  r, r")
	(lshiftrt:VHIX (match_operand:VHIX 1 "register_operand" "   r, r")
		      (match_operand:SI 2  "rimm4u_operand"   " u04, r")))]
  "TARGET_ZPN"
  "@
   srli16\t%0, %1, %2
   srl16\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "*riscv_ashl<mode>3"
  [(set (match_operand:VHIX 0 "register_operand"             "=  r, r")
	(ashift:VHIX (match_operand:VHIX 1 "register_operand" "   r, r")
		    (match_operand:SI 2  "rimm4u_operand"   " u04, r")))]
  "TARGET_ZPN"
  "@
   slli16\t%0, %1, %2
   sll16\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "*riscv_ashr<mode>3"
  [(set (match_operand:VHIX 0 "register_operand"               "=   r, r")
	(ashiftrt:VHIX (match_operand:VHIX 1 "register_operand" "    r, r")
		      (match_operand:SI 2  "rimm4u_operand"   " u04, r")))]
  "TARGET_ZPN"
  "@
   srai16\t%0, %1, %2
   sra16\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_expand "<shift><mode>3"
  [(set (match_operand:VQIX 0 "register_operand"                "")
	(any_shift:VQIX (match_operand:VQIX 1 "register_operand" "")
			(match_operand:SI 2 "rimm3u_operand" "")))]
  "TARGET_ZPN"
{
  if (operands[2] == const0_rtx)
    {
      emit_move_insn (operands[0], operands[1]);
      DONE;
    }
})

(define_insn "*riscv_ashr<mode>3"
  [(set (match_operand:VQIX 0 "register_operand"               "=  r, r")
	(ashiftrt:VQIX (match_operand:VQIX 1 "register_operand" "   r, r")
		       (match_operand:SI 2 "rimm3u_operand"   " u03, r")))]
  "TARGET_ZPN"
  "@
   srai8\t%0, %1, %2
   sra8\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "*riscv_lshr<mode>3"
  [(set (match_operand:VQIX 0 "register_operand"               "=  r, r")
	(lshiftrt:VQIX (match_operand:VQIX 1 "register_operand" "   r, r")
		       (match_operand:SI 2 "rimm3u_operand"   " u03, r")))]
  "TARGET_ZPN"
  "@
   srli8\t%0, %1, %2
   srl8\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "*riscv_ashl<mode>3"
  [(set (match_operand:VQIX 0 "register_operand"             "=  r, r")
	(ashift:VQIX (match_operand:VQIX 1 "register_operand" "   r, r")
		     (match_operand:SI 2   "rimm3u_operand" " u03, r")))]
  "TARGET_ZPN"
  "@
   slli8\t%0, %1, %2
   sll8\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

;; SRA[I] 8|16|32 .u
(define_insn "sra8_round<mode>"
  [(set (match_operand:VQIX 0 "register_operand"                            "=  r, r")
	(unspec:VQIX [(ashiftrt:VQIX (match_operand:VQIX 1 "register_operand" "   r, r")
				   (match_operand:SI 2  "rimm3u_operand"   " u03, r"))]
		      UNSPEC_ROUND))]
  "TARGET_ZPN"
  "@
   srai8.u\t%0, %1, %2
   sra8.u\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "sra16_round<mode>"
  [(set (match_operand:VHIX 0 "register_operand"                            "=  r, r")
	(unspec:VHIX [(ashiftrt:VHIX (match_operand:VHIX 1 "register_operand" "   r, r")
				   (match_operand:SI 2  "rimm4u_operand"   " u04, r"))]
		     UNSPEC_ROUND))]
  "TARGET_ZPN"
  "@
   srai16.u\t%0, %1, %2
   sra16.u\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "sra32_round"
  [(set (match_operand:RVPV2SI 0 "register_operand"                              "=  r, r")
	(unspec:RVPV2SI [(ashiftrt:RVPV2SI (match_operand:RVPV2SI 1 "register_operand" "   r, r")
				     (match_operand:SI 2   "rimm5u_operand"   " u05, r"))]
		       UNSPEC_ROUND))]
  "TARGET_ZPRV && TARGET_64BIT"
  "@
   srai32.u\t%0, %1, %2
   sra32.u\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "RVPV2SI,  RVPV2SI")])

;; SRL[I] 8|16|32 .u
(define_insn "srl8_round<mode>"
  [(set (match_operand:VQIX 0 "register_operand"                            "=  r, r")
	(unspec:VQIX [(lshiftrt:VQIX (match_operand:VQIX 1 "register_operand" "   r, r")
				   (match_operand:SI 2  "rimm3u_operand"   " u03, r"))]
		      UNSPEC_ROUND))]
  "TARGET_ZPN"
  "@
   srli8.u\t%0, %1, %2
   srl8.u\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "srl16_round<mode>"
  [(set (match_operand:VHIX 0 "register_operand"                            "=  r, r")
	(unspec:VHIX [(lshiftrt:VHIX (match_operand:VHIX 1 "register_operand" "   r, r")
				   (match_operand:SI 2  "rimm4u_operand"   " u04, r"))]
		     UNSPEC_ROUND))]
  "TARGET_ZPN"
  "@
   srli16.u\t%0, %1, %2
   srl16.u\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "srl32_round"
  [(set (match_operand:RVPV2SI 0 "register_operand"                              "=  r, r")
	(unspec:RVPV2SI [(lshiftrt:RVPV2SI (match_operand:RVPV2SI 1 "register_operand" "   r, r")
				     (match_operand:SI 2   "rimm5u_operand"   " u05, r"))]
		       UNSPEC_ROUND))]
  "TARGET_ZPRV && TARGET_64BIT"
  "@
   srli32.u\t%0, %1, %2
   srl32.u\t%0, %1, %2"
  [(set_attr "type" "simd, simd")
   (set_attr "mode" "RVPV2SI,  RVPV2SI")])

(define_insn "sraiw_u"
  [(set (match_operand:SI 0 "register_operand"             "=  r")
	(unspec:SI [(match_operand:SI 1 "register_operand" "   r")
		    (match_operand:SI 2 "imm5u_operand"    " u05")]
		    UNSPEC_ROUND64))]
  "TARGET_ZPRV && TARGET_64BIT"
  "sraiw.u\t%0, %1, %2"
  [(set_attr "type"   "dsp")
   (set_attr "mode"   "DI")])

(define_insn "sraiu"
  [(set (match_operand:SI 0 "register_operand"                          "=  r, r")
	(unspec:SI [(ashiftrt:SI (match_operand:SI 1 "register_operand" "   r, r")
				 (match_operand:SI 2 "rimm5u_operand"   " u05, r"))]
		    UNSPEC_ROUND))]
  "TARGET_ZPN && !TARGET_64BIT"
  "@
   srai.u\t%0, %1, %2
   sra.u\t%0, %1, %2"
  [(set_attr "type"   "simd")
   (set_attr "mode"   "SI")])

(define_insn "sraiu64"
  [(set (match_operand:DI 0 "register_operand"                          "=  r, r")
	(unspec:DI [(ashiftrt:DI (match_operand:DI 1 "register_operand" "   r, r")
				 (match_operand:DI 2 "rimm6u_operand"   " u06, r"))]
		    UNSPEC_ROUND))]
  "TARGET_ZPN && TARGET_64BIT"
  "@
   srai.u\t%0, %1, %2
   sra.u\t%0, %1, %2"
  [(set_attr "type"   "simd")
   (set_attr "mode"   "DI")])

;; STAS 16|32
;; stasrvpv2hi for stas15 in RV32P
;; stasrvpv2si for stas32
(define_expand "stas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_stas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "stas<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "stas<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

;; STAS16 in RV64P
(define_expand "stas16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_stas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "stas16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (minus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				     (parallel [(const_int 0)]))
		      (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				     (parallel [(const_int 0)])))
	    (plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
		     (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:RVPV2HI
	    (minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "stas16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; STSA 16|32
(define_expand "stsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_stsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "stsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "stsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

(define_expand "stsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_stsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "stsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (plus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				    (parallel [(const_int 0)]))
		     (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
	    (minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:RVPV2HI
	    (plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
		     (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
		       (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "stsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; SUNPKD810, ZUNPKD810
(define_insn "<zs>unpkd810_imp"
  [(set (match_operand:RVPV2HI 0 "register_operand"                     "=r")
	(vec_merge:RVPV2HI
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:RVPV4QI 1 "register_operand"             " r")
		(parallel [(const_int 1)]))))
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 0)]))))
	  (const_int 2)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "<zs>unpkd810\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV2HI")])

;; SUNPKD810 in RV32P
(define_expand "sunpkd810"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd810_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "zunpkd810"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd810_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

;; ZUNPKD810 and SUNPKD810 in RV32P
(define_insn "<zs>unpkd810_64"
  [(set (match_operand:RVPV4HI 0 "register_operand"                    "=r")
	(vec_select:RVPV4HI
	  (any_extend:RVPV8HI (match_operand:RVPV8QI 1 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 1)
		     (const_int 4) (const_int 5)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "<zs>unpkd810\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV4HI")])

;; SUNPKD820, ZUNPKD820
(define_insn "<zs>unpkd820_imp"
  [(set (match_operand:RVPV2HI 0 "register_operand"                     "=r")
	(vec_merge:RVPV2HI
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:RVPV4QI 1 "register_operand"             " r")
		(parallel [(const_int 2)]))))
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 0)]))))
	  (const_int 2)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "<zs>unpkd820\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV2HI")])

;; ZUNPKD820 RV32P
(define_expand "zunpkd820"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd820_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

;; SUNPKD820 RV32P
(define_expand "sunpkd820"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd820_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

;; SUNPKD820, ZUNPKD820 in RV64P
(define_insn "<zs>unpkd820_64"
  [(set (match_operand:RVPV4HI 0 "register_operand"                    "=r")
	(vec_select:RVPV4HI
	  (any_extend:RVPV8HI (match_operand:RVPV8QI 1 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 2)
		     (const_int 4) (const_int 6)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "<zs>unpkd820\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV4HI")])

;; SUNPKD830, ZUNPKD830
;; RV32P
(define_insn "<zs>unpkd830_imp"
  [(set (match_operand:RVPV2HI 0 "register_operand"                     "=r")
	(vec_merge:RVPV2HI
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:RVPV4QI 1 "register_operand"             " r")
		(parallel [(const_int 3)]))))
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 0)]))))
	  (const_int 2)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "<zs>unpkd830\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV2HI")])

(define_expand "sunpkd830"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd830_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "zunpkd830"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd830_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

;; RV64P
(define_insn "<zs>unpkd830_64"
  [(set (match_operand:RVPV4HI 0 "register_operand"                    "=r")
	(vec_select:RVPV4HI
	  (any_extend:RVPV8HI (match_operand:RVPV8QI 1 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 3)
		     (const_int 4) (const_int 7)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "<zs>unpkd830\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV4HI")])

;; SUNPKD831, ZUNPKD831
;; RV32P
(define_expand "sunpkd831"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd831_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "zunpkd831"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd831_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "<zs>unpkd831_imp"
  [(set (match_operand:RVPV2HI 0 "register_operand"                     "=r")
	(vec_merge:RVPV2HI
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:RVPV4QI 1 "register_operand"             " r")
		(parallel [(const_int 3)]))))
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "<zs>unpkd831\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV2HI")])

;; RV64P
(define_insn "<zs>unpkd831_64"
  [(set (match_operand:RVPV4HI 0 "register_operand"                    "=r")
	(vec_select:RVPV4HI
	  (any_extend:RVPV8HI (match_operand:RVPV8QI 1 "register_operand" "r"))
	  (parallel [(const_int 1) (const_int 3)
		     (const_int 5) (const_int 7)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "<zs>unpkd831\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV4HI")])

;; SUNPKD832, ZUNPKD832
;; RV32P
(define_expand "sunpkd832"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd832_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_expand "zunpkd832"
  [(match_operand:RVPV2HI 0 "register_operand")
   (match_operand:RVPV4QI 1 "register_operand")]
  "TARGET_ZPN && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd832_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dsp")])

(define_insn "<zs>unpkd832_imp"
  [(set (match_operand:RVPV2HI 0 "register_operand"                     "=r")
	(vec_merge:RVPV2HI
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:RVPV4QI 1 "register_operand"             " r")
		(parallel [(const_int 3)]))))
	  (vec_duplicate:RVPV2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 2)]))))
	  (const_int 2)))]
  "TARGET_ZPN && !TARGET_64BIT"
  "<zs>unpkd832\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV2HI")])

;; RV64P
(define_insn "<zs>unpkd832_64"
  [(set (match_operand:RVPV4HI 0 "register_operand"                    "=r")
	(vec_select:RVPV4HI
	  (any_extend:RVPV8HI (match_operand:RVPV8QI 1 "register_operand" "r"))
	  (parallel [(const_int 2) (const_int 3)
		     (const_int 6) (const_int 7)])))]
  "TARGET_ZPN && TARGET_64BIT"
  "<zs>unpkd832\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode"  "RVPV4HI")])

;; SWAP 8|16
;; SWAP8
(define_insn "bswap8"
  [(set (match_operand:RVPV4QI 0 "register_operand" "=r")
	(unspec:RVPV4QI [(match_operand:RVPV4QI 1 "register_operand" "r")] UNSPEC_BSWAP))]
  "TARGET_ZPN"
  "swap8\t%0, %1"
  [(set_attr "type"  "dsp")
   (set_attr "mode"  "RVPV4QI")])

(define_insn "bswap8_64"
  [(set (match_operand:RVPV8QI 0 "register_operand" "=r")
	(unspec:RVPV8QI [(match_operand:RVPV8QI 1 "register_operand" "r")] UNSPEC_BSWAP))]
  "TARGET_ZPN"
  "swap8\t%0, %1"
  [(set_attr "type"  "dsp")
   (set_attr "mode"  "RVPV8QI")])

;; UCLIP8|16|32
(define_insn "uclip8<mode>"
  [(set (match_operand:VQIX 0 "register_operand"               "=  r")
	(unspec:VQIX [(match_operand:VQIX 1 "register_operand"  "   r")
		     (match_operand:SI 2 "imm3u_operand"      " u03")]
		     UNSPEC_UCLIP))]
  "TARGET_ZPN"
  "uclip8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "uclip16<mode>"
  [(set (match_operand:VHIX 0 "register_operand"               "=   r")
	(unspec:VHIX [(match_operand:VHIX 1 "register_operand"  "    r")
		      (match_operand:SI 2 "imm4u_operand"     " u04")]
		     UNSPEC_UCLIP))]
  "TARGET_ZPN"
  "uclip16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

(define_insn "uclip32<VD_SI:mode><X:mode>"
  [(set (match_operand:VD_SI 0 "register_operand" "=r")
	(unspec:VD_SI [(match_operand:VD_SI 1 "register_operand" "r")
		       (match_operand:X 2 "immediate_operand" "i")] UNSPEC_UCLIP_OV))]
  "TARGET_ZPN"
  "uclip32\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<VD_SI:MODE>")])

;; UCMPLE8|16
(define_insn "ucmple<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(leu:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				  (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_ZPN"
  "ucmple<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "<MODE>")])

;; UCMPLT8|16
(define_insn "ucmplt<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(ltu:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				  (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_ZPN"
  "ucmplt<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "SI")])

(define_insn "rvp_ukmar64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_UKMAR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "ukmar64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; RV64P ukmar64
(define_insn "vukmar64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(us_plus:DI (match_operand:DI 1 "register_operand"    " 0")
	  (plus:DI
	    (mult:DI
	      (zero_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 2 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (zero_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 3 "register_operand" " r")
		  (parallel [(const_int 0)]))))
	    (mult:DI
	      (sign_extend:DI
		(vec_select:SI (match_dup 2) (parallel [(const_int 1)])))
	      (sign_extend:DI
		(vec_select:SI (match_dup 3) (parallel [(const_int 1)])))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "ukmar64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "rvp_ukmsr64"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		    (match_operand:SI 2 "register_operand" " r")
			(match_operand:SI 3 "register_operand" " r")]
		    UNSPEC_UKMSR64))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "ukmsr64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; RV64P ukmsr64
(define_insn "vukmsr64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(us_minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_operand"    " 0")
	    (mult:DI
	      (zero_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 2 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (zero_extend:DI
		(vec_select:SI
		  (match_operand:RVPV2SI 3 "register_operand" " r")
		  (parallel [(const_int 0)])))))
	    (mult:DI
	      (sign_extend:DI
		(vec_select:SI (match_dup 2) (parallel [(const_int 1)])))
	      (sign_extend:DI
		(vec_select:SI (match_dup 3) (parallel [(const_int 1)]))))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "ukmsr64\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;; UKSTAS 16|32
;; ukstasrvpv2si for ukstas32
;; ukstasrvpv2hi for ukstas16 in RV32P
(define_expand "ukstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_ukstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukstas<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (us_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (us_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "ukstas<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

;; RV64P ukstas16
(define_expand "ukstas16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_ukstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukstas16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (us_minus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
					(parallel [(const_int 0)])))
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:RVPV2HI
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (us_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "ukstas16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; UKSTSA 16|32
;; ukstsarvpv2si for ukstsa16
;; ukstsarvpv2si for ukstsa32
(define_expand "ukstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_ukstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukstsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"         "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (us_minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" " r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:VSHI
	    (us_plus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_dup 1)
		(parallel [(const_int 1)]))
	      (vec_select:<VNHALF>
		(match_dup 2)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "ukstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

;; RV64P ukstsa16
(define_expand "ukstsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_ukstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "ukstsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (us_plus:HI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
				       (parallel [(const_int 0)])))
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:RVPV2HI
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (us_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "ukstsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; URSTAS 16|32
;; urstasrvpv2si for urstas32
;; urstasrvpv2hi for urstas16 in RV32P
(define_expand "urstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_urstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urstas<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
		(minus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 0)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 1)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 1)))]
  "TARGET_ZPN"
  "urstas<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

;; urstas16 in RV64P
(define_expand "urstas16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_urstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urstas16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "urstas16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; URSTSA 16|32
(define_expand "urstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_ZPN"
{
  emit_insn (gen_urstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urstsa<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand"           "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
	        (minus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" " r")
		      (parallel [(const_int 0)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" " r")
		      (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
		(plus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 1)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 2)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 2)))]
  "TARGET_ZPN"
  "urstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "simd")]
)

;; urstsa16 in RV64P
(define_expand "urstsa16_64"
  [(match_operand:RVPV4HI 0 "register_operand" "")
   (match_operand:RVPV4HI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")]
  "TARGET_ZPN && TARGET_64BIT"
{
  emit_insn (gen_urstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "urstsa16_64_le"
  [(set (match_operand:RVPV4HI 0 "register_operand"         "=r")
	(vec_concat:RVPV4HI
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:RVPV4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:RVPV2HI
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 2)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 3)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))
		(const_int 1))))))]
  "TARGET_ZPN && TARGET_64BIT"
  "urstsa16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; WEXTI, WEXT
(define_insn "wext"
  [(set (match_operand:SI 0 "register_operand"     "=r,  r")
	(truncate:SI
	  (ashiftrt:DI
	    (match_operand:DI 1 "register_operand" " r,  r")
	    (match_operand:SI 2 "rimm5u_operand"   " r,u05"))))]
  "TARGET_ZPSF && !TARGET_64BIT"
  "@
   wext\t%0, %1, %2
   wexti\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "SI")])

(define_insn "wext64"
  [(set (match_operand:DI 0 "register_operand"     "=r,  r")
	(sign_extend:DI
	  (truncate:SI
	    (ashiftrt:DI
	      (match_operand:DI 1 "register_operand" " r,  r")
	      (match_operand:DI 2 "rimm5u_operand"   " r,u05")))))]
  "TARGET_ZPSF && TARGET_64BIT"
  "@
   wext\t%0, %1, %2
   wexti\t%0, %1, %2"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

;; KDMBB16, KDMBT16, KDMTT16

(define_insn "kdmbb16"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" "r")
		      (match_operand:RVPV4HI 2 "register_operand" "r")] UNSPEC_KDMBB16))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kdmbb16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_insn "kdmbt16"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" "r")
		      (match_operand:RVPV4HI 2 "register_operand" "r")] UNSPEC_KDMBT16))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kdmbt16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_insn "kdmtt16"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" "r")
		      (match_operand:RVPV4HI 2 "register_operand" "r")] UNSPEC_KDMTT16))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kdmtt16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; KDMABB16, KDMABT16, KDMATT16
(define_expand "kdmabb16"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_vkdma_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (0), GEN_INT (2),
				 GEN_INT (2), operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kdmabt16"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_vkdma_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (1), GEN_INT (2),
				 GEN_INT (3), operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kdmatt16"
  [(match_operand:RVPV2SI 0 "register_operand" "")
   (match_operand:RVPV2SI 1 "register_operand" "")
   (match_operand:RVPV4HI 2 "register_operand" "")
   (match_operand:RVPV4HI 3 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_vkdma_internal (operands[0], operands[2], operands[3],
				 GEN_INT (1), GEN_INT (1), GEN_INT (3),
				 GEN_INT (3), operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "vkdma_internal"
  [(set (match_operand:RVPV2SI 0 "register_operand"                      "=   r,   r,   r,   r")
	(ss_plus:RVPV2SI
	  (vec_concat:RVPV2SI
	    (ashift:SI
	      (mult:SI
		(sign_extend:SI
		  (vec_select:HI
		    (match_operand:RVPV4HI 1 "register_operand"          "   r,   r,   r,   r")
		    (parallel [(match_operand:SI 3 "imm_0_1_operand"  " c00, c00, c01, c01")])))
		(sign_extend:SI
		  (vec_select:HI
		    (match_operand:RVPV4HI 2 "register_operand"          "   r,   r,   r,   r")
		    (parallel [(match_operand:SI 4 "imm_0_1_operand"  " c00, c01, c01, c00")]))))
	      (const_int 1))
	    (ashift:SI
	      (mult:SI
		(sign_extend:SI
		  (vec_select:HI
		    (match_dup 1)
		    (parallel [(match_operand:SI 5 "imm_2_3_operand"  " c02, c02, c03, c03")])))
		(sign_extend:SI
		  (vec_select:HI
		    (match_dup 2)
		    (parallel [(match_operand:SI 6 "imm_2_3_operand"  " c02, c03, c03, c02")]))))
	      (const_int 1)))
	  (match_operand:RVPV2SI 7 "register_operand"                    "   0,   0,   0,   0")))]
  "TARGET_ZPRV && TARGET_64BIT"
  "@
   kdmabb16\t%0, %1, %2
   kdmabt16\t%0, %1, %2
   kdmatt16\t%0, %1, %2
   kdmabt16\t%0, %2, %1"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV2SI")])

;; KHMBB16, KHMBT16, KHMTT16

(define_insn "khmbb16"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" "r")
		      (match_operand:RVPV4HI 2 "register_operand" "r")] UNSPEC_KHMBB16))]
  "TARGET_ZPRV && TARGET_64BIT"
  "khmbb16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_insn "khmbt16"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" "r")
		      (match_operand:RVPV4HI 2 "register_operand" "r")] UNSPEC_KHMBT16))]
  "TARGET_ZPRV && TARGET_64BIT"
  "khmbt16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

(define_insn "khmtt16"
  [(set (match_operand:RVPV4HI 0 "register_operand" "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" "r")
		      (match_operand:RVPV4HI 2 "register_operand" "r")] UNSPEC_KHMTT16))]
  "TARGET_ZPRV && TARGET_64BIT"
  "khmtt16\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV4HI")])

;; KMABB32, KMABT32, KMATT32
(define_expand "kmabb32"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV2SI 3 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_kma32_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (0),
				 operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmabt32"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV2SI 3 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_kma32_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (1),
				 operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_expand "kmatt32"
  [(match_operand:DI 0 "register_operand" "")
   (match_operand:DI 1 "register_operand" "")
   (match_operand:RVPV2SI 2 "register_operand" "")
   (match_operand:RVPV2SI 3 "register_operand" "")]
  "TARGET_ZPRV && TARGET_64BIT"
{
  emit_insn (gen_kma32_internal (operands[0], operands[2], operands[3],
				 GEN_INT (1), GEN_INT (1),
				 operands[1]));
  DONE;
}
[(set_attr "type" "simd")])

(define_insn "kma32_internal"
  [(set (match_operand:DI 0 "register_operand"                   "=   r,   r,   r,   r")
	(ss_plus:DI
	  (mult:DI
	    (sign_extend:DI
	      (vec_select:SI
		(match_operand:RVPV2SI 1 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 3 "imm_0_1_operand" " c00, c00, c01, c01")])))
	    (sign_extend:DI
	      (vec_select:SI
	        (match_operand:RVPV2SI 2 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 4 "imm_0_1_operand" " c00, c01, c01, c00")]))))
	  (match_operand:DI 5 "register_operand"                 "   0,   0,   0,   0")))]
  "TARGET_ZPRV && TARGET_64BIT"
  "@
  kmabb32\t%0, %1, %2
  kmabt32\t%0, %1, %2
  kmatt32\t%0, %1, %2
  kmabt32\t%0, %2, %1"
  [(set_attr "type" "simd")
   (set_attr "mode" "DI")])

;; KMADA32, KMAXDA32
(define_insn "kmada32"
  [(set (match_operand:DI 0 "register_operand"                           "=r")
	(ss_plus:DI
	  (match_operand:DI 1 "register_operand"                         " 0")
	  (ss_plus:DI
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:DI (vec_select:SI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmada32\t%0, %2, %3"
  [(set_attr "type" "dsp")])

(define_insn "kmaxda32"
  [(set (match_operand:DI 0 "register_operand"                           "=r")
	(ss_plus:DI
	  (match_operand:DI 1 "register_operand"                         " 0")
	  (ss_plus:DI
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:DI (vec_select:SI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmaxda32\t%0, %2, %3"
  [(set_attr "type" "dsp")])

;; KMDA32, KMXDA32
(define_insn "kmda32"
  [(set (match_operand:DI 0 "register_operand"                         "=r")
	(ss_plus:DI
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 1 "register_operand" "r")
			      (parallel [(const_int 1)])))
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 2 "register_operand" "r")
			      (parallel [(const_int 1)]))))
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:DI (vec_select:SI
			      (match_dup 2)
			      (parallel [(const_int 0)]))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmda32\t%0, %1, %2"
  [(set_attr "type" "dsp")])

(define_insn "kmxda32"
  [(set (match_operand:DI 0 "register_operand"                        "=r")
	(ss_plus:DI
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 1 "register_operand" "r")
			      (parallel [(const_int 1)])))
	    (sign_extend:DI (vec_select:SI
			      (match_operand:RVPV2SI 2 "register_operand" "r")
			      (parallel [(const_int 0)]))))
	  (mult:DI
	    (sign_extend:DI (vec_select:SI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:DI (vec_select:SI
			      (match_dup 2)
			      (parallel [(const_int 1)]))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmxda32\t%0, %1, %2"
  [(set_attr "type" "dsp")])

;; KMADS32, KMADRS32, KMAXDS32
(define_insn "kmads32"
  [(set (match_operand:DI 0 "register_operand"                           "=r")
	(ss_plus:DI
	  (match_operand:DI 1 "register_operand"                         " 0")
	  (ss_minus:DI
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:DI (vec_select:SI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmads32\t%0, %2, %3"
  [(set_attr "type" "dsp")])

(define_insn "kmadrs32"
  [(set (match_operand:DI 0 "register_operand"                           "=r")
	(ss_plus:DI
	  (match_operand:DI 1 "register_operand"                         " 0")
	  (ss_minus:DI
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 2 "register_operand" " r")
				(parallel [(const_int 0)])))
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_dup 2)
				(parallel [(const_int 1)])))
	      (sign_extend:DI (vec_select:SI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmadrs32\t%0, %2, %3"
  [(set_attr "type" "dsp")])

(define_insn "kmaxds32"
  [(set (match_operand:DI 0 "register_operand"                           "=r")
	(ss_plus:DI
	  (match_operand:DI 1 "register_operand"                         " 0")
	  (ss_minus:DI
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:DI (vec_select:SI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmaxds32\t%0, %2, %3"
  [(set_attr "type" "dsp")])

;; KMSDA32, KMSXDA32
(define_insn "kmsda32"
  [(set (match_operand:DI 0 "register_operand"                           "=r")
	(ss_minus:DI
	  (match_operand:DI 1 "register_operand"                         " 0")
	  (ss_minus:DI
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:DI (vec_select:SI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmsda32\t%0, %2, %3"
  [(set_attr "type" "dsp")])

(define_insn "kmsxda32"
  [(set (match_operand:DI 0 "register_operand"                           "=r")
	(ss_minus:DI
	  (match_operand:DI 1 "register_operand"                         " 0")
	  (ss_minus:DI
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:DI (vec_select:SI
				(match_operand:RVPV2SI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:DI
	      (sign_extend:DI (vec_select:SI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:DI (vec_select:SI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_ZPRV && TARGET_64BIT"
  "kmsxda32\t%0, %2, %3"
  [(set_attr "type" "dsp")])

;; KSLL32, KSLLI32
(define_insn "ksll32"
  [(set (match_operand:RVPV2SI 0 "register_operand"                 "=  r, r")
	(ss_ashift:RVPV2SI (match_operand:RVPV2SI 1 "register_operand" "   r, r")
			(match_operand:SI 2   "rimm5u_operand"   " u05, r")))]
  "TARGET_ZPRV && TARGET_64BIT"
  "@
   kslli32\t%0, %1, %2
   ksll32\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV2SI")])

;; move pattern
(define_expand "mov<mode>"
  [(set (match_operand:VPMOVE 0 "")
	(match_operand:VPMOVE 1 ""))]
  "TARGET_ZPN"
{
  if (riscv_legitimize_move (<MODE>mode, operands[0], operands[1]))
    DONE;
})

(define_insn "*mov<mode>_internal"
  [(set (match_operand:VPMOVE 0 "nonimmediate_operand" "=r,r,r, m,  *f,*f,*r,*m")
	(match_operand:VPMOVE 1 "move_operand"         " r,T,m,rJ,*r*J,*m,*f,*f"))]
  "(register_operand (operands[0], <MODE>mode)
    || reg_or_0_operand (operands[1], <MODE>mode))
   && TARGET_ZPN"
  { return riscv_output_move (operands[0], operands[1]); }
  [(set_attr "move_type" "move,const,load,store,mtc,fpload,mfc,fpstore")
   (set_attr "mode" "<MODE>")])

(define_expand "movrvpv2si"
  [(set (match_operand:RVPV2SI 0 "")
	(match_operand:RVPV2SI 1 ""))]
  "TARGET_ZPN "
{
  if (riscv_legitimize_move (RVPV2SImode, operands[0], operands[1]))
    DONE;
})

(define_insn "*movrvpv2si_64bit"
  [(set (match_operand:RVPV2SI 0 "nonimmediate_operand" "=r,r,r, m,  *f,*f,*r,*f,*m")
	(match_operand:RVPV2SI 1 "move_operand"         " r,T,m,rJ,*r*J,*m,*f,*f,*f"))]
  "TARGET_ZPN
   && (register_operand (operands[0], RVPV2SImode)
       || reg_or_0_operand (operands[1], RVPV2SImode))"
  { return riscv_output_move (operands[0], operands[1]); }
  [(set_attr "move_type" "move,const,load,store,mtc,fpload,mfc,fmove,fpstore")
   (set_attr "mode" "RVPV2SI")])

;;Nuclei custom dsp N1
(define_insn "dsp_dkhmdi3"
  [(set (match_operand:DI 0 "register_operand"              "=r")
  	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		    (match_operand:DI 2 "register_operand" " r")]
		    UNSPEC_DKHM8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkhm8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkhmdi3"
	[(set (match_operand:RVPV8QI 0 "register_operand"               "=r")
	(unspec:RVPV8QI [(match_operand:RVPV8QI 1 "register_operand" " r")
		     (match_operand:RVPV8QI 2 "register_operand" " r")]
			 UNSPEC_DKHM8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkhm8\t%0, %1, %2"
  [(set_attr "type" "simd")
   (set_attr "mode" "RVPV8QI")])

(define_insn "dsp_dkhmsi3"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKHM16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkhm16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkhmsi3"
	[(set (match_operand:RVPV4HI 0 "register_operand"               "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" " r")
		     (match_operand:RVPV4HI 2 "register_operand" " r")]
			 UNSPEC_DKHM16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkhm16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV4HI")])

;; dkslra8 dkslra16

(define_insn "dsp_dkabsdi3"
  [(set (match_operand:DI 0 "register_operand" "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" "r")]
		UNSPEC_DKABS8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkabs8\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkabsdi3"
  [(set (match_operand:RVPV8QI 0 "register_operand" "=r")
	(unspec:RVPV8QI [(match_operand:RVPV8QI 1 "register_operand" "r")]
		UNSPEC_DKABS8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkabs8\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV8QI")])

(define_insn "dsp_dkabssi3"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DKABS16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkabs16\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkabssi3"
	[(set (match_operand:RVPV4HI 0 "register_operand"               "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" " r")]
			 UNSPEC_DKABS16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkabs16\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV4HI")])

;; dkslra8 dkslra16
(define_insn "dsp_dkslradi3"
	[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:SI 2 "register_operand" " r")]
			 UNSPEC_DKSLRA8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkslra8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkslradi3"
	[(set (match_operand:RVPV8QI 0 "register_operand"               "=r")
	(unspec:RVPV8QI [(match_operand:RVPV8QI 1 "register_operand" " r")
		     (match_operand:SI 2 "register_operand" " r")]
			 UNSPEC_DKSLRA8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkslra8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV8QI")])

(define_insn "dsp_dkslrasi3"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:SI 2 "register_operand" " r")]
			 UNSPEC_DKSLRA16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkslra16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkslrasi3"
	[(set (match_operand:RVPV4HI 0 "register_operand"               "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" " r")
		     (match_operand:SI 2 "register_operand" " r")]
			 UNSPEC_DKSLRA16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkslra16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV4HI")])

;; dkadd8 dkadd16
(define_insn "dsp_dkadddi3"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKADD8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkadd8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkadddi3"
	[(set (match_operand:RVPV8QI 0 "register_operand"               "=r")
	(unspec:RVPV8QI [(match_operand:RVPV8QI 1 "register_operand" " r")
		     (match_operand:RVPV8QI 2 "register_operand" " r")]
			 UNSPEC_DKADD8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkadd8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV8QI")])

(define_insn "dsp_dkaddsi3"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKADD16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkadd16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dkaddsi3"
	[(set (match_operand:RVPV4HI 0 "register_operand"               "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" " r")
		     (match_operand:RVPV4HI 2 "register_operand" " r")]
			 UNSPEC_DKADD16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dkadd16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV4HI")])

;; dksub8 dksub16
(define_insn "dsp_dksubdi3"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKSUB8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dksub8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dksubdi3"
	[(set (match_operand:RVPV8QI 0 "register_operand"               "=r")
	(unspec:RVPV8QI [(match_operand:RVPV8QI 1 "register_operand" " r")
		     (match_operand:RVPV8QI 2 "register_operand" " r")]
			 UNSPEC_DKSUB8))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dksub8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV8QI")])

(define_insn "dsp_dksubsi3"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKSUB16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dksub16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_v_dksubsi3"
	[(set (match_operand:RVPV4HI 0 "register_operand"               "=r")
	(unspec:RVPV4HI [(match_operand:RVPV4HI 1 "register_operand" " r")
		     (match_operand:RVPV4HI 2 "register_operand" " r")]
			 UNSPEC_DKSUB16))]
  "TARGET_XXLDSPN1X && !TARGET_64BIT"
  "dksub16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV4HI")])

;;expd
(define_insn "dsp_expd80si"
 [(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r")]
			 UNSPEC_EXPD80))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd80\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_v_expd80si"
	[(set (match_operand:RVPV2HI 0 "register_operand"               "=r")
	(unspec:RVPV2HI [(match_operand:RVPV2HI 1 "register_operand" " r")]
			 UNSPEC_EXPD80))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd80\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV2HI")])

(define_insn "dsp_expd81si"
 [(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r")]
			 UNSPEC_EXPD81))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd81\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_v_expd81si"
	[(set (match_operand:RVPV2HI 0 "register_operand"               "=r")
	(unspec:RVPV2HI [(match_operand:RVPV2HI 1 "register_operand" " r")]
			 UNSPEC_EXPD81))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd81\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV2HI")])

(define_insn "dsp_expd82si"
 [(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r")]
			 UNSPEC_EXPD82))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd82\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_v_expd82si"
	[(set (match_operand:RVPV2HI 0 "register_operand"               "=r")
	(unspec:RVPV2HI [(match_operand:RVPV2HI 1 "register_operand" " r")]
			 UNSPEC_EXPD82))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd82\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV2HI")])

(define_insn "dsp_expd83si"
 [(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r")]
			 UNSPEC_EXPD83))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd83\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_v_expd83si"
	[(set (match_operand:RVPV2HI 0 "register_operand"               "=r")
	(unspec:RVPV2HI [(match_operand:RVPV2HI 1 "register_operand" " r")]
			 UNSPEC_EXPD83))]
  "TARGET_XXLDSP && !TARGET_64BIT"
  "expd83\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "RVPV2HI")])

(define_insn "dsp_expd80di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD80))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd80\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_expd81di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD81))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd81\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_expd82di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD82))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd82\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_expd83di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD83))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd83\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_expd84di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD84))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd84\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_expd85di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD85))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd85\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_expd86di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD86))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd86\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_expd87di"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_EXPD87))]
  "TARGET_XXLDSP && TARGET_64BIT"
  "expd87\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

;;Nuclei custom dsp N2
(define_insn "dsp_dkhmx8"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKHMX8))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkhmx8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkhmx16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKHMX16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkhmx16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmmul"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMMUL))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmmul\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmmul_u"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMMUL_U))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmmul.u\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkwmmul"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKWMMUL))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkwmmul\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkwmmul_u"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKWMMUL_U))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkwmmul.u\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkabs32"
 [(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DKABS32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkabs32\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkslra32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:SI 2 "register_operand" " r")]
			 UNSPEC_DKSLRA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkslra32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkadd32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKADD32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkadd32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dksub32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKSUB32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dksub32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dradd16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRADD16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dradd16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsub16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSUB16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsub16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dradd32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRADD32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dradd32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsub32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSUB32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsub32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKMDA))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkmda\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmxda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKMXDA))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkmxda\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmdrs"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMDRS))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmdrs\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmxds"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMXDS))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmxds\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbb32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMBB32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbb32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbb32_sra14"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMBB32_SRA14))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbb32.sra14\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbb32_sra32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMBB32_SRA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbb32.sra32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbt32"
[(set (match_operand:DI 0 "register_operand"               "=r")
 	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
 		     (match_operand:DI 2 "register_operand" " r")]
 			 UNSPEC_DSMBT32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbt32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbt32_sra14"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMBT32_SRA14))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbt32.sra14\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbt32_sra32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMBT32_SRA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbt32.sra32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmtt32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMTT32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmtt32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmtt32_sra14"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMTT32_SRA14))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmtt32.sra14\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmtt32_sra32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMTT32_SRA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmtt32.sra32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpkbb32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKBB32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpkbb32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpkbt32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKBT32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpkbt32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpack32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		     (match_operand:SI 2 "register_operand" " r")]
			 UNSPEC_DPACK32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpack32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpktt32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKTT32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpktt32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpktb32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKTB32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpktb32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpktb16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKTB16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpktb16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpkbb16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKBB16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpkbb16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpkbt16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKBT16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpkbt16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dpktt16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DPKTT16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dpktt16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsra16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSRA16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsra16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dadd16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DADD16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dadd16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dadd32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DADD32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dadd32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbb16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMBB16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbb16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmbt16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMBT16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmbt16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmtt16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMTT16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsmtt16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_drcrsa16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRCRSA16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "drcrsa16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_drcras16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRCRAS16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "drcras16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkcrsa16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKCRSA16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkcrsa16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkcras16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKCRAS16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkcras16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_drsub16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRSUB16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "drsub16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_drsub32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRSUB32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "drsub32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dstsa32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSTSA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dstsa32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dstas32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSTAS32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dstas32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkcras32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKCRAS32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkcras32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkcrsa32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKCRSA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkcrsa32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dcrsa32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DCRSA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dcrsa32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dcras32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DCRAS32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dcras32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkstsa16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKSTSA16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkstsa16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkstas16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKSTAS16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkstas16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsclip8"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:SI 2 "imm5u_operand"	" u05")]
			 UNSPEC_DSCLIP8))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsclip8\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsclip16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:SI 2 "imm5u_operand"	" u05")]
			 UNSPEC_DSCLIP16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsclip16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsclip32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:SI 2 "imm5u_operand"	" u05")]
			 UNSPEC_DSCLIP32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsclip32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_drcrsa32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRCRSA32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "drcrsa32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_drcras32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DRCRAS32))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "drcras32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkclip64"
[(set (match_operand:HI 0 "register_operand"               "=r")
	(unspec:HI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DKCLIP64))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dkclip64\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "HI")])

;;Nuclei custom dsp N3
(define_insn "dsp_dkmmac"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMMAC))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmmac\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmmac_u"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMMAC_U))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmmac.u\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmmsb"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMMSB))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmmsb\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmmsb_u"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMMSB_U))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmmsb.u\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmada"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMADA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmada\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmaxda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMAXDA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmaxda\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmads"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMADS))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmads\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmadrs"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMADRS))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmadrs\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmaxds"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMAXDS))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmaxds\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmsda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMSDA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmsda\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmsxda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMSXDA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmsxda\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmaqa"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMAQA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmaqa\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmaqa_su"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMAQA_SU))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmaqa.su\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dumaqa"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DUMAQA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dumaqa\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmda32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
			 (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKMDA32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmda32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmxda32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
			 (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DKMXDA32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmxda32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmada32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMADA32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmada32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmaxda32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMAXDA32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmaxda32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmads32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMADS32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmads32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmadrs32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMADRS32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmadrs32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmaxds32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMAXDS32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmaxds32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmsda32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMSDA32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmsda32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmsxda32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMSXDA32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmsxda32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmds32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
			 (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMDS32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmds32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmdrs32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
			 (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMDRS32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmdrs32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmxds32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
			 (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMXDS32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmxds32\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmalda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALDA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmalda\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmalxda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALXDA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmalxda\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmalds"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALDS))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmalds\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmaldrs"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALDRS))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmaldrs\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmalxds"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALXDS))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmalxds\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmslda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMSLDA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmslda\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmslxda"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMSLXDA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmslxda\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_ddsmaqa"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DDSMAQA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "ddsmaqa\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_ddsmaqa_su"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DDSMAQA_SU))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "ddsmaqa.su\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_ddumaqa"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DDUMAQA))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "ddumaqa\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dmsr16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DMSR16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dmsr16\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dmsr17"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DMSR17))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dmsr17\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dmsr33"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DMSR33))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dmsr33\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dmxsr33"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DMXSR33))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dmxsr33\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmada16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMADA16))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmada16\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmaxda16"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMAXDA16))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmaxda16\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dksms32_u"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKSMS32_U))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dksms32.u\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dmada32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DMADA32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dmada32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dredas16"
[(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DREDAS16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dredas16\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_dredsa16"
[(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DREDSA16))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dredsa16\t%0, %1"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_dsunpkd810"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DSUNPKD810))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsunpkd810\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsunpkd820"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DSUNPKD820))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsunpkd820\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsunpkd830"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DSUNPKD830))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsunpkd830\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsunpkd831"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DSUNPKD831))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsunpkd831\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsunpkd832"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DSUNPKD832))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dsunpkd832\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dzunpkd810"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DZUNPKD810))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dzunpkd810\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dzunpkd820"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DZUNPKD820))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dzunpkd820\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dzunpkd830"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DZUNPKD830))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dzunpkd830\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dzunpkd831"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DZUNPKD831))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dzunpkd831\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dzunpkd832"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r")]
			 UNSPEC_DZUNPKD832))]
  "TARGET_XXLDSPN2X && !TARGET_64BIT"
  "dzunpkd832\t%0, %1"
  [(set_attr "type" "dsp")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsma32_u"
[(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMA32_U))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsma32.u\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_dsmxs32_u"
[(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMXS32_U))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmxs32.u\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_dsmxa32_u"
[(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMXA32_U))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmxa32.u\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_dsms32_u"
[(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:DI 1 "register_operand" " r")
		     (match_operand:DI 2 "register_operand" " r")]
			 UNSPEC_DSMS32_U))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsms32.u\t%0, %1, %2"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "SI")])

(define_insn "dsp_dsmalbb"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALBB))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmalbb\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmalbt"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALBT))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmalbt\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dsmaltt"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DSMALTT))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dsmaltt\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmabb32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMABB32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmabb32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmabt32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMABT32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmabt32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])

(define_insn "dsp_dkmatt32"
[(set (match_operand:DI 0 "register_operand"               "=r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " 0")
		     (match_operand:DI 2 "register_operand" " r")
			 (match_operand:DI 3 "register_operand" " r")]
			 UNSPEC_DKMATT32))]
  "TARGET_XXLDSPN3X && !TARGET_64BIT"
  "dkmatt32\t%0, %2, %3"
  [(set_attr "type" "dsp64")
   (set_attr "mode" "DI")])
