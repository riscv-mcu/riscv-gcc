;; The machine description is based on
;; https://raw.githubusercontent.com/andestech/gcc/bsp-v5_1_0/gcc/config/riscv/dsp.md

(define_mode_attr VEXT [(V4QI "V4HI") (V2HI "V2SI") (V8QI "V8HI") (V4HI "V4SI")
			(V2SI "V2DI")])

(define_mode_iterator VQIHI [(V4QI "!TARGET_64BIT") (V2HI "!TARGET_64BIT")
    (V8QI "TARGET_64BIT") (V4HI "TARGET_64BIT")])

(define_mode_iterator VECI [(V4QI "!TARGET_64BIT") (V2HI "!TARGET_64BIT")
    (V8QI "TARGET_64BIT") (V4HI "TARGET_64BIT")
    (V2SI "TARGET_64BIT")])

(define_mode_iterator VSHI [(V2HI "!TARGET_64BIT") (V2SI "TARGET_64BIT")])

(define_mode_iterator VQI [(V4QI "!TARGET_64BIT") (V8QI "TARGET_64BIT")])

(define_mode_iterator VD_SI [(SI "!TARGET_64BIT") (V2SI "TARGET_64BIT")])

(define_mode_iterator VHI [(V2HI "!TARGET_64BIT") (V4HI "TARGET_64BIT")])

(define_mode_attr VNHALF [(V2SI "SI") (V2HI "HI")])

(define_mode_attr VSH_EXT [(V2SI "DI") (V2HI "SI")])

(define_mode_attr bits [(V8QI "8") (V4QI "8") (QI "8") (V4HI "16") (V2HI "16")
    (HI "16") (V2SI "32") (DI "64")])

(define_code_attr uk
    [(plus "") (ss_plus "k") (us_plus "uk")
    (minus "") (ss_minus "k") (us_minus "uk")])

(define_code_attr shift
  [(ashift "ashl") (ashiftrt "ashr") (lshiftrt "lshr") (rotatert "rotr")])

(define_code_iterator sumax [smax umax])

(define_code_iterator sumin [smin umin])

(define_code_iterator sumin_max [smax umax smin umin])

(define_code_attr opcode
  [(plus "add") (minus "sub") (smax "smax") (umax "umax") (smin "smin") (umin "umin")])

(define_code_attr zs
  [(sign_extend "s") (zero_extend "z")])

(define_expand "mov<mode>"
  [(set (match_operand:VQIHI 0 "")
        (match_operand:VQIHI 1 ""))]
    "TARGET_DSP"
{
  if (riscv_legitimize_move (<MODE>mode, operands[0], operands[1]))
    DONE;
})

(define_insn "*mov<mode>_internal"
    [(set (match_operand:VQIHI 0 "nonimmediate_operand" "=r,r,r, m,  *f,*f,*r,*m")
          (match_operand:VQIHI 1 "move_operand"         " r,T,m,rJ,*r*J,*m,*f,*f"))]
    "(register_operand (operands[0], <MODE>mode)
    || reg_or_0_operand (operands[1], <MODE>mode))
    && TARGET_DSP"
  { return riscv_output_move (operands[0], operands[1]); }
  [(set_attr "move_type" "move,const,load,store,mtc,fpload,mfc,fpstore")
   (set_attr "mode" "<MODE>")])

(define_insn "<uk>add<mode>3"
  [(set (match_operand:VECI 0 "register_operand"                "=r")
        (all_plus:VECI (match_operand:VECI 1 "register_operand" " r")
                       (match_operand:VECI 2 "register_operand" " r")))]
    "TARGET_DSP"
    "<uk>add<bits>\t%0, %1, %2"
    [(set_attr "type" "dalu")
    (set_attr "mode" "<MODE>")])

(define_insn "radd<mode>3"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(truncate:VECI
	  (ashiftrt:<VEXT>
	    (plus:<VEXT> (sign_extend:<VEXT> (match_operand:VECI 1 "register_operand" "r"))
			 (sign_extend:<VEXT> (match_operand:VECI 2 "register_operand" "r")))
	    (const_int 1))))]
  "TARGET_DSP"
  "radd<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "uradd<mode>3"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(truncate:VECI
	  (lshiftrt:<VEXT>
	    (plus:<VEXT> (zero_extend:<VEXT> (match_operand:VECI 1 "register_operand" "r"))
			 (zero_extend:<VEXT> (match_operand:VECI 2 "register_operand" "r")))
	    (const_int 1))))]
  "TARGET_DSP"
  "uradd<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "<uk>sub<mode>3"
  [(set (match_operand:VECI                 0 "register_operand" "=r")
	(all_minus:VECI (match_operand:VECI 1 "register_operand" " r")
			(match_operand:VECI 2 "register_operand" " r")))]
  "TARGET_DSP"
  "<uk>sub<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "rsub<mode>3"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(truncate:VECI
	  (ashiftrt:<VEXT>
	    (minus:<VEXT> (sign_extend:<VEXT> (match_operand:VECI 1 "register_operand" "r"))
			  (sign_extend:<VEXT> (match_operand:VECI 2 "register_operand" "r")))		 (const_int 1))))]
  "TARGET_DSP"
  "rsub<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "ursub<mode>3"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(truncate:VECI
	  (ashiftrt:<VEXT>
	    (minus:<VEXT> (zero_extend:<VEXT> (match_operand:VECI 1 "register_operand" "r"))
			  (zero_extend:<VEXT> (match_operand:VECI 2 "register_operand" "r")))
	    (const_int 1))))]
  "TARGET_DSP"
  "ursub<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_expand "cras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_cras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
  [(set_attr "type" "dalu")])

(define_insn "cras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand" "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (minus:<VNHALF>
	      (vec_select:<VNHALF>
		(match_operand:VSHI 1 "register_operand" "r")
		(parallel [(const_int 0)]))
	      (vec_select:<VNHALF>
		(match_operand:VSHI 2 "register_operand" "r")
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
  "TARGET_DSP"
  "cras<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "rcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_rcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
  [(set_attr "type" "dalu")])

(define_insn "rcras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand" "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (ashiftrt:<VSH_EXT>
		(minus:<VSH_EXT>
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" "r")
		      (parallel [(const_int 0)])))
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" "r")
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
		  (sign_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_dup 1)
		      (parallel [(const_int 1)]))))
		(const_int 1))))
	  (const_int 1)))]
  "TARGET_DSP"
  "rcras<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")])

(define_expand "cras16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_cras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
  [(set_attr "type" "dalu")])

(define_insn "cras16_64_le"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (minus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" "r")
				     (parallel [(const_int 0)]))
		      (vec_select:HI (match_operand:V4HI 2 "register_operand" "r")
				     (parallel [(const_int 1)])))
	    (plus:HI  (vec_select:HI (match_dup 1)
				     (parallel [(const_int 1)]))
		      (vec_select:HI (match_dup 2)
				     (parallel [(const_int 0)]))))
	  (vec_concat:V2HI
	    (minus:HI (vec_select:HI (match_dup 1)
				     (parallel [(const_int 2)]))
		      (vec_select:HI (match_dup 2)
				     (parallel [(const_int 3)])))
            (plus:HI  (vec_select:HI (match_dup 1)
				     (parallel [(const_int 3)]))
		      (vec_select:HI (match_dup 2)
				     (parallel [(const_int 2)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "cras16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "rcras16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_rcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
  [(set_attr "type" "dalu")])

(define_insn "rcras16_64_le"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "rcras16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "urcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_urcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
  [(set_attr "type" "dalu")])

(define_insn "urcras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand" "=r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (truncate:<VNHALF>
	      (lshiftrt:<VSH_EXT>
		(minus:<VSH_EXT>
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 1 "register_operand" "r")
		      (parallel [(const_int 0)])))
		  (zero_extend:<VSH_EXT>
		    (vec_select:<VNHALF>
		      (match_operand:VSHI 2 "register_operand" "r")
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
  "TARGET_DSP"
  "urcras<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "urcras16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_urcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "urcras16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "urcras16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "kcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_kcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "kcras<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "kcras16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_kcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "kcras16_64_le"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (ss_minus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
					(parallel [(const_int 1)])))
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:V2HI
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (ss_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kcras16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "ukcras<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_ukcras<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "ukcras<mode>_le"
  [(set (match_operand:VSHI 0 "register_operand" "=r")
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
  "TARGET_DSP"
  "ukcras<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "ukcras16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_ukcras16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "ukcras16_64_le"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (us_minus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" "r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:V4HI 2 "register_operand" "r")
					(parallel [(const_int 1)])))
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:V2HI
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (us_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "ukcras16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "crsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_crsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "crsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "kcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_kcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "kcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "ukcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_ukcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "ukcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "rcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_rcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "rcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "urcrsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_urcrsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "urcrsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "crsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_crsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "crsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (plus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
				    (parallel [(const_int 0)]))
		     (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
				    (parallel [(const_int 1)])))
	    (minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:V2HI
	    (plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
		     (vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
		       (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "crsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "kcrsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_kcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "kcrsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (ss_plus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
				       (parallel [(const_int 1)])))
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:V2HI
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (ss_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kcrsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "ukcrsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_ukcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "ukcrsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (us_plus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
				       (parallel [(const_int 1)])))
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
	  (vec_concat:V2HI
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 3)])))
	    (us_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 2)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "ukcrsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "rcrsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_rcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "rcrsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "rcrsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "urcrsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_urcrsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "urcrsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 1)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 0)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "urcrsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "stas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_stas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "stas<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "kstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_kstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "kstas<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "ukstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_ukstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "ukstas<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "rstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_rstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "rstas<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "urstas<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_urstas<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "urstas<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "stas16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_stas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "stas16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (minus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
				     (parallel [(const_int 0)]))
		      (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
				     (parallel [(const_int 0)])))
	    (plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
		     (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:V2HI
	    (minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "stas16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "kstas16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_kstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "kstas16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (ss_minus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
					(parallel [(const_int 0)])))
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:V2HI
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (ss_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kstas16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "ukstas16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_ukstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "ukstas16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (us_minus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
					(parallel [(const_int 0)]))
			 (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
					(parallel [(const_int 0)])))
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:V2HI
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (us_plus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "ukstas16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "rstas16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_rstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "rstas16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "rstas16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "urstas16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_urstas16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "urstas16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "urstas16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "stsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_stsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "stsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "kstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_kstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "kstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "ukstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_ukstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "ukstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "rstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_rstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "rstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")]
)

(define_expand "urstsa<mode>"
  [(match_operand:VSHI 0 "register_operand" "")
   (match_operand:VSHI 1 "register_operand" "")
   (match_operand:VSHI 2 "register_operand" "")]
  "TARGET_DSP"
{
  emit_insn (gen_urstsa<mode>_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

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
  "TARGET_DSP"
  "urstsa<bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")])

(define_expand "stsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_stsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "stsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (plus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
				    (parallel [(const_int 0)]))
		     (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
	    (minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
		      (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:V2HI
	    (plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
		     (vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
		       (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "stsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "kstsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_kstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "kstsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (ss_plus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
				       (parallel [(const_int 0)])))
	    (ss_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:V2HI
	    (ss_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (ss_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kstsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "ukstsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_ukstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "ukstsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (us_plus:HI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
				       (parallel [(const_int 0)]))
			(vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
				       (parallel [(const_int 0)])))
	    (us_minus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 1)]))
			 (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
	  (vec_concat:V2HI
	    (us_plus:HI (vec_select:HI (match_dup 1) (parallel [(const_int 2)]))
			(vec_select:HI (match_dup 2) (parallel [(const_int 2)])))
	    (us_minus:HI  (vec_select:HI (match_dup 1) (parallel [(const_int 3)]))
			  (vec_select:HI (match_dup 2) (parallel [(const_int 3)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "ukstsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "rstsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_rstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "rstsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (ashiftrt:SI
		(plus:SI
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (ashiftrt:SI
		(minus:SI
		  (sign_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "rstsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "urstsa16_64"
  [(match_operand:V4HI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_urstsa16_64_le (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dalu")])

(define_insn "urstsa16_64_le"
  [(set (match_operand:V4HI 0 "register_operand"         "=r")
	(vec_concat:V4HI
	  (vec_concat:V2HI
	    (truncate:HI
	      (lshiftrt:SI
		(plus:SI
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 1 "register_operand" " r")
						 (parallel [(const_int 0)])))
		  (zero_extend:SI (vec_select:HI (match_operand:V4HI 2 "register_operand" " r")
						  (parallel [(const_int 0)]))))
		(const_int 1)))
	    (truncate:HI
	      (lshiftrt:SI
		(minus:SI
		  (zero_extend:SI (vec_select:HI (match_dup 1) (parallel [(const_int 1)])))
		  (zero_extend:SI (vec_select:HI (match_dup 2) (parallel [(const_int 1)]))))
		(const_int 1))))
	  (vec_concat:V2HI
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
  "TARGET_DSP && TARGET_64BIT"
  "urstsa16\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "V4HI")])

(define_expand "<shift><mode>3"
  [(set (match_operand:VHI                0 "register_operand" "")
	(any_shift:VHI (match_operand:VHI 1 "register_operand" "")
		       (match_operand:SI  2 "rimm4u_operand"   "")))]
  "TARGET_DSP"
{
  if (operands[2] == const0_rtx)
    {
      emit_move_insn (operands[0], operands[1]);
      DONE;
    }
})

(define_insn "*ashr<mode>3"
  [(set (match_operand:VHI               0 "register_operand" "=r,r")
	(ashiftrt:VHI (match_operand:VHI 1 "register_operand" "r,r")
		      (match_operand:SI  2 "rimm4u_operand"   "u04,r")))]
  "TARGET_DSP"
  "@
   srai16\t%0, %1, %2
   sra16\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "sra16_round<mode>"
  [(set (match_operand:VHI 0 "register_operand"  "=r,r")
	(unspec:VHI [(ashiftrt:VHI (match_operand:VHI 1 "register_operand" "r,r")
				   (match_operand:SI 2  "rimm4u_operand" "u04,r"))]
		     UNSPEC_ROUND))]
  "TARGET_DSP"
  "@
   srai16.u\t%0, %1, %2
   sra16.u\t%0, %1, %2"
  [(set_attr "type" "daluround, daluround")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "*lshr<mode>3"
  [(set (match_operand:VHI 0 "register_operand"               "=  r, r")
	(lshiftrt:VHI (match_operand:VHI 1 "register_operand" "   r, r")
		      (match_operand:SI 2  "rimm4u_operand"   " u04, r")))]
  "TARGET_DSP"
  "@
   srli16\t%0, %1, %2
   srl16\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "srl16_round<mode>"
  [(set (match_operand:VHI 0 "register_operand" "=  r, r")
	(unspec:VHI [(lshiftrt:VHI (match_operand:VHI 1 "register_operand" "r,r")
				   (match_operand:SI 2  "rimm4u_operand" "u04,r"))]
		     UNSPEC_ROUND))]
  "TARGET_DSP"
  "@
   srli16.u\t%0, %1, %2
   srl16.u\t%0, %1, %2"
  [(set_attr "type" "daluround, daluround")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "*ashl<mode>3"
  [(set (match_operand:VHI 0 "register_operand"             "=r,r")
	(ashift:VHI (match_operand:VHI 1 "register_operand" "r,r")
		    (match_operand:SI 2  "rimm4u_operand"   "u04,r")))]
  "TARGET_DSP"
  "@
   slli16\t%0, %1, %2
   sll16\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "kslli16<mode>"
  [(set (match_operand:VHI 0 "register_operand"                "=r,r")
	(ss_ashift:VHI (match_operand:VHI 1 "register_operand" "r,r")
		       (match_operand:SI 2  "rimm4u_operand"   "u04,r")))]
  "TARGET_DSP"
  "@
   kslli16\t%0, %1, %2
   ksll16\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "kslra<VECI:mode><X:mode>"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(if_then_else:VECI
	  (lt:X (match_operand:X 2 "register_operand" "r")
		(const_int 0))
	  (ashiftrt:VECI (match_operand:VECI 1 "register_operand" "r")
			 (neg:X (match_dup 2)))
	  (ss_ashift:VECI (match_dup 1)
			  (match_dup 2))))]
  "TARGET_DSP"
  "kslra<VECI:bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<VECI:MODE>")])

(define_insn "kslra<VECI:mode><X:mode>_round"
  [(set (match_operand:VECI 0 "register_operand" "=r")
	(if_then_else:VECI
	  (lt:X (match_operand:X 2 "register_operand" " r")
		(const_int 0))
	  (unspec:VECI [(ashiftrt:VECI (match_operand:VECI 1 "register_operand" "r")
				       (neg:X (match_dup 2)))]
		        UNSPEC_ROUND)
	  (ss_ashift:VECI (match_dup 1)
			  (match_dup 2))))]
  "TARGET_DSP"
  "kslra<VECI:bits>.u\t%0, %1, %2"
  [(set_attr "type" "daluround")
   (set_attr "mode" "<VECI:MODE>")])

(define_expand "<shift><mode>3"
  [(set (match_operand:VQI 0 "register_operand"                "")
	(any_shift:VQI (match_operand:VQI 1 "register_operand" "")
			(match_operand:SI 2 "rimm3u_operand" "")))]
  "TARGET_DSP"
{
  if (operands[2] == const0_rtx)
    {
      emit_move_insn (operands[0], operands[1]);
      DONE;
    }
})

(define_insn "*ashr<mode>3"
  [(set (match_operand:VQI 0 "register_operand"               "=r,r")
	(ashiftrt:VQI (match_operand:VQI 1 "register_operand" "r,r")
		       (match_operand:SI 2 "rimm3u_operand"   "u03,r")))]
  "TARGET_DSP"
  "@
   srai8\t%0, %1, %2
   sra8\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "sra8_round<mode>"
  [(set (match_operand:VQI 0 "register_operand"                            "=r,r")
	(unspec:VQI [(ashiftrt:VQI (match_operand:VQI 1 "register_operand" "r,r")
				   (match_operand:SI 2  "rimm3u_operand"   "u03,r"))]
		      UNSPEC_ROUND))]
  "TARGET_DSP"
  "@
   srai8.u\t%0, %1, %2
   sra8.u\t%0, %1, %2"
  [(set_attr "type" "daluround, daluround")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "*ashl<mode>3"
  [(set (match_operand:VQI 0 "register_operand"             "=  r, r")
	(ashift:VQI (match_operand:VQI 1 "register_operand" "   r, r")
		     (match_operand:SI 2   "rimm3u_operand" " u03, r")))]
  "TARGET_DSP"
  "@
   slli8\t%0, %1, %2
   sll8\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "kslli8<VQI:mode><X:mode>"
  [(set (match_operand:VQI 0 "register_operand"                "=  r, r")
	(ss_ashift:VQI (match_operand:VQI 1 "register_operand" "   r, r")
		       (match_operand:X 2   "rimm3u_operand"   " u03, r")))]
  "TARGET_DSP"
  "@
   kslli8\t%0, %1, %2
   ksll8\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<VQI:MODE>, <VQI:MODE>")])

(define_insn "*lshr<mode>3"
  [(set (match_operand:VQI 0 "register_operand"               "=  r, r")
	(lshiftrt:VQI (match_operand:VQI 1 "register_operand" "   r, r")
		       (match_operand:SI 2 "rimm3u_operand"   " u03, r")))]
  "TARGET_DSP"
  "@
   srli8\t%0, %1, %2
   srl8\t%0, %1, %2"
  [(set_attr "type" "dalu, dalu")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "srl8_round<mode>"
  [(set (match_operand:VQI 0 "register_operand"                            "=  r, r")
	(unspec:VQI [(lshiftrt:VQI (match_operand:VQI 1 "register_operand" "   r, r")
				   (match_operand:SI 2  "rimm3u_operand"   " u03, r"))]
		      UNSPEC_ROUND))]
  "TARGET_DSP"
  "@
   srli8.u\t%0, %1, %2
   srl8.u\t%0, %1, %2"
  [(set_attr "type" "daluround, daluround")
   (set_attr "mode" "<MODE>, <MODE>")])

(define_insn "cmpeq<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(eq:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				 (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_DSP"
  "cmpeq<bits>\t%0, %1, %2"
  [(set_attr "type" "dcmp")
   (set_attr "mode" "<MODE>")])

(define_insn "scmplt<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(lt:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				 (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_DSP"
  "scmplt<bits>\t%0, %1, %2"
  [(set_attr "type" "dcmp")
   (set_attr "mode" "<MODE>")])

(define_insn "scmple<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(le:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				 (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_DSP"
  "scmple<bits>\t%0, %1, %2"
  [(set_attr "type" "dcmp")
   (set_attr "mode" "<MODE>")])

(define_insn "ucmplt<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(ltu:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				  (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_DSP"
  "ucmplt<bits>\t%0, %1, %2"
  [(set_attr "type" "dcmp")
   (set_attr "mode" "SI")])

(define_insn "ucmple<mode>"
  [(set (match_operand:VQIHI 0 "register_operand"                          "=r")
	(unspec:VQIHI [(leu:VQIHI (match_operand:VQIHI 1 "register_operand" " r")
				  (match_operand:VQIHI 2 "register_operand" " r"))]
		       UNSPEC_VEC_COMPARE))]
  "TARGET_DSP"
  "ucmple<bits>\t%0, %1, %2"
  [(set_attr "type" "dcmp")
   (set_attr "mode" "<MODE>")])

(define_insn "<su>mul16"
  [(set (match_operand:V2SI 0 "register_operand"                             "=r")
	(mult:V2SI (any_extend:V2SI (match_operand:V2HI 1 "register_operand" " r"))
		   (any_extend:V2SI (match_operand:V2HI 2 "register_operand" " r"))))]
  "TARGET_DSP && !TARGET_64BIT"
  "<su>mul16\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "V2SI")])

(define_insn "smul16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMUL16))]
  "TARGET_DSP && TARGET_64BIT"
  "smul16\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "DI")])

(define_insn "umul16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMUL16))]
  "TARGET_DSP && TARGET_64BIT"
  "umul16\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "DI")])

(define_insn "smul8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMUL8))]
  "TARGET_DSP"
  "smul8\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "V4HI")])

(define_insn "umul8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMUL8))]
  "TARGET_DSP"
  "umul8\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "V4HI")])

(define_insn "<su>mulx16"
  [(set (match_operand:V2SI 0 "register_operand"         "=r")
	(vec_merge:V2SI
	  (vec_duplicate:V2SI
	    (mult:SI
	      (any_extend:SI
		(vec_select:HI
		  (match_operand:V2HI 1 "register_operand" " r")
		  (parallel [(const_int 0)])))
	      (any_extend:SI
		(vec_select:HI
		  (match_operand:V2HI 2 "register_operand" " r")
		  (parallel [(const_int 1)])))))
	  (vec_duplicate:V2SI
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
  "TARGET_DSP && !TARGET_64BIT"
  "<su>mulx16\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "V2SI")])

(define_insn "smulx16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMULX16))]
  "TARGET_DSP && TARGET_64BIT"
  "smulx16\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "DI")])

(define_insn "umulx16_64"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMULX16))]
  "TARGET_DSP && TARGET_64BIT"
  "umulx16\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "DI")])

(define_insn "smulx8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_SMULX8))]
  "TARGET_DSP"
  "smulx8\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "V4HI")])

(define_insn "umulx8"
  [(set (match_operand:DI 0 "register_operand"             "=r")
	(unspec:DI [(match_operand:SI 1 "register_operand" " r")
		    (match_operand:SI 2 "register_operand" " r")]
		    UNSPEC_UMULX8))]
  "TARGET_DSP"
  "umulx8\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "V4HI")])

(define_insn "khm16<mode>"
  [(set (match_operand:VHI 0 "register_operand"              "=r")
	(unspec:VHI [(match_operand:VHI 1 "register_operand" " r")
		     (match_operand:VHI 2 "register_operand" " r")]
		     UNSPEC_KHM))]
  "TARGET_DSP"
  "khm16\t%0, %1, %2"
  [(set_attr "type"   "dmul")
   (set_attr "mode" "<MODE>")])

(define_insn "khmx16<mode>"
  [(set (match_operand:VHI 0 "register_operand"              "=r")
	(unspec:VHI [(match_operand:VHI 1 "register_operand" " r")
		     (match_operand:VHI 2 "register_operand" " r")]
		     UNSPEC_KHMX))]
  "TARGET_DSP"
  "khmx16\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "<MODE>")])

(define_insn "khm8<mode>"
  [(set (match_operand:VQI 0 "register_operand"              "=r")
	(unspec:VQI [(match_operand:VQI 1 "register_operand" " r")
		     (match_operand:VQI 2 "register_operand" " r")]
		     UNSPEC_KHM))]
  "TARGET_DSP"
  "khm8\t%0, %1, %2"
  [(set_attr "type"   "dmul")
   (set_attr "mode" "<MODE>")])

(define_insn "khmx8<mode>"
  [(set (match_operand:VQI 0 "register_operand"              "=r")
	(unspec:VQI [(match_operand:VQI 1 "register_operand" " r")
		     (match_operand:VQI 2 "register_operand" " r")]
		     UNSPEC_KHMX))]
  "TARGET_DSP"
  "khmx8\t%0, %1, %2"
  [(set_attr "type"   "dmul")
   (set_attr "mode" "<MODE>")])

;; smax[8|16] and umax[8|16]
(define_insn "<opcode><mode>3"
  [(set (match_operand:VECI 0 "register_operand"             "=r")
	(sumax:VECI (match_operand:VECI 1 "register_operand" " r")
		    (match_operand:VECI 2 "register_operand" " r")))]
  "TARGET_DSP"
  "<opcode><bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")])

;; smin[8|16] and umin[8|16]
(define_insn "<opcode><mode>3"
  [(set (match_operand:VECI 0 "register_operand"             "=r")
	(sumin:VECI (match_operand:VECI 1 "register_operand" " r")
		    (match_operand:VECI 2 "register_operand" " r")))]
  "TARGET_DSP"
  "<opcode><bits>\t%0, %1, %2"
  [(set_attr "type" "dalu")])

(define_insn "sclip8<mode>"
  [(set (match_operand:VQI 0 "register_operand"              "=  r")
	(unspec:VQI [(match_operand:VQI 1 "register_operand" "   r")
		      (match_operand:SI 2 "imm3u_operand"    " u03")]
		     UNSPEC_CLIPS))]
  "TARGET_DSP"
  "sclip8\t%0, %1, %2"
  [(set_attr "type" "dclip")
   (set_attr "mode" "<MODE>")])

(define_insn "uclip8<mode>"
  [(set (match_operand:VQI 0 "register_operand"               "=  r")
	(unspec:VQI [(match_operand:VQI 1 "register_operand"  "   r")
		     (match_operand:SI 2 "imm3u_operand"      " u03")]
		     UNSPEC_CLIP))]
  "TARGET_DSP"
  "uclip8\t%0, %1, %2"
  [(set_attr "type" "dclip")
   (set_attr "mode" "<MODE>")])

(define_insn "sclip16<mode>"
  [(set (match_operand:VHI 0 "register_operand"              "=   r")
	(unspec:VHI [(match_operand:VHI 1 "register_operand" "    r")
		     (match_operand:SI 2 "imm4u_operand"     " u04")]
		     UNSPEC_CLIPS))]
  "TARGET_DSP"
  "sclip16\t%0, %1, %2"
  [(set_attr "type" "dclip")
   (set_attr "mode" "<MODE>")])

(define_insn "uclip16<mode>"
  [(set (match_operand:VHI 0 "register_operand"               "=   r")
	(unspec:VHI [(match_operand:VHI 1 "register_operand"  "    r")
		      (match_operand:SI 2 "imm4u_operand"     " u04")]
		     UNSPEC_CLIP))]
  "TARGET_DSP"
  "uclip16\t%0, %1, %2"
  [(set_attr "type" "dclip")
   (set_attr "mode" "<MODE>")])

(define_insn "kabs<mode>2"
  [(set (match_operand:VECI 0 "register_operand"              "=r")
	(ss_abs:VECI (match_operand:VECI 1 "register_operand" " r")))]
  "TARGET_DSP"
  "kabs<bits>\t%0, %1"
  [(set_attr "type"   "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "clrs<mode>2"
  [(set (match_operand:VECI 0 "register_operand"               "=r")
	(unspec:VECI [(match_operand:VECI 1 "register_operand" " r")]
		      UNSPEC_CLRS))]
  "TARGET_DSP"
  "clrs<bits>\t%0, %1"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "clrssi2"
  [(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r")]
		      UNSPEC_CLRS))]
  "TARGET_DSP"
  "clrs32\t%0, %1"
  [(set_attr "type" "dalu")
   (set_attr "mode" "SI")])

(define_insn "clz<mode>2"
  [(set (match_operand:VECI 0 "register_operand"               "=r")
	(unspec:VECI [(match_operand:VECI 1 "register_operand" " r")]
		      UNSPEC_CLZ))]
  "TARGET_DSP"
  "clz<bits>\t%0, %1"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "clzsi2"
  [(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r")]
		      UNSPEC_CLZ))]
  "TARGET_DSP"
  "clz32\t%0, %1"
  [(set_attr "type" "dalu")
   (set_attr "mode" "SI")])

(define_insn "clo<mode>2"
  [(set (match_operand:VECI 0 "register_operand"               "=r")
	(unspec:VECI [(match_operand:VECI 1 "register_operand" " r")]
		      UNSPEC_CLO))]
  "TARGET_DSP"
  "clo<bits>\t%0, %1"
  [(set_attr "type" "dalu")
   (set_attr "mode" "<MODE>")])

(define_insn "closi2"
  [(set (match_operand:SI 0 "register_operand"               "=r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r")]
		      UNSPEC_CLO))]
  "TARGET_DSP"
  "clo32\t%0, %1"
  [(set_attr "type" "dalu")
   (set_attr "mode" "SI")])

(define_expand "vec_unpacks_lo_v4qi"
  [(match_operand:V2HI 0 "register_operand" "=r")
   (match_operand:V4QI 1 "register_operand" " r")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd810 (operands[0], operands[1]));
  DONE;
})

(define_expand "sunpkd810"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd810_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "<zs>unpkd810_imp"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 1)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 0)]))))
	  (const_int 2)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd810\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_insn "<zs>unpkd810_imp_inv"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 1)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd810\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_expand "sunpkd820"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd820_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "<zs>unpkd820_imp"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 2)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 0)]))))
	  (const_int 2)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd820\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_insn "<zs>unpkd820_imp_inv"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 2)]))))
	  (const_int 1)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd820\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_expand "sunpkd830"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd830_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "<zs>unpkd830_imp"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 3)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 0)]))))
	  (const_int 2)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd830\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_insn "<zs>unpkd830_imp_inv"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 0)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 3)]))))
	  (const_int 1)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd830\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_expand "sunpkd831"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd831_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "<zs>unpkd831_imp"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 3)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 1)]))))
	  (const_int 2)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd831\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_insn "<zs>unpkd831_imp_inv"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 1)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 3)]))))
	  (const_int 1)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd831\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_expand "sunpkd832"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_sunpkd832_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "<zs>unpkd832_imp"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 3)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 2)]))))
	  (const_int 2)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd832\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_insn "<zs>unpkd832_imp_inv"
  [(set (match_operand:V2HI 0 "register_operand"                     "=r")
	(vec_merge:V2HI
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_operand:V4QI 1 "register_operand"             " r")
		(parallel [(const_int 2)]))))
	  (vec_duplicate:V2HI
	    (any_extend:HI
	      (vec_select:QI
		(match_dup 1)
		(parallel [(const_int 3)]))))
	  (const_int 1)))]
  "TARGET_DSP && !TARGET_64BIT"
  "<zs>unpkd832\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V2HI")])

(define_expand "zunpkd810"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd810_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_expand "zunpkd820"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd820_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_expand "zunpkd830"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd830_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_expand "zunpkd831"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd831_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_expand "zunpkd832"
  [(match_operand:V2HI 0 "register_operand")
   (match_operand:V4QI 1 "register_operand")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_zunpkd832_imp (operands[0], operands[1]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "<zs>unpkd810_64"
  [(set (match_operand:V4HI 0 "register_operand"                    "=r")
	(vec_select:V4HI
	  (any_extend:V8HI (match_operand:V8QI 1 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 1)
		     (const_int 4) (const_int 5)])))]
  "TARGET_DSP && TARGET_64BIT"
  "<zs>unpkd810\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V4HI")])

(define_insn "<zs>unpkd820_64"
  [(set (match_operand:V4HI 0 "register_operand"                    "=r")
	(vec_select:V4HI
	  (any_extend:V8HI (match_operand:V8QI 1 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 2)
		     (const_int 4) (const_int 6)])))]
  "TARGET_DSP && TARGET_64BIT"
  "<zs>unpkd820\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V4HI")])

(define_insn "<zs>unpkd830_64"
  [(set (match_operand:V4HI 0 "register_operand"                    "=r")
	(vec_select:V4HI
	  (any_extend:V8HI (match_operand:V8QI 1 "register_operand" "r"))
	  (parallel [(const_int 0) (const_int 3)
		     (const_int 4) (const_int 7)])))]
  "TARGET_DSP && TARGET_64BIT"
  "<zs>unpkd830\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V4HI")])

(define_insn "<zs>unpkd831_64"
  [(set (match_operand:V4HI 0 "register_operand"                    "=r")
	(vec_select:V4HI
	  (any_extend:V8HI (match_operand:V8QI 1 "register_operand" "r"))
	  (parallel [(const_int 1) (const_int 3)
		     (const_int 5) (const_int 7)])))]
  "TARGET_DSP && TARGET_64BIT"
  "<zs>unpkd831\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V4HI")])

(define_insn "<zs>unpkd832_64"
  [(set (match_operand:V4HI 0 "register_operand"                    "=r")
	(vec_select:V4HI
	  (any_extend:V8HI (match_operand:V8QI 1 "register_operand" "r"))
	  (parallel [(const_int 2) (const_int 3)
		     (const_int 6) (const_int 7)])))]
  "TARGET_DSP && TARGET_64BIT"
  "<zs>unpkd832\t%0, %1"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "V4HI")])

(define_expand "pkbb<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_DSP"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dpack")])

(define_expand "pkbt<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_DSP"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dpack")])

(define_expand "pktt<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_DSP"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dpack")])

(define_expand "pktb<mode>"
  [(match_operand:VSHI 0 "register_operand")
   (match_operand:VSHI 1 "register_operand")
   (match_operand:VSHI 2 "register_operand")]
  "TARGET_DSP"
{
  emit_insn (gen_vec_merge<mode> (operands[0], operands[1], operands[2],
				  GEN_INT (2), GEN_INT (1), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "vec_merge<mode>"
  [(set (match_operand:VSHI 0 "register_operand"               "= r,   r,   r,   r,   r,   r,   r,   r")
	(vec_merge:VSHI
	  (vec_duplicate:VSHI
	    (vec_select:<VNHALF>
	      (match_operand:VSHI 1 "register_operand"         "  r,   r,   r,   r,   r,   r,   r,   r")
	      (parallel [(match_operand:SI 4 "imm_0_1_operand" "w00, w00, w01, w01, w00, w00, w01, w01")])))
	  (vec_duplicate:VSHI
	    (vec_select:<VNHALF>
	      (match_operand:VSHI 2 "register_operand"         "  r,   r,   r,   r,   r,   r,   r,   r")
	      (parallel [(match_operand:SI 5 "imm_0_1_operand" "w00, w01, w01, w00, w00, w01, w01, w00")])))
	  (match_operand:SI 3 "imm_1_2_operand"                "w01, w01, w01, w01, w02, w02, w02, w02")))]
  "TARGET_DSP"
  "@
   pkbb<bits>\t%0, %2, %1
   pktb<bits>\t%0, %2, %1
   pktt<bits>\t%0, %2, %1
   pkbt<bits>\t%0, %2, %1
   pkbb<bits>\t%0, %1, %2
   pkbt<bits>\t%0, %1, %2
   pktt<bits>\t%0, %1, %2
   pktb<bits>\t%0, %1, %2"
  [(set_attr "type" "dpack")
   (set_attr "mode"  "<MODE>")])


(define_expand "pkbbv4hi"
  [(match_operand:V4HI 0 "register_operand")
   (match_operand:V4HI 1 "register_operand")
   (match_operand:V4HI 2 "register_operand")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_vec_pkbb64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "vec_pkbb64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_select:V4HI
	 (vec_concat:V8HI (match_operand:V4HI 1 "register_operand" "r")
			  (match_operand:V4HI 2 "register_operand" "r"))
	 (parallel [(const_int 0) (const_int 4)
		    (const_int 2) (const_int 6)])))]
  "TARGET_DSP && TARGET_64BIT"
  "pkbb16\t%0, %1, %2"
  [(set_attr "type" "dpack")
   (set_attr "mode" "V4HI")])

(define_expand "pkbtv4hi"
  [(match_operand:V4HI 0 "register_operand")
   (match_operand:V4HI 1 "register_operand")
   (match_operand:V4HI 2 "register_operand")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_vec_pkbt64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "vec_pkbt64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_select:V4HI
	 (vec_concat:V8HI (match_operand:V4HI 1 "register_operand" "r")
			  (match_operand:V4HI 2 "register_operand" "r"))
	 (parallel [(const_int 0) (const_int 5)
		    (const_int 2) (const_int 7)])))]
  "TARGET_DSP && TARGET_64BIT"
  "pkbt16\t%0, %1, %2"
  [(set_attr "type" "dpack")
   (set_attr "mode" "V4HI")])

(define_expand "pkttv4hi"
  [(match_operand:V4HI 0 "register_operand")
   (match_operand:V4HI 1 "register_operand")
   (match_operand:V4HI 2 "register_operand")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_vec_pktt64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "vec_pktt64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_select:V4HI
	 (vec_concat:V8HI (match_operand:V4HI 1 "register_operand" "r")
			  (match_operand:V4HI 2 "register_operand" "r"))
	 (parallel [(const_int 1) (const_int 5)
		    (const_int 3) (const_int 7)])))]
  "TARGET_DSP && TARGET_64BIT"
  "pktt16\t%0, %1, %2"
  [(set_attr "type" "dpack")
   (set_attr "mode" "V4HI")])

(define_expand "pktbv4hi"
  [(match_operand:V4HI 0 "register_operand")
   (match_operand:V4HI 1 "register_operand")
   (match_operand:V4HI 2 "register_operand")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_vec_pktb64 (operands[0], operands[1], operands[2]));
  DONE;
}
[(set_attr "type" "dpack")])

(define_insn "vec_pktb64"
  [(set (match_operand:V4HI 0 "register_operand" "=r")
	(vec_select:V4HI
	 (vec_concat:V8HI (match_operand:V4HI 1 "register_operand" "r")
			  (match_operand:V4HI 2 "register_operand" "r"))
	 (parallel [(const_int 1) (const_int 4)
		    (const_int 3) (const_int 6)])))]
  "TARGET_DSP && TARGET_64BIT"
  "pktb16\t%0, %1, %2"
  [(set_attr "type" "dpack")
   (set_attr "mode" "V4HI")])

(define_insn "smulsi3_highpart"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (lshiftrt:DI
	    (mult:DI
	      (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
	      (sign_extend:DI (match_operand:SI 2 "register_operand" " r")))
	    (const_int 32))))]
  "TARGET_DSP && !TARGET_64BIT"
  "smmul\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "HI")])

(define_insn "smmul_round"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (lshiftrt:DI
	    (unspec:DI [(mult:DI
		  	  (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
			  (sign_extend:DI (match_operand:SI 2 "register_operand" " r")))]
		       UNSPEC_ROUND)
	    (const_int 32))))]
  "TARGET_DSP && !TARGET_64BIT"
  "smmul.u\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "HI")])

(define_insn "smulv2si3_highpart"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
	(truncate:V2SI
	  (lshiftrt:V2DI
	    (mult:V2DI (sign_extend:V2DI (match_operand:V2SI 1 "register_operand" " r"))
		       (sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r")))
	    (const_int 32))))]
  "TARGET_DSP && TARGET_64BIT"
  "smmul\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "V2SI")])

(define_insn "smmulv2si3_round"
  [(set (match_operand:V2SI 0 "register_operand" "=r")
	(truncate:V2SI
	  (lshiftrt:V2DI
	    (unspec:V2DI [(mult:V2DI
			    (sign_extend:V2DI (match_operand:V2SI 1 "register_operand" " r"))
			    (sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r")))]
			  UNSPEC_ROUND)
	    (const_int 32))))]
  "TARGET_DSP  && TARGET_64BIT"
  "smmul.u\t%0, %1, %2"
  [(set_attr "type" "dmul")
   (set_attr "mode" "DI")])

(define_insn "kmmac"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(ss_plus:SI (match_operand:SI 1 "register_operand"             " 0")
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI (match_operand:SI 2 "register_operand" " r"))
		(sign_extend:DI (match_operand:SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmmac\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmmac_64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_plus:V2SI (match_operand:V2SI 1 "register_operand"             " 0")
	  (truncate:V2SI
	    (lshiftrt:V2DI
	      (mult:V2DI
		(sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r"))
		(sign_extend:V2DI (match_operand:V2SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmmac\t%0, %2, %3"
  [(set_attr "type" "dmac")])

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
  "TARGET_DSP && !TARGET_64BIT"
  "kmmac.u\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmmac64_round"
  [(set (match_operand:V2SI 0 "register_operand"                                     "=r")
	(ss_plus:V2SI (match_operand:V2SI 1 "register_operand"                       " 0")
	  (truncate:V2SI
	    (lshiftrt:V2DI
	      (unspec:V2DI [(mult:V2DI
			    (sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r"))
			    (sign_extend:V2DI (match_operand:V2SI 3 "register_operand" " r")))]
			 UNSPEC_ROUND)
	      (const_int 32)))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmmac.u\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmmsb"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(ss_minus:SI (match_operand:SI 1 "register_operand"            " 0")
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI (match_operand:SI 2 "register_operand" " r"))
		(sign_extend:DI (match_operand:SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmmsb\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmmsb_64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_minus:V2SI (match_operand:V2SI 1 "register_operand"             " 0")
	  (truncate:V2SI
	    (lshiftrt:V2DI
	      (mult:V2DI
		(sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r"))
		(sign_extend:V2DI (match_operand:V2SI 3 "register_operand" " r")))
	      (const_int 32)))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmmsb\t%0, %2, %3"
  [(set_attr "type" "dmac")])

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
  "TARGET_DSP && !TARGET_64BIT"
  "kmmsb.u\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmmsb64_round"
  [(set (match_operand:V2SI 0 "register_operand"                                     "=r")
	(ss_minus:V2SI (match_operand:V2SI 1 "register_operand"                       " 0")
	  (truncate:V2SI
	    (lshiftrt:V2DI
	      (unspec:V2DI [(mult:V2DI
			    (sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r"))
			    (sign_extend:V2DI (match_operand:V2SI 3 "register_operand" " r")))]
			 UNSPEC_ROUND)
	      (const_int 32)))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmmsb.u\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kwmmul"
  [(set (match_operand:SI 0 "register_operand"                       "=r")
	(truncate:SI
	  (lshiftrt:DI
	    (ss_mult:DI
	      (mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" " r")) (const_int 2))
	      (mult:DI (sign_extend:DI (match_operand:SI 2 "register_operand" " r")) (const_int 2)))
	    (const_int 32))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kwmmul\t%0, %1, %2"
  [(set_attr "type" "dmul")])

(define_insn "kwmmul_64"
  [(set (match_operand:V2SI 0 "register_operand"                       "=r")
	(truncate:V2SI
	  (lshiftrt:V2DI
	    (ss_mult:V2DI
	      (mult:V2DI (sign_extend:V2DI (match_operand:V2SI 1 "register_operand" " r")) (const_int 2))
	      (mult:V2DI (sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r")) (const_int 2)))
	    (const_int 32))))]
  "TARGET_DSP && TARGET_64BIT"
  "kwmmul\t%0, %1, %2"
  [(set_attr "type" "dmul")])

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
  "TARGET_DSP && !TARGET_64BIT"
  "kwmmul.u\t%0, %1, %2"
  [(set_attr "type" "dmul")])

(define_insn "kwmmul64_round"
  [(set (match_operand:V2SI 0 "register_operand"                       "=r")
	(truncate:V2SI
	  (lshiftrt:V2DI
	    (unspec:V2DI [
	      (ss_mult:V2DI
		(mult:V2DI (sign_extend:V2DI (match_operand:V2SI 1 "register_operand" " r")) (const_int 2))
		(mult:V2DI (sign_extend:V2DI (match_operand:V2SI 2 "register_operand" " r")) (const_int 2)))]
	      UNSPEC_ROUND)
	    (const_int 32))))]
  "TARGET_DSP && TARGET_64BIT"
  "kwmmul.u\t%0, %1, %2"
  [(set_attr "type" "dmul")])

(define_expand "smmwb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_1 (operands[0], operands[1], operands[2], GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smmwt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_1 (operands[0], operands[1], operands[2], GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_insn "smulhisi3_highpart_1"
  [(set (match_operand:SI 0 "register_operand"                       "= r,   r")
	(truncate:SI
	  (lshiftrt:DI
	    (mult:DI
	      (sign_extend:DI (match_operand:SI 1 "register_operand" "  r,   r"))
	      (sign_extend:DI
	        (vec_select:HI
		  (match_operand:V2HI 2 "register_operand"           "  r,   r")
		  (parallel [(match_operand:SI 3 "imm_0_1_operand"   "w00, w01")]))))
	    (const_int 16))))]
  "TARGET_DSP && !TARGET_64BIT"
{
  const char *pats[] = { "smmwb\t%0, %1, %2",
			 "smmwt\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "dmul")])

(define_insn "smulhisi3_highpart_2"
  [(set (match_operand:SI 0 "register_operand"                       "= r,   r")
	(truncate:SI
	  (lshiftrt:DI
	    (mult:DI
	      (sign_extend:DI
	        (vec_select:HI
		  (match_operand:V2HI 1 "register_operand"           "  r,   r")
		  (parallel [(match_operand:SI 3 "imm_0_1_operand"   "w00, w01")])))
	      (sign_extend:DI (match_operand:SI 2 "register_operand" "  r,   r")))
	    (const_int 16))))]
  "TARGET_DSP && !TARGET_64BIT"
{
  const char *pats[] = { "smmwb\t%0, %1, %2",
			 "smmwt\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "dmul")])

(define_expand "smmwb64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2SI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_64 (operands[0], operands[1], operands[2],
					GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smmwt64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2SI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_smulhisi3_highpart_64 (operands[0], operands[1], operands[2],
					GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_insn "smulhisi3_highpart_64"
  [(set (match_operand:V2SI 0 "register_operand"                       "=r,    r")
	(vec_concat:V2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (mult:DI
		(sign_extend:DI
		  (vec_select:SI
		    (match_operand:V2SI 1 "register_operand"           "  r,   r")
		      (parallel [(const_int 0)])))
		(sign_extend:DI
		  (vec_select:HI
		    (match_operand:V4HI 2 "register_operand"           "  r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand"   "w00, w01")]))))
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
		      (parallel [(match_operand:SI 4 "imm_2_3_operand"   "w02, w03")]))))
	      (const_int 16)))))]
  "TARGET_DSP && TARGET_64BIT"
{
  const char *pats[] = { "smmwb\t%0, %1, %2",
			 "smmwt\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "dmul")])

(define_expand "smmwb_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_smmw_round_internal (operands[0], operands[1], operands[2], GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smmwt_round"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_smmw_round_internal (operands[0], operands[1], operands[2], GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_insn "smmw_round_internal"
  [(set (match_operand:SI 0 "register_operand"                          "=  r,   r")
	(truncate:SI
	  (lshiftrt:DI
	    (unspec:DI
	      [(mult:DI
		 (sign_extend:DI (match_operand:SI 1 "register_operand" "   r,   r"))
		 (sign_extend:DI
		   (vec_select:HI
		     (match_operand:V2HI 2 "register_operand"           "   r,   r")
		     (parallel [(match_operand:SI 3 "imm_0_1_operand"   " w00, w01")]))))]
	      UNSPEC_ROUND)
	    (const_int 16))))]
  "TARGET_DSP && !TARGET_64BIT"
{
  const char *pats[] = { "smmwb.u\t%0, %1, %2",
			 "smmwt.u\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "dmul")])

(define_expand "smmwb64_round"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2SI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_smmw64_round_internal (operands[0], operands[1], operands[2],
					GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smmwt64_round"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2SI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_smmw64_round_internal (operands[0], operands[1], operands[2],
					GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_insn "smmw64_round_internal"
  [(set (match_operand:V2SI 0 "register_operand"                       "=r,    r")
	(vec_concat:V2SI
	  (truncate:SI
	    (lshiftrt:DI
	      (unspec:DI
	        [(mult:DI
		  (sign_extend:DI
		    (vec_select:SI
		      (match_operand:V2SI 1 "register_operand"           "  r,   r")
		      (parallel [(const_int 0)])))
		  (sign_extend:DI
		    (vec_select:HI
		      (match_operand:V4HI 2 "register_operand"           "  r,   r")
		      (parallel [(match_operand:SI 3 "imm_0_1_operand"   "w00, w01")]))))]
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
		      (parallel [(match_operand:SI 4 "imm_2_3_operand"   "w02, w03")]))))]
	        UNSPEC_ROUND)
	      (const_int 16)))))]
  "TARGET_DSP && TARGET_64BIT"
{
  const char *pats[] = { "smmwb.u\t%0, %1, %2",
			 "smmwt.u\t%0, %1, %2" };
  return pats[which_alternative];
}
[(set_attr "type" "dmul")])

(define_insn "smslda1"
  [(set (match_operand:DI 0 "register_even_operand"                             "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_even_operand"                         " 0")
	    (sign_extend:DI
	      (mult:SI
		(sign_extend:SI (vec_select:HI
				  (match_operand:V2HI 2 "register_operand" " r")
				  (parallel [(const_int 1)])))
		(sign_extend:SI (vec_select:HI
				  (match_operand:V2HI 3 "register_operand" " r")
				  (parallel [(const_int 1)]))))))
	  (sign_extend:DI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "smslda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "smslda64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_operand"                           " 0")
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:V4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:V4HI 3 "register_operand" " r")
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
  "TARGET_DSP && TARGET_64BIT"
  "smslda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "smslxda1"
  [(set (match_operand:DI 0 "register_even_operand"                               "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_even_operand"                           " 0")
	      (sign_extend:DI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:V2HI 2 "register_operand" " r")
				    (parallel [(const_int 1)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:V2HI 3 "register_operand" " r")
				    (parallel [(const_int 0)]))))))
	  (sign_extend:DI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "smslxda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "smslxda64"
  [(set (match_operand:DI 0 "register_operand"                             "=r")
	(minus:DI
	  (minus:DI
	    (match_operand:DI 1 "register_operand"                           " 0")
	    (sign_extend:DI
	      (minus:SI
		(mult:SI
		  (sign_extend:SI (vec_select:HI
				    (match_operand:V4HI 2 "register_operand" " r")
				    (parallel [(const_int 0)])))
		  (sign_extend:SI (vec_select:HI
				    (match_operand:V4HI 3 "register_operand" " r")
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
  "TARGET_DSP && TARGET_64BIT"
  "smslxda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_expand "smbb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:V2HI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_mulhisi3v (operands[0], operands[1], operands[2],
			    GEN_INT (0), GEN_INT (0)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smbt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:V2HI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_mulhisi3v (operands[0], operands[1], operands[2],
			    GEN_INT (0), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smtt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:V2HI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_mulhisi3v (operands[0], operands[1], operands[2],
			    GEN_INT (1), GEN_INT (1)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_insn "mulhisi3v"
  [(set (match_operand:SI 0 "register_operand"                  "=  r,   r,   r,   r")
	(mult:SI
	  (sign_extend:SI
	     (vec_select:HI
	       (match_operand:V2HI 1 "register_operand"         "   r,   r,   r,   r")
	       (parallel [(match_operand:SI 3 "imm_0_1_operand" " w00, w00, w01, w01")])))
	  (sign_extend:SI (vec_select:HI
	       (match_operand:V2HI 2 "register_operand"         "   r,   r,   r,   r")
	       (parallel [(match_operand:SI 4 "imm_0_1_operand" " w00, w01, w01, w00")])))))]
  "TARGET_DSP && !TARGET_64BIT"
{
  const char *pats[] = { "smbb16\t%0, %1, %2",
			 "smbt16\t%0, %1, %2",
			 "smtt16\t%0, %1, %2",
			 "smbt16\t%0, %2, %1" };
  return pats[which_alternative];
}
  [(set_attr "type"   "dmul")
   (set_attr "mode"   "SI")])

(define_expand "smbb64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_mulv2hiv2si3v (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (2), GEN_INT (0), GEN_INT (2)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smbt64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_mulv2hiv2si3v (operands[0], operands[1], operands[2],
				GEN_INT (0), GEN_INT (2), GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_expand "smtt64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V4HI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_mulv2hiv2si3v (operands[0], operands[1], operands[2],
				GEN_INT (1), GEN_INT (3), GEN_INT (1), GEN_INT (3)));
  DONE;
}
[(set_attr "type" "dmul")])

(define_insn "mulv2hiv2si3v"
  [(set (match_operand:V2SI 0 "register_operand" "=r, r, r")
        (mult:V2SI
	 (sign_extend:V2SI
	  (vec_select:V2HI
	   (match_operand:V4HI 1 "register_operand" "r, r, r")
	   (parallel [(match_operand:SI 3 "imm2u_operand" " w00, w00, w01")
		      (match_operand:SI 4 "imm2u_operand" " w02, w02, w03")])))
	 (sign_extend:V2SI
	  (vec_select:V2HI
	   (match_operand:V4HI 2 "register_operand" "r, r, r")
	   (parallel [(match_operand:SI 5 "imm2u_operand" " w00, w01, w01")
		      (match_operand:SI 6 "imm2u_operand" " w02, w03, w03")])))))]
  "TARGET_DSP && TARGET_64BIT"
  "@
   smbb16\t%0, %1, %2
   smbt16\t%0, %1, %2
   smtt16\t%0, %1, %2"
  [(set_attr "type"   "dmul")
   (set_attr "mode"   "DI")])

(define_insn "kmda"
  [(set (match_operand:SI 0 "register_operand"                         "=r")
	(ss_plus:SI
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_operand:V2HI 1 "register_operand" "r")
			      (parallel [(const_int 1)])))
	    (sign_extend:SI (vec_select:HI
			      (match_operand:V2HI 2 "register_operand" "r")
			      (parallel [(const_int 1)]))))
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:SI (vec_select:HI
			      (match_dup 2)
			      (parallel [(const_int 0)]))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmda\t%0, %1, %2"
  [(set_attr "type" "dmac")])

(define_insn "kmda64"
  [(set (match_operand:V2SI 0 "register_operand"                      "=r")
	(ss_plus:V2SI
	  (mult:V2SI
	    (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 1 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)])))
	    (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)]))))
	  (mult:V2SI
	    (sign_extend:V2SI (vec_select:V2HI
				(match_dup 1)
				(parallel [(const_int 0) (const_int 2)])))
	    (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmda\t%0, %1, %2"
  [(set_attr "type" "dmac")])

(define_insn "kmxda"
  [(set (match_operand:SI 0 "register_operand"                        "=r")
	(ss_plus:SI
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_operand:V2HI 1 "register_operand" "r")
			      (parallel [(const_int 1)])))
	    (sign_extend:SI (vec_select:HI
			      (match_operand:V2HI 2 "register_operand" "r")
			      (parallel [(const_int 0)]))))
	  (mult:SI
	    (sign_extend:SI (vec_select:HI
			      (match_dup 1)
			      (parallel [(const_int 0)])))
	    (sign_extend:SI (vec_select:HI
			      (match_dup 2)
			      (parallel [(const_int 1)]))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmxda\t%0, %1, %2"
  [(set_attr "type" "dmac")])

(define_insn "kmxda64"
  [(set (match_operand:V2SI 0 "register_operand"                      "=r")
	(ss_plus:V2SI
	  (mult:V2SI
	    (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 1 "register_operand" "r")
				(parallel [(const_int 1) (const_int 3)])))
	    (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" "r")
				(parallel [(const_int 0) (const_int 2)]))))
	  (mult:V2SI
	    (sign_extend:V2SI (vec_select:V2HI
				(match_dup 1)
				(parallel [(const_int 0) (const_int 2)])))
	    (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 1) (const_int 3)]))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmxda\t%0, %1, %2"
  [(set_attr "type" "dmac")])

(define_expand "kmabb"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")
   (match_operand:V2HI 3 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_kma_internal (operands[0], operands[2], operands[3],
			       GEN_INT (0), GEN_INT (0),
			       operands[1]));
  DONE;
}
[(set_attr "type" "dmac")])

(define_expand "kmabt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")
   (match_operand:V2HI 3 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_kma_internal (operands[0], operands[2], operands[3],
			       GEN_INT (0), GEN_INT (1),
			       operands[1]));
  DONE;
}
[(set_attr "type" "dmac")])

(define_expand "kmatt"
  [(match_operand:SI 0 "register_operand" "")
   (match_operand:SI 1 "register_operand" "")
   (match_operand:V2HI 2 "register_operand" "")
   (match_operand:V2HI 3 "register_operand" "")]
  "TARGET_DSP && !TARGET_64BIT"
{
  emit_insn (gen_kma_internal (operands[0], operands[2], operands[3],
			       GEN_INT (1), GEN_INT (1),
			       operands[1]));
  DONE;
}
[(set_attr "type" "dmac")])

(define_insn "kma_internal"
  [(set (match_operand:SI 0 "register_operand"                   "=   r,   r,   r,   r")
	(ss_plus:SI
	  (mult:SI
	    (sign_extend:SI
	      (vec_select:HI
		(match_operand:V2HI 1 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 3 "imm_0_1_operand" " v00, v00, v01, v01")])))
	    (sign_extend:SI
	      (vec_select:HI
	        (match_operand:V2HI 2 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 4 "imm_0_1_operand" " v00, v01, v01, v00")]))))
	  (match_operand:SI 5 "register_operand"                 "   0,   0,   0,   0")))]
  "TARGET_DSP && !TARGET_64BIT"
{
  const char *pats[] = { "kmabb\t%0, %1, %2",
			 "kmabt\t%0, %1, %2",
			 "kmatt\t%0, %1, %2",
			 "kmabt\t%0, %2, %1" };
  return pats[which_alternative];
}
  [(set_attr "type" "dmac")
   (set_attr "mode" "SI")])

(define_expand "kmabb64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2SI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")
   (match_operand:V4HI 3 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_kma64_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (2), GEN_INT (0),
				 GEN_INT (2), operands[1]));
  DONE;
}
[(set_attr "type" "dmac")])

(define_expand "kmabt64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2SI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")
   (match_operand:V4HI 3 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_kma64_internal (operands[0], operands[2], operands[3],
				 GEN_INT (0), GEN_INT (2), GEN_INT (1),
				 GEN_INT (3), operands[1]));
  DONE;
}
[(set_attr "type" "dmac")])

(define_expand "kmatt64"
  [(match_operand:V2SI 0 "register_operand" "")
   (match_operand:V2SI 1 "register_operand" "")
   (match_operand:V4HI 2 "register_operand" "")
   (match_operand:V4HI 3 "register_operand" "")]
  "TARGET_DSP && TARGET_64BIT"
{
  emit_insn (gen_kma64_internal (operands[0], operands[2], operands[3],
				 GEN_INT (1), GEN_INT (3), GEN_INT (1),
				 GEN_INT (3), operands[1]));
  DONE;
}
[(set_attr "type" "dmac")])

(define_insn "kma64_internal"
  [(set (match_operand:V2SI 0 "register_operand"                 "=   r,   r,   r,   r")
	(ss_plus:V2SI
	  (mult:V2SI
	    (sign_extend:V2SI
	      (vec_select:V2HI
		(match_operand:V4HI 1 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 3 "imm_0_1_operand" " v00, v00, v01, v01")
			   (match_operand:SI 4 "imm_2_3_operand" " v02, v02, v03, v03")])))
	    (sign_extend:V2SI
	      (vec_select:V2HI
	        (match_operand:V4HI 2 "register_operand"         "   r,   r,   r,   r")
	        (parallel [(match_operand:SI 5 "imm_0_1_operand" " v00, v01, v01, v00")
			   (match_operand:SI 6 "imm_2_3_operand" " v02, v03, v03, v02")]))))
	  (match_operand:V2SI 7 "register_operand"               "   0,   0,   0,   0")))]
  "TARGET_DSP && TARGET_64BIT"
  "@
  kmabb\t%0, %1, %2
  kmabt\t%0, %1, %2
  kmatt\t%0, %1, %2
  kmabt\t%0, %2, %1"
  [(set_attr "type" "dmac")
   (set_attr "mode" "V2SI")])

(define_insn "kmaxda"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_plus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmaxda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmaxda64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_plus:V2SI
	  (match_operand:V2SI 1 "register_operand"                       " 0")
	  (ss_plus:V2SI
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmaxda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmads"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmads\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmads64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_plus:V2SI
	  (match_operand:V2SI 1 "register_operand"                       " 0")
	  (ss_minus:V2SI
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 3 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)]))))
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 3)
				(parallel [(const_int 0) (const_int 2)])))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmads\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmadrs"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 2 "register_operand" " r")
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmadrs\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmadrs64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_plus:V2SI
	  (match_operand:V2SI 1 "register_operand"                       " 0")
	  (ss_minus:V2SI
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmadrs\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmaxds"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmaxds\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmaxds64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_plus:V2SI
	  (match_operand:V2SI 1 "register_operand"                       " 0")
	  (ss_minus:V2SI
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmaxds\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmsda"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_minus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmsda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmsda64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_minus:V2SI
	  (match_operand:V2SI 1 "register_operand"                       " 0")
	  (ss_minus:V2SI
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 3 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)]))))
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 3)
				(parallel [(const_int 0) (const_int 2)])))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmsda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmsxda"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_minus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_minus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 3 "register_operand" " r")
				(parallel [(const_int 0)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 1)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmsxda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmsxda64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_minus:V2SI
	  (match_operand:V2SI 1 "register_operand"                       " 0")
	  (ss_minus:V2SI
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 3 "register_operand" " r")
				(parallel [(const_int 0) (const_int 2)]))))
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 3)
				(parallel [(const_int 1) (const_int 3)])))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmsxda\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmada"
  [(set (match_operand:SI 0 "register_operand"                           "=r")
	(ss_plus:SI
	  (match_operand:SI 1 "register_operand"                         " 0")
	  (ss_plus:SI
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 2 "register_operand" " r")
				(parallel [(const_int 1)])))
	      (sign_extend:SI (vec_select:HI
				(match_operand:V2HI 3 "register_operand" " r")
				(parallel [(const_int 1)]))))
	    (mult:SI
	      (sign_extend:SI (vec_select:HI
				(match_dup 2)
				(parallel [(const_int 0)])))
	      (sign_extend:SI (vec_select:HI
				(match_dup 3)
				(parallel [(const_int 0)])))))))]
  "TARGET_DSP && !TARGET_64BIT"
  "kmada\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "kmada64"
  [(set (match_operand:V2SI 0 "register_operand"                         "=r")
	(ss_plus:V2SI
	  (match_operand:V2SI 1 "register_operand"                       " 0")
	  (ss_plus:V2SI
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 2 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_operand:V4HI 3 "register_operand" " r")
				(parallel [(const_int 1) (const_int 3)]))))
	    (mult:V2SI
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 2)
				(parallel [(const_int 0) (const_int 2)])))
	      (sign_extend:V2SI (vec_select:V2HI
				(match_dup 3)
				(parallel [(const_int 0) (const_int 2)])))))))]
  "TARGET_DSP && TARGET_64BIT"
  "kmada\t%0, %2, %3"
  [(set_attr "type" "dmac")])

(define_insn "sclip32<VD_SI:mode><X:mode>"
  [(set (match_operand:VD_SI 0 "register_operand" "=r")
	(unspec:VD_SI [(match_operand:VD_SI 1 "register_operand" "r")
		       (match_operand:X 2 "immediate_operand" "i")] UNSPEC_CLIPS_OV))]
  "TARGET_DSP"
  "sclip32\t%0, %1, %2"
  [(set_attr "type"   "dclip")
   (set_attr "mode" "<VD_SI:MODE>")])

(define_insn "uclip32<VD_SI:mode><X:mode>"
  [(set (match_operand:VD_SI 0 "register_operand" "=r")
	(unspec:VD_SI [(match_operand:VD_SI 1 "register_operand" "r")
		       (match_operand:X 2 "immediate_operand" "i")] UNSPEC_CLIP_OV))]
  "TARGET_DSP"
  "uclip32\t%0, %1, %2"
  [(set_attr "type"   "dclip")
   (set_attr "mode" "<VD_SI:MODE>")])

(define_insn "pbsad<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_PBSAD))]
  "TARGET_DSP"
  "pbsad\t%0, %1, %2"
  [(set_attr "type" "dmac")
   (set_attr "mode" "<MODE>")])

(define_insn "pbsada<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_PBSADA))]
  ""
  "pbsada\t%0, %2, %3"
  [(set_attr "type" "dmac")
   (set_attr "mode" "<MODE>")])

(define_insn "smaqa<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_SMAQA))]
  ""
  "smaqa\t%0, %2, %3"
  [(set_attr "type" "dmac")
   (set_attr "mode" "<MODE>")])

(define_insn "umaqa<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_UMAQA))]
  ""
  "umaqa\t%0, %2, %3"
  [(set_attr "type" "dmac")
   (set_attr "mode" "<MODE>")])

(define_insn "smaqasu<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_SMAQASU))]
  ""
  "smaqa.su\t%0, %2, %3"
  [(set_attr "type" "dmac")
   (set_attr "mode" "<MODE>")])

(define_insn "kaddh<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KADDH))]
  ""
  "kaddh\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "ksubh<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KSUBH))]
  ""
  "ksubh\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "khmbb<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KHMBB))]
  ""
  "khmbb\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "khmbt<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KHMBT))]
  ""
  "khmbt\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "khmtt<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KHMTT))]
  ""
  "khmtt\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "ukaddh<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_UKADDH))]
  ""
  "ukaddh\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "uksubh<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_UKSUBH))]
  ""
  "uksubh\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "kaddw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KADDW))]
  ""
  "kaddw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "ukaddw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_UKADDW))]
  ""
  "ukaddw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "ksubw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KSUBW))]
  ""
  "ksubw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "uksubw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_UKSUBW))]
  ""
  "uksubw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "kdmbb<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KDMBB))]
  ""
  "kdmbb\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "kdmbt<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KDMBT))]
  ""
  "kdmbt\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "kdmtt<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KDMTT))]
  ""
  "kdmtt\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "kslraw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KSLRAW))]
  ""
  "kslraw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "kslrawu<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KSLRAWU))]
  ""
  "kslraw.u\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "ksllw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_KSLLW))]
  ""
  "ksllw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "kslliw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "rimm5u_operand" "")] UNSPEC_KSLLIW))]
  ""
  "kslliw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])


(define_insn "kdmabb<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_KDMABB))]
  ""
  "kdmabb\t%0, %2, %3"
  [(set_attr "mode" "<MODE>")])

(define_insn "kdmabt<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_KDMABT))]
  ""
  "kdmabt\t%0, %2, %3"
  [(set_attr "mode" "<MODE>")])

(define_insn "kdmatt<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "0")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_KDMATT))]
  ""
  "kdmatt\t%0, %2, %3"
  [(set_attr "mode" "<MODE>")])

(define_insn "kabsw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")] UNSPEC_KABSW))]
  ""
  "kabsw\t%0, %1"
  [(set_attr "mode" "<MODE>")])

(define_insn "raddw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_RADDW))]
  ""
  "raddw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "uraddw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_URADDW))]
  ""
  "uraddw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "rsubw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_RSUBW))]
  ""
  "rsubw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "ursubw<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_URSUBW))]
  ""
  "ursubw\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "ave<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_AVE))]
  ""
  "ave\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "sraiu"
  [(set (match_operand:SI 0 "register_operand"                          "=  r, r")
	(unspec:SI [(ashiftrt:SI (match_operand:SI 1 "register_operand" "   r, r")
				 (match_operand:SI 2 "rimm5u_operand"   " u05, r"))]
		    UNSPEC_ROUND))]
  "TARGET_DSP && !TARGET_64BIT"
  "@
   srai.u\t%0, %1, %2
   sra.u\t%0, %1, %2"
  [(set_attr "type"   "daluround")
   (set_attr "mode"   "SI")])

(define_insn "sraiu64"
  [(set (match_operand:DI 0 "register_operand"                          "=  r, r")
	(unspec:DI [(ashiftrt:DI (match_operand:DI 1 "register_operand" "   r, r")
				 (match_operand:DI 2 "rimm6u_operand"   " u06, r"))]
		    UNSPEC_ROUND))]
  "TARGET_DSP && TARGET_64BIT"
  "@
   srai.u\t%0, %1, %2
   sra.u\t%0, %1, %2"
  [(set_attr "type"   "daluround")
   (set_attr "mode"   "DI")])

(define_insn "bitrev"
  [(set (match_operand:SI 0 "register_operand"             "=r,   r")
	(unspec:SI [(match_operand:SI 1 "register_operand" " r,   r")
		    (match_operand:SI 2 "rimm5u_operand"   " r, u05")]
		   UNSPEC_BITREV))]
  "TARGET_DSP && !TARGET_64BIT"
  "@
   bitrev\t%0, %1, %2
   bitrevi\t%0, %1, %2"
  [(set_attr "type"   "dalu")
   (set_attr "mode"   "SI")])

(define_insn "bitrev64"
  [(set (match_operand:DI 0 "register_operand"             "=r,   r")
	(unspec:DI [(match_operand:DI 1 "register_operand" " r,   r")
		    (match_operand:SI 2 "rimm6u_operand"   " r, u06")]
		   UNSPEC_BITREV))]
  "TARGET_DSP && TARGET_64BIT"
  "@
   bitrev\t%0, %1, %2
   bitrevi\t%0, %1, %2"
  [(set_attr "type"   "dalu")
   (set_attr "mode"   "SI")])

(define_insn "bpick1<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")
		     (match_operand:GPR 3 "register_operand" "r")] UNSPEC_BPICK))]
  "TARGET_DSP"
  "bpick\t%0, %1, %2, %3"
  [(set_attr "type"   "dbpick")
   (set_attr "mode"   "<MODE>")])

(define_insn "maddr32<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_MADDR32))]
  ""
  "maddr32\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "smaxsi3"
  [(set (match_operand:SI 0 "register_operand"          "=r")
	(smax:SI (match_operand:SI 1 "register_operand" " r")
		 (match_operand:SI 2 "register_operand" " r")))]
  "TARGET_DSP"
  "maxw\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "SI")])

(define_insn "sminsi3"
  [(set (match_operand:SI 0 "register_operand"          "=r")
	(smin:SI (match_operand:SI 1 "register_operand" " r")
		 (match_operand:SI 2 "register_operand" " r")))]
  "TARGET_DSP"
  "minw\t%0, %1, %2"
  [(set_attr "type" "dalu")
   (set_attr "mode" "SI")])

(define_insn "msubr32<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")
		     (match_operand:GPR 2 "register_operand" "r")] UNSPEC_MSUBR32))]
  ""
  "msubr32\t%0, %1, %2"
  [(set_attr "mode" "<MODE>")])

(define_insn "dsp_mulsidi3"
  [(set (match_operand:DI 0 "register_operand"                          "=r")
	(mult:DI (sign_extend:DI (match_operand:SI 1 "register_operand" " r"))
		 (sign_extend:DI (match_operand:SI 2 "register_operand" " r"))))]
  "TARGET_DSP"
  "mulsr64\t%0, %1, %2"
  [(set_attr "type"   "dmul")
   (set_attr "mode"   "DI")])

(define_insn "dsp_umulsidi3"
  [(set (match_operand:DI 0 "register_operand"                          "=r")
	(mult:DI (zero_extend:DI (match_operand:SI 1 "register_operand" " r"))
		 (zero_extend:DI (match_operand:SI 2 "register_operand" " r"))))]
  "TARGET_DSP"
  "mulr64\t%0, %1, %2"
  [(set_attr "type"   "dmul")
   (set_attr "mode"   "DI")])
