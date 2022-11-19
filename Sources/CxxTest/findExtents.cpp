//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: findExtents.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "findExtents.h"
#include "eml_mtimes_helper.h"
#include "eml_setop.h"
#include "ixfun.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void c_binary_expand_op(coder::array<boolean_T, 1U> &in1,
                               const coder::array<double, 1U> &in2,
                               const coder::array<int, 1U> &in3,
                               const coder::array<double, 1U> &in4);

namespace coder {
namespace signal {
namespace internal {
namespace findpeaks {
static void getLeftBase(const ::coder::array<double, 1U> &yTemp,
                        const ::coder::array<int, 1U> &iPeak,
                        const ::coder::array<int, 1U> &iFinite,
                        const ::coder::array<int, 1U> &iInflect,
                        ::coder::array<int, 1U> &iBase,
                        ::coder::array<int, 1U> &iSaddle);

}
} // namespace internal
} // namespace signal
} // namespace coder

// Function Definitions
//
// Arguments    : coder::array<boolean_T, 1U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<int, 1U> &in3
//                const coder::array<double, 1U> &in4
// Return Type  : void
//
static void c_binary_expand_op(coder::array<boolean_T, 1U> &in1,
                               const coder::array<double, 1U> &in2,
                               const coder::array<int, 1U> &in3,
                               const coder::array<double, 1U> &in4)
{
  int i;
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  if (in4.size(0) == 1) {
    i = in3.size(0);
  } else {
    i = in4.size(0);
  }
  in1.set_size(i);
  stride_0_0 = (in3.size(0) != 1);
  stride_1_0 = (in4.size(0) != 1);
  if (in4.size(0) == 1) {
    loop_ub = in3.size(0);
  } else {
    loop_ub = in4.size(0);
  }
  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[in3[i * stride_0_0] - 1] - in4[i * stride_1_0] >= 0.65);
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &yTemp
//                const ::coder::array<int, 1U> &iPeak
//                const ::coder::array<int, 1U> &iFinite
//                const ::coder::array<int, 1U> &iInflect
//                ::coder::array<int, 1U> &iBase
//                ::coder::array<int, 1U> &iSaddle
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace findpeaks {
static void getLeftBase(const ::coder::array<double, 1U> &yTemp,
                        const ::coder::array<int, 1U> &iPeak,
                        const ::coder::array<int, 1U> &iFinite,
                        const ::coder::array<int, 1U> &iInflect,
                        ::coder::array<int, 1U> &iBase,
                        ::coder::array<int, 1U> &iSaddle)
{
  array<double, 1U> peak;
  array<double, 1U> valley;
  array<int, 1U> iValley;
  double v;
  int i;
  int iv;
  int j;
  int k;
  int n;
  iBase.set_size(iPeak.size(0));
  n = iPeak.size(0);
  for (i = 0; i < n; i++) {
    iBase[i] = 0;
  }
  iSaddle.set_size(iPeak.size(0));
  n = iPeak.size(0);
  for (i = 0; i < n; i++) {
    iSaddle[i] = 0;
  }
  peak.set_size(iFinite.size(0));
  n = iFinite.size(0);
  for (i = 0; i < n; i++) {
    peak[i] = 0.0;
  }
  valley.set_size(iFinite.size(0));
  n = iFinite.size(0);
  for (i = 0; i < n; i++) {
    valley[i] = 0.0;
  }
  iValley.set_size(iFinite.size(0));
  n = iFinite.size(0);
  for (i = 0; i < n; i++) {
    iValley[i] = 0;
  }
  n = -1;
  i = 0;
  j = 0;
  k = 0;
  v = rtNaN;
  iv = 1;
  while (k + 1 <= iPeak.size(0)) {
    double p;
    int isv;
    while (iInflect[i] != iFinite[j]) {
      v = yTemp[iInflect[i] - 1];
      iv = iInflect[i];
      if (std::isnan(yTemp[iInflect[i] - 1])) {
        n = -1;
      } else {
        while ((n + 1 > 0) && (valley[n] > v)) {
          n--;
        }
      }
      i++;
    }
    p = yTemp[iInflect[i] - 1];
    while ((n + 1 > 0) && (peak[n] < p)) {
      if (valley[n] < v) {
        v = valley[n];
        iv = iValley[n];
      }
      n--;
    }
    isv = iv;
    while ((n + 1 > 0) && (peak[n] <= p)) {
      if (valley[n] < v) {
        v = valley[n];
        iv = iValley[n];
      }
      n--;
    }
    n++;
    peak[n] = yTemp[iInflect[i] - 1];
    valley[n] = v;
    iValley[n] = iv;
    if (iInflect[i] == iPeak[k]) {
      iBase[k] = iv;
      iSaddle[k] = isv;
      k++;
    }
    i++;
    j++;
  }
}

//
// Arguments    : const ::coder::array<double, 1U> &y
//                const ::coder::array<double, 1U> &x
//                ::coder::array<int, 1U> &iPk
//                const ::coder::array<int, 1U> &iFin
//                const ::coder::array<int, 1U> &iInf
//                const ::coder::array<int, 1U> &iInflect
//                ::coder::array<double, 1U> &bPk
//                ::coder::array<double, 2U> &bxPk
//                ::coder::array<double, 2U> &byPk
//                ::coder::array<double, 2U> &wxPk
// Return Type  : void
//
void findExtents(
    const ::coder::array<double, 1U> &y, const ::coder::array<double, 1U> &x,
    ::coder::array<int, 1U> &iPk, const ::coder::array<int, 1U> &iFin,
    const ::coder::array<int, 1U> &iInf,
    const ::coder::array<int, 1U> &iInflect, ::coder::array<double, 1U> &bPk,
    ::coder::array<double, 2U> &bxPk, ::coder::array<double, 2U> &byPk,
    ::coder::array<double, 2U> &wxPk)
{
  array<double, 2U> b_wxPk;
  array<double, 1U> b_bPk;
  array<double, 1U> idx;
  array<double, 1U> varargin_2;
  array<double, 1U> yFinite;
  array<int, 1U> b_x;
  array<int, 1U> c_x;
  array<int, 1U> iInfR;
  array<int, 1U> iLeftSaddle;
  array<int, 1U> iRightBase;
  array<int, 1U> iRightSaddle;
  array<int, 1U> ii;
  array<boolean_T, 1U> d_x;
  double refHeight;
  double varargin_1;
  int m;
  int md2;
  int nx;
  int xtmp;
  boolean_T exitg1;
  yFinite.set_size(y.size(0));
  md2 = y.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    yFinite[xtmp] = y[xtmp];
  }
  md2 = iInf.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    yFinite[iInf[xtmp] - 1] = rtNaN;
  }
  getLeftBase(yFinite, iPk, iFin, iInflect, ii, iLeftSaddle);
  iInfR.set_size(iPk.size(0));
  md2 = iPk.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    iInfR[xtmp] = iPk[xtmp];
  }
  m = iPk.size(0) - 1;
  md2 = iPk.size(0) >> 1;
  for (int i{0}; i < md2; i++) {
    xtmp = iInfR[i];
    nx = m - i;
    iInfR[i] = iInfR[nx];
    iInfR[nx] = xtmp;
  }
  b_x.set_size(iFin.size(0));
  md2 = iFin.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    b_x[xtmp] = iFin[xtmp];
  }
  m = iFin.size(0) - 1;
  md2 = iFin.size(0) >> 1;
  for (int i{0}; i < md2; i++) {
    xtmp = b_x[i];
    nx = m - i;
    b_x[i] = b_x[nx];
    b_x[nx] = xtmp;
  }
  c_x.set_size(iInflect.size(0));
  md2 = iInflect.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    c_x[xtmp] = iInflect[xtmp];
  }
  m = iInflect.size(0) - 1;
  md2 = iInflect.size(0) >> 1;
  for (int i{0}; i < md2; i++) {
    xtmp = c_x[i];
    nx = m - i;
    c_x[i] = c_x[nx];
    c_x[nx] = xtmp;
  }
  getLeftBase(yFinite, iInfR, b_x, c_x, iRightBase, iRightSaddle);
  m = iRightBase.size(0) - 1;
  md2 = iRightBase.size(0) >> 1;
  for (int i{0}; i < md2; i++) {
    xtmp = iRightBase[i];
    nx = m - i;
    iRightBase[i] = iRightBase[nx];
    iRightBase[nx] = xtmp;
  }
  m = iRightSaddle.size(0) - 1;
  md2 = iRightSaddle.size(0) >> 1;
  for (int i{0}; i < md2; i++) {
    xtmp = iRightSaddle[i];
    nx = m - i;
    iRightSaddle[i] = iRightSaddle[nx];
    iRightSaddle[nx] = xtmp;
  }
  idx.set_size(ii.size(0));
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    idx[xtmp] = yFinite[ii[xtmp] - 1];
  }
  varargin_2.set_size(iRightBase.size(0));
  md2 = iRightBase.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    varargin_2[xtmp] = yFinite[iRightBase[xtmp] - 1];
  }
  if (ii.size(0) == iRightBase.size(0)) {
    b_bPk.set_size(idx.size(0));
    md2 = idx.size(0);
    for (xtmp = 0; xtmp < md2; xtmp++) {
      varargin_1 = idx[xtmp];
      refHeight = varargin_2[xtmp];
      b_bPk[xtmp] = std::fmax(varargin_1, refHeight);
    }
  } else {
    ::coder::internal::expand_max(idx, varargin_2, b_bPk);
  }
  if (iPk.size(0) == b_bPk.size(0)) {
    d_x.set_size(iPk.size(0));
    md2 = iPk.size(0);
    for (xtmp = 0; xtmp < md2; xtmp++) {
      d_x[xtmp] = (yFinite[iPk[xtmp] - 1] - b_bPk[xtmp] >= 0.65);
    }
  } else {
    c_binary_expand_op(d_x, yFinite, iPk, b_bPk);
  }
  nx = d_x.size(0);
  m = 0;
  ii.set_size(d_x.size(0));
  md2 = 0;
  exitg1 = false;
  while ((!exitg1) && (md2 <= nx - 1)) {
    if (d_x[md2]) {
      m++;
      ii[m - 1] = md2 + 1;
      if (m >= nx) {
        exitg1 = true;
      } else {
        md2++;
      }
    } else {
      md2++;
    }
  }
  if (d_x.size(0) == 1) {
    if (m == 0) {
      ii.set_size(0);
    }
  } else {
    if (m < 1) {
      m = 0;
    }
    ii.set_size(m);
  }
  idx.set_size(ii.size(0));
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    idx[xtmp] = ii[xtmp];
  }
  ii.set_size(idx.size(0));
  md2 = idx.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    ii[xtmp] = iPk[static_cast<int>(idx[xtmp]) - 1];
  }
  iPk.set_size(ii.size(0));
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    iPk[xtmp] = ii[xtmp];
  }
  bPk.set_size(idx.size(0));
  md2 = idx.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    bPk[xtmp] = b_bPk[static_cast<int>(idx[xtmp]) - 1];
  }
  b_bPk.set_size(bPk.size(0));
  md2 = bPk.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    b_bPk[xtmp] = bPk[xtmp];
  }
  ii.set_size(idx.size(0));
  md2 = idx.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    ii[xtmp] = iLeftSaddle[static_cast<int>(idx[xtmp]) - 1];
  }
  iLeftSaddle.set_size(ii.size(0));
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    iLeftSaddle[xtmp] = ii[xtmp];
  }
  ii.set_size(idx.size(0));
  md2 = idx.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    ii[xtmp] = iRightSaddle[static_cast<int>(idx[xtmp]) - 1];
  }
  iRightSaddle.set_size(ii.size(0));
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    iRightSaddle[xtmp] = ii[xtmp];
  }
  if (iPk.size(0) == 0) {
    idx.set_size(0);
    iLeftSaddle.set_size(0);
    iRightSaddle.set_size(0);
  } else {
    idx.set_size(b_bPk.size(0));
    md2 = b_bPk.size(0);
    for (xtmp = 0; xtmp < md2; xtmp++) {
      idx[xtmp] = b_bPk[xtmp];
    }
  }
  b_wxPk.set_size(iPk.size(0), 2);
  md2 = iPk.size(0) << 1;
  for (xtmp = 0; xtmp < md2; xtmp++) {
    b_wxPk[xtmp] = 0.0;
  }
  xtmp = iPk.size(0);
  for (int i{0}; i < xtmp; i++) {
    double xc_tmp;
    varargin_1 = yFinite[iPk[i] - 1] + idx[i];
    refHeight = varargin_1 / 2.0;
    nx = iPk[i];
    while ((nx >= iLeftSaddle[i]) && (yFinite[nx - 1] > refHeight)) {
      nx--;
    }
    if (nx < iLeftSaddle[i]) {
      b_wxPk[i] = x[iLeftSaddle[i] - 1];
    } else {
      double b_xc_tmp;
      xc_tmp = yFinite[nx - 1];
      b_xc_tmp = x[nx - 1];
      varargin_1 = b_xc_tmp + (x[nx] - b_xc_tmp) * (0.5 * varargin_1 - xc_tmp) /
                                  (yFinite[nx] - xc_tmp);
      if (std::isnan(varargin_1)) {
        if (std::isinf(idx[i])) {
          varargin_1 = 0.5 * (b_xc_tmp + x[nx]);
        } else {
          varargin_1 = x[nx];
        }
      }
      b_wxPk[i] = varargin_1;
    }
    nx = iPk[i] - 1;
    while ((nx + 1 <= iRightSaddle[i]) && (yFinite[nx] > refHeight)) {
      nx++;
    }
    if (nx + 1 > iRightSaddle[i]) {
      b_wxPk[i + b_wxPk.size(0)] = x[iRightSaddle[i] - 1];
    } else {
      xc_tmp = x[nx - 1];
      varargin_1 =
          x[nx] + (xc_tmp - x[nx]) *
                      (0.5 * (yFinite[iPk[i] - 1] + idx[i]) - yFinite[nx]) /
                      (yFinite[nx - 1] - yFinite[nx]);
      if (std::isnan(varargin_1)) {
        if (std::isinf(idx[i])) {
          varargin_1 = 0.5 * (x[nx] + xc_tmp);
        } else {
          varargin_1 = xc_tmp;
        }
      }
      b_wxPk[i + b_wxPk.size(0)] = varargin_1;
    }
  }
  do_vectors(iPk, iInf, c_x, ii, iInfR);
  b_do_vectors(c_x, iPk, b_x, ii, iInfR);
  idx.set_size(ii.size(0));
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    idx[xtmp] = ii[xtmp];
  }
  b_do_vectors(c_x, iInf, b_x, ii, iInfR);
  varargin_2.set_size(ii.size(0));
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    varargin_2[xtmp] = ii[xtmp];
  }
  bPk.set_size(c_x.size(0));
  md2 = c_x.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    bPk[xtmp] = 0.0;
  }
  md2 = b_bPk.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    bPk[static_cast<int>(idx[xtmp]) - 1] = b_bPk[xtmp];
  }
  ii.set_size(varargin_2.size(0));
  md2 = varargin_2.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    ii[xtmp] = static_cast<int>(varargin_2[xtmp]);
  }
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    bPk[ii[xtmp] - 1] = 0.0;
  }
  ii.set_size(iInf.size(0));
  md2 = iInf.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    nx = iInf[xtmp] - 1;
    if (nx < 1) {
      nx = 1;
    }
    ii[xtmp] = nx;
  }
  iInfR.set_size(iInf.size(0));
  md2 = iInf.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    m = iInf[xtmp] + 1;
    nx = x.size(0);
    if (m > nx) {
      iInfR[xtmp] = nx;
    } else {
      iInfR[xtmp] = m;
    }
  }
  bxPk.set_size(c_x.size(0), 2);
  md2 = c_x.size(0) << 1;
  for (xtmp = 0; xtmp < md2; xtmp++) {
    bxPk[xtmp] = 0.0;
  }
  md2 = iLeftSaddle.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    bxPk[static_cast<int>(idx[xtmp]) - 1] = x[iLeftSaddle[xtmp] - 1];
  }
  md2 = iRightSaddle.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    bxPk[(static_cast<int>(idx[xtmp]) + bxPk.size(0)) - 1] =
        x[iRightSaddle[xtmp] - 1];
  }
  if (iInf.size(0) == ii.size(0)) {
    md2 = iInf.size(0);
    for (xtmp = 0; xtmp < md2; xtmp++) {
      bxPk[static_cast<int>(varargin_2[xtmp]) - 1] =
          0.5 * (x[iInf[xtmp] - 1] + x[ii[xtmp] - 1]);
    }
  } else {
    b_binary_expand_op(bxPk, varargin_2, x, iInf, ii);
  }
  if (iInf.size(0) == iInfR.size(0)) {
    md2 = iInf.size(0);
    for (xtmp = 0; xtmp < md2; xtmp++) {
      bxPk[(static_cast<int>(varargin_2[xtmp]) + bxPk.size(0)) - 1] =
          0.5 * (x[iInf[xtmp] - 1] + x[iInfR[xtmp] - 1]);
    }
  } else {
    binary_expand_op(bxPk, varargin_2, x, iInf, iInfR);
  }
  byPk.set_size(c_x.size(0), 2);
  md2 = c_x.size(0) << 1;
  for (xtmp = 0; xtmp < md2; xtmp++) {
    byPk[xtmp] = 0.0;
  }
  md2 = iLeftSaddle.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    byPk[static_cast<int>(idx[xtmp]) - 1] = y[iLeftSaddle[xtmp] - 1];
  }
  md2 = iRightSaddle.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    byPk[(static_cast<int>(idx[xtmp]) + byPk.size(0)) - 1] =
        y[iRightSaddle[xtmp] - 1];
  }
  md2 = ii.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    byPk[static_cast<int>(varargin_2[xtmp]) - 1] = y[ii[xtmp] - 1];
  }
  md2 = iInfR.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    byPk[(static_cast<int>(varargin_2[xtmp]) + byPk.size(0)) - 1] =
        y[iInfR[xtmp] - 1];
  }
  wxPk.set_size(c_x.size(0), 2);
  md2 = c_x.size(0) << 1;
  for (xtmp = 0; xtmp < md2; xtmp++) {
    wxPk[xtmp] = 0.0;
  }
  md2 = b_wxPk.size(0);
  for (xtmp = 0; xtmp < 2; xtmp++) {
    for (nx = 0; nx < md2; nx++) {
      wxPk[(static_cast<int>(idx[nx]) + wxPk.size(0) * xtmp) - 1] =
          b_wxPk[nx + b_wxPk.size(0) * xtmp];
    }
  }
  if (iInf.size(0) == ii.size(0)) {
    md2 = iInf.size(0);
    for (xtmp = 0; xtmp < md2; xtmp++) {
      wxPk[static_cast<int>(varargin_2[xtmp]) - 1] =
          0.5 * (x[iInf[xtmp] - 1] + x[ii[xtmp] - 1]);
    }
  } else {
    b_binary_expand_op(wxPk, varargin_2, x, iInf, ii);
  }
  if (iInf.size(0) == iInfR.size(0)) {
    md2 = iInf.size(0);
    for (xtmp = 0; xtmp < md2; xtmp++) {
      wxPk[(static_cast<int>(varargin_2[xtmp]) + wxPk.size(0)) - 1] =
          0.5 * (x[iInf[xtmp] - 1] + x[iInfR[xtmp] - 1]);
    }
  } else {
    binary_expand_op(wxPk, varargin_2, x, iInf, iInfR);
  }
  iPk.set_size(c_x.size(0));
  md2 = c_x.size(0);
  for (xtmp = 0; xtmp < md2; xtmp++) {
    iPk[xtmp] = c_x[xtmp];
  }
}

} // namespace findpeaks
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for findExtents.cpp
//
// [EOF]
//
