;;(define_automaton "nuclei_100")

(define_automaton "nuclei_900")
(define_cpu_unit "nuclei_900_alu" "nuclei_900")
(define_cpu_unit "nuclei_900_imuldiv" "nuclei_900")
(define_cpu_unit "nuclei_900_fdivsqrt" "nuclei_900")

(define_insn_reservation "nuclei_900_alu" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "unknown,const,arith,shift,slt,multi,auipc,nop,logical,\
			move,bitmanip,min,max,minu,maxu,clz,ctz,rotate,atomic,\
			condmove,crypto,mvpair,zicond"))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_load" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "load,fpload"))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_store" 0
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "store,fpstore"))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_xfer" 4
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "mfc,mtc,fcvt,fcvt_i2f,fcvt_f2i,fmove,fcmp"))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_branch" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "branch,jump,call,jalr,ret,trap"))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_sfb_alu" 2
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "sfb_alu"))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_imul" 10
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "imul,clmul,cpop"))
  "nuclei_900_imuldiv*10")

(define_insn_reservation "nuclei_900_idivsi" 33
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "idiv")
	    (eq_attr "mode" "SI")))
  "nuclei_900_imuldiv*33")

(define_insn_reservation "nuclei_900_idivdi" 66
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "idiv")
	    (eq_attr "mode" "DI")))
  "nuclei_900_imuldiv*66")

(define_insn_reservation "nuclei_900_fmul_half" 4
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "HF")))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_fmul_single" 4
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "SF")))
  "alu")

(define_insn_reservation "nuclei_900_fmul_double" 8
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fadd,fmul,fmadd")
	    (eq_attr "mode" "DF")))
  "nuclei_900_alu")

(define_insn_reservation "nuclei_900_fdiv" 20
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fdiv"))
  "nuclei_900_fdivsqrt*20")

(define_insn_reservation "nuclei_900_fsqrt" 25
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fsqrt"))
  "nuclei_900_fdivsqrt*25")

;; DSP SIMD
(define_insn_reservation "nuclei_900_dsp_simd_insn" 2
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "simd"))
  "nuclei_900_alu")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_900_dsp_psimd_insn" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "psimd"))
  "nuclei_900_alu")

;; DSP Others
(define_insn_reservation "nuclei_900_dsp_other_insn" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_900_alu")

;; BMU
(define_insn_reservation "nuclei_900_bitmanip_insn" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "bitmanip"))
  "nuclei_900_alu")