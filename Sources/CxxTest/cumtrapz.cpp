//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cumtrapz.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "cumtrapz.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : const ::coder::array<double, 1U> &x
//                const ::coder::array<double, 1U> &y
//                ::coder::array<double, 1U> &z
// Return Type  : void
//
namespace coder {
void cumtrapz(const ::coder::array<double, 1U> &x,
              const ::coder::array<double, 1U> &y,
              ::coder::array<double, 1U> &z)
{
  array<double, 1U> b_x;
  int dim;
  int i;
  int vlen;
  b_x.set_size(x.size(0));
  dim = x.size(0);
  for (i = 0; i < dim; i++) {
    b_x[i] = x[i];
  }
  dim = 0;
  if (y.size(0) != 1) {
    dim = -1;
  }
  if (dim + 2 <= 1) {
    vlen = y.size(0) - 2;
  } else {
    vlen = -1;
  }
  for (i = 0; i <= vlen; i++) {
    b_x[i] = b_x[i + 1] - b_x[i];
  }
  z.set_size(y.size(0));
  if (y.size(0) != 0) {
    int vstride;
    vstride = 1;
    for (int k{0}; k <= dim; k++) {
      vstride *= y.size(0);
    }
    for (int j{0}; j < vstride; j++) {
      double s;
      double ylast;
      s = 0.0;
      dim = -1;
      ylast = y[j];
      z[j] = 0.0;
      for (int k{0}; k <= vlen; k++) {
        if (b_x.size(0) == 0) {
          s += (ylast + y[j + (k + 1) * vstride]) / 2.0;
        } else {
          dim++;
          s += b_x[dim] * ((ylast + y[j + (k + 1) * vstride]) / 2.0);
        }
        i = j + (k + 1) * vstride;
        ylast = y[i];
        z[i] = s;
      }
    }
  }
}

} // namespace coder

//
// File trailer for cumtrapz.cpp
//
// [EOF]
//
