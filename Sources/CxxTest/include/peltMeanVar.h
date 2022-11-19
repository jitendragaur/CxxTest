//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: peltMeanVar.h
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

#ifndef PELTMEANVAR_H
#define PELTMEANVAR_H

// Include Files
#include "list1.h"
#include "rtwtypes.h"
#include "coder_array.h"
#include <cstddef>
#include <cstdlib>

// Type Definitions
struct c_struct_T {
  double Syy;
  double yBar;
};

namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace findchangepts {
class peltMeanVar {
public:
  peltMeanVar *init();
  void solveH(const ::coder::array<double, 2U> &y, double nx, double penalty,
              ::coder::array<double, 2U> &cpidx, double *residue);

protected:
  void updateDistsWithNewEndpointH(double y, double ix);
  double getBestPartitionH(const ::coder::array<double, 2U> &y, double ix,
                           int *ibest);
  boolean_T prunePartition(double threshold, int *partitionListIterator);
  double z;
  array<double, 2U> dists;
  array<double, 2U> costs;
  ::coder::internal::list partition;

private:
  array<c_struct_T, 2U> work;
  double logrealmin;
};

} // namespace findchangepts
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

#endif
//
// File trailer for peltMeanVar.h
//
// [EOF]
//
