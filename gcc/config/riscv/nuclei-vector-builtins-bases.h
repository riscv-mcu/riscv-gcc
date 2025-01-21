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
/* Zvw extensions*/
extern const function_base *const vdsmul;
extern const function_base *const vcpack;
extern const function_base *const vcunpackr;
extern const function_base *const vcunpacki;
extern const function_base *const vdsmacini;
extern const function_base *const xl_vlsb;
extern const function_base *const vconj;
extern const function_base *const vdscmul;
extern const function_base *const vdscmulj;
extern const function_base *const vdscredsum;
extern const function_base *const vdscmaco;
extern const function_base *const vdscmacjo;
extern const function_base *const vdscmacor;
extern const function_base *const vdscmacoi;
extern const function_base *const vdscmacjor;
extern const function_base *const vdscmacjoi;
extern const function_base *const vdscmulr;
extern const function_base *const vdscmuli;
extern const function_base *const vdscmuljr;
extern const function_base *const vdscmulji;
extern const function_base *const vdsredsum;
extern const function_base *const vdsredsumn;
extern const function_base *const vredmaxi;
extern const function_base *const vredmini;
extern const function_base *const vperm;
extern const function_base *const vfsl;
extern const function_base *const vfsr;
extern const function_base *const vlnlp0;
extern const function_base *const vlnlp1;
extern const function_base *const vnle;
extern const function_base *const vnlm;
extern const function_base *const vdsmac;
extern const function_base *const vdscmac;
extern const function_base *const vdscmacj;
extern const function_base *const vdsmaco;
extern const function_base *const vfcvt_b2h;
extern const function_base *const vfcvt_b2w;
extern const function_base *const vfcvt_h2w;
extern const function_base *const xl_vfcvt_h2b;
extern const function_base *const xl_vfcvt_w2b;
extern const function_base *const xl_vfcvt_w2h;
extern const function_base *const vfcvt_p2c;
extern const function_base *const xl_vfcvt_c2p;
}

} // end namespace riscv_vector
#endif
