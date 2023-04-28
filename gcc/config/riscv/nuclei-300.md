(define_automaton "nuclei_300")

(define_cpu_unit "nuclei_300_pipe0" "nuclei_300")

;; imul can be piped, but idiv cannot
(define_cpu_unit "nuclei_300_imul" "nuclei_300")
(define_cpu_unit "nuclei_300_idiv" "nuclei_300")

(define_cpu_unit "nuclei_300_load" "nuclei_300")
(define_cpu_unit "nuclei_300_store" "nuclei_300")

;; fmisc/fmac can be piped, but fdiv cannot
(define_cpu_unit "nuclei_300_fmisc" "nuclei_300")
(define_cpu_unit "nuclei_300_fmac" "nuclei_300")
(define_cpu_unit "nuclei_300_fdiv" "nuclei_300")

;; DSP cannot be piped
(define_cpu_unit "nuclei_300_dsp" "nuclei_300")

;; ALU instructions
(define_insn_reservation "nuclei_300_alu_insn" 1
  (and (eq_attr "tune" "nuclei_300")
    (eq_attr "type" "unknown, arith, shift, slt, multi, logical, move, nop, const, auipc"))
  "nuclei_300_pipe0")

;; Load
(define_insn_reservation "nuclei_300_load_insn" 2
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "load"))
  "nuclei_300_pipe0 + nuclei_300_load")

;; Store
(define_insn_reservation "nuclei_300_store_insn" 1
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "store"))
  "nuclei_300_pipe0 + nuclei_300_store")

;; Branch
(define_insn_reservation "nuclei_300_branch_insn" 1
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "branch, jump, call"))
  "nuclei_300_pipe0")

;; Integer multiplication
(define_insn_reservation "nuclei_300_imul_insn" 1
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "imul"))
  "nuclei_300_pipe0 + nuclei_300_imul")

;; Integer division, 32 bits, defer to tune info
(define_insn_reservation "nuclei_300_idiv_si_insn" 17
  (and (eq_attr "tune" "nuclei_300")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_300_pipe0 + nuclei_300_idiv, nuclei_300_idiv * 16")

;; Integer division, 64 bits, defer to tune info
(define_insn_reservation "nuclei_300_idiv_di_insn" 33
  (and (eq_attr "tune" "nuclei_300")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_300_pipe0 + nuclei_300_idiv, nuclei_300_idiv * 32")

;; FPU misc
(define_insn_reservation "nuclei_300_fmisc_insn" 2
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "mfc, mtc, fcvt, fmove"))
  "nuclei_300_pipe0 + nuclei_300_fmisc")

;; Float mul/add/cmp, defer to tune info
(define_insn_reservation "nuclei_300_fmac_insn" 2
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "fmul, fadd, fcmp, fmadd"))
  "nuclei_300_pipe0 + nuclei_300_fmac")

;; Float division/sqrt, 32 bits, defer to tune info
(define_insn_reservation "nuclei_300_fdiv_sf_insn" 20
  (and (eq_attr "tune" "nuclei_300")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "SF")))
  "nuclei_300_pipe0 + nuclei_300_fdiv, nuclei_300_fdiv * 19")

;; Float division/sqrt, 64 bits, defer to tune info
(define_insn_reservation "nuclei_300_fdiv_df_insn" 34
  (and (eq_attr "tune" "nuclei_300")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "DF")))
  "nuclei_300_pipe0 + nuclei_300_fdiv, nuclei_300_fdiv * 33")

;; Float load
(define_insn_reservation "nuclei_300_fpload_insn" 2
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "fpload"))
  "nuclei_300_pipe0 + nuclei_300_load")

;; Float store
(define_insn_reservation "nuclei_300_fpstore_insn" 1
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "fpstore"))
  "nuclei_300_pipe0 + nuclei_300_store")

;; DSP SIMD
(define_insn_reservation "nuclei_300_dsp_simd_insn" 1
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "simd"))
  "nuclei_300_pipe0 + nuclei_300_dsp")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_300_dsp_psimd_insn" 2
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "psimd"))
  "nuclei_300_pipe0 + nuclei_300_dsp, nuclei_300_dsp")

;; DSP Others
(define_insn_reservation "nuclei_300_dsp_other_insn" 2
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_300_pipe0 + nuclei_300_dsp, nuclei_300_dsp")

;; BMU
(define_insn_reservation "nuclei_300_bitmanip_insn" 1
  (and (eq_attr "tune" "nuclei_300")
       (eq_attr "type" "bitmanip"))
  "nuclei_300_pipe0")
