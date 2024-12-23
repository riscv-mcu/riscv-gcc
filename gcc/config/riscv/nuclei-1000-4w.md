;; Scheduling description for nuclei 1000 4w series.

;; Four automata are defined to reduce number of states
;; which a single large automaton will have.
(define_automaton "nuclei_1000_4w_iex,nuclei_1000_4w_fex,nuclei_1000_4w_mem,nuclei_1000_4w_div")

(define_cpu_unit "nuclei_1000_4w_A" "nuclei_1000_4w_mem")
(define_cpu_unit "nuclei_1000_4w_B1" "nuclei_1000_4w_iex")
(define_cpu_unit "nuclei_1000_4w_B2" "nuclei_1000_4w_iex")
(define_cpu_unit "nuclei_1000_4w_M" "nuclei_1000_4w_iex")
(define_cpu_unit "nuclei_1000_4w_C" "nuclei_1000_4w_iex")
(define_cpu_unit "nuclei_1000_4w_F" "nuclei_1000_4w_fex")
(define_cpu_unit "nuclei_1000_4w_FM" "nuclei_1000_4w_fex")

;; Load and store unit.
(define_cpu_unit "nuclei_1000_4w_ld" "nuclei_1000_4w_mem")
(define_cpu_unit "nuclei_1000_4w_st" "nuclei_1000_4w_mem")

;; Branch unit.
(define_cpu_unit "nuclei_1000_4w_bru" "nuclei_1000_4w_iex")

;; Integer and multiply unit.
(define_cpu_unit "nuclei_1000_4w_ialu" "nuclei_1000_4w_iex")
(define_cpu_unit "nuclei_1000_4w_imul" "nuclei_1000_4w_iex")
(define_cpu_unit "nuclei_1000_4w_system" "nuclei_1000_4w_iex")

;; Divide unit.
(define_cpu_unit "nuclei_1000_4w_idiv" "nuclei_1000_4w_div")
(define_cpu_unit "nuclei_1000_4w_fdiv" "nuclei_1000_4w_div")

;; Float and multiply unit.
(define_cpu_unit "nuclei_1000_4w_fmul" "nuclei_1000_4w_fex")
(define_cpu_unit "nuclei_1000_4w_fpu" "nuclei_1000_4w_fex")

;; ALU instruction can use pipeline C, B1, B2 and M.
(define_reservation "nuclei_1000_4w_int_pipe" "(nuclei_1000_4w_C|nuclei_1000_4w_B1|nuclei_1000_4w_B2|nuclei_1000_4w_M)")
;; FPU instruction can use pipeline F and FM.
(define_reservation "nuclei_1000_4w_float_pipe" "(nuclei_1000_4w_F|nuclei_1000_4w_FM)")
;; Branch instruction can use pipeline B1 and B2.
(define_reservation "nuclei_1000_4w_branch_pipe" "(nuclei_1000_4w_B1|nuclei_1000_4w_B2)")

(define_insn_reservation "nuclei_1000_4w_load" 3
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "load"))
  "nuclei_1000_4w_A,nuclei_1000_4w_ld*2")

(define_insn_reservation "nuclei_1000_4w_fpload" 4
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "fpload"))
  "nuclei_1000_4w_A,nuclei_1000_4w_ld*3")

(define_insn_reservation "nuclei_1000_4w_store" 1
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "store"))
  "nuclei_1000_4w_A+nuclei_1000_4w_st")

(define_insn_reservation "nuclei_1000_4w_fpstore" 1
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "fpstore"))
  "nuclei_1000_4w_A+nuclei_1000_4w_st")

(define_insn_reservation "nuclei_1000_4w_branch" 1
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "branch,jump,call,jalr,ret,trap"))
  "nuclei_1000_4w_branch_pipe+nuclei_1000_4w_bru")

(define_insn_reservation "nuclei_1000_4w_sfb_alu" 1
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "sfb_alu"))
  "nuclei_1000_4w_C+nuclei_1000_4w_bru+nuclei_1000_4w_ialu")

(define_insn_reservation "nuclei_1000_4w_atomic" 3
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "atomic"))
  "nuclei_1000_4w_C,nuclei_1000_4w_system*2")

(define_insn_reservation "nuclei_1000_4w_mul" 3
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "imul"))
  "nuclei_1000_4w_M,nuclei_1000_4w_imul*2")

(define_insn_reservation "nuclei_1000_4w_div" 16
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "idiv"))
  "nuclei_1000_4w_M, nuclei_1000_4w_idiv*4")

(define_insn_reservation "nuclei_1000_4w_alu" 1
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "unknown,arith,logical,shift,slt,multi,bitmanip,\
			clz,ctz,rotate,min,max,minu,maxu,condmove,mvpair,zicond"))
  "nuclei_1000_4w_int_pipe+nuclei_1000_4w_ialu")

(define_insn_reservation "nuclei_1000_4w_cpop" 3
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "cpop"))
  "nuclei_1000_4w_int_pipe,nuclei_1000_4w_ialu*2")

(define_insn_reservation "nuclei_1000_4w_clmul" 3
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "clmul"))
  "nuclei_1000_4w_int_pipe,nuclei_1000_4w_ialu*2")

(define_insn_reservation "nuclei_1000_4w_load_immediate" 1
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "nop,const,auipc,move"))
  "nuclei_1000_4w_int_pipe")

(define_insn_reservation "nuclei_1000_4w_fma" 4
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "fadd,fmul,fmadd"))
  "nuclei_1000_4w_float_pipe,nuclei_1000_4w_fmul*3")

(define_insn_reservation "nuclei_1000_4w_i2f" 2
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "mtc,fcvt_i2f"))
  "nuclei_1000_4w_M,nuclei_1000_4w_ialu")

(define_insn_reservation "nuclei_1000_4w_f2i" 2
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "mfc,fcmp,fcvt_f2i"))
  "nuclei_1000_4w_F,nuclei_1000_4w_fpu")

(define_insn_reservation "nuclei_1000_4w_fmove" 2
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "fmove,fcvt"))
  "nuclei_1000_4w_float_pipe,nuclei_1000_4w_fpu")

(define_insn_reservation "nuclei_1000_4w_fdiv_s" 11
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "fdiv,fsqrt")
       (eq_attr "mode" "SF"))
  "nuclei_1000_4w_FM, nuclei_1000_4w_fdiv*5")

(define_insn_reservation "nuclei_1000_4w_fdiv_d" 19
  (and (eq_attr "tune" "nuclei_1000_4w")
       (eq_attr "type" "fdiv,fsqrt")
       (eq_attr "mode" "DF"))
  "nuclei_1000_4w_FM, nuclei_1000_4w_fdiv*5")

(define_bypass 1 "nuclei_1000_4w_load,nuclei_1000_4w_alu,nuclei_1000_4w_mul,nuclei_1000_4w_sfb_alu"
  "nuclei_1000_4w_alu,nuclei_1000_4w_branch")

(define_bypass 1 "nuclei_1000_4w_load,nuclei_1000_4w_alu,nuclei_1000_4w_mul,
                  nuclei_1000_4w_f2i,nuclei_1000_4w_fmove,nuclei_1000_4w_sfb_alu"
  "nuclei_1000_4w_store" "riscv_store_data_bypass_p")

(define_bypass 1 "nuclei_1000_4w_i2f"
  "nuclei_1000_4w_fma,nuclei_1000_4w_f2i,nuclei_1000_4w_fmove,nuclei_1000_4w_fdiv_s,nuclei_1000_4w_fdiv_d")

(define_bypass 1 "nuclei_1000_4w_f2i"
  "nuclei_1000_4w_branch,nuclei_1000_4w_sfb_alu,nuclei_1000_4w_mul,
   nuclei_1000_4w_div,nuclei_1000_4w_alu,nuclei_1000_4w_cpop")
