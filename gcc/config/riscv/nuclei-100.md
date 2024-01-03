(define_automaton "nuclei_100")

(define_cpu_unit "nuclei_100_pipe0" "nuclei_100")

;; imul can be piped, but idiv cannot
(define_cpu_unit "nuclei_100_imul" "nuclei_100")
(define_cpu_unit "nuclei_100_idiv" "nuclei_100")

(define_cpu_unit "nuclei_100_load" "nuclei_100")
(define_cpu_unit "nuclei_100_store" "nuclei_100")

;; fmisc/fmac can be piped, but fdiv cannot
(define_cpu_unit "nuclei_100_fmisc" "nuclei_100")
(define_cpu_unit "nuclei_100_fmac" "nuclei_100")
(define_cpu_unit "nuclei_100_fdiv" "nuclei_100")

;; DSP cannot be piped
(define_cpu_unit "nuclei_100_dsp" "nuclei_100")

;; ALU instructions
(define_insn_reservation "nuclei_100_alu_insn" 1
  (and (eq_attr "tune" "nuclei_100")
    (eq_attr "type" "unknown, arith, shift, slt, multi, logical, move, nop, const, auipc"))
  "nuclei_100_pipe0")

;; Load
(define_insn_reservation "nuclei_100_load_insn" 2
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "load"))
  "nuclei_100_pipe0 + nuclei_100_load")

;; Store
(define_insn_reservation "nuclei_100_store_insn" 1
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "store"))
  "nuclei_100_pipe0 + nuclei_100_store")

;; Branch
(define_insn_reservation "nuclei_100_branch_insn" 1
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "branch, jump, call"))
  "nuclei_100_pipe0")

;; Integer multiplication
(define_insn_reservation "nuclei_100_imul_insn" 1
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "imul"))
  "nuclei_100_pipe0 + nuclei_100_imul")

;; Integer division, 32 bits, defer to tune info
(define_insn_reservation "nuclei_100_idiv_si_insn" 33
  (and (eq_attr "tune" "nuclei_100")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_100_pipe0 + nuclei_100_idiv, nuclei_100_idiv * 32")

;; Integer division, 64 bits, defer to tune info
(define_insn_reservation "nuclei_100_idiv_di_insn" 64
  (and (eq_attr "tune" "nuclei_100")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_100_pipe0 + nuclei_100_idiv, nuclei_100_idiv * 63")

;; FPU misc
(define_insn_reservation "nuclei_100_fmisc_insn" 2
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "mfc, mtc, fcvt, fmove"))
  "nuclei_100_pipe0 + nuclei_100_fmisc")

;; Float mul/add/cmp, defer to tune info
(define_insn_reservation "nuclei_100_fmac_insn" 2
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "fmul, fadd, fcmp, fmadd"))
  "nuclei_100_pipe0 + nuclei_100_fmac")

;; Float division/sqrt, 32 bits, defer to tune info
(define_insn_reservation "nuclei_100_fdiv_sf_insn" 20
  (and (eq_attr "tune" "nuclei_100")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "SF")))
  "nuclei_100_pipe0 + nuclei_100_fdiv, nuclei_100_fdiv * 19")

;; Float division/sqrt, 64 bits, defer to tune info
(define_insn_reservation "nuclei_100_fdiv_df_insn" 34
  (and (eq_attr "tune" "nuclei_100")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "DF")))
  "nuclei_100_pipe0 + nuclei_100_fdiv, nuclei_100_fdiv * 33")

;; Float load
(define_insn_reservation "nuclei_100_fpload_insn" 2
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "fpload"))
  "nuclei_100_pipe0 + nuclei_100_load")

;; Float store
(define_insn_reservation "nuclei_100_fpstore_insn" 1
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "fpstore"))
  "nuclei_100_pipe0 + nuclei_100_store")

;; DSP SIMD
(define_insn_reservation "nuclei_100_dsp_simd_insn" 1
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "simd"))
  "nuclei_100_pipe0 + nuclei_100_dsp")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_100_dsp_psimd_insn" 2
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "psimd"))
  "nuclei_100_pipe0 + nuclei_100_dsp, nuclei_100_dsp")

;; DSP Others
(define_insn_reservation "nuclei_100_dsp_other_insn" 2
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_100_pipe0 + nuclei_100_dsp, nuclei_100_dsp")

;; BMU
(define_insn_reservation "nuclei_100_bitmanip_insn" 1
  (and (eq_attr "tune" "nuclei_100")
       (eq_attr "type" "bitmanip"))
  "nuclei_100_pipe0")
