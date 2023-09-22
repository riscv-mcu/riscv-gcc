;; Post modified load and store

(define_insn "load<mode>_ind_postinc"
  [(set (match_operand:SUBDISF 0 "register_operand" "=r")
        (mem:SUBDISF (post_inc:SI (match_operand:SI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_XXLCZPSTINC"
  "xl.l<size_load_store>\t%0,<size_mem>(%1)\t# load post inc"
  [(set_attr "type" "load")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "load<mode>_<u>ext_ind_postinc"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (any_extend:SI
             (mem:SUBDISF (post_inc:SI (match_operand:SI 1 "register_operand" "+r")))
        )
   )
  ]
  "TARGET_XXLCZPSTINC"
  "xl.l<size_load_store><u>\t%0,<size_mem>(%1)\t# load post inc, ext"
  [(set_attr "type" "load")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "load<mode>_ind_postdec"
  [(set (match_operand:SUBDISF 0 "register_operand" "=r")
        (mem:SUBDISF (post_dec:SI (match_operand:SI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_XXLCZPSTINC"
  "xl.l<size_load_store>\t%0,-<size_mem>(%1)\t# load post dec"
  [(set_attr "type" "load")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "load<mode>_<u>ext_ind_postdec"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (any_extend:SI
             (mem:SUBDISF (post_dec:SI (match_operand:SI 1 "register_operand" "+r")))
        )
   )
  ]
  "TARGET_XXLCZPSTINC"
  "xl.l<size_load_store><u>\t%0,-<size_mem>(%1)\t# load post dec, ext"
  [(set_attr "type" "load")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "store<mode>_ind_postinc"
  [(set (mem:SUBDISF (post_inc:SI (match_operand:SI 0 "register_operand" "+r,r")))
        (match_operand:SUBDISF 1 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_XXLCZPSTINC"
  "@
   xl.s<size_load_store>\t%1,<size_mem>(%0)\t# store post inc
   xl.s<size_load_store>\tx0,<size_mem>(%0)\t# store 0 post inc"
  [(set_attr "type" "store,store")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "store<mode>_ind_postdec"
  [(set (mem:SUBDISF (post_dec:SI (match_operand:SI 0 "register_operand" "+r,r")))
        (match_operand:SUBDISF 1 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_XXLCZPSTINC"
  "@
   xl.s<size_load_store>\t%1,-<size_mem>(%0)\t# store post dec
   xl.s<size_load_store>\tx0,-<size_mem>(%0)\t# store 0 post dec"
  [(set_attr "type" "store,store")
   (set_attr "mode" "<LDSTINDMODE>")]
)

;; Bitop insns

(define_insn "xl_bclrsi4"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_BCLR))]
"TARGET_XXLCZBITOP"
"xl.bclr \t%0,%1,%2,%3 # Bit clear"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_bclrsi3_reg"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_BCLRR))]
  "TARGET_XXLCZBITOP"
  "xl.bclrr \t%0,%1,%2 # Bit clear reg"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_bsetsi4"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_BSET))]
  "TARGET_XXLCZBITOP"
  "xl.bset \t%0,%1,%2,%3 # Bit set"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_bsetsi3_reg"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_BSETR))]
  "TARGET_XXLCZBITOP"
  "xl.bsetr \t%0,%1,%2 # Bit set reg"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_extractsi4"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_EXTRACT))]
  "TARGET_XXLCZBITOP"
  "xl.extract \t%0,%1,%2,%3 # Bit extract signed"
  [(set_attr "type" "logical")
   (set_attr "length" "1")]
)

(define_insn "xl_extractsi3_reg"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_EXTRACTR))]
  "TARGET_XXLCZBITOP"
  "xl.extractr \t%0,%1,%2 # Bit extract signed, arg reg"
  [(set_attr "type" "logical")
   (set_attr "length" "1")]
)

(define_insn "xl_extractusi4"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_EXTRACTU))]
  "TARGET_XXLCZBITOP"
  "xl.extractu\t%0,%1,%2,%3 # Bit extract unsigned"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_extractusi3_reg"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_EXTRACTUR))]
  "TARGET_XXLCZBITOP"
  "xl.extractur\t%0,%1,%2 # Bit extract unsigned, reg arg";
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_insertsi4"
  [(set	(match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_INSERT))]
  "TARGET_XXLCZBITOP"
  "xl.insert\t%0,%1,%2,%3"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_ff1si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FF1))]
"TARGET_XXLCZBITOP"
"xl.ff1 \t%0,%1\t# position of first set bit from lsb"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_fl1si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FL1))]
"TARGET_XXLCZBITOP"
"xl.fl1 \t%0,%1\t# position of first set bit from msb"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_ff0si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FF0))]
"TARGET_XXLCZBITOP"
"xl.ff0 \t%0,%1\t# position of first clr bit from lsb"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_fl0si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FL0))]
"TARGET_XXLCZBITOP"
"xl.fl0 \t%0,%1\t# position of first clr bit from msb"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_clbsi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (unspec:QI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_XXLCZ_CLB))]
  "TARGET_XXLCZBITOP"
  "xl.clb\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "xl_slet<u>si3"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (any_le:SI (match_operand:SI 1 "register_operand" "r")
                   (match_operand:SI 2 "register_operand" "r")))]
  "TARGET_XXLCZSLET"
  "xl.slet<u>\t%0,%1,%2"
  [(set_attr "type" "slt")
   (set_attr "mode" "SI")])


(define_insn "xl_mulisi3"
  [(set (match_operand:SI  0 "register_operand" "=r")
  (mult:SI (match_operand:SI 1 "register_operand" "r")
           (sign_extend:SI
           (match_operand:HI 2 "immediate_operand" "i"))))]
  "TARGET_XXLCZMAC"
  "xl.muli\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "SI")])

(define_insn "xl_bitrevsi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:QI 2 "immediate_operand" "i")
                    (match_operand:QI 3 "immediate_operand" "i")]
         UNSPEC_XXLCZ_BITREV))]
  "TARGET_XXLCZBITREV"
  "xl.bitrev\t%0,%1,%2,%3"
  [(set_attr "type" "bitmanip")
  (set_attr "mode" "SI")])

(define_insn "*xxlcz_branching<mode>"
  [(set (pc)
	(if_then_else
	 (match_operator 1 "xxlcz_branching_operator"
			 [(match_operand:X 2 "register_operand" "r")
			  (match_operand:X 3 "imm5z_operand" "C05")])
	 (label_ref (match_operand 0 "" ""))
	 (pc)))]
  "TARGET_XXLCZBRI"
  "xl.b%C1i\t%2,%z3,%0"
  [(set_attr "type" "branch")
   (set_attr "mode" "none")])

(define_insn "xl_nzmsksi2"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_NZMSK))]
"TARGET_XXLCZBMRK"
"xl.nzmsk\t%0,%1"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_ffnzsi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FFNZ))]
"TARGET_XXLCZBMRK"
"xl.ffnz\t%0,%1"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_addrchksi3"
  [(unspec:SI [(match_operand:SI 0 "register_operand" "r")
                (match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "immediate_operand" "i")]
  UNSPEC_XXLCZ_ADDRCHK)]
"TARGET_XXLCZBMRK"
"xl.addrchk\t%0,%1,%2"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_bezmsi3"
  [(unspec:SI [(match_operand:SI 0 "register_operand" "r")
                (match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "immediate_operand" "i")]
  UNSPEC_XXLCZ_BEZM)]
"TARGET_XXLCZBMRK"
"xl.bezm\t%0,%1,%2"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)
