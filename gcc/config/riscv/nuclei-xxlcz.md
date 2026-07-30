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
;; Auto-match for contiguous mask set: x | (((1 << len) - 1) << pos) -> xl.bset
(define_insn "*bset<mode>_xlcz"
  [(set (match_operand:GPR 0 "register_operand" "=r")
        (ior:GPR (match_operand:GPR 1 "register_operand" "r")
                 (match_operand:GPR 2 "xxlcz_contiguous_mask_1_31" "i")))]
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
    tmp[2] = GEN_INT (len);
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
                 (match_operand:GPR 2 "xxlcz_not_contiguous_mask_1_31" "i")))]
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
    tmp[2] = GEN_INT (len);
    tmp[3] = GEN_INT (pos);
    output_asm_insn (\"xl.bclr\\t%0,%1,%2,%3\", tmp);
    return \"\";
  }
  [(set_attr "type" "logical")
   (set_attr "mode" "<GPR:MODE>")])

;; xl.extract rd, rs1, uimm3(len), uimm2(bottom) - Extract signed, immediate
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

;; Extract signed bitfield (auto match for xl.extract)
;; Sign-extend extract from rs1[pos : pos+len-1]
;; operand2 = len, operand3 = pos
;; pos must be <= 31 (gas 'bi' constraint is 5 bits), even on DI mode.
(define_insn "*xl_extract<mode>4"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(sign_extract:GPR (match_operand:GPR 1 "register_operand" "r")
		       (match_operand 2 "const_int_operand" "i")
		       (match_operand 3 "const_int_operand" "i")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN && INTVAL (operands[2]) >= 1 && INTVAL (operands[2]) <= 31 && INTVAL (operands[3]) <= 31 && INTVAL (operands[2]) + INTVAL (operands[3]) <= GET_MODE_BITSIZE (<MODE>mode)"
  {
    /* len is operand2, pos is operand3 -> output matches instruction format */
    return \"xl.extract\\t%0,%1,%2,%3\";
  }
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "<GPR:MODE>")])

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

;; Auto-match for GCC standard CLZ (count leading zeros) -> xl.ff1
;; clz returns number of leading 0s from MSB, which is exactly the position of first 1 from MSB
(define_insn "*clz<mode>2_xlcz"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(clz:GPR (match_operand:GPR 1 "register_operand" "r")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.ff1\t%0,%1"
  [(set_attr "type" "bitmanip")
   (set_attr "mode" "<GPR:MODE>")])

;; Auto-match for GCC standard CTZ (count trailing zeros) -> xl.fl1
;; ctz returns number of trailing 0s from LSB, which is exactly the position of first 1 from LSB
(define_insn "*ctz<mode>2_xlcz"
  [(set (match_operand:GPR 0 "register_operand" "=r")
	(ctz:GPR (match_operand:GPR 1 "register_operand" "r")))]
  "TARGET_XXLCZBITOP && TARGET_NUCLEI_XXLCZ_AUTOGEN"
  "xl.fl1\t%0,%1"
  [(set_attr "type" "bitmanip")
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
   (set_attr "mode" "none")])
