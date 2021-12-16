(define_automaton "nuclei_n900")

(define_cpu_unit "nuclei_n900_pipe0" "nuclei_n900")
(define_cpu_unit "nuclei_n900_pipe1" "nuclei_n900")
(final_presence_set "nuclei_n900_pipe1" "nuclei_n900_pipe0")

(define_reservation "nuclei_n900_pipe_any" "nuclei_n900_pipe0 | nuclei_n900_pipe1")

;; load + store can be piped, load + load or store + store cannot
(define_cpu_unit "nuclei_n900_load" "nuclei_n900")
(define_cpu_unit "nuclei_n900_store" "nuclei_n900")

;; Single-issue branch instructions
(define_cpu_unit "nuclei_n900_branch" "nuclei_n900")

;; imul can be piped, but idiv cannot
(define_cpu_unit "nuclei_n900_imul" "nuclei_n900")
(define_cpu_unit "nuclei_n900_idiv" "nuclei_n900")

;; fmisc/fmac can be piped, but fdiv cannot
(define_cpu_unit "nuclei_n900_fmisc" "nuclei_n900")
(define_cpu_unit "nuclei_n900_fmac" "nuclei_n900")
(define_cpu_unit "nuclei_n900_fdiv" "nuclei_n900")

;; DSP cannot be piped
(define_cpu_unit "nuclei_n900_dsp" "nuclei_n900")

;; ALU instructions
(define_insn_reservation "nuclei_n900_alu_insn" 1
  (and (eq_attr "tune" "nuclei_n900")
    (eq_attr "type" "unknown, arith, shift, slt, multi, logical, move, nop, const, auipc"))
  "nuclei_n900_pipe_any")

;; Load 32/64 bits
(define_insn_reservation "nuclei_n900_load_wd_insn" 3
  (and (eq_attr "tune" "nuclei_n900")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "SI,DI")))
  "nuclei_n900_pipe_any + nuclei_n900_load")

;; Load 8/16 bits
(define_insn_reservation "nuclei_n900_load_bh_insn" 4
  (and (eq_attr "tune" "nuclei_n900")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "QI,HI")))
  "nuclei_n900_pipe_any + nuclei_n900_load")

;; Stroe, defer to tune info
(define_insn_reservation "nuclei_n900_store_insn" 0
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "store"))
  "nuclei_n900_pipe_any + nuclei_n900_store")

;; Branch, defer to tune info
(define_insn_reservation "nuclei_n900_branch_insn" 0
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "branch, jump, call"))
  "nuclei_n900_pipe_any + nuclei_n900_branch")

;; Integer multiplication, defer to tune info
(define_insn_reservation "nuclei_n900_imul_insn" 4
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "imul"))
  "nuclei_n900_pipe_any + nuclei_n900_imul")

;; Integer division, 32 bits, defer to tune info
(define_insn_reservation "nuclei_n900_idiv_si_insn" 4
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_n900_pipe_any + nuclei_n900_idiv, nuclei_n900_idiv * 3")

;; Integer division, 64 bits, defer to tune info
(define_insn_reservation "nuclei_n900_idiv_di_insn" 4
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_n900_pipe_any + nuclei_n900_idiv, nuclei_n900_idiv * 3")

;; FPU misc
(define_insn_reservation "nuclei_n900_fmisc_insn" 3
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "mfc, mtc, fcvt, fmove"))
  "nuclei_n900_pipe_any + nuclei_n900_fmisc")

;; Float mul/add/cmp, defer to tune info
(define_insn_reservation "nuclei_n900_fmac_insn" 5
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "fmul, fadd, fcmp, fmadd"))
  "nuclei_n900_pipe_any + nuclei_n900_fmac")

;; Float division/sqrt, 32 bits, defer to tune info
(define_insn_reservation "nuclei_n900_fdiv_sf_insn" 20
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "SF")))
  "nuclei_n900_pipe_any + nuclei_n900_fdiv, nuclei_n900_fdiv * 19")

;; Float division/sqrt, 64 bits, defer to tune info
(define_insn_reservation "nuclei_n900_fdiv_df_insn" 34
  (and (eq_attr "tune" "nuclei_n900")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "DF")))
  "nuclei_n900_pipe_any + nuclei_n900_fdiv, nuclei_n900_fdiv * 33")

;; Float load
(define_insn_reservation "nuclei_n900_fpload_insn" 4
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "fpload"))
  "nuclei_n900_pipe_any + nuclei_n900_load")

;; Float store, defer to tune info
(define_insn_reservation "nuclei_n900_fpstore_insn" 0
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "fpstore"))
  "nuclei_n900_pipe_any + nuclei_n900_store")

;; DSP SIMD
(define_insn_reservation "nuclei_n900_dsp_simd_insn" 2
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "simd"))
  "nuclei_n900_pipe_any + nuclei_n900_dsp, nuclei_n900_dsp")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_n900_dsp_psimd_insn" 3
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "psimd"))
  "nuclei_n900_pipe_any + nuclei_n900_dsp, nuclei_n900_dsp * 2")

;; DSP Others
(define_insn_reservation "nuclei_n900_dsp_other_insn" 3
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_n900_pipe_any + nuclei_n900_dsp, nuclei_n900_dsp * 2")

;; BMU
(define_insn_reservation "nuclei_n900_bitmanip_insn" 1
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "bitmanip"))
  "nuclei_n900_pipe_any")
