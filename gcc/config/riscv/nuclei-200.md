(define_automaton "nuclei_200")

(define_cpu_unit "nuclei_200_pipe0" "nuclei_200")

;; imul can be piped, but idiv cannot
(define_cpu_unit "nuclei_200_imul" "nuclei_200")
(define_cpu_unit "nuclei_200_idiv" "nuclei_200")

(define_cpu_unit "nuclei_200_load" "nuclei_200")
(define_cpu_unit "nuclei_200_store" "nuclei_200")

;; fmisc/fmac can be piped, but fdiv cannot
(define_cpu_unit "nuclei_200_fmisc" "nuclei_200")
(define_cpu_unit "nuclei_200_fmac" "nuclei_200")
(define_cpu_unit "nuclei_200_fdiv" "nuclei_200")

;; DSP cannot be piped
(define_cpu_unit "nuclei_200_dsp" "nuclei_200")

;; ALU instructions
(define_insn_reservation "nuclei_200_alu_insn" 1
  (and (eq_attr "tune" "nuclei_200")
    (eq_attr "type" "unknown, arith, shift, slt, multi, logical, move, nop, const, auipc"))
  "nuclei_200_pipe0")

;; Load
(define_insn_reservation "nuclei_200_load_insn" 2
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "load"))
  "nuclei_200_pipe0 + nuclei_200_load")

;; Store
(define_insn_reservation "nuclei_200_store_insn" 1
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "store"))
  "nuclei_200_pipe0 + nuclei_200_store")

;; Branch
(define_insn_reservation "nuclei_200_branch_insn" 1
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "branch, jump, call"))
  "nuclei_200_pipe0")

;; Integer multiplication
(define_insn_reservation "nuclei_200_imul_insn" 1
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "imul"))
  "nuclei_200_pipe0 + nuclei_200_imul")

;; Integer division, 32 bits, defer to tune info
(define_insn_reservation "nuclei_200_idiv_si_insn" 33
  (and (eq_attr "tune" "nuclei_200")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_200_pipe0 + nuclei_200_idiv, nuclei_200_idiv * 32")

;; Integer division, 64 bits, defer to tune info
(define_insn_reservation "nuclei_200_idiv_di_insn" 64
  (and (eq_attr "tune" "nuclei_200")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_200_pipe0 + nuclei_200_idiv, nuclei_200_idiv * 63")

;; FPU misc
(define_insn_reservation "nuclei_200_fmisc_insn" 2
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "mfc, mtc, fcvt, fmove"))
  "nuclei_200_pipe0 + nuclei_200_fmisc")

;; Float mul/add/cmp, defer to tune info
(define_insn_reservation "nuclei_200_fmac_insn" 2
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "fmul, fadd, fcmp, fmadd"))
  "nuclei_200_pipe0 + nuclei_200_fmac")

;; Float division/sqrt, 32 bits, defer to tune info
(define_insn_reservation "nuclei_200_fdiv_sf_insn" 20
  (and (eq_attr "tune" "nuclei_200")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "SF")))
  "nuclei_200_pipe0 + nuclei_200_fdiv, nuclei_200_fdiv * 19")

;; Float division/sqrt, 64 bits, defer to tune info
(define_insn_reservation "nuclei_200_fdiv_df_insn" 34
  (and (eq_attr "tune" "nuclei_200")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "DF")))
  "nuclei_200_pipe0 + nuclei_200_fdiv, nuclei_200_fdiv * 33")

;; Float load
(define_insn_reservation "nuclei_200_fpload_insn" 2
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "fpload"))
  "nuclei_200_pipe0 + nuclei_200_load")

;; Float store
(define_insn_reservation "nuclei_200_fpstore_insn" 1
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "fpstore"))
  "nuclei_200_pipe0 + nuclei_200_store")

;; DSP SIMD
(define_insn_reservation "nuclei_200_dsp_simd_insn" 1
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "simd"))
  "nuclei_200_pipe0 + nuclei_200_dsp")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_200_dsp_psimd_insn" 2
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "psimd"))
  "nuclei_200_pipe0 + nuclei_200_dsp, nuclei_200_dsp")

;; DSP Others
(define_insn_reservation "nuclei_200_dsp_other_insn" 2
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_200_pipe0 + nuclei_200_dsp, nuclei_200_dsp")

;; BMU
(define_insn_reservation "nuclei_200_bitmanip_insn" 1
  (and (eq_attr "tune" "nuclei_200")
       (eq_attr "type" "bitmanip"))
  "nuclei_200_pipe0")
