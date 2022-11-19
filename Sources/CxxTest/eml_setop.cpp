//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_setop.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "eml_setop.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<int, 1U> &a
//                const ::coder::array<int, 1U> &b
//                ::coder::array<int, 1U> &c
//                ::coder::array<int, 1U> &ia
//                ::coder::array<int, 1U> &ib
// Return Type  : void
//
namespace coder {
void b_do_vectors(const ::coder::array<int, 1U> &a,
                  const ::coder::array<int, 1U> &b, ::coder::array<int, 1U> &c,
                  ::coder::array<int, 1U> &ia, ::coder::array<int, 1U> &ib)
{
  int iafirst;
  int ialast;
  int ibfirst;
  int iblast;
  int nc;
  int ncmax;
  nc = a.size(0);
  ncmax = b.size(0);
  if (nc <= ncmax) {
    ncmax = nc;
  }
  c.set_size(ncmax);
  ia.set_size(ncmax);
  ib.set_size(ncmax);
  nc = 0;
  iafirst = 0;
  ialast = 1;
  ibfirst = 0;
  iblast = 1;
  while ((ialast <= a.size(0)) && (iblast <= b.size(0))) {
    int ak;
    int b_ialast;
    int b_iblast;
    int bk;
    b_ialast = ialast;
    ak = a[ialast - 1];
    while ((b_ialast < a.size(0)) && (a[b_ialast] == ak)) {
      b_ialast++;
    }
    ialast = b_ialast;
    b_iblast = iblast;
    bk = b[iblast - 1];
    while ((b_iblast < b.size(0)) && (b[b_iblast] == bk)) {
      b_iblast++;
    }
    iblast = b_iblast;
    if (ak == bk) {
      nc++;
      c[nc - 1] = ak;
      ia[nc - 1] = iafirst + 1;
      ib[nc - 1] = ibfirst + 1;
      ialast = b_ialast + 1;
      iafirst = b_ialast;
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      ialast = b_ialast + 1;
      iafirst = b_ialast;
    } else {
      iblast = b_iblast + 1;
      ibfirst = b_iblast;
    }
  }
  if (ncmax > 0) {
    if (nc < 1) {
      ncmax = 0;
    } else {
      ncmax = nc;
    }
    ia.set_size(ncmax);
    if (nc < 1) {
      ncmax = 0;
    } else {
      ncmax = nc;
    }
    ib.set_size(ncmax);
    if (nc < 1) {
      nc = 0;
    }
    c.set_size(nc);
  }
}

//
// Arguments    : const ::coder::array<int, 1U> &a
//                const ::coder::array<int, 1U> &b
//                ::coder::array<int, 1U> &c
//                ::coder::array<int, 1U> &ia
//                ::coder::array<int, 1U> &ib
// Return Type  : void
//
void do_vectors(const ::coder::array<int, 1U> &a,
                const ::coder::array<int, 1U> &b, ::coder::array<int, 1U> &c,
                ::coder::array<int, 1U> &ia, ::coder::array<int, 1U> &ib)
{
  int b_ialast;
  int b_iblast;
  int iafirst;
  int ialast;
  int ibfirst;
  int iblast;
  int na;
  int nb;
  int nc;
  int ncmax;
  int nia;
  int nib;
  na = a.size(0);
  nb = b.size(0);
  ncmax = a.size(0) + b.size(0);
  c.set_size(ncmax);
  ia.set_size(a.size(0));
  ib.set_size(b.size(0));
  nc = -1;
  nia = -1;
  nib = 0;
  iafirst = 1;
  ialast = 0;
  ibfirst = 0;
  iblast = 0;
  while ((ialast + 1 <= na) && (iblast + 1 <= nb)) {
    int ak;
    int bk;
    b_ialast = ialast + 1;
    ak = a[ialast];
    while ((b_ialast < a.size(0)) && (a[b_ialast] == ak)) {
      b_ialast++;
    }
    ialast = b_ialast - 1;
    b_iblast = iblast + 1;
    bk = b[iblast];
    while ((b_iblast < b.size(0)) && (b[b_iblast] == bk)) {
      b_iblast++;
    }
    iblast = b_iblast - 1;
    if (ak == bk) {
      nc++;
      c[nc] = ak;
      nia++;
      ia[nia] = iafirst;
      ialast = b_ialast;
      iafirst = b_ialast + 1;
      iblast = b_iblast;
      ibfirst = b_iblast;
    } else if (ak < bk) {
      nc++;
      nia++;
      c[nc] = ak;
      ia[nia] = iafirst;
      ialast = b_ialast;
      iafirst = b_ialast + 1;
    } else {
      nc++;
      nib++;
      c[nc] = bk;
      ib[nib - 1] = ibfirst + 1;
      iblast = b_iblast;
      ibfirst = b_iblast;
    }
  }
  while (ialast + 1 <= na) {
    b_ialast = ialast + 1;
    while ((b_ialast < a.size(0)) && (a[b_ialast] == a[ialast])) {
      b_ialast++;
    }
    nc++;
    nia++;
    c[nc] = a[ialast];
    ia[nia] = iafirst;
    ialast = b_ialast;
    iafirst = b_ialast + 1;
  }
  while (iblast + 1 <= nb) {
    b_iblast = iblast + 1;
    while ((b_iblast < b.size(0)) && (b[b_iblast] == b[iblast])) {
      b_iblast++;
    }
    nc++;
    nib++;
    c[nc] = b[iblast];
    ib[nib - 1] = ibfirst + 1;
    iblast = b_iblast;
    ibfirst = b_iblast;
  }
  if (a.size(0) > 0) {
    if (nia + 1 < 1) {
      nia = 0;
    } else {
      nia++;
    }
    ia.set_size(nia);
  }
  if (b.size(0) > 0) {
    if (nib < 1) {
      nib = 0;
    }
    ib.set_size(nib);
  }
  if (ncmax > 0) {
    if (nc + 1 < 1) {
      nc = 0;
    } else {
      nc++;
    }
    c.set_size(nc);
  }
}

} // namespace coder

//
// File trailer for eml_setop.cpp
//
// [EOF]
//
