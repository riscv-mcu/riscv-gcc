(define_automaton "nuclei_900")

(define_cpu_unit "nuclei_900_A" "nuclei_900")
(define_cpu_unit "nuclei_900_B" "nuclei_900")

(define_cpu_unit "nuclei_900_idiv" "nuclei_900")
(define_cpu_unit "nuclei_900_fpu" "nuclei_900")

(define_insn_reservation "nuclei_900_load" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "load"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_fpload" 2
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fpload"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_store" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "store"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_fpstore" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fpstore"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_branch" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "branch,ret,trap"))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_sfb_alu" 2
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "sfb_alu"))
  "nuclei_900_A+nuclei_900_B")

(define_insn_reservation "nuclei_900_jump" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "jump,call,jalr"))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_mul" 10
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "imul"))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_div" 16
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "idiv"))
  "nuclei_900_B,nuclei_900_idiv*15")

(define_insn_reservation "nuclei_900_alu" 2
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "unknown,arith,shift,slt,multi,logical,move,bitmanip,\
			rotate,min,max,minu,maxu,clz,ctz,atomic,condmove,mvpair,zicond"))
  "nuclei_900_A|nuclei_900_B")

(define_insn_reservation "nuclei_900_load_immediate" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "nop,const,auipc"))
  "nuclei_900_A|nuclei_900_B")

(define_insn_reservation "nuclei_900_hfma" 5
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "HF")))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_sfma" 5
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "SF")))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_dfma" 7
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "DF")))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_fp_other" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fcvt,fcvt_i2f,fcvt_f2i,fcmp,fmove"))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_fdiv_s" 33
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fdiv,fsqrt")
       (eq_attr "mode" "SF"))
  "nuclei_900_B,nuclei_900_fpu*32")

(define_insn_reservation "nuclei_900_fdiv_d" 66
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fdiv,fsqrt")
       (eq_attr "mode" "DF"))
  "nuclei_900_B,nuclei_900_fpu*65")

(define_insn_reservation "nuclei_900_i2f" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "mtc"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_f2i" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "mfc"))
  "nuclei_900_A")

;; Popcount and clmul.
(define_insn_reservation "nuclei_900_popcount" 2
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "cpop,clmul"))
  "nuclei_900_A")

(define_bypass 1 "nuclei_900_load,nuclei_900_alu,nuclei_900_mul,nuclei_900_f2i,nuclei_900_sfb_alu"
  "nuclei_900_alu,nuclei_900_branch")

(define_bypass 1 "nuclei_900_alu,nuclei_900_sfb_alu"
  "nuclei_900_sfb_alu")

(define_bypass 1 "nuclei_900_load,nuclei_900_alu,nuclei_900_mul,nuclei_900_f2i,nuclei_900_sfb_alu"
  "nuclei_900_store" "riscv_store_data_bypass_p")

(define_bypass 2 "nuclei_900_i2f"
  "nuclei_900_sfma,nuclei_900_dfma,nuclei_900_fp_other,nuclei_900_fdiv_s,nuclei_900_fdiv_d")

(define_bypass 2 "nuclei_900_fp_other"
  "nuclei_900_sfma,nuclei_900_dfma,nuclei_900_fp_other,nuclei_900_fdiv_s,nuclei_900_fdiv_d")

(define_bypass 2 "nuclei_900_fp_other"
  "nuclei_900_alu,nuclei_900_branch")

(define_bypass 2 "nuclei_900_fp_other"
  "nuclei_900_store" "riscv_store_data_bypass_p")
