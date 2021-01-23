(define_mode_iterator VQIHI [(V4QI "!TARGET_64BIT") (V2HI "!TARGET_64BIT")
    (V8QI "TARGET_64BIT") (V4HI "TARGET_64BIT")])

(define_mode_iterator VECI [(V4QI "!TARGET_64BIT") (V2HI "!TARGET_64BIT")
    (V8QI "TARGET_64BIT") (V4HI "TARGET_64BIT")
    (V2SI "TARGET_64BIT")])

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
