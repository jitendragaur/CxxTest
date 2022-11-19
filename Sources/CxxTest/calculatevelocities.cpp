//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
// File: calculatevelocities.cpp
//
// MATLAB Coder version            : 5.4
// C/C++ source code generated on  : 01-Nov-2022 16:06:29
//

// Include Files
#include "calculatevelocities.h"
#include "calculatevelocities_types.h"
#include "cumtrapz.h"
#include "findchangepts.h"
#include "findpeaks.h"
#include "rt_nonfinite.h"
#include "coder_array.h"
#include <cmath>

// Function Declarations
static void b_binary_expand_op(struct0_T *in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3);

static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3);

static void binary_expand_op(struct0_T *in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3);

// Function Definitions
//
// Arguments    : struct0_T *in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void b_binary_expand_op(struct0_T *in1,
                               const coder::array<double, 2U> &in2,
                               const coder::array<double, 2U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(1) == 1) {
    i = in2.size(1);
  } else {
    i = in3.size(1);
  }
  in1->V_lowering.set_size(1, i);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    in1->V_lowering[i] = in2[i * stride_0_1] - in3[i * stride_1_1];
  }
}

//
// Arguments    : coder::array<double, 2U> &in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op(coder::array<double, 2U> &in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(1) == 1) {
    i = in2.size(1);
  } else {
    i = in3.size(1);
  }
  in1.set_size(1, i);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    in1[i] = (in2[i * stride_0_1] + in3[i * stride_1_1]) / 2.0;
  }
}

//
// Arguments    : struct0_T *in1
//                const coder::array<double, 2U> &in2
//                const coder::array<double, 2U> &in3
// Return Type  : void
//
static void binary_expand_op(struct0_T *in1,
                             const coder::array<double, 2U> &in2,
                             const coder::array<double, 2U> &in3)
{
  int i;
  int loop_ub;
  int stride_0_1;
  int stride_1_1;
  if (in3.size(1) == 1) {
    i = in2.size(1);
  } else {
    i = in3.size(1);
  }
  in1->V_raising.set_size(1, i);
  stride_0_1 = (in2.size(1) != 1);
  stride_1_1 = (in3.size(1) != 1);
  if (in3.size(1) == 1) {
    loop_ub = in2.size(1);
  } else {
    loop_ub = in3.size(1);
  }
  for (i = 0; i < loop_ub; i++) {
    in1->V_raising[i] = in2[i * stride_0_1] + in3[i * stride_1_1];
  }
}

//
// Defining the acceleration to use for velocity calculation
//
// Arguments    : const coder::array<double, 2U> &acc_final
//                coder::array<double, 2U> &gravity_final
//                const coder::array<double, 2U> &att_final
//                coder::array<double, 2U> &time_final
//                struct0_T *V_out
//                double *Rep_count
// Return Type  : void
//
void calculatevelocities(const coder::array<double, 2U> &acc_final,
                         coder::array<double, 2U> &gravity_final,
                         const coder::array<double, 2U> &,
                         coder::array<double, 2U> &time_final, struct0_T *V_out,
                         double *Rep_count)
{
  coder::array<double, 2U> acc_filt;
  coder::array<double, 2U> b_Velocity;
  coder::array<double, 2U> b_locs_vel_rais_temp;
  coder::array<double, 2U> locs_vel_low_temp;
  coder::array<double, 2U> locs_vel_rais_temp;
  coder::array<double, 1U> Velocity;
  coder::array<double, 1U> b_acc_filt;
  coder::array<double, 1U> b_time_final;
  coder::array<double, 1U> c_pts;
  coder::array<boolean_T, 1U> x;
  double count[3];
  double varargin_1[3];
  double bsum;
  double y;
  int firstBlockLength;
  int hi;
  int i;
  int k;
  int nblocks;
  int xblockoffset;
  boolean_T b_y;
  boolean_T exitg1;
  // checking in which direction gravity is. Threshold of 0.8 was used to flag
  // gravity
  //  Finding index of gravity direction which has max flags.
  i = time_final.size(1);
  for (int b_i{0}; b_i < 3; b_i++) {
    for (firstBlockLength = 0; firstBlockLength < i; firstBlockLength++) {
      y = gravity_final[b_i + 3 * firstBlockLength];
      if (y >= 0.8) {
        gravity_final[b_i + 3 * firstBlockLength] = 1.0;
      } else if ((y < 0.8) && (y > -0.8)) {
        gravity_final[b_i + 3 * firstBlockLength] = 0.0;
      } else {
        gravity_final[b_i + 3 * firstBlockLength] = -1.0;
      }
    }
    if (gravity_final.size(1) == 0) {
      y = 0.0;
    } else {
      int lastBlockLength;
      if (gravity_final.size(1) <= 1024) {
        firstBlockLength = gravity_final.size(1);
        lastBlockLength = 0;
        nblocks = 1;
      } else {
        firstBlockLength = 1024;
        nblocks = gravity_final.size(1) / 1024;
        lastBlockLength = gravity_final.size(1) - (nblocks << 10);
        if (lastBlockLength > 0) {
          nblocks++;
        } else {
          lastBlockLength = 1024;
        }
      }
      y = gravity_final[b_i];
      for (k = 2; k <= firstBlockLength; k++) {
        y += gravity_final[b_i + 3 * (k - 1)];
      }
      for (firstBlockLength = 2; firstBlockLength <= nblocks;
           firstBlockLength++) {
        xblockoffset = (firstBlockLength - 1) << 10;
        bsum = gravity_final[b_i + 3 * xblockoffset];
        if (firstBlockLength == nblocks) {
          hi = lastBlockLength;
        } else {
          hi = 1024;
        }
        for (k = 2; k <= hi; k++) {
          bsum += gravity_final[b_i + 3 * ((xblockoffset + k) - 1)];
        }
        y += bsum;
      }
    }
    count[b_i] = y;
    varargin_1[b_i] = std::abs(y);
  }
  if (!std::isnan(varargin_1[0])) {
    firstBlockLength = 1;
  } else {
    firstBlockLength = 0;
    k = 2;
    exitg1 = false;
    while ((!exitg1) && (k < 4)) {
      if (!std::isnan(varargin_1[k - 1])) {
        firstBlockLength = k;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (firstBlockLength == 0) {
    xblockoffset = 0;
  } else {
    bsum = varargin_1[firstBlockLength - 1];
    xblockoffset = firstBlockLength - 1;
    i = firstBlockLength + 1;
    for (k = i; k < 4; k++) {
      y = varargin_1[k - 1];
      if (bsum < y) {
        bsum = y;
        xblockoffset = k - 1;
      }
    }
  }
  //  Setting the acceleration to use based on max flag gravity direction
  if (count[xblockoffset] > 0.0) {
    //  If the IMU is oriented down
    hi = acc_final.size(1);
    acc_filt.set_size(1, acc_final.size(1));
    for (i = 0; i < hi; i++) {
      acc_filt[i] = -acc_final[xblockoffset + 3 * i];
    }
  } else {
    //  If the IMU is oriented up
    hi = acc_final.size(1);
    acc_filt.set_size(1, acc_final.size(1));
    for (i = 0; i < hi; i++) {
      acc_filt[i] = acc_final[xblockoffset + 3 * i];
    }
  }
  //  Finding the indices of start-time (t0_index) and finish-time (tf_index)
  //  Use this section to manually define start and end indices
  // load('cursor_info.mat');
  //  t0_index = min(cursor_info.DataIndex);
  //  tf_index = max(cursor_info.DataIndex);
  b_acc_filt.set_size(acc_filt.size(1));
  hi = acc_filt.size(1);
  for (i = 0; i < hi; i++) {
    b_acc_filt[i] = acc_filt[i];
  }
  coder::findchangepts(b_acc_filt, c_pts);
  //  Identifying the index of time at which exercise starts
  if (c_pts.size(0) == 2) {
    if (c_pts[1] - c_pts[0] >= 500.0) {
      y = c_pts[0];
      c_pts.set_size(1);
      c_pts[0] = y - 250.0;
    } else {
      y = c_pts[1];
      c_pts.set_size(1);
      c_pts[0] = y - 250.0;
    }
  } else {
    hi = c_pts.size(0);
    for (i = 0; i < hi; i++) {
      c_pts[i] = c_pts[i] - 250.0;
    }
  }
  //  Integration for velocity calculation
  b_time_final.set_size(time_final.size(1));
  hi = time_final.size(1);
  for (i = 0; i < hi; i++) {
    b_time_final[i] = time_final[i];
  }
  b_acc_filt.set_size(acc_filt.size(1));
  hi = acc_filt.size(1);
  for (i = 0; i < hi; i++) {
    b_acc_filt[i] = acc_filt[i];
  }
  coder::cumtrapz(b_time_final, b_acc_filt, Velocity);
  hi = Velocity.size(0);
  for (i = 0; i < hi; i++) {
    Velocity[i] = Velocity[i] * 9.81;
  }
  //  Finding peaks/valleys and their locations
  if (c_pts[0] > Velocity.size(0)) {
    i = 0;
    nblocks = 0;
  } else {
    i = static_cast<int>(c_pts[0]) - 1;
    nblocks = Velocity.size(0);
  }
  hi = nblocks - i;
  b_Velocity.set_size(1, hi);
  for (nblocks = 0; nblocks < hi; nblocks++) {
    b_Velocity[nblocks] = Velocity[i + nblocks];
  }
  coder::findpeaks(b_Velocity, locs_vel_rais_temp, locs_vel_low_temp);
  if (c_pts[0] > Velocity.size(0)) {
    i = 0;
    nblocks = 0;
  } else {
    i = static_cast<int>(c_pts[0]) - 1;
    nblocks = Velocity.size(0);
  }
  hi = nblocks - i;
  b_Velocity.set_size(1, hi);
  for (nblocks = 0; nblocks < hi; nblocks++) {
    b_Velocity[nblocks] = -Velocity[i + nblocks];
  }
  coder::findpeaks(b_Velocity, locs_vel_rais_temp, b_locs_vel_rais_temp);
  locs_vel_rais_temp.set_size(1, b_locs_vel_rais_temp.size(1));
  hi = b_locs_vel_rais_temp.size(1);
  for (i = 0; i < hi; i++) {
    locs_vel_rais_temp[i] = b_locs_vel_rais_temp[i];
  }
  //  Checking if number of peaks in lowering and raising are the same and if
  //  not make it equal by clipping the end of higher one
  firstBlockLength = locs_vel_low_temp.size(1) - b_locs_vel_rais_temp.size(1);
  if (firstBlockLength != 0) {
    if (firstBlockLength > 0) {
      i = locs_vel_low_temp.size(1) - firstBlockLength;
      if (i < 1) {
        hi = 0;
      } else {
        hi = i;
      }
      for (i = 0; i < hi; i++) {
        locs_vel_low_temp[i] = locs_vel_low_temp[i];
      }
      locs_vel_low_temp.set_size(1, hi);
    } else {
      i = b_locs_vel_rais_temp.size(1) + firstBlockLength;
      if (i < 1) {
        hi = 0;
      } else {
        hi = i;
      }
      locs_vel_rais_temp.set_size(1, hi);
      for (i = 0; i < hi; i++) {
        locs_vel_rais_temp[i] = b_locs_vel_rais_temp[i];
      }
    }
  }
  //  Finding the indices of start time and end time
  y = locs_vel_low_temp[0];
  Velocity.set_size(c_pts.size(0));
  hi = c_pts.size(0);
  for (i = 0; i < hi; i++) {
    Velocity[i] = (y + c_pts[i]) - 250.0;
  }
  x.set_size(Velocity.size(0));
  hi = Velocity.size(0);
  for (i = 0; i < hi; i++) {
    x[i] = (Velocity[i] < 0.0);
  }
  b_y = (x.size(0) != 0);
  if (b_y) {
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(0) - 1)) {
      if (!x[k]) {
        b_y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (b_y) {
    Velocity.set_size(1);
    Velocity[0] = 1.0;
  }
  y = locs_vel_rais_temp[locs_vel_rais_temp.size(1) - 1];
  hi = c_pts.size(0);
  for (i = 0; i < hi; i++) {
    c_pts[i] = (y + c_pts[i]) + 250.0;
  }
  x.set_size(c_pts.size(0));
  hi = c_pts.size(0);
  for (i = 0; i < hi; i++) {
    x[i] = (c_pts[i] > acc_filt.size(1));
  }
  b_y = (x.size(0) != 0);
  if (b_y) {
    k = 0;
    exitg1 = false;
    while ((!exitg1) && (k <= x.size(0) - 1)) {
      if (!x[k]) {
        b_y = false;
        exitg1 = true;
      } else {
        k++;
      }
    }
  }
  if (b_y) {
    c_pts.set_size(1);
    c_pts[0] = acc_filt.size(1);
  }
  //  Clipping from the start and end times
  if (Velocity[0] > c_pts[0]) {
    i = 0;
    nblocks = 0;
    xblockoffset = 0;
    hi = 0;
  } else {
    i = static_cast<int>(Velocity[0]) - 1;
    nblocks = static_cast<int>(c_pts[0]);
    xblockoffset = static_cast<int>(Velocity[0]) - 1;
    hi = static_cast<int>(c_pts[0]);
  }
  //  gravity_final = gravity_final(:,t0_index:tf_index);
  //  rot_final = rot_final(:,t0_index:tf_index);
  firstBlockLength = hi - xblockoffset;
  for (hi = 0; hi < firstBlockLength; hi++) {
    time_final[hi] = time_final[xblockoffset + hi];
  }
  time_final.set_size(1, firstBlockLength);
  //  Analysis   :   Algorithm_1 (Using findchangepts function)
  //
  //  % Integration for velocity calculation
  //  Velocity = cumtrapz(time_final',acc_final')*9.81;
  //
  //  %Finding peaks/valleys and their locations
  //  [pks_vel_low,locs_vel_low] =
  //  findpeaks(Velocity','MinPeakProminence',Min_PkProm);
  //  [pks_vel_rais,locs_vel_rais] =
  //  findpeaks(-Velocity','MinPeakProminence',Min_PkProm);
  //
  //  %Count number of reps (equivalent to number of minima in acceleration)
  //  Rep_count = length(pks_vel_low);
  //
  //  %Dividing reps into parts to detect starting point of reps
  //  k = findchangepts(Velocity','MaxNumChanges',Rep_count*3);
  //
  //  %Finding velocity drift at the start point of rep (0.5 of standard
  //  deviation added to shift the drift) vel_drft = zeros(1,Rep_count); y=0;
  //  for j = 0:3:numel(k)-3
  //      y=y+1;
  //      if j==0
  //      vel_drft(y) = mean(Velocity(1:k(j+1)))-0.5*std(Velocity(1:k(j+1)));
  //      else
  //      vel_drft(y) =
  //      mean(Velocity(k(j):k(j+1)))-0.5*std(Velocity(k(j):k(j+1))); end
  //  end
  //
  //  %Peak velocity during lowering and raising
  //  Peak_Velocity_Lowering = pks_vel_low-vel_drft;
  //  Peak_Velocity_Raising = pks_vel_rais+vel_drft;
  //
  //  V_out =
  //  struct('V_lowering',Peak_Velocity_Lowering,'V_raising',Peak_Velocity_Raising);
  //  Analysis   :   Algorithm_2 (Vmax+Vmin/2)
  //  Integration for velocity calculation
  b_time_final.set_size(firstBlockLength);
  for (xblockoffset = 0; xblockoffset < firstBlockLength; xblockoffset++) {
    b_time_final[xblockoffset] = time_final[xblockoffset];
  }
  hi = nblocks - i;
  b_acc_filt.set_size(hi);
  for (nblocks = 0; nblocks < hi; nblocks++) {
    b_acc_filt[nblocks] = acc_filt[i + nblocks];
  }
  coder::cumtrapz(b_time_final, b_acc_filt, Velocity);
  hi = Velocity.size(0);
  for (i = 0; i < hi; i++) {
    Velocity[i] = Velocity[i] * 9.81;
  }
  // Finding peaks/valleys and their locations
  b_Velocity.set_size(1, Velocity.size(0));
  hi = Velocity.size(0);
  for (i = 0; i < hi; i++) {
    b_Velocity[i] = Velocity[i];
  }
  coder::findpeaks(b_Velocity, b_locs_vel_rais_temp, locs_vel_rais_temp);
  b_Velocity.set_size(1, Velocity.size(0));
  hi = Velocity.size(0);
  for (i = 0; i < hi; i++) {
    b_Velocity[i] = -Velocity[i];
  }
  coder::findpeaks(b_Velocity, locs_vel_low_temp, locs_vel_rais_temp);
  // Count number of reps (equivalent to number of minima in acceleration)
  firstBlockLength = b_locs_vel_rais_temp.size(1);
  //  Finding middle point in a rep
  if (b_locs_vel_rais_temp.size(1) == locs_vel_low_temp.size(1)) {
    locs_vel_rais_temp.set_size(1, b_locs_vel_rais_temp.size(1));
    hi = b_locs_vel_rais_temp.size(1);
    for (i = 0; i < hi; i++) {
      locs_vel_rais_temp[i] =
          (b_locs_vel_rais_temp[i] + locs_vel_low_temp[i]) / 2.0;
    }
  } else {
    binary_expand_op(locs_vel_rais_temp, b_locs_vel_rais_temp,
                     locs_vel_low_temp);
  }
  // Peak velocity during lowering and raising
  if (locs_vel_rais_temp.size(1) == b_locs_vel_rais_temp.size(1)) {
    V_out->V_lowering.set_size(1, locs_vel_rais_temp.size(1));
    hi = locs_vel_rais_temp.size(1);
    for (i = 0; i < hi; i++) {
      V_out->V_lowering[i] = locs_vel_rais_temp[i] - b_locs_vel_rais_temp[i];
    }
  } else {
    b_binary_expand_op(V_out, locs_vel_rais_temp, b_locs_vel_rais_temp);
  }
  if (locs_vel_rais_temp.size(1) == locs_vel_low_temp.size(1)) {
    V_out->V_raising.set_size(1, locs_vel_rais_temp.size(1));
    hi = locs_vel_rais_temp.size(1);
    for (i = 0; i < hi; i++) {
      V_out->V_raising[i] = locs_vel_rais_temp[i] + locs_vel_low_temp[i];
    }
  } else {
    binary_expand_op(V_out, locs_vel_rais_temp, locs_vel_low_temp);
  }
  *Rep_count = firstBlockLength;
}

//
// File trailer for calculatevelocities.cpp
//
// [EOF]
//
