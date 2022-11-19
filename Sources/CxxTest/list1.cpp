//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: list1.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "list1.h"
#include "calculatevelocities_data.h"
#include "calculatevelocities_internal_types.h"
#include "calculatevelocities_types.h"
#include "rt_nonfinite.h"
#include "coder_array.h"

// Function Definitions
//
// Arguments    : int nodeAddr
//                double value_start
//                double value_stop
// Return Type  : void
//
namespace coder {
namespace internal {
void list::insertAfter(int nodeAddr, double value_start, double value_stop)
{
  struct_T expl_temp;
  if ((nodeAddr < 1) || (nodeAddr > valuePool.size(0))) {
    int k;
    k = newNodeAddr();
    if (k != 0) {
      if (frontAddr == 0) {
        frontAddr = k;
        backAddr = k;
      } else {
        nodePool[k - 1].next = frontAddr;
        nodePool[frontAddr - 1].prev = k;
        frontAddr = k;
      }
      expl_temp.start = value_start;
      expl_temp.stop = value_stop;
      valuePool[k - 1] = expl_temp;
    }
  } else if (nodeAddr == backAddr) {
    int k;
    k = newNodeAddr();
    if (k != 0) {
      if (frontAddr == 0) {
        frontAddr = k;
        backAddr = k;
        nodePool[k - 1].next = 0;
      } else {
        nodePool[k - 1].prev = backAddr;
        nodePool[backAddr - 1].next = k;
        backAddr = k;
      }
      expl_temp.start = value_start;
      expl_temp.stop = value_stop;
      valuePool[k - 1] = expl_temp;
    }
  } else {
    int k;
    k = newNodeAddr();
    if (k != 0) {
      int node_next;
      if (nodeAddr > valuePool.size(0)) {
        node_next = 0;
      } else {
        node_next = nodePool[nodeAddr - 1].next;
      }
      expl_temp.start = value_start;
      expl_temp.stop = value_stop;
      valuePool[k - 1] = expl_temp;
      nodePool[k - 1].prev = nodeAddr;
      nodePool[k - 1].next = node_next;
      nodePool[nodeAddr - 1].next = k;
      nodePool[node_next - 1].prev = k;
    }
  }
}

//
// Arguments    : void
// Return Type  : int
//
int list::newNodeAddr()
{
  int k;
  if (unusedAddr == 0) {
    struct_T obj;
    int cap;
    int i;
    int startlen;
    startlen = nodePool.size(0) - 1;
    obj = valuePool[0];
    i = valuePool.size(0);
    valuePool.set_size(valuePool.size(0) + 8);
    cap = nodePool.size(0);
    nodePool.set_size(cap + 8);
    for (int i1{0}; i1 < 8; i1++) {
      valuePool[i1 + i] = obj;
      nodePool[cap + i1] = r;
    }
    for (k = 0; k < 8; k++) {
      i = startlen + k;
      nodePool[(startlen + k) + 1].addr = i + 2;
      nodePool[(startlen + k) + 1].next = i + 3;
      nodePool[(startlen + k) + 1].prev = i + 1;
    }
    cap = nodePool.size(0);
    unusedAddr = startlen + 2;
    nodePool[startlen + 1].prev = 0;
    nodePool[cap - 1].next = 0;
  }
  k = unusedAddr;
  if (unusedAddr != 0) {
    len++;
    unusedAddr = nodePool[unusedAddr - 1].next;
    nodePool[k - 1].next = 0;
    if (unusedAddr != 0) {
      nodePool[unusedAddr - 1].prev = 0;
    }
  }
  return k;
}

} // namespace internal
} // namespace coder

//
// File trailer for list1.cpp
//
// [EOF]
//
