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

(define_mode_attr VNHALF [(V2SI "SI") (V2HI "HI")])

(define_mode_attr VSH_EXT [(V2SI "DI") (V2HI "SI")])

(define_mode_attr bits [(V8QI "8") (V4QI "8") (QI "8") (V4HI "16") (V2HI "16")
    (HI "16") (V2SI "32") (DI "64")])

(define_code_attr uk
    [(plus "") (ss_plus "k") (us_plus "uk")
    (minus "") (ss_minus "k") (us_minus "uk")])

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
