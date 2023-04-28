(define_automaton "nuclei_900")

(define_cpu_unit "nuclei_900_pipe0" "nuclei_900")
(define_cpu_unit "nuclei_900_pipe1" "nuclei_900")
(final_presence_set "nuclei_900_pipe1" "nuclei_900_pipe0")

(define_reservation "nuclei_900_pipe_any" "nuclei_900_pipe0 | nuclei_900_pipe1")

;; Dual-issue (load + store), but not (load + load) or (store + store)
(define_cpu_unit "nuclei_900_load" "nuclei_900")
(define_cpu_unit "nuclei_900_store" "nuclei_900")

;; Single-issue branch instructions
(define_cpu_unit "nuclei_900_branch" "nuclei_900")

;; imul can be piped, but idiv cannot
(define_cpu_unit "nuclei_900_imul" "nuclei_900")
(define_cpu_unit "nuclei_900_idiv" "nuclei_900")

;; fmisc/fmac can be piped, but fdiv cannot
(define_cpu_unit "nuclei_900_fmisc" "nuclei_900")
(define_cpu_unit "nuclei_900_fmac" "nuclei_900")
(define_cpu_unit "nuclei_900_fdiv" "nuclei_900")

;; DSP cannot be piped
(define_cpu_unit "nuclei_900_dsp" "nuclei_900")

;; ALU instructions
(define_insn_reservation "nuclei_900_alu_insn" 1
  (and (eq_attr "tune" "nuclei_900")
    (eq_attr "type" "unknown, arith, shift, slt, multi, logical, move, nop, const, auipc"))
  "nuclei_900_pipe_any")

;; Load 32/64 bits
(define_insn_reservation "nuclei_900_load_wd_insn" 3
  (and (eq_attr "tune" "nuclei_900")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "SI,DI")))
  "nuclei_900_pipe_any + nuclei_900_load")

;; Load 8/16 bits
(define_insn_reservation "nuclei_900_load_bh_insn" 4
  (and (eq_attr "tune" "nuclei_900")
    (and (eq_attr "type" "load")
      (eq_attr "mode" "QI,HI")))
  "nuclei_900_pipe_any + nuclei_900_load")

;; Stroe, defer to tune info
(define_insn_reservation "nuclei_900_store_insn" 0
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "store"))
  "nuclei_900_pipe_any + nuclei_900_store")

;; Branch, defer to tune info
(define_insn_reservation "nuclei_900_branch_insn" 0
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "branch, jump, call"))
  "nuclei_900_pipe_any + nuclei_900_branch")

;; Integer multiplication, defer to tune info
(define_insn_reservation "nuclei_900_imul_insn" 4
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "imul"))
  "nuclei_900_pipe_any + nuclei_900_imul")

;; Integer division, 32 bits, defer to tune info
(define_insn_reservation "nuclei_900_idiv_si_insn" 4
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "SI")))
  "nuclei_900_pipe_any + nuclei_900_idiv, nuclei_900_idiv * 3")

;; Integer division, 64 bits, defer to tune info
(define_insn_reservation "nuclei_900_idiv_di_insn" 4
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "idiv")
            (eq_attr "mode" "DI")))
  "nuclei_900_pipe_any + nuclei_900_idiv, nuclei_900_idiv * 3")

;; FPU misc
(define_insn_reservation "nuclei_900_fmisc_insn" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "mfc, mtc, fcvt, fmove"))
  "nuclei_900_pipe_any + nuclei_900_fmisc")

;; Float mul/add/cmp, defer to tune info
(define_insn_reservation "nuclei_900_fmac_insn" 5
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fmul, fadd, fcmp, fmadd"))
  "nuclei_900_pipe_any + nuclei_900_fmac")

;; Float division/sqrt, 32 bits, defer to tune info
(define_insn_reservation "nuclei_900_fdiv_sf_insn" 20
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "SF")))
  "nuclei_900_pipe_any + nuclei_900_fdiv, nuclei_900_fdiv * 19")

;; Float division/sqrt, 64 bits, defer to tune info
(define_insn_reservation "nuclei_900_fdiv_df_insn" 34
  (and (eq_attr "tune" "nuclei_900")
       (and (eq_attr "type" "fdiv, fsqrt")
            (eq_attr "mode" "DF")))
  "nuclei_900_pipe_any + nuclei_900_fdiv, nuclei_900_fdiv * 33")

;; Float load
(define_insn_reservation "nuclei_900_fpload_insn" 4
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fpload"))
  "nuclei_900_pipe_any + nuclei_900_load")

;; Float store, defer to tune info
(define_insn_reservation "nuclei_900_fpstore_insn" 0
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "fpstore"))
  "nuclei_900_pipe_any + nuclei_900_store")

;; DSP SIMD
(define_insn_reservation "nuclei_900_dsp_simd_insn" 2
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "simd"))
  "nuclei_900_pipe_any + nuclei_900_dsp, nuclei_900_dsp")

;; DSP Partial SIMD
(define_insn_reservation "nuclei_900_dsp_psimd_insn" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "psimd"))
  "nuclei_900_pipe_any + nuclei_900_dsp, nuclei_900_dsp * 2")

;; DSP Others
(define_insn_reservation "nuclei_900_dsp_other_insn" 3
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "dsp, dsp64"))
  "nuclei_900_pipe_any + nuclei_900_dsp, nuclei_900_dsp * 2")

;; BMU
(define_insn_reservation "nuclei_900_bitmanip_insn" 1
  (and (eq_attr "tune" "nuclei_900")
       (eq_attr "type" "bitmanip"))
  "nuclei_900_pipe_any")
