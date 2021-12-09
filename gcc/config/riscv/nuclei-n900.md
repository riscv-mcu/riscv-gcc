(define_automaton "nuclei_n900")

(define_cpu_unit "nuclei_n900_pipe0, nuclei_n900_pipe1" "nuclei_n900")
(define_cpu_unit "nuclei_n900_alu0, nuclei_n900_alu1" "nuclei_n900")
(define_cpu_unit "nuclei_n900_lsu" "nuclei_n900")
(define_cpu_unit "nuclei_n900_imul, nuclei_n900_idiv" "nuclei_n900")
(define_cpu_unit "nuclei_n900_fmisc, nuclei_n900_fmac, nuclei_n900_fdiv" "nuclei_n900")
(define_cpu_unit "nuclei_n900_bmu" "nuclei_n900")
(define_cpu_unit "nuclei_n900_dsp" "nuclei_n900")

;; Common instructions
(define_insn_reservation "nuclei_n900_alu_insn" 1
  (and (eq_attr "tune" "nuclei_n900")
    (eq_attr "type" "unknown, arith, shift, slt, multi, logical, move, nop, const, auipc"))
  "nuclei_n900_pipe0 + nuclei_n900_alu0 | nuclei_n900_pipe1 + nuclei_n900_alu1")

;; Load 32/64 bits
(define_insn_reservation "nuclei_n900_load_wd" 3
  (and (eq_attr "tune" "nuclei_n900")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "SI,DI")))
  "nuclei_n900_pipe0 + nuclei_n900_lsu | nuclei_n900_pipe1 + nuclei_n900_lsu")

;; Load 8/16 bits
(define_insn_reservation "nuclei_n900_load_bh" 4
  (and (eq_attr "tune" "nuclei_n900")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "QI,HI")))
  "nuclei_n900_pipe0 + nuclei_n900_lsu | nuclei_n900_pipe1 + nuclei_n900_lsu")

;; Stroe, defer to tune info
(define_insn_reservation "nuclei_n900_store" 0
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "store"))
  "nuclei_n900_pipe0 + nuclei_n900_lsu | nuclei_n900_pipe1 + nuclei_n900_lsu")

;; Branch, defer to tune info
(define_insn_reservation "nuclei_n900_branch" 0
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "branch, jump, call"))
  "nuclei_n900_pipe0 + nuclei_n900_alu0 | nuclei_n900_pipe1 + nuclei_n900_alu1")

;; Integer multiply, defer to tune info
(define_insn_reservation "nuclei_n900_imul" 4
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "imul"))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_imul * 2")

;; Integer divide, 32 bits, defer to tune info
(define_insn_reservation "nuclei_n900_idiv_si" 4
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_idiv * 2")

;; Integer divide, 64 bits, defer to tune info
(define_insn_reservation "nuclei_n900_idiv_di" 4
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_idiv * 2")

;; FPU misc
(define_insn_reservation "nuclei_n900_fmisc" 3
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "mfc, mtc, fcvt, fmove"))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_fmisc * 2")

;; Float mul/add/cmp, defer to tune info
(define_insn_reservation "nuclei_n900_fmac" 5
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "fmul, fadd, fcmp, fmadd"))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_fmac * 4")

;; Float divide/sqrt, 32 bits, defer to tune info
(define_insn_reservation "nuclei_n900_fdiv_sf" 10
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "SF")))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_fdiv * 9")

;; Float divide/sqrt, 64 bits, defer to tune info
(define_insn_reservation "nuclei_n900_fdiv_df" 25
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "DF")))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_fdiv * 24")

;; Float load
(define_insn_reservation "nuclei_n900_fpload" 4
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "fpload"))
  "nuclei_n900_pipe0 + nuclei_n900_lsu | nuclei_n900_pipe1 + nuclei_n900_lsu")

;; Float store, defer to tune info
(define_insn_reservation "nuclei_n900_fpstore" 0
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "fpstore"))
  "nuclei_n900_pipe0 + nuclei_n900_lsu | nuclei_n900_pipe1 + nuclei_n900_lsu")

;; DSP SIMD
(define_insn_reservation "nuclei_n900_dsp_simd" 2
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "simd"))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_dsp")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_n900_dsp_psimd" 3
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "psimd"))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_dsp")

;; DSP Others
(define_insn_reservation "nuclei_n900_dsp_other" 3
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1, nuclei_n900_dsp")

;; BMU
(define_insn_reservation "nuclei_n900_bmu" 1
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "bitmanip"))
  "nuclei_n900_pipe0 + nuclei_n900_bmu | nuclei_n900_pipe1 + nuclei_n900_bmu")
