/* Builtin definitions for Nuclei xlcz extension
   Copyright (C) 2023 Free Software Foundation, Inc.
This file is part of GCC.
GCC is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 3, or (at your option)
any later version.
GCC is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ifndef _NUCLEI_XXLCZ_H_
#define _NUCLEI_XXLCZ_H_

#define __xl_bclr(a, b, c) \
  (__builtin_xxlcz_bclr ((a), (b), (c)))

#define __xl_bclr_r(a, b) \
  (__builtin_xxlcz_bclr_r ((a), (b)))

#define __xl_bset(a, b, c) \
  (__builtin_xxlcz_bset ((a), (b), (c)))

#define __xl_bset_r(a, b) \
  (__builtin_xxlcz_bset_r ((a), (b)))

#define __xl_extract(a, b, c) \
  (__builtin_xxlcz_extract ((a), (b), (c)))

#define __xl_extract_r(a, b) \
  (__builtin_xxlcz_extract_r ((a), (b)))

#define __xl_extractu(a, b, c) \
  (__builtin_xxlcz_extractu ((a), (b), (c)))

#define __xl_extractu_r(a, b) \
  (__builtin_xxlcz_extractu_r ((a), (b)))

#define __xl_insert(a, b, c) \
  (__builtin_xxlcz_insert ((a), (b), (c)))

#define __xl_slet(a, b) \
  (__builtin_xxlcz_slet ((a), (b)))

#define __xl_slet_u(a, b) \
  (__builtin_xxlcz_slet_u ((a), (b)))

#define __xl_muli(a, b) \
  (__builtin_xxlcz_muli ((a), (b)))

#define __xl_bitrev(a, b, c) \
  (__builtin_xxlcz_bitrev ((a), (b), (c)))

#define __xl_fl1(a) \
  (__builtin_xxlcz_fl1 (a))

#define __xl_ff1(a) \
  (__builtin_xxlcz_ff1 (a))

#define __xl_fl0(a) \
  (__builtin_xxlcz_fl0 (a))

#define __xl_ff0(a) \
  (__builtin_xxlcz_ff0 (a))

#define __xl_clb(a) \
  (__builtin_xxlcz_clb (a))

#define __xl_nzmsk(a) \
  (__builtin_xxlcz_nzmsk (a))

#define __xl_ffnz(a) \
  (__builtin_xxlcz_ffnz (a))

#define __xl_addrchk(a, b, c) \
  (__builtin_xxlcz_addrchk ((a), (b), (c)))

#define __xl_bezm(a, b, c) \
  (__builtin_xxlcz_bezm ((a), (b), (c)))

#endif
