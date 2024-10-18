;; Peephole optimizations for RISC-V for GNU compiler.
;; Copyright (C) 2011-2024 Free Software Foundation, Inc.
;; Contributed by Andrew Waterman (andrew@sifive.com).

;; This file is part of GCC.

;; GCC is free software; you can redistribute it and/or modify
;; it under the terms of the GNU General Public License as published by
;; the Free Software Foundation; either version 3, or (at your option)
;; any later version.

;; GCC is distributed in the hope that it will be useful,
;; but WITHOUT ANY WARRANTY; without even the implied warranty of
;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;; GNU General Public License for more details.

;; You should have received a copy of the GNU General Public License
;; along with GCC; see the file COPYING3.  If not see
;; <http://www.gnu.org/licenses/>.

;; Simplify (unsigned long)(unsigned int)a << const
(define_peephole2
  [(set (match_operand:DI 0 "register_operand")
	(ashift:DI (match_operand:DI 1 "register_operand")
		   (match_operand 2 "const_int_operand")))
   (set (match_operand:DI 3 "register_operand")
	(lshiftrt:DI (match_dup 0) (match_dup 2)))
   (set (match_operand:DI 4 "register_operand")
	(ashift:DI (match_dup 3) (match_operand 5 "const_int_operand")))]
  "TARGET_64BIT
   && INTVAL (operands[5]) < INTVAL (operands[2])
   && (REGNO (operands[3]) == REGNO (operands[4])
       || peep2_reg_dead_p (3, operands[3]))"
  [(set (match_dup 0)
	(ashift:DI (match_dup 1) (match_dup 2)))
   (set (match_dup 4)
	(lshiftrt:DI (match_dup 0) (match_operand 5)))]
{
  operands[5] = GEN_INT (INTVAL (operands[2]) - INTVAL (operands[5]));
})

;; ZCMP
(define_peephole2
  [(set (match_operand:X 0 "a0a1_reg_operand")
        (match_operand:X 1 "zcmp_mv_sreg_operand"))
   (set (match_operand:X 2 "a0a1_reg_operand")
        (match_operand:X 3 "zcmp_mv_sreg_operand"))]
  "TARGET_ZCMP
   && (REGNO (operands[2]) != REGNO (operands[0]))"
  [(parallel [(set (match_dup 0)
                   (match_dup 1))
              (set (match_dup 2)
                   (match_dup 3))])]
)

(define_peephole2
  [(set (match_operand:X 0 "zcmp_mv_sreg_operand")
        (match_operand:X 1 "a0a1_reg_operand"))
   (set (match_operand:X 2 "zcmp_mv_sreg_operand")
        (match_operand:X 3 "a0a1_reg_operand"))]
  "TARGET_ZCMP
   && (REGNO (operands[0]) != REGNO (operands[2]))
   && (REGNO (operands[1]) != REGNO (operands[3]))"
  [(parallel [(set (match_dup 0)
                   (match_dup 1))
              (set (match_dup 2)
                   (match_dup 3))])]
)

(define_peephole2 ; ld
  [(set (match_operand:SI 0 "register_operand" "")
	(match_operand:SI 2 "memory_operand" ""))
   (set (match_operand:SI 1 "register_operand" "")
	(match_operand:SI 3 "memory_operand" ""))]
  "TARGET_ZILSD"
  [(parallel [(set (match_dup 0) (match_dup 2))
	      (set (match_dup 1) (match_dup 3))])]
{
  if (!riscv_fix_operands_ld_sd (operands, true, false, false))
    FAIL;
})

(define_peephole2 ; sd
  [(set (match_operand:SI 2 "memory_operand" "")
	(match_operand:SI 0 "register_operand" ""))
   (set (match_operand:SI 3 "memory_operand" "")
	(match_operand:SI 1 "register_operand" ""))]
  "TARGET_ZILSD"
  [(parallel [(set (match_dup 2) (match_dup 0))
	      (set (match_dup 3) (match_dup 1))])]
{
  if (!riscv_fix_operands_ld_sd (operands, false, false, false))
    FAIL;
})

;; The following peepholes reorder registers to enable LD/SD.
(define_peephole2 ; sd of constants
  [(set (match_operand:SI 0 "register_operand" "")
	(match_operand:SI 4 "const_int_operand" ""))
   (set (match_operand:SI 2 "memory_operand" "")
	(match_dup 0))
   (set (match_operand:SI 1 "register_operand" "")
	(match_operand:SI 5 "const_int_operand" ""))
   (set (match_operand:SI 3 "memory_operand" "")
	(match_dup 1))]
  "TARGET_ZILSD"
  [(set (match_dup 0) (match_dup 4))
   (set (match_dup 1) (match_dup 5))
   (parallel [(set (match_dup 2) (match_dup 0))
	      (set (match_dup 3) (match_dup 1))])]
{
  if (!riscv_fix_operands_ld_sd (operands, false, true, false))
    FAIL;
})

(define_peephole2 ; sd of constants
  [(set (match_operand:SI 0 "register_operand" "")
	(match_operand:SI 4 "const_int_operand" ""))
   (set (match_operand:SI 1 "register_operand" "")
	(match_operand:SI 5 "const_int_operand" ""))
   (set (match_operand:SI 2 "memory_operand" "")
	(match_dup 0))
   (set (match_operand:SI 3 "memory_operand" "")
	(match_dup 1))]
  "TARGET_ZILSD"
  [(set (match_dup 0) (match_dup 4))
   (set (match_dup 1) (match_dup 5))
   (parallel [(set (match_dup 2) (match_dup 0))
	      (set (match_dup 3) (match_dup 1))])]
{
  if (!riscv_fix_operands_ld_sd (operands, false, true, false))
     FAIL;
})

;; insns matching the LD/SD patterns that will get created by the above peepholes.
(define_insn "*riscv_ld"
  [(parallel [(set (match_operand:SI 0 "register_operand" "=r")
		   (match_operand:SI 2 "memory_operand" "m"))
	      (set (match_operand:SI 1 "register_operand" "=r")
		   (match_operand:SI 3 "memory_operand" "m"))])]
  "TARGET_ZILSD && reload_completed
  && riscv_valid_operands_ld_sd (operands)"
  {
    rtx op[2];
    op[0] = gen_rtx_REG (DImode, REGNO (operands[0]));
    op[1] = adjust_address (operands[2], DImode, 0);
    return riscv_output_move_double (op);
  }
  [(set_attr "length" "4")
   (set_attr "type" "load")]
)

(define_insn "*riscv_sd"
  [(parallel [(set (match_operand:SI 2 "memory_operand" "=m")
		   (match_operand:SI 0 "register_operand" "r"))
	      (set (match_operand:SI 3 "memory_operand" "=m")
		   (match_operand:SI 1 "register_operand" "r"))])]
  "TARGET_ZILSD && reload_completed
  && riscv_valid_operands_ld_sd (operands)"
  {
    rtx op[2];
    op[0] = adjust_address (operands[2], DImode, 0);
    op[1] = gen_rtx_REG (DImode, REGNO (operands[0]));
    return riscv_output_move_double (op);
  }
  [(set_attr "length" "4")
   (set_attr "type" "store")]
)
