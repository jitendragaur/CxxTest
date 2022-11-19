//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: findchangepts.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "findchangepts.h"
#include "cppelt.h"
#include "cpsingle.h"
#include "peltMeanVar.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                ::coder::array<double, 1U> &ipoints
// Return Type  : void
//
namespace coder {
void findchangepts(const ::coder::array<double, 1U> &x,
                   ::coder::array<double, 1U> &ipoints)
{
  signal::internal::codegenable::findchangepts::peltMeanVar b_p;
  signal::internal::codegenable::findchangepts::peltMeanVar c_p;
  signal::internal::codegenable::findchangepts::peltMeanVar d_p;
  signal::internal::codegenable::findchangepts::peltMeanVar e_p;
  signal::internal::codegenable::findchangepts::peltMeanVar p;
  array<double, 2U> b_x;
  array<double, 2U> cp;
  array<double, 2U> cpidx;
  array<double, 2U> cpmax;
  array<double, 2U> fwd;
  array<double, 2U> rev;
  double bsum;
  double t;
  int ib;
  int nblocks;
  int sz_idx_1;
  int varargin_2;
  varargin_2 = x.size(0);
  sz_idx_1 = x.size(0);
  if (x.size(0) < 2) {
    cp.set_size(1, 0);
  } else {
    double minresidue;
    double resmax;
    double xbar;
    int firstBlockLength;
    int k;
    int lastBlockLength;
    int n;
    int xblockoffset;
    n = x.size(0);
    if (x.size(0) <= 1024) {
      firstBlockLength = x.size(0);
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = x.size(0) / 1024;
      lastBlockLength = x.size(0) - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    xbar = x[0];
    for (k = 2; k <= firstBlockLength; k++) {
      xbar += x[k - 1];
    }
    for (ib = 2; ib <= nblocks; ib++) {
      xblockoffset = (ib - 1) << 10;
      bsum = x[xblockoffset];
      if (ib == nblocks) {
        firstBlockLength = lastBlockLength;
      } else {
        firstBlockLength = 1024;
      }
      for (k = 2; k <= firstBlockLength; k++) {
        bsum += x[(xblockoffset + k) - 1];
      }
      xbar += bsum;
    }
    xbar /= static_cast<double>(x.size(0));
    bsum = 0.0;
    for (k = 0; k < n; k++) {
      t = x[k] - xbar;
      bsum += t * t;
    }
    resmax = static_cast<double>(x.size(0)) *
             std::log(bsum / static_cast<double>(x.size(0)));
    p.init();
    firstBlockLength = x.size(0);
    b_x = x.reshape(1, firstBlockLength);
    p.solveH(b_x, static_cast<double>(x.size(0)), 0.0, cpidx, &bsum);
    signal::internal::codegenable::findchangepts::makeChangePoints(
        cpidx, static_cast<double>(x.size(0)), cpmax, &t);
    minresidue = bsum - t * 0.0;
    if (cpmax.size(1) <= 2) {
      cp.set_size(1, cpmax.size(1));
      nblocks = cpmax.size(1);
      for (ib = 0; ib < nblocks; ib++) {
        cp[ib] = cpmax[ib];
      }
    } else {
      double Pmax;
      double Pmin;
      n = x.size(0);
      fwd.set_size(1, x.size(0));
      rev.set_size(1, x.size(0));
      bsum = 0.0;
      t = 0.0;
      ib = x.size(0);
      for (nblocks = 0; nblocks < ib; nblocks++) {
        xbar = x[nblocks] - bsum;
        bsum += xbar / (static_cast<double>(nblocks) + 1.0);
        t += xbar * (x[nblocks] - bsum);
        fwd[nblocks] =
            (static_cast<double>(nblocks) + 1.0) *
            std::fmax(-708.39641853226408 -
                          std::log(static_cast<double>(nblocks) + 1.0),
                      std::log(t / (static_cast<double>(nblocks) + 1.0)));
      }
      bsum = 0.0;
      t = 0.0;
      ib = x.size(0);
      for (nblocks = 0; nblocks < ib; nblocks++) {
        xblockoffset = (n - nblocks) - 1;
        xbar = x[xblockoffset] - bsum;
        firstBlockLength =
            static_cast<int>((static_cast<double>(n) + 1.0) -
                             static_cast<double>(xblockoffset + 1));
        bsum += xbar / static_cast<double>(firstBlockLength);
        t += xbar * (x[xblockoffset] - bsum);
        rev[xblockoffset] =
            static_cast<double>(firstBlockLength) *
            std::fmax(-708.39641853226408 -
                          std::log(static_cast<double>(firstBlockLength)),
                      std::log(t / static_cast<double>(firstBlockLength)));
      }
      if (fwd.size(1) - 2 < 2) {
        ib = 0;
        lastBlockLength = 0;
      } else {
        ib = 1;
        lastBlockLength = fwd.size(1) - 2;
      }
      if (rev.size(1) - 1 < 3) {
        xblockoffset = 0;
        firstBlockLength = 0;
      } else {
        xblockoffset = 2;
        firstBlockLength = rev.size(1) - 1;
      }
      nblocks = lastBlockLength - ib;
      if (nblocks == firstBlockLength - xblockoffset) {
        cp.set_size(1, nblocks);
        for (lastBlockLength = 0; lastBlockLength < nblocks;
             lastBlockLength++) {
          cp[lastBlockLength] =
              fwd[ib + lastBlockLength] + rev[xblockoffset + lastBlockLength];
        }
      } else {
        binary_expand_op(cp, fwd, ib, lastBlockLength - 1, rev, xblockoffset,
                         firstBlockLength - 1);
      }
      xblockoffset = cp.size(1);
      if (cp.size(1) <= 2) {
        if (cp.size(1) == 1) {
          bsum = cp[0];
        } else if ((cp[0] > cp[cp.size(1) - 1]) ||
                   (std::isnan(cp[0]) && (!std::isnan(cp[cp.size(1) - 1])))) {
          bsum = cp[cp.size(1) - 1];
        } else {
          bsum = cp[0];
        }
      } else {
        if (!std::isnan(cp[0])) {
          firstBlockLength = 1;
        } else {
          boolean_T exitg1;
          firstBlockLength = 0;
          k = 2;
          exitg1 = false;
          while ((!exitg1) && (k <= xblockoffset)) {
            if (!std::isnan(cp[k - 1])) {
              firstBlockLength = k;
              exitg1 = true;
            } else {
              k++;
            }
          }
        }
        if (firstBlockLength == 0) {
          bsum = cp[0];
        } else {
          bsum = cp[firstBlockLength - 1];
          ib = firstBlockLength + 1;
          for (k = ib; k <= xblockoffset; k++) {
            t = cp[k - 1];
            if (bsum > t) {
              bsum = t;
            }
          }
        }
      }
      xbar = resmax - bsum;
      b_p.init();
      firstBlockLength = x.size(0);
      b_x = x.reshape(1, firstBlockLength);
      b_p.solveH(b_x, static_cast<double>(x.size(0)), xbar, cpidx, &bsum);
      signal::internal::codegenable::findchangepts::makeChangePoints(
          cpidx, static_cast<double>(x.size(0)), cp, &t);
      bsum -= t * xbar;
      Pmax = rtInf;
      Pmin = 0.0;
      while ((cp.size(1) < 2) && (bsum >= minresidue)) {
        Pmax = xbar;
        resmax = bsum;
        cpmax.set_size(1, cp.size(1));
        nblocks = cp.size(1);
        for (ib = 0; ib < nblocks; ib++) {
          cpmax[0] = cp[0];
        }
        xbar *= 0.5;
        e_p.init();
        b_x = x.reshape(1, varargin_2);
        e_p.solveH(b_x, static_cast<double>(sz_idx_1), xbar, cpidx, &bsum);
        signal::internal::codegenable::findchangepts::makeChangePoints(
            cpidx, static_cast<double>(sz_idx_1), cp, &t);
        bsum -= t * xbar;
        if (cp.size(1) > 2) {
          Pmin = xbar;
          minresidue = bsum;
        }
      }
      while ((cp.size(1) > 2) && (bsum <= resmax) && std::isinf(Pmax)) {
        Pmin = xbar;
        xbar *= 2.0;
        c_p.init();
        b_x = x.reshape(1, varargin_2);
        c_p.solveH(b_x, static_cast<double>(sz_idx_1), xbar, cpidx, &bsum);
        signal::internal::codegenable::findchangepts::makeChangePoints(
            cpidx, static_cast<double>(sz_idx_1), cp, &t);
        bsum -= t * xbar;
        if (cp.size(1) < 2) {
          Pmax = xbar;
          cpmax.set_size(1, cp.size(1));
          nblocks = cp.size(1);
          for (ib = 0; ib < nblocks; ib++) {
            cpmax[0] = cp[0];
          }
          resmax = bsum;
        }
      }
      if (cp.size(1) != 2) {
        xbar = (Pmax + Pmin) / 2.0;
        while ((cp.size(1) != 2) && (Pmin < xbar) && (xbar < Pmax)) {
          d_p.init();
          b_x = x.reshape(1, varargin_2);
          d_p.solveH(b_x, static_cast<double>(sz_idx_1), xbar, cpidx, &bsum);
          signal::internal::codegenable::findchangepts::makeChangePoints(
              cpidx, static_cast<double>(sz_idx_1), cp, &t);
          if (cp.size(1) < 2) {
            cpmax.set_size(1, cp.size(1));
            nblocks = cp.size(1);
            for (ib = 0; ib < nblocks; ib++) {
              cpmax[0] = cp[0];
            }
            Pmax = xbar;
          } else {
            Pmin = xbar;
          }
          xbar = (Pmax + Pmin) / 2.0;
        }
        if (cp.size(1) != 2) {
          cp.set_size(1, cpmax.size(1));
          nblocks = cpmax.size(1);
          for (ib = 0; ib < nblocks; ib++) {
            cp[ib] = cpmax[ib];
          }
        }
      }
    }
  }
  ipoints.set_size(cp.size(1));
  nblocks = cp.size(1);
  for (ib = 0; ib < nblocks; ib++) {
    ipoints[ib] = cp[ib];
  }
}

} // namespace coder

//
// File trailer for findchangepts.cpp
//
// [EOF]
//
