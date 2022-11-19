//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: ixfun.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "ixfun.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &a
//                const ::coder::array<double, 1U> &b
//                ::coder::array<double, 1U> &c
// Return Type  : void
//
namespace coder {
namespace internal {
void expand_max(const ::coder::array<double, 1U> &a,
                const ::coder::array<double, 1U> &b,
                ::coder::array<double, 1U> &c)
{
  int acoef;
  int csz_idx_0;
  int u0;
  u0 = a.size(0);
  acoef = b.size(0);
  if (u0 <= acoef) {
    acoef = u0;
  }
  if (b.size(0) == 1) {
    csz_idx_0 = a.size(0);
  } else if (a.size(0) == 1) {
    csz_idx_0 = b.size(0);
  } else {
    csz_idx_0 = acoef;
  }
  u0 = a.size(0);
  acoef = b.size(0);
  if (u0 <= acoef) {
    acoef = u0;
  }
  if (b.size(0) == 1) {
    acoef = a.size(0);
  } else if (a.size(0) == 1) {
    acoef = b.size(0);
  }
  c.set_size(acoef);
  if (csz_idx_0 != 0) {
    int bcoef;
    acoef = (a.size(0) != 1);
    bcoef = (b.size(0) != 1);
    u0 = csz_idx_0 - 1;
    for (csz_idx_0 = 0; csz_idx_0 <= u0; csz_idx_0++) {
      c[csz_idx_0] = std::fmax(a[acoef * csz_idx_0], b[bcoef * csz_idx_0]);
    }
  }
}

} // namespace internal
} // namespace coder

//
// File trailer for ixfun.cpp
//
// [EOF]
//
