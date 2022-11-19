//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: findpeaks.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "findpeaks.h"
#include "findExtents.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &Yin
//                ::coder::array<double, 2U> &Ypk
//                ::coder::array<double, 2U> &Xpk
// Return Type  : void
//
namespace coder {
void findpeaks(const ::coder::array<double, 2U> &Yin,
               ::coder::array<double, 2U> &Ypk, ::coder::array<double, 2U> &Xpk)
{
  array<double, 2U> bxPk;
  array<double, 2U> byPk;
  array<double, 2U> wxPk;
  array<double, 1U> bPk;
  array<double, 1U> b_Yin;
  array<double, 1U> b_r;
  array<int, 2U> y;
  array<int, 1U> iInfinite;
  array<int, 1U> iInflect;
  array<int, 1U> iPk;
  array<int, 1U> idx;
  double ykfirst;
  int i;
  int kfirst;
  int nInf;
  int nInflect;
  int nPk;
  int ny;
  char dir;
  boolean_T isinfykfirst;
  idx.set_size(Yin.size(1));
  iInfinite.set_size(Yin.size(1));
  iInflect.set_size(Yin.size(1));
  ny = Yin.size(1);
  nPk = 0;
  nInf = 0;
  nInflect = -1;
  dir = 'n';
  kfirst = 0;
  ykfirst = rtInf;
  isinfykfirst = true;
  for (int k{1}; k <= ny; k++) {
    double yk;
    boolean_T isinfyk;
    yk = Yin[k - 1];
    if (std::isnan(yk)) {
      yk = rtInf;
      isinfyk = true;
    } else if (std::isinf(yk) && (yk > 0.0)) {
      isinfyk = true;
      nInf++;
      iInfinite[nInf - 1] = k;
    } else {
      isinfyk = false;
    }
    if (yk != ykfirst) {
      char previousdir;
      previousdir = dir;
      if (isinfyk || isinfykfirst) {
        dir = 'n';
        if (kfirst >= 1) {
          nInflect++;
          iInflect[nInflect] = kfirst;
        }
      } else if (yk < ykfirst) {
        dir = 'd';
        if (previousdir != 'd') {
          nInflect++;
          iInflect[nInflect] = kfirst;
          if (previousdir == 'i') {
            nPk++;
            idx[nPk - 1] = kfirst;
          }
        }
      } else {
        dir = 'i';
        if (previousdir != 'i') {
          nInflect++;
          iInflect[nInflect] = kfirst;
        }
      }
      ykfirst = yk;
      kfirst = k;
      isinfykfirst = isinfyk;
    }
  }
  if ((Yin.size(1) > 0) && (!isinfykfirst) &&
      ((nInflect + 1 == 0) || (iInflect[nInflect] < Yin.size(1)))) {
    nInflect++;
    iInflect[nInflect] = Yin.size(1);
  }
  if (nPk < 1) {
    i = 0;
  } else {
    i = nPk;
  }
  idx.set_size(i);
  if (nInf < 1) {
    nInf = 0;
  }
  iInfinite.set_size(nInf);
  if (nInflect + 1 < 1) {
    nInflect = -1;
  }
  iInflect.set_size(nInflect + 1);
  iPk.set_size(i);
  nPk = 0;
  for (int k{0}; k < i; k++) {
    ykfirst = Yin[idx[k] - 1];
    if ((ykfirst > rtMinusInf) &&
        (ykfirst - std::fmax(Yin[idx[k] - 2], Yin[idx[k]]) >= 0.0)) {
      nPk++;
      iPk[nPk - 1] = idx[k];
    }
  }
  if (nPk < 1) {
    nPk = 0;
  }
  iPk.set_size(nPk);
  ny = Yin.size(1);
  b_r.set_size(Yin.size(1));
  kfirst = Yin.size(1) - 1;
  for (i = 0; i <= kfirst; i++) {
    b_r[i] = static_cast<double>(i) + 1.0;
  }
  b_Yin = Yin.reshape(ny);
  signal::internal::findpeaks::findExtents(b_Yin, b_r, iPk, idx, iInfinite,
                                           iInflect, bPk, bxPk, byPk, wxPk);
  if (iPk.size(0) < 1) {
    ny = 0;
  } else {
    ny = iPk.size(0);
  }
  y.set_size(1, ny);
  if (ny > 0) {
    y[0] = 1;
    kfirst = 1;
    for (int k{2}; k <= ny; k++) {
      kfirst++;
      y[k - 1] = kfirst;
    }
  }
  idx.set_size(y.size(1));
  kfirst = y.size(1);
  for (i = 0; i < kfirst; i++) {
    idx[i] = y[i];
  }
  if (idx.size(0) > Yin.size(1)) {
    idx.set_size(Yin.size(1));
  }
  iInfinite.set_size(idx.size(0));
  kfirst = idx.size(0);
  for (i = 0; i < kfirst; i++) {
    iInfinite[i] = iPk[idx[i] - 1];
  }
  iPk.set_size(iInfinite.size(0));
  kfirst = iInfinite.size(0);
  for (i = 0; i < kfirst; i++) {
    iPk[i] = iInfinite[i];
  }
  Ypk.set_size(1, iPk.size(0));
  kfirst = iPk.size(0);
  for (i = 0; i < kfirst; i++) {
    Ypk[i] = Yin[iPk[i] - 1];
  }
  Xpk.set_size(1, iPk.size(0));
  kfirst = iPk.size(0);
  for (i = 0; i < kfirst; i++) {
    Xpk[i] = static_cast<unsigned int>(iPk[i]);
  }
}

} // namespace coder

//
// File trailer for findpeaks.cpp
//
// [EOF]
//
