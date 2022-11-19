//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: eml_mtimes_helper.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "eml_mtimes_helper.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<double, 1U> &in3
//                const coder::array<int, 1U> &in4
//                const coder::array<int, 1U> &in5
// Return Type  : void
//
void b_binary_expand_op(coder::array<double, 2U> &in1,
                        const coder::array<double, 1U> &in2,
                        const coder::array<double, 1U> &in3,
                        const coder::array<int, 1U> &in4,
                        const coder::array<int, 1U> &in5)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  stride_0_0 = (in4.size(0) != 1);
  stride_1_0 = (in5.size(0) != 1);
  if (in5.size(0) == 1) {
    loop_ub = in4.size(0);
  } else {
    loop_ub = in5.size(0);
  }
  for (int i{0}; i < loop_ub; i++) {
    in1[static_cast<int>(in2[i]) - 1] =
        0.5 * (in3[in4[i * stride_0_0] - 1] + in3[in5[i * stride_1_0] - 1]);
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 1U> &in2
//                const coder::array<double, 1U> &in3
//                const coder::array<int, 1U> &in4
//                const coder::array<int, 1U> &in5
// Return Type  : void
//
void binary_expand_op(coder::array<double, 2U> &in1,
                      const coder::array<double, 1U> &in2,
                      const coder::array<double, 1U> &in3,
                      const coder::array<int, 1U> &in4,
                      const coder::array<int, 1U> &in5)
{
  int loop_ub;
  int stride_0_0;
  int stride_1_0;
  stride_0_0 = (in4.size(0) != 1);
  stride_1_0 = (in5.size(0) != 1);
  if (in5.size(0) == 1) {
    loop_ub = in4.size(0);
  } else {
    loop_ub = in5.size(0);
  }
  for (int i{0}; i < loop_ub; i++) {
    in1[(static_cast<int>(in2[i]) + in1.size(0)) - 1] =
        0.5 * (in3[in4[i * stride_0_0] - 1] + in3[in5[i * stride_1_0] - 1]);
  }
}

//
// File trailer for eml_mtimes_helper.cpp
//
// [EOF]
//
