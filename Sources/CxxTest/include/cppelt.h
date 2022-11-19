//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cppelt.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

#ifndef CPPELT_H
#define CPPELT_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace findchangepts {
void makeChangePoints(::coder::array<double, 2U> &cpidx, double n,
                      ::coder::array<double, 2U> &cp, double *nchanges);

}
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for cppelt.h
//
// [EOF]
//
