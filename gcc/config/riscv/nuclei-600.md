(define_automaton "nuclei_600")

(define_cpu_unit "nuclei_600_pipe0" "nuclei_600")

(define_cpu_unit "nuclei_600_load" "nuclei_600")
(define_cpu_unit "nuclei_600_store" "nuclei_600")

;; imul can be piped, but idiv cannot
(define_cpu_unit "nuclei_600_imul" "nuclei_600")
(define_cpu_unit "nuclei_600_idiv" "nuclei_600")

;; fmisc/fmac can be piped, but fdiv cannot
(define_cpu_unit "nuclei_600_fmisc" "nuclei_600")
(define_cpu_unit "nuclei_600_fmac" "nuclei_600")
(define_cpu_unit "nuclei_600_fdiv" "nuclei_600")

;; DSP cannot be piped
(define_cpu_unit "nuclei_600_dsp" "nuclei_600")

;; ALU instructions
(define_insn_reservation "nuclei_600_alu_insn" 1
  (and (eq_attr "tune" "nuclei_600")
    (eq_attr "type" "unknown, arith, shift, slt, multi, logical, move, nop, const, auipc"))
  "nuclei_600_pipe0")

;; Load 32/64 bits
(define_insn_reservation "nuclei_600_load_wd_insn" 3
  (and (eq_attr "tune" "nuclei_600")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "SI,DI")))
  "nuclei_600_pipe0 + nuclei_600_load")

;; Load 8/16 bits
(define_insn_reservation "nuclei_600_load_bh_insn" 4
  (and (eq_attr "tune" "nuclei_600")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "QI,HI")))
  "nuclei_600_pipe0 + nuclei_600_load")

;; Stroe, defer to tune info
(define_insn_reservation "nuclei_600_store_insn" 0
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "store"))
  "nuclei_600_pipe0 + nuclei_600_store")

;; Branch, defer to tune info
(define_insn_reservation "nuclei_600_branch_insn" 0
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "branch, jump, call"))
  "nuclei_600_pipe0")

;; Integer multiplication, defer to tune info
(define_insn_reservation "nuclei_600_imul_insn" 4
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "imul"))
  "nuclei_600_pipe0 + nuclei_600_imul")

;; Integer division, 32 bits, defer to tune info
(define_insn_reservation "nuclei_600_idiv_si_insn" 4
  (and (eq_attr "tune" "nuclei_600")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_600_pipe0 + nuclei_600_idiv, nuclei_600_idiv * 3")

;; Integer division, 64 bits, defer to tune info
(define_insn_reservation "nuclei_600_idiv_di_insn" 4
  (and (eq_attr "tune" "nuclei_600")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_600_pipe0 + nuclei_600_idiv, nuclei_600_idiv * 3")

;; FPU misc
(define_insn_reservation "nuclei_600_fmisc_insn" 3
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "mfc, mtc, fcvt, fmove"))
  "nuclei_600_pipe0 + nuclei_600_fmisc")

;; Float mul/add/cmp, defer to tune info
(define_insn_reservation "nuclei_600_fmac_insn" 5
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "fmul, fadd, fcmp, fmadd"))
  "nuclei_600_pipe0 + nuclei_600_fmac")

;; Float division/sqrt, 32 bits, defer to tune info
(define_insn_reservation "nuclei_600_fdiv_sf_insn" 20
  (and (eq_attr "tune" "nuclei_600")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "SF")))
  "nuclei_600_pipe0 + nuclei_600_fdiv, nuclei_600_fdiv * 19")

;; Float division/sqrt, 64 bits, defer to tune info
(define_insn_reservation "nuclei_600_fdiv_df_insn" 34
  (and (eq_attr "tune" "nuclei_600")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "DF")))
  "nuclei_600_pipe0 + nuclei_600_fdiv, nuclei_600_fdiv * 33")

;; Float load
(define_insn_reservation "nuclei_600_fpload_insn" 4
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "fpload"))
  "nuclei_600_pipe0 + nuclei_600_load")

;; Float store, defer to tune info
(define_insn_reservation "nuclei_600_fpstore_insn" 0
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "fpstore"))
  "nuclei_600_pipe0 + nuclei_600_store")

;; DSP SIMD
(define_insn_reservation "nuclei_600_dsp_simd_insn" 2
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "simd"))
  "nuclei_600_pipe0 + nuclei_600_dsp, nuclei_600_dsp")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_600_dsp_psimd_insn" 3
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "psimd"))
  "nuclei_600_pipe0 + nuclei_600_dsp, nuclei_600_dsp * 2")

;; DSP Others
(define_insn_reservation "nuclei_600_dsp_other_insn" 3
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_600_pipe0 + nuclei_600_dsp, nuclei_600_dsp * 2")

;; BMU
(define_insn_reservation "nuclei_600_bitmanip_insn" 1
  (and (eq_attr "tune" "nuclei_600")
       (eq_attr "type" "bitmanip"))
  "nuclei_600_pipe0")
