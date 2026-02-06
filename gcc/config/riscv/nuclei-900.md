;; Nuclei-900 Dual-Issue Pipeline Model
;; Based on hardware specification table
;; Pipeline A: ALU, Bitmanip, Branch, Load/Store
;; Pipeline B: DSP, Floating Point, Multiplication, Division

(define_automaton "nuclei_900")

;; Pipeline A - ALU pipe
(define_cpu_unit "nuclei_900_A" "nuclei_900")

;; Pipeline B - DSP/FP pipe 
(define_cpu_unit "nuclei_900_B" "nuclei_900")

;; Special functional units (non-pipelined)
(define_cpu_unit "nuclei_900_idiv" "nuclei_900")
(define_cpu_unit "nuclei_900_fdiv" "nuclei_900")

(define_insn_reservation "nuclei_900_alu" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "unknown,arith,shift,slt,multi,logical,move,bitmanip,\
			rotate,min,max,minu,maxu,clz,ctz,cpop,clmul,\
			atomic,condmove,mvpair,zicond"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_const" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "nop,const,auipc"))
  "nuclei_900_A|nuclei_900_B")

(define_insn_reservation "nuclei_900_imul" 4
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "imul"))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_idiv32" 17
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_900_B,nuclei_900_idiv*16")

(define_insn_reservation "nuclei_900_idiv64" 33
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_900_B,nuclei_900_idiv*32")

(define_insn_reservation "nuclei_900_branch" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "branch,ret,trap"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_jump" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "jump,call,jalr"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_load" 4
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "load"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_fpload" 4
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

(define_insn_reservation "nuclei_900_hfmac" 3
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "HF")))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_sfmac" 4
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "SF")))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_dfmac" 6
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "DF")))
  "nuclei_900_B")

;; (non-pipelined)
(define_insn_reservation "nuclei_900_fdiv_s" 20
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fdiv,fsqrt")
	    (eq_attr "mode" "SF")))
  "nuclei_900_B,nuclei_900_fdiv*19")

(define_insn_reservation "nuclei_900_fdiv_d" 34
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fdiv,fsqrt")
	    (eq_attr "mode" "DF")))
  "nuclei_900_B,nuclei_900_fdiv*33")

(define_insn_reservation "nuclei_900_fp_misc" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fcvt,fcvt_i2f,fcvt_f2i,fcmp,fmove"))
  "nuclei_900_B")

(define_insn_reservation "nuclei_900_i2f" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "mtc"))
  "nuclei_900_A")

(define_insn_reservation "nuclei_900_f2i" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "mfc"))
  "nuclei_900_A")

(define_bypass 1 "nuclei_900_alu,nuclei_900_const" 
  "nuclei_900_alu,nuclei_900_branch,nuclei_900_jump")

(define_bypass 3 "nuclei_900_load,nuclei_900_fpload"
  "nuclei_900_alu,nuclei_900_branch")

(define_bypass 1 "nuclei_900_alu"
  "nuclei_900_store" "riscv_store_data_bypass_p")


