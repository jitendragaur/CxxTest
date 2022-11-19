//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: findExtents.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

#ifndef FINDEXTENTS_H
#define FINDEXTENTS_H

// Include Files
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
namespace coder {
namespace signal {
namespace internal {
namespace findpeaks {
void findExtents(
    const ::coder::array<double, 1U> &y, const ::coder::array<double, 1U> &x,
    ::coder::array<int, 1U> &iPk, const ::coder::array<int, 1U> &iFin,
    const ::coder::array<int, 1U> &iInf,
    const ::coder::array<int, 1U> &iInflect, ::coder::array<double, 1U> &bPk,
    ::coder::array<double, 2U> &bxPk, ::coder::array<double, 2U> &byPk,
    ::coder::array<double, 2U> &wxPk);

}
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for findExtents.h
//
// [EOF]
//
