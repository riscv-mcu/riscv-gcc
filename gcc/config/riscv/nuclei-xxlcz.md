;; Post modified load and store

(define_insn "load<mode>_ind_postinc"
  [(set (match_operand:SUBDISF 0 "register_operand" "=r")
        (mem:SUBDISF (post_inc:SI (match_operand:SI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.l<size_load_store>\t%0,<size_mem>(%1)\t# load post inc"
  [(set_attr "type" "load")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "load_di_ind_postinc"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (mem:DI (post_inc:DI (match_operand:DI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_64BIT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.ld\t%0,8(%1)\t# load post inc"
  [(set_attr "type" "load")
   (set_attr "mode" "DI")]
)


(define_insn "load_di_ind_postdec"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (mem:DI (post_dec:DI (match_operand:DI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_64BIT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.ld\t%0,-8(%1)\t# load post dec"
  [(set_attr "type" "load")
   (set_attr "mode" "DI")]
)

(define_insn "store_di_ind_postinc"
  [(set (mem:DI (post_inc:DI (match_operand:DI 0 "register_operand" "+r,r")))
        (match_operand:DI 1 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_64BIT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "@
   xl.sd\t%1,8(%0)\t# store post inc
   xl.sd\tx0,8(%0)\t# store 0 post inc"
  [(set_attr "type" "store,store")
   (set_attr "mode" "DI")]
)

(define_insn "store_di_ind_postdec"
  [(set (mem:DI (post_dec:DI (match_operand:DI 0 "register_operand" "+r,r")))
        (match_operand:DI 1 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_64BIT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "@
   xl.sd\t%1,-8(%0)\t# store post dec
   xl.sd\tx0,-8(%0)\t# store 0 post dec"
  [(set_attr "type" "store,store")
   (set_attr "mode" "DI")]
)

(define_insn "load_hf_ind_postinc<GPR:mode>"
  [(set (match_operand:HF 0 "register_operand" "=f")
        (mem:HF (post_inc:GPR (match_operand:GPR 1 "register_operand" "+r")))
   )
  ]
  "TARGET_ZFHMIN && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.flh\t%0,2(%1)\t# load float post inc"
  [(set_attr "type" "load")
   (set_attr "mode" "HF")]
)

(define_insn "store_hf_ind_postinc<GPR:mode>"
  [(set (mem:HF (post_inc:GPR (match_operand:GPR 0 "register_operand" "+r")))
        (match_operand:HF 1 "register_operand" "f")
   )
  ]
  "TARGET_ZFHMIN && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fsh\t%1,2(%0)\t# store float post inc"
  [(set_attr "type" "store")
   (set_attr "mode" "HF")]
)

(define_insn "load_hf_ind_postdec<GPR:mode>"
  [(set (match_operand:HF 0 "register_operand" "=f")
        (mem:HF (post_dec:GPR (match_operand:GPR 1 "register_operand" "+r")))
   )
  ]
  "TARGET_ZFHMIN && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.flh\t%0,-2(%1)\t# load float post dec"
  [(set_attr "type" "load")
   (set_attr "mode" "SF")]
)

(define_insn "store_hf_ind_postdec<GPR:mode>"
  [(set (mem:HF (post_dec:GPR (match_operand:GPR 0 "register_operand" "+r")))
        (match_operand:HF 1 "register_operand" "f")
   )
  ]
  "TARGET_ZFHMIN && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fsh\t%1,-2(%0)\t# store float post dec"
  [(set_attr "type" "store")
   (set_attr "mode" "HF")]
)

(define_insn "load_sf_ind_postinc<GPR:mode>"
  [(set (match_operand:SF 0 "register_operand" "=f")
        (mem:SF (post_inc:GPR (match_operand:GPR 1 "register_operand" "+r")))
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.flw\t%0,4(%1)\t# load float post inc"
  [(set_attr "type" "load")
   (set_attr "mode" "SF")]
)

(define_insn "store_sf_ind_postinc<GPR:mode>"
  [(set (mem:SF (post_inc:GPR (match_operand:GPR 0 "register_operand" "+r")))
        (match_operand:SF 1 "register_operand" "f")
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fsw\t%1,4(%0)\t# store float post inc"
  [(set_attr "type" "store")
   (set_attr "mode" "SF")]
)

(define_insn "load_sf_ind_postdec<GPR:mode>"
  [(set (match_operand:SF 0 "register_operand" "=f")
        (mem:SF (post_dec:GPR (match_operand:GPR 1 "register_operand" "+r")))
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.flw\t%0,-4(%1)\t# load float post dec"
  [(set_attr "type" "load")
   (set_attr "mode" "SF")]
)

(define_insn "store_sf_ind_postdec<GPR:mode>"
  [(set (mem:SF (post_dec:GPR (match_operand:GPR 0 "register_operand" "+r")))
        (match_operand:SF 1 "register_operand" "f")
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fsw\t%1,-4(%0)\t# store float post dec"
  [(set_attr "type" "store")
   (set_attr "mode" "SF")]
)

(define_insn "load_df_ind_postinc<GPR:mode>"
  [(set (match_operand:DF 0 "register_operand" "=f")
        (mem:DF (post_inc:GPR (match_operand:GPR 1 "register_operand" "+r")))
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fld\t%0,8(%1)\t# load fp post inc"
  [(set_attr "type" "load")
   (set_attr "mode" "DF")]
)


(define_insn "load_df_ind_postdec<GPR:mode>"
  [(set (match_operand:DF 0 "register_operand" "=f")
        (mem:DF (post_dec:GPR (match_operand:GPR 1 "register_operand" "+r")))
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fld\t%0,-8(%1)\t# load fp post dec"
  [(set_attr "type" "load")
   (set_attr "mode" "DF")]
)


(define_insn "store_df_ind_postinc<GPR:mode>"
  [(set (mem:DF (post_inc:GPR (match_operand:GPR 0 "register_operand" "+r")))
        (match_operand:DF 1 "register_operand" "f")
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fsd\t%1,8(%0)\t# store fp post inc"
  [(set_attr "type" "store")
   (set_attr "mode" "DF")]
)

(define_insn "store_df_ind_postdec<GPR:mode>"
  [(set (mem:DF (post_dec:GPR (match_operand:GPR 0 "register_operand" "+r")))
        (match_operand:DF 1 "register_operand" "f")
   )
  ]
  "TARGET_HARD_FLOAT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fsd\t%1,-8(%0)\t# store fp post dec"
  [(set_attr "type" "store")
   (set_attr "mode" "DF")]
)

(define_insn "load<mode>_<u>ext_ind_postinc"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (any_extend:SI
             (mem:SUBDISF (post_inc:SI (match_operand:SI 1 "register_operand" "+r")))
        )
   )
  ]
  "TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.l<size_load_store><u>\t%0,<size_mem>(%1)\t# load post inc, ext"
  [(set_attr "type" "load")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "load<mode>_ind_postdec"
  [(set (match_operand:SUBDISF 0 "register_operand" "=r")
        (mem:SUBDISF (post_dec:SI (match_operand:SI 1 "register_operand" "+r")))
   )
  ]
  "TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
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
  "TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.l<size_load_store><u>\t%0,-<size_mem>(%1)\t# load post dec, ext"
  [(set_attr "type" "load")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "store<mode>_ind_postinc"
  [(set (mem:SUBDISF (post_inc:SI (match_operand:SI 0 "register_operand" "+r,r")))
        (match_operand:SUBDISF 1 "nonmemory_operand" "r,J")
   )
  ]
  "TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
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
  "TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "@
   xl.s<size_load_store>\t%1,-<size_mem>(%0)\t# store post dec
   xl.s<size_load_store>\tx0,-<size_mem>(%0)\t# store 0 post dec"
  [(set_attr "type" "store,store")
   (set_attr "mode" "<LDSTINDMODE>")]
)

(define_insn "load_di_ind_postinc2"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (zero_extend:DI
          (mem:SI (post_inc:DI (match_operand:DI 1 "register_operand" "+r")))
        )
   )
  ]
  "TARGET_64BIT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.lwu\t%0,4(%1)\t# load word unsigned post inc"
  [(set_attr "type" "load")
   (set_attr "mode" "DI")]
)

(define_insn "load_di_ind_postdec2"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (zero_extend:DI
          (mem:SI (post_dec:DI (match_operand:DI 1 "register_operand" "+r")))
        )
   )
  ]
  "TARGET_64BIT && TARGET_XXLCZPSTINC && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.lwu\t%0,-4(%1)\t# load word unsigned post dec"
  [(set_attr "type" "load")
   (set_attr "mode" "DI")]
)

;; Bitop insns

(define_insn "xl_bclrsi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
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
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_BCLRR))]
  "TARGET_XXLCZBITOP"
  "xl.bclrr \t%0,%1,%2 # Bit clear reg"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_bclrdi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_BCLR))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.bclr \t%0,%1,%2,%3 # Bit clear"
[(set_attr "type" "logical")
 (set_attr "mode" "DI")]
)

(define_insn "xl_bclrdi3_reg"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_BCLRR))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.bclrr \t%0,%1,%2 # Bit clear reg"
[(set_attr "type" "logical")
 (set_attr "mode" "DI")]
)

(define_insn "xl_bsetsi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
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
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:HI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_BSETR))]
  "TARGET_XXLCZBITOP"
  "xl.bsetr \t%0,%1,%2 # Bit set reg"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_bsetdi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_BSET))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.bset \t%0,%1,%2,%3 # Bit set"
[(set_attr "type" "logical")
 (set_attr "mode" "DI")]
)

(define_insn "xl_bsetdi3_reg"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_BSETR))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.bsetr \t%0,%1,%2 # Bit set reg"
[(set_attr "type" "logical")
 (set_attr "mode" "DI")]
)

;; Auto-match for contiguous mask set: x | (((1 << len) - 1) << pos) -> xl.bset
;; Only for byte-wide or wider masks (len >= 8); shorter runs stay on
;; standard andi/ori sequences.
(define_insn "*bset<mode>_xlcz"
  [(set (match_operand:GPR 0 "register_operand" "=r")
        (ior:GPR (match_operand:GPR 1 "register_operand" "r")
                 (match_operand:GPR 2 "xxlcz_contiguous_mask_8_31" "i")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN"
{
  HOST_WIDE_INT mask = INTVAL (operands[2]);
  unsigned HOST_WIDE_INT umask = (unsigned HOST_WIDE_INT)mask;
  int pos = 0;
  int len = 0;
  unsigned HOST_WIDE_INT m = umask;
  while ((m & 1) == 0 && m != 0) { pos++; m >>= 1; }
  len = 0;
  while (m & 1) { len++; m >>= 1; }
  rtx tmp[4];
    tmp[0] = operands[0];
    tmp[1] = operands[1];
    /* Per the Nuclei spec the first immediate is (len - 1):
       mask = ((1 << (uimm3 + 1)) - 1) << uimm2.  */
    tmp[2] = GEN_INT (len - 1);
    tmp[3] = GEN_INT (pos);
    output_asm_insn (\"xl.bset\\t%0,%1,%2,%3\", tmp);
    return \"\";
  }
  [(set_attr "type" "logical")
   (set_attr "mode" "<GPR:MODE>")])

;; Auto-match for contiguous mask clear: x & ~(((1 << len) - 1) << pos) -> xl.bclr
(define_insn "*bclr<mode>_xlcz"
  [(set (match_operand:GPR 0 "register_operand" "=r")
        (and:GPR (match_operand:GPR 1 "register_operand" "r")
                 (match_operand:GPR 2 "xxlcz_not_contiguous_mask_8_31" "i")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN"
{
  HOST_WIDE_INT not_mask = INTVAL (operands[2]);
  unsigned HOST_WIDE_INT umask = (unsigned HOST_WIDE_INT)(~not_mask);
  int pos = 0;
  int len = 0;
  unsigned HOST_WIDE_INT m = umask;
  while ((m & 1) == 0 && m != 0) { pos++; m >>= 1; }
  len = 0;
  while (m & 1) { len++; m >>= 1; }
  rtx tmp[4];
    tmp[0] = operands[0];
    tmp[1] = operands[1];
    /* Per the Nuclei spec the first immediate is (len - 1):
       mask = ((1 << (uimm3 + 1)) - 1) << uimm2.  */
    tmp[2] = GEN_INT (len - 1);
    tmp[3] = GEN_INT (pos);
    output_asm_insn (\"xl.bclr\\t%0,%1,%2,%3\", tmp);
    return \"\";
  }
  [(set_attr "type" "logical")
   (set_attr "mode" "<GPR:MODE>")])

;; xl.extract rd, rs1, uimm3(len), uimm2(bottom) - Extract signed, immediate
;; NOTE: there is deliberately no auto-match (sign_extract) pattern for the
;; signed form.  combine would otherwise synthesize xl.extract for plain
;; shift-pair idioms ((x >> p) << n) >> n) where the shift sequence is just
;; as good; signed bitfields reach the extv<mode> expander instead, which
;; emits the instruction directly.
(define_insn "xl_extractsi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "const_1_31_operand" "i")
                (match_operand:SI 3 "const_0_31_operand" "i")]
  UNSPEC_XXLCZ_EXTRACT))]
  "TARGET_XXLCZBITOP"
  "xl.extract \t%0,%1,%2,%3"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "SI")]
)

(define_insn "xl_extractdi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:DI 2 "const_1_63_operand" "i")
                (match_operand:DI 3 "const_0_63_operand" "i")]
  UNSPEC_XXLCZ_EXTRACT))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.extract \t%0,%1,%2,%3"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "DI")]
)

;; xl.extractr rd, rs1, rs2 - Extract signed, register
;; rs2[4:0] = bottom, rs2[9:5] = len
(define_insn "xl_extractsi3_reg"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_EXTRACTR))]
  "TARGET_XXLCZBITOP"
  "xl.extractr \t%0,%1,%2"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "SI")]
)

(define_insn "xl_extractdi3_reg"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:DI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_EXTRACTR))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.extractr \t%0,%1,%2"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "DI")]
)

;; xl.extractu rd, rs1, uimm3(len), uimm2(bottom) - Extract unsigned, immediate
(define_insn "xl_extractusi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "const_1_31_operand" "i")
                (match_operand:SI 3 "const_0_31_operand" "i")]
  UNSPEC_XXLCZ_EXTRACTU))]
  "TARGET_XXLCZBITOP"
  "xl.extractu\t%0,%1,%2,%3"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "SI")]
)

(define_insn "xl_extractudi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:DI 2 "const_1_63_operand" "i")
                (match_operand:DI 3 "const_0_63_operand" "i")]
  UNSPEC_XXLCZ_EXTRACTU))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.extractu\t%0,%1,%2,%3"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "DI")]
)

;; xl.extractur rd, rs1, rs2 - Extract unsigned, register
;; rs2[4:0] = bottom, rs2[9:5] = len
(define_insn "xl_extractusi3_reg"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_EXTRACTUR))]
  "TARGET_XXLCZBITOP"
  "xl.extractur\t%0,%1,%2"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "SI")]
)

(define_insn "xl_extractudi3_reg"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:DI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_EXTRACTUR))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.extractur\t%0,%1,%2"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "DI")]
)

;; Extract unsigned bitfield (auto match for xl.extractu)
;; Zero-extend extract from rs1[pos : pos+len-1]
;; operand2 = len, operand3 = pos
;; pos must be <= 31 (gas 'bi' constraint is 5 bits), even on DI mode.
(define_insn "*xl_extractu<mode>4"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(zero_extract:GPR (match_operand:GPR 1 "register_operand" "r")
			 (match_operand 2 "const_int_operand" "i")
			 (match_operand 3 "const_int_operand" "i")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN && INTVAL (operands[2]) >= 1 && INTVAL (operands[2]) <= 31 && INTVAL (operands[3]) <= 31 && INTVAL (operands[2]) + INTVAL (operands[3]) <= GET_MODE_BITSIZE (<MODE>mode)"
  {
    /* len is operand2, pos is operand3 -> output matches instruction format */
    return \"xl.extractu\\t%0,%1,%2,%3\";
  }
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "<GPR:MODE>")])

(define_insn "xl_insertsi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_INSERT))]
  "TARGET_XXLCZBITOP"
  "xl.insert\t%0,%1,%2,%3"
[(set_attr "type" "logical")
 (set_attr "mode" "SI")]
)

(define_insn "xl_insertdi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:QI 2 "immediate_operand" "i")
                (match_operand:QI 3 "immediate_operand" "i")]
  UNSPEC_XXLCZ_INSERT))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.insert\t%0,%1,%2,%3"
[(set_attr "type" "logical")
 (set_attr "mode" "DI")]
)

;; xl.insertr rd, rs1, rs2 - Insert, register version
;; rs2[4:0] = bottom, rs2[9:5] = len
(define_insn "xl_insertsi3_reg"
  [(set (match_operand:SI 0 "register_operand" "=r")
    (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                (match_operand:SI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_INSERTR))]
  "TARGET_XXLCZBITOP"
  "xl.insertr\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "SI")])

(define_insn "xl_insertdi3_reg"
  [(set (match_operand:DI 0 "register_operand" "=r")
    (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                (match_operand:DI 2 "register_operand" "r")]
  UNSPEC_XXLCZ_INSERTR))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.insertr\t%0,%1,%2"
  [(set_attr "type" "logical")
   (set_attr "mode" "DI")])


(define_insn "xl_ff1si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FF1))]
"TARGET_XXLCZBITOP"
"xl.ff1 \t%0,%1\t# first '1' from MSB = highest set bit index"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_fl1si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FL1))]
"TARGET_XXLCZBITOP"
"xl.fl1 \t%0,%1\t# last '1' seen from MSB = lowest set bit index"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_ff0si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FF0))]
"TARGET_XXLCZBITOP"
"xl.ff0 \t%0,%1\t# first '0' from MSB = highest clear bit index"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_fl0si2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:SI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FL0))]
"TARGET_XXLCZBITOP"
"xl.fl0 \t%0,%1\t# last '0' seen from MSB = lowest clear bit index"
[(set_attr "type" "arith")
 (set_attr "mode" "SI")]
)

(define_insn "xl_ff1di2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:DI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FF1))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.ff1 \t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "xl_fl1di2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:DI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FL1))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.fl1 \t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "xl_ff0di2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:DI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FF0))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.ff0 \t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "xl_fl0di2"
  [(set (match_operand:QI 0 "register_operand" "=r")
    (unspec:QI [(match_operand:DI 1 "register_operand" "r")]
  UNSPEC_XXLCZ_FL0))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.fl0 \t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

;; GPR-output variant of xl.ff1 (find the first '1' seen from the MSB),
;; which returns the bit index of the most significant set bit counted
;; from bit 0.  Used by the clz auto-match sequence below.
(define_insn "*xl_ff1_gpr<mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(unspec:GPR [(match_operand:GPR 1 "register_operand" "r")] UNSPEC_XXLCZ_FF1))]
  "TARGET_XXLCZBITOP"
  "xl.ff1\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "<GPR:MODE>")])

;; Auto-match for GCC standard CTZ (count trailing zeros) -> xl.fl1.
;; xl.fl1 (find the last '1' seen from the MSB, i.e. the least significant
;; set bit) returns its bit index, which equals the number of trailing
;; zeros.
(define_insn "*ctz<mode>2_xlcz"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(ctz:GPR (match_operand:GPR 1 "register_operand" "r")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fl1\t%0,%1"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "<GPR:MODE>")])

;; Auto-match for GCC standard CLZ (count leading zeros) -> xl.ff1 + xori.
;; xl.ff1 returns the bit index i of the most significant set bit, so
;; clz is (XLEN - 1) - i.  Since i is in [0, XLEN-1] the subtraction
;; from the all-ones value never borrows, and (XLEN - 1) - i equals
;; (XLEN - 1) ^ i, emitted as xl.ff1 + xori.
(define_insn_and_split "*clz<mode>2_xlcz"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(clz:GPR (match_operand:GPR 1 "register_operand" "r")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "#"
  "&& 1"
  [(set (match_dup 0)
	(unspec:GPR [(match_dup 1)] UNSPEC_XXLCZ_FF1))
   (set (match_dup 0)
	(xor:GPR (match_dup 0) (match_dup 2)))]
  {
    operands[2] = gen_int_mode (GET_MODE_BITSIZE (<GPR:MODE>mode) - 1,
				<GPR:MODE>mode);
  }
  [(set_attr "type" "multi")
   (set_attr "mode" "<GPR:MODE>")])

(define_insn "xl_clbsi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (unspec:QI [(match_operand:SI 1 "register_operand" "r")] UNSPEC_XXLCZ_CLB))]
  "TARGET_XXLCZBITOP"
  "xl.clb\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "SI")])

(define_insn "xl_clbdi2"
  [(set (match_operand:QI 0 "register_operand" "=r")
        (unspec:QI [(match_operand:DI 1 "register_operand" "r")] UNSPEC_XXLCZ_CLB))]
  "TARGET_XXLCZBITOP && TARGET_64BIT"
  "xl.clb\t%0,%1"
  [(set_attr "type" "arith")
   (set_attr "mode" "DI")])

(define_insn "xl_slet<u>si3<GPR:mode>"
  [(set (match_operand:GPR 0 "register_operand" "=r")
        (any_le:GPR (match_operand:GPR 1 "register_operand" "r")
                   (match_operand:GPR 2 "register_operand" "r")))]
  "TARGET_XXLCZSLET && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.slet<u>\t%0,%1,%2"
  [(set_attr "type" "arith")
   (set_attr "mode" "none")])

(define_insn "xl_mulisi3"
  [(set (match_operand:SI        0 "register_operand" "=r")
	(mult:SI (match_operand:SI 1 "register_operand" " r")
		 (match_operand:SI 2 "const_arith_operand" " I")))]
  "(TARGET_ZMMUL || TARGET_MUL) && !TARGET_64BIT &&TARGET_XXLCZMAC && TARGET_NUCLEI_XXLCZ_AUTOGEN && (INTVAL (operands[2]) >= 0) && (INTVAL (operands[2]) <= 255)"
  "xl.muli\t%0,%1,%2"
  [(set_attr "type" "imul")
   (set_attr "mode" "none")])

(define_insn "xl_bitrevsi4"
  [(set (match_operand:SI 0 "register_operand" "=r")
        (unspec:SI [(match_operand:SI 1 "register_operand" "r")
                    (match_operand:SI 2 "const_0_2_operand" "i")
                    (match_operand:SI 3 "const_0_31_operand" "i")]
         UNSPEC_XXLCZ_BITREV))]
  "TARGET_XXLCZBITREV"
  "xl.bitrev\t%0,%1,%2,%3"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "SI")])

(define_insn "xl_bitrevdi4"
  [(set (match_operand:DI 0 "register_operand" "=r")
        (unspec:DI [(match_operand:DI 1 "register_operand" "r")
                    (match_operand:DI 2 "const_0_2_operand" "i")
                    (match_operand:DI 3 "const_0_31_operand" "i")]
         UNSPEC_XXLCZ_BITREV))]
  "TARGET_XXLCZBITREV && TARGET_64BIT"
  "xl.bitrev\t%0,%1,%2,%3"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "DI")])

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

;; XXLCZBRI Instructions
;; xl.beqi/xl.bnei: branch if register ==/!= immediate (5-bit signed, -16..15)
;; Only generated when xxlczbri is enabled and zibi is NOT (zibi uses beqi/bnei
;; with the same encoding; when both are on, zibi takes precedence).
;; Relational comparisons (lt/le/gt/ge/etc.) use the standard
;; *branch<mode>_relational_comparison pattern which is not disabled by xxlczbri.
(define_insn "*xl_branch<mode>"
  [(set (pc)
	(if_then_else
	 (match_operator 1 "equality_operator"
			 [(match_operand:X 2 "register_operand" "r")
			  (match_operand:X 3 "const_int5s_operand" "CV_bi_sign5")])
	 (label_ref (match_operand 0 "" ""))
	 (pc)))]
  "TARGET_XXLCZBRI && !TARGET_ZIBI && TARGET_NUCLEI_XXLCZ_AUTOGEN"
{
  if (get_attr_length (insn) == 12)
    return "xl.b%N1i\t%2,%z3,1f; jump\t%l0,ra; 1:";

  return "xl.b%C1i\t%2,%3,%0";
}
  [(set_attr "type" "branch")
   (set_attr "mode" "none")
   ;; The 12-byte far form (inverted xl.b<i> + jump) exists exactly because
   ;; the 4-byte near form cannot reach every target.  Without this attribute
   ;; get_attr_length is the default 4, the == 12 test never fires, and an
   ;; out-of-range near form gets assembled into a branch with a truncated
   ;; offset field -- observed as a branch to itself (self-loop) on rv64
   ;; coremark.  Keep the near form inside the standard B-type reach with a
   ;; small margin; the far form is only 12 bytes (xl.b<i> + jump), where the
   ;; forward branch to 1f is always encodable and jump covers +/-1MiB.
   (set (attr "length")
	(if_then_else
	    (and (ge (minus (match_dup 0) (pc)) (const_int -4090))
		 (le (minus (pc) (match_dup 0)) (const_int 4090)))
	    (const_int 4)
	    (const_int 12)))])

;; xl.addibne: fuse  addi rd,rd,+N  +  bne rd,rs1,label  into one insn
;; (RV32 only; the bne may be the bnez form, bne rd,x0,label, and the
;; comparison may be written in either operand order).  Only under the
;; xxlcz autogen path.  rd is written back on both the taken and
;; fall-through paths, so any liveness of rd after the branch is preserved.
(define_peephole2
  [(set (match_operand:SI 0 "register_operand" "")
	(plus:SI (match_operand:SI 1 "register_operand" "")
		 (match_operand:SI 2 "const_int_operand" "")))
   (set (pc)
	(if_then_else
	  (ne (match_operand:SI 3 "register_operand" "")
		 (match_operand:SI 4 "reg_or_0_operand" ""))
	  (label_ref (match_operand 5 "" ""))
	  (pc)))]
  "TARGET_XXLCZBRI && TARGET_NUCLEI_XXLCZ_AUTOGEN && !TARGET_64BIT
   && REGNO (operands[1]) == REGNO (operands[0])
   && (REGNO (operands[3]) == REGNO (operands[0])
       || (REG_P (operands[4])
	   && REGNO (operands[4]) == REGNO (operands[0])))
   && (INTVAL (operands[2]) == 1 || INTVAL (operands[2]) == 2
       || INTVAL (operands[2]) == 4 || INTVAL (operands[2]) == 8)"
  [(parallel
    [(set (pc)
	  (if_then_else
	    (ne (plus:SI (match_operand:SI 0 "register_operand" "")
			 (match_operand:SI 2 "const_int_operand" ""))
		(match_operand:SI 1 "register_operand" ""))
	    (label_ref (match_operand 3 "" ""))
	    (pc)))
     (set (match_dup 0)
	  (plus:SI (match_dup 0)
		   (match_dup 2)))])]
{
  /* Renumber for the fused insn: 0=rd, 1=rs1, 2=addend, 3=label.
     rs1 is the comparison operand that is not the loop counter; it may
     arrive as const0_rtx (bnez form) -> normalize to x0.  */
  rtx cmp = (REGNO (operands[3]) == REGNO (operands[0]))
	    ? operands[4] : operands[3];
  operands[1] = REG_P (cmp) ? cmp : gen_rtx_REG (SImode, 0);
  operands[3] = operands[5];
})

;; Fused xl.addibne: rd += scale; if (rs1 != rd) goto label.
;; scale is the positive increment (1/2/4/8); gas maps it straight to the
;; 2-bit SCALE field and resolves the label through
;; BFD_RELOC_RISCV_XL_ADDIBNE.  The offset field only holds x[9:1], so
;; reachable offsets are the even values up to 1022 -- keep the first tier
;; inside that.
;; Length tiers override the default branch attr (which assumes operand 0 is
;; the label; here operand 3 is the label):
;;   4  : xl.addibne reaches backward offsets <= 1022    -> 1 insn
;;   8  : plain bne reach (+/-4KiB) but outside addibne  -> addi;bne
;;   16 : beyond bne reach                               -> addi;beq 1f;jump;1:
(define_insn "*xl_addibne"
  [(parallel
    [(set (pc)
	  (if_then_else
	    (ne (plus:SI (match_operand:SI 0 "register_operand" "+r")
			 (match_operand:SI 2 "xl_addibne_addend_operand" "i"))
		(match_operand:SI 1 "register_operand" "r"))
	    (label_ref (match_operand 3 "" ""))
	    (pc)))
     (set (match_dup 0)
	  (plus:SI (match_dup 0)
		   (match_dup 2)))])]
  "TARGET_XXLCZBRI && TARGET_NUCLEI_XXLCZ_AUTOGEN && !TARGET_64BIT"
{
  if (get_attr_length (insn) == 4)
    return "xl.addibne\t%0,%1,%2,%3";
  if (get_attr_length (insn) == 8)
    return "addi\t%0,%0,%2;bne\t%0,%1,%l3";
  return "addi\t%0,%0,%2;beq\t%0,%1,1f;jump\t%l3,ra;1:";
}
  [(set_attr "type" "branch")
   (set_attr "mode" "none")
   (set (attr "length")
	(if_then_else
	  (and (le (minus (match_dup 3) (pc)) (const_int 0))
	       (le (minus (pc) (match_dup 3)) (const_int 1022)))
	  (const_int 4)
	  (if_then_else
	    (and (le (minus (match_dup 3) (pc)) (const_int 4088))
		 (le (minus (pc) (match_dup 3)) (const_int 4092)))
	    (const_int 8)
	    (const_int 16))))])
