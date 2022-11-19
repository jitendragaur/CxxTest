//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: cpsingle.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "cpsingle.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                int in3
//                int in4
//                const coder::array<double, 2U> &in5
//                int in6
//                int in7
// Return Type  : void
//
void binary_expand_op(coder::array<double, 2U> &in1,
                      const coder::array<double, 2U> &in2, int in3, int in4,
                      const coder::array<double, 2U> &in5, int in6, int in7)
{
  int b_in7;
  int loop_ub;
  int stride_1_1;
  if ((in7 - in6) + 1 == 1) {
    b_in7 = (in4 - in3) + 1;
  } else {
    b_in7 = (in7 - in6) + 1;
  }
  in1.set_size(1, b_in7);
  b_in7 = ((in4 - in3) + 1 != 1);
  stride_1_1 = ((in7 - in6) + 1 != 1);
  if ((in7 - in6) + 1 == 1) {
    loop_ub = (in4 - in3) + 1;
  } else {
    loop_ub = (in7 - in6) + 1;
  }
  for (int i{0}; i < loop_ub; i++) {
    in1[i] = in2[in3 + i * b_in7] + in5[in6 + i * stride_1_1];
  }
}

//
// File trailer for cpsingle.cpp
//
// [EOF]
//
