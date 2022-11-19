//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: list1.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

#ifndef LIST1_H
#define LIST1_H

// Include Files
#include "calculatevelocities_internal_types.h"
#include "calculatevelocities_types.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
namespace coder {
namespace internal {
class list {
public:
  int newNodeAddr();
  void insertAfter(int nodeAddr, double value_start, double value_stop);
  array<b_struct_T, 1U> nodePool;
  array<struct_T, 1U> valuePool;
  int unusedAddr;
  int frontAddr;
  int backAddr;
  int len;
};

} // namespace internal
} // namespace coder

#endif
//
// File trailer for list1.h
//
// [EOF]
//
