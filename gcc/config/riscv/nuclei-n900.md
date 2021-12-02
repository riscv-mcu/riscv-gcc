(define_automaton "nuclei_n900")

(define_cpu_unit "nuclei_n900_pipe0" "nuclei_n900")
(define_cpu_unit "nuclei_n900_pipe1" "nuclei_n900")

(define_insn_reservation "nuclei_n900_alu_inst_placeholder" 1
  (and (eq_attr "tune" "nuclei_n900")
       (eq_attr "type" "unknown,arith,shift,slt,multi,logical,move"))
  "nuclei_n900_pipe0 | nuclei_n900_pipe1")
