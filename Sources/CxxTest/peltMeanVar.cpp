//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: peltMeanVar.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "peltMeanVar.h"
#include "calculatevelocities_data.h"
#include "calculatevelocities_internal_types.h"
#include "calculatevelocities_types.h"
#include "list1.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Definitions
//
// Arguments    : const ::coder::array<double, 2U> &y
//                double ix
//                int *ibest
// Return Type  : double
//
namespace coder {
namespace signal {
namespace internal {
namespace codegenable {
namespace findchangepts {
double peltMeanVar::getBestPartitionH(const ::coder::array<double, 2U> &y,
                                      double ix, int *ibest)
{
  struct_T ibestPartitionData;
  double best;
  int ip;
  if ((*ibest < 1) || (*ibest > partition.valuePool.size(0))) {
    ibestPartitionData = partition.valuePool[0];
  } else {
    ibestPartitionData = partition.valuePool[*ibest - 1];
  }
  best = costs[static_cast<int>(ibestPartitionData.start + 1.0) - 1] +
         dists[static_cast<int>(ibestPartitionData.stop + 1.0) - 1];
  ip = partition.frontAddr;
  while (ip != 0) {
    if ((ip < 1) || (ip > partition.valuePool.size(0))) {
      ibestPartitionData = partition.valuePool[0];
    } else {
      ibestPartitionData = partition.valuePool[ip - 1];
    }
    while (costs[static_cast<int>(ibestPartitionData.start + 1.0) - 1] +
               dists[static_cast<int>(ibestPartitionData.stop + 1.0) - 1] <
           best) {
      double istart;
      double istop;
      double startcost;
      double stopdist;
      if ((ip < 1) || (ip > partition.valuePool.size(0))) {
        ibestPartitionData = partition.valuePool[0];
      } else {
        ibestPartitionData = partition.valuePool[ip - 1];
      }
      istart = ibestPartitionData.start;
      istop = ibestPartitionData.stop;
      startcost = costs[static_cast<int>(ibestPartitionData.start + 1.0) - 1];
      stopdist = dists[static_cast<int>(ibestPartitionData.stop + 1.0) - 1];
      if (ibestPartitionData.start == ibestPartitionData.stop) {
        best = startcost + stopdist;
        *ibest = ip;
      } else if (costs[static_cast<int>(ibestPartitionData.stop + 1.0) - 1] +
                     stopdist <
                 best) {
        struct_T nodeValue;
        double npoints;
        double ydelta;
        double ydelta_tmp;
        double ymean;
        partition.insertAfter(ip, ibestPartitionData.stop,
                              ibestPartitionData.stop);
        if ((ip < 1) || (ip > partition.valuePool.size(0))) {
          *ibest = 0;
        } else {
          *ibest = partition.nodePool[ip - 1].next;
        }
        best = costs[static_cast<int>(ibestPartitionData.stop + 1.0) - 1] +
               stopdist;
        if ((ip < 1) || (ip > partition.valuePool.size(0))) {
          nodeValue = partition.valuePool[0];
        } else {
          nodeValue = partition.valuePool[ip - 1];
        }
        nodeValue.stop = ibestPartitionData.stop - 1.0;
        if ((ip >= 1) && (ip <= partition.valuePool.size(0))) {
          partition.valuePool[ip - 1] = nodeValue;
        }
        ymean = work[static_cast<int>(((ibestPartitionData.stop - 1.0) + 1.0) +
                                      1.0) -
                     1]
                    .yBar;
        ydelta_tmp =
            y[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1];
        ydelta = ydelta_tmp - ymean;
        npoints = (ix - (ibestPartitionData.stop - 1.0)) + 1.0;
        ymean += ydelta / npoints;
        work[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1].yBar =
            ymean;
        work[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1].Syy =
            work[static_cast<int>(((ibestPartitionData.stop - 1.0) + 1.0) +
                                  1.0) -
                 1]
                .Syy +
            ydelta * (ydelta_tmp - ymean);
        ymean =
            npoints *
            std::fmax(logrealmin - std::log(npoints),
                      std::log(work[static_cast<int>(
                                        (ibestPartitionData.stop - 1.0) + 1.0) -
                                    1]
                                   .Syy /
                               npoints));
        dists[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1] =
            ymean;
        dists[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1] =
            ymean;
      } else {
        double imiddle;
        double npoints;
        double ydelta;
        double ydelta_tmp;
        double ymean;
        if ((ip < 1) || (ip > partition.valuePool.size(0))) {
          ibestPartitionData = partition.valuePool[0];
        } else {
          ibestPartitionData = partition.valuePool[ip - 1];
        }
        imiddle = ibestPartitionData.stop - 1.0;
        ymean = work[static_cast<int>(((ibestPartitionData.stop - 1.0) + 1.0) +
                                      1.0) -
                     1]
                    .yBar;
        ydelta_tmp =
            y[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1];
        ydelta = ydelta_tmp - ymean;
        npoints = (ix - (ibestPartitionData.stop - 1.0)) + 1.0;
        ymean += ydelta / npoints;
        work[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1].yBar =
            ymean;
        work[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1].Syy =
            work[static_cast<int>(((ibestPartitionData.stop - 1.0) + 1.0) +
                                  1.0) -
                 1]
                .Syy +
            ydelta * (ydelta_tmp - ymean);
        ymean =
            npoints *
            std::fmax(logrealmin - std::log(npoints),
                      std::log(work[static_cast<int>(
                                        (ibestPartitionData.stop - 1.0) + 1.0) -
                                    1]
                                   .Syy /
                               npoints));
        dists[static_cast<int>((ibestPartitionData.stop - 1.0) + 1.0) - 1] =
            ymean;
        while (
            (startcost + ymean < best) &&
            (costs[static_cast<int>(imiddle + 1.0) - 1] <=
             costs[static_cast<int>(imiddle + 2.0) - 1]) &&
            (costs[static_cast<int>(imiddle + 1.0) - 1] + stopdist >= best) &&
            (imiddle != istart)) {
          imiddle--;
          ymean = work[static_cast<int>((imiddle + 1.0) + 1.0) - 1].yBar;
          ydelta = y[static_cast<int>(imiddle + 1.0) - 1] - ymean;
          npoints = (ix - imiddle) + 1.0;
          ymean += ydelta / npoints;
          work[static_cast<int>(imiddle + 1.0) - 1].yBar = ymean;
          work[static_cast<int>(imiddle + 1.0) - 1].Syy =
              work[static_cast<int>((imiddle + 1.0) + 1.0) - 1].Syy +
              ydelta * (y[static_cast<int>(imiddle + 1.0) - 1] - ymean);
          ymean =
              npoints *
              std::fmax(logrealmin - std::log(npoints),
                        std::log(work[static_cast<int>(imiddle + 1.0) - 1].Syy /
                                 npoints));
          dists[static_cast<int>(imiddle + 1.0) - 1] = ymean;
        }
        partition.insertAfter(ip, imiddle + 1.0, istop);
        if ((ip < 1) || (ip > partition.valuePool.size(0))) {
          ibestPartitionData = partition.valuePool[0];
        } else {
          ibestPartitionData = partition.valuePool[ip - 1];
        }
        ibestPartitionData.stop = imiddle;
        if ((ip >= 1) && (ip <= partition.valuePool.size(0))) {
          partition.valuePool[ip - 1] = ibestPartitionData;
        }
        dists[static_cast<int>(imiddle + 1.0) - 1] = ymean;
      }
    }
    if ((ip < 1) || (ip > partition.valuePool.size(0))) {
      ip = 0;
    } else {
      ip = partition.nodePool[ip - 1].next;
    }
  }
  return best;
}

//
// Arguments    : double threshold
//                int *partitionListIterator
// Return Type  : boolean_T
//
boolean_T peltMeanVar::prunePartition(double threshold,
                                      int *partitionListIterator)
{
  double ipPartitionData_start;
  double ipPartitionData_stop;
  boolean_T tf;
  if ((*partitionListIterator < 1) ||
      (*partitionListIterator > partition.valuePool.size(0))) {
    ipPartitionData_start = partition.valuePool[0].start;
    ipPartitionData_stop = partition.valuePool[0].stop;
  } else {
    ipPartitionData_start =
        partition.valuePool[*partitionListIterator - 1].start;
    ipPartitionData_stop = partition.valuePool[*partitionListIterator - 1].stop;
  }
  tf = (costs[static_cast<int>(ipPartitionData_start + 1.0) - 1] +
            dists[static_cast<int>(ipPartitionData_stop + 1.0) - 1] >
        threshold);
  if (tf) {
    int nodeAddr;
    nodeAddr = *partitionListIterator;
    if ((*partitionListIterator < 1) ||
        (*partitionListIterator > partition.valuePool.size(0))) {
      *partitionListIterator = 0;
    } else {
      *partitionListIterator =
          partition.nodePool[*partitionListIterator - 1].next;
    }
    if ((nodeAddr >= 1) && (nodeAddr <= partition.valuePool.size(0))) {
      int node_next;
      int node_prev;
      if (nodeAddr > partition.valuePool.size(0)) {
        node_next = 0;
        node_prev = 0;
      } else {
        node_next = partition.nodePool[nodeAddr - 1].next;
        node_prev = partition.nodePool[nodeAddr - 1].prev;
      }
      if (nodeAddr == partition.frontAddr) {
        partition.frontAddr = node_next;
      }
      if (nodeAddr == partition.backAddr) {
        partition.backAddr = node_prev;
      }
      if (node_prev != 0) {
        partition.nodePool[node_prev - 1].next = node_next;
      }
      if (node_next != 0) {
        partition.nodePool[node_next - 1].prev = node_prev;
      }
      partition.len--;
      if (partition.unusedAddr != 0) {
        partition.nodePool[partition.unusedAddr - 1].prev = nodeAddr;
      }
      partition.nodePool[nodeAddr - 1].next = partition.unusedAddr;
      partition.nodePool[nodeAddr - 1].prev = 0;
      partition.unusedAddr = nodeAddr;
    }
  }
  return tf;
}

//
// Arguments    : double y
//                double ix
// Return Type  : void
//
void peltMeanVar::updateDistsWithNewEndpointH(double y, double ix)
{
  int ip;
  ip = partition.frontAddr;
  while (ip != 0) {
    double ipPartitionData_stop;
    double npoints;
    double ydelta;
    if ((ip < 1) || (ip > partition.valuePool.size(0))) {
      ipPartitionData_stop = partition.valuePool[0].stop;
    } else {
      ipPartitionData_stop = partition.valuePool[ip - 1].stop;
    }
    ydelta = y - work[static_cast<int>(ipPartitionData_stop + 1.0) - 1].yBar;
    npoints = (ix + 1.0) - ipPartitionData_stop;
    work[static_cast<int>(ipPartitionData_stop + 1.0) - 1].yBar =
        work[static_cast<int>(ipPartitionData_stop + 1.0) - 1].yBar +
        ydelta / npoints;
    work[static_cast<int>(ipPartitionData_stop + 1.0) - 1].Syy =
        work[static_cast<int>(ipPartitionData_stop + 1.0) - 1].Syy +
        ydelta *
            (y - work[static_cast<int>(ipPartitionData_stop + 1.0) - 1].yBar);
    dists[static_cast<int>(ipPartitionData_stop + 1.0) - 1] =
        npoints *
        std::fmax(
            logrealmin - std::log(npoints),
            std::log(
                work[static_cast<int>(ipPartitionData_stop + 1.0) - 1].Syy /
                npoints));
    if ((ip < 1) || (ip > partition.valuePool.size(0))) {
      ip = 0;
    } else {
      ip = partition.nodePool[ip - 1].next;
    }
  }
}

//
// Arguments    : void
// Return Type  : peltMeanVar *
//
peltMeanVar *peltMeanVar::init()
{
  ::coder::internal::list b_obj;
  peltMeanVar *obj;
  c_struct_T b_s;
  struct_T partition_data;
  double s;
  obj = this;
  obj->z = 0.0;
  s = obj->z;
  obj->dists.set_size(1, 1);
  obj->dists[0] = s;
  s = obj->z;
  obj->costs.set_size(1, 1);
  obj->costs[0] = s;
  partition_data.start = obj->z;
  partition_data.stop = obj->z;
  b_obj.valuePool.set_size(8);
  b_obj.nodePool.set_size(8);
  b_obj.len = 0;
  b_obj.frontAddr = 0;
  b_obj.backAddr = 0;
  for (int k{0}; k < 8; k++) {
    b_obj.valuePool[k] = partition_data;
    b_obj.nodePool[k] = r;
    b_obj.nodePool[k].addr = k + 1;
    b_obj.nodePool[k].next = k + 2;
    b_obj.nodePool[k].prev = k;
  }
  b_obj.nodePool[7].next = 0;
  b_obj.unusedAddr = 1;
  obj->partition = b_obj;
  b_s.Syy = obj->z;
  b_s.yBar = obj->z;
  obj->work.set_size(1, 1);
  obj->work[0] = b_s;
  s = obj->z;
  obj->logrealmin = s;
  return obj;
}

//
// Arguments    : const ::coder::array<double, 2U> &y
//                double nx
//                double penalty
//                ::coder::array<double, 2U> &cpidx
//                double *residue
// Return Type  : void
//
void peltMeanVar::solveH(const ::coder::array<double, 2U> &y, double nx,
                         double penalty, ::coder::array<double, 2U> &cpidx,
                         double *residue)
{
  c_struct_T s;
  struct_T expl_temp;
  struct_T ibestPartition;
  double b_ixBreak;
  double ixBreak;
  double syy;
  int i;
  int ibest;
  int ip;
  int ix;
  boolean_T exitg1;
  ip = static_cast<int>(nx + 1.0);
  cpidx.set_size(1, ip);
  costs.set_size(1, ip);
  dists.set_size(1, ip);
  s.Syy = z;
  s.yBar = z;
  work.set_size(1, ip);
  for (i = 0; i < ip; i++) {
    cpidx[i] = 0.0;
    costs[i] = rtInf;
    dists[i] = 0.0;
    work[i] = s;
  }
  logrealmin = -708.39641853226408;
  ibestPartition.start = z;
  ibestPartition.stop = z;
  ip = partition.newNodeAddr();
  if (ip != 0) {
    if (partition.frontAddr == 0) {
      partition.frontAddr = ip;
      partition.backAddr = ip;
      partition.nodePool[ip - 1].next = 0;
    } else {
      partition.nodePool[ip - 1].prev = partition.backAddr;
      partition.nodePool[partition.backAddr - 1].next = ip;
      partition.backAddr = ip;
    }
    partition.valuePool[ip - 1] = ibestPartition;
  }
  ibest = partition.frontAddr;
  if ((partition.frontAddr < 1) ||
      (partition.frontAddr > partition.valuePool.size(0))) {
    ibestPartition = partition.valuePool[0];
  } else {
    ibestPartition = partition.valuePool[partition.frontAddr - 1];
  }
  costs[static_cast<int>(ibestPartition.start + 1.0) - 1] = -penalty;
  dists[static_cast<int>(ibestPartition.stop + 1.0) - 1] = z;
  ixBreak = z;
  syy = z;
  ix = 0;
  exitg1 = false;
  while ((!exitg1) && (ix <= static_cast<int>(1.0 - syy) - 1)) {
    ixBreak = syy + static_cast<double>(ix);
    if (ixBreak >= nx) {
      exitg1 = true;
    } else {
      updateDistsWithNewEndpointH(y[static_cast<int>(ixBreak + 1.0) - 1],
                                  ixBreak);
      ixBreak++;
      ix++;
    }
  }
  b_ixBreak = ixBreak;
  i = static_cast<int>((nx - 1.0) + (1.0 - ixBreak));
  for (ix = 0; ix < i; ix++) {
    double npoints;
    double ydelta;
    double ydelta_tmp;
    double ymean;
    ixBreak = b_ixBreak + static_cast<double>(ix);
    updateDistsWithNewEndpointH(y[static_cast<int>(ixBreak + 1.0) - 1],
                                ixBreak);
    if (ixBreak + 1.0 > 2.0) {
      ip = partition.newNodeAddr();
      if (ip != 0) {
        if (partition.frontAddr == 0) {
          partition.frontAddr = ip;
          partition.backAddr = ip;
          partition.nodePool[ip - 1].next = 0;
        } else {
          partition.nodePool[ip - 1].prev = partition.backAddr;
          partition.nodePool[partition.backAddr - 1].next = ip;
          partition.backAddr = ip;
        }
        expl_temp.start = (ixBreak - 2.0) + 1.0;
        expl_temp.stop = (ixBreak - 2.0) + 1.0;
        partition.valuePool[ip - 1] = expl_temp;
      }
      if ((partition.backAddr < 1) ||
          (partition.backAddr > partition.valuePool.size(0))) {
        ibestPartition = partition.valuePool[0];
      } else {
        ibestPartition = partition.valuePool[partition.backAddr - 1];
      }
      npoints = z;
      ymean = z;
      syy = z;
      ip = static_cast<int>(ixBreak + (1.0 - ibestPartition.stop));
      for (int b_i{0}; b_i < ip; b_i++) {
        ydelta_tmp =
            y[static_cast<int>(
                  (ibestPartition.stop + static_cast<double>(b_i)) + 1.0) -
              1];
        ydelta = ydelta_tmp - ymean;
        npoints++;
        ymean += ydelta / npoints;
        syy += ydelta * (ydelta_tmp - ymean);
      }
      work[static_cast<int>(ibestPartition.stop + 1.0) - 1].yBar = ymean;
      work[static_cast<int>(ibestPartition.stop + 1.0) - 1].Syy = syy;
      syy = npoints *
            std::fmax(logrealmin - std::log(npoints), std::log(syy / npoints));
      dists[static_cast<int>(ibestPartition.stop + 1.0) - 1] = syy;
      dists[static_cast<int>(ibestPartition.stop + 1.0) - 1] = syy;
    }
    syy = getBestPartitionH(y, ixBreak, &ibest);
    if ((ibest < 1) || (ibest > partition.valuePool.size(0))) {
      ibestPartition = partition.valuePool[0];
    } else {
      ibestPartition = partition.valuePool[ibest - 1];
    }
    cpidx[static_cast<int>(ixBreak + 2.0) - 1] = ibestPartition.start;
    ydelta_tmp = syy + penalty;
    costs[static_cast<int>(ixBreak + 2.0) - 1] = ydelta_tmp;
    ip = partition.frontAddr;
    while (ip != 0) {
      boolean_T flag;
      flag = prunePartition(ydelta_tmp, &ip);
      if (!flag) {
        double istop;
        double startcost;
        if ((ip < 1) || (ip > partition.valuePool.size(0))) {
          ibestPartition = partition.valuePool[0];
        } else {
          ibestPartition = partition.valuePool[ip - 1];
        }
        istop = ibestPartition.stop;
        startcost = costs[static_cast<int>(ibestPartition.start + 1.0) - 1];
        syy = dists[static_cast<int>(ibestPartition.stop + 1.0) - 1];
        while ((startcost + syy < ydelta_tmp) &&
               (costs[static_cast<int>(istop + 1.0) - 1] + syy > ydelta_tmp) &&
               (ibestPartition.start < istop)) {
          istop--;
          ymean = work[static_cast<int>((istop + 1.0) + 1.0) - 1].yBar;
          ydelta = y[static_cast<int>(istop + 1.0) - 1] - ymean;
          npoints = (ixBreak - istop) + 1.0;
          ymean += ydelta / npoints;
          work[static_cast<int>(istop + 1.0) - 1].yBar = ymean;
          work[static_cast<int>(istop + 1.0) - 1].Syy =
              work[static_cast<int>((istop + 1.0) + 1.0) - 1].Syy +
              ydelta * (y[static_cast<int>(istop + 1.0) - 1] - ymean);
          syy = npoints *
                std::fmax(logrealmin - std::log(npoints),
                          std::log(work[static_cast<int>(istop + 1.0) - 1].Syy /
                                   npoints));
          dists[static_cast<int>(istop + 1.0) - 1] = syy;
        }
        if ((ip < 1) || (ip > partition.valuePool.size(0))) {
          ibestPartition = partition.valuePool[0];
        } else {
          ibestPartition = partition.valuePool[ip - 1];
        }
        ibestPartition.stop = istop;
        if ((ip >= 1) && (ip <= partition.valuePool.size(0))) {
          partition.valuePool[ip - 1] = ibestPartition;
        }
        flag = prunePartition(ydelta_tmp, &ip);
        if (!flag) {
          if ((ip < 1) || (ip > partition.valuePool.size(0))) {
            ip = 0;
          } else {
            ip = partition.nodePool[ip - 1].next;
          }
        }
      }
    }
    ixBreak++;
  }
  *residue = costs[static_cast<int>(ixBreak + 1.0) - 1];
}

} // namespace findchangepts
} // namespace codegenable
} // namespace internal
} // namespace signal
} // namespace coder

//
// File trailer for peltMeanVar.cpp
//
// [EOF]
//
