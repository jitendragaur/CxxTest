//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cppelt.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "cppelt.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : ::coder::array<double, 2U> &cpidx
//                double n
//                ::coder::array<double, 2U> &cp
//                double *nchanges
// Return Type  : void
//
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace findchangepts {
void makeChangePoints(::coder::array<double, 2U> &cpidx, double n,
                      ::coder::array<double, 2U> &cp, double *nchanges)
{
  double in;
  double ix;
  int i;
  int loop_ub_tmp;
  boolean_T exitg1;
  ix = n;
  in = n + 1.0;
  exitg1 = false;
  while ((!exitg1) && (ix != 0.0)) {
    double d;
    d = cpidx[static_cast<int>(ix + 1.0) - 1];
    if ((d != 0.0) && (d < ix)) {
      in--;
      cpidx[static_cast<int>(in + 1.0) - 1] = d;
      ix = cpidx[static_cast<int>(ix + 1.0) - 1];
    } else {
      exitg1 = true;
    }
  }
  *nchanges = (n + 1.0) - in;
  loop_ub_tmp = static_cast<int>(*nchanges);
  cp.set_size(1, loop_ub_tmp);
  for (i = 0; i < loop_ub_tmp; i++) {
    cp[i] = 0.0;
  }
  i = static_cast<int>(n + (1.0 - in));
  for (loop_ub_tmp = 0; loop_ub_tmp < i; loop_ub_tmp++) {
    ix = in + static_cast<double>(loop_ub_tmp);
    cp[static_cast<int>((ix - in) + 1.0) - 1] =
        cpidx[static_cast<int>(ix + 1.0) - 1] + 1.0;
  }
}

} // namespace findchangepts
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for cppelt.cpp
//
// [EOF]
//
