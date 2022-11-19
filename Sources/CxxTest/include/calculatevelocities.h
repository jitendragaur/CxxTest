//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calculatevelocities.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

#ifndef CALCULATEVELOCITIES_H
#define CALCULATEVELOCITIES_H

// Include Files
#include "calculatevelocities_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Function Declarations
extern void calculatevelocities(const coder::array<double, 2U> &acc_final,
                                coder::array<double, 2U> &gravity_final,
                                const coder::array<double, 2U> &att_final,
                                coder::array<double, 2U> &time_final,
                                struct0_T *V_out, double *Rep_count);

#endif
//
// File trailer for calculatevelocities.h
//
// [EOF]
//
