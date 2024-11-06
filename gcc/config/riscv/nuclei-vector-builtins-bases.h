/* function_base declaration for nuclei custom 'V' Extension for GNU compiler.
   Copyright (C) 2024 Free Software Foundation, Inc.
   Contributed by Nuclei.

   This file is part of GCC.

   GCC is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   GCC is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with GCC; see the file COPYING3.  If not see
   <http://www.gnu.org/licenses/>.  */

#ifndef GCC_NUCLEI_VECTOR_BUILTINS_BASES_H
#define GCC_NUCLEI_VECTOR_BUILTINS_BASES_H

namespace riscv_vector {

namespace bases {
extern const function_base *const xl_vqmacc;
extern const function_base *const xl_vqmaccu;
extern const function_base *const xl_vqmaccsu;
extern const function_base *const xl_vqmaccus;
/* Xxlvfbf */
extern const function_base *const xl_vfwadd;
extern const function_base *const xl_vfwadd_frm;
extern const function_base *const xl_vfwsub;
extern const function_base *const xl_vfwsub_frm;
extern const function_base *const xl_vfwmul;
extern const function_base *const xl_vfwmul_frm;
extern const function_base *const xl_vfwmacc;
extern const function_base *const xl_vfwmacc_frm;
extern const function_base *const xl_vfwnmacc;
extern const function_base *const xl_vfwnmacc_frm;
extern const function_base *const xl_vfwmsac;
extern const function_base *const xl_vfwmsac_frm;
extern const function_base *const xl_vfwnmsac;
extern const function_base *const xl_vfwnmsac_frm;
extern const function_base *const xl_vfclass;
extern const function_base *const xl_vfcvt_x;
extern const function_base *const xl_vfcvt_x_frm;
extern const function_base *const xl_vfcvt_xu;
extern const function_base *const xl_vfcvt_xu_frm;
extern const function_base *const xl_vfcvt_rtz_x;
extern const function_base *const xl_vfcvt_rtz_xu;
extern const function_base *const xl_vfwcvt_x;
extern const function_base *const xl_vfwcvt_x_frm;
extern const function_base *const xl_vfwcvt_xu;
extern const function_base *const xl_vfwcvt_xu_frm;
extern const function_base *const xl_vfwcvt_rtz_x;
extern const function_base *const xl_vfwcvt_rtz_xu;
extern const function_base *const xl_vfwcvt_f;
extern const function_base *const xl_vfncvt_f;
extern const function_base *const xl_vfncvt_f_frm;
extern const function_base *const xl_vfncvt_rod_f;
}

} // end namespace riscv_vector
#endif
