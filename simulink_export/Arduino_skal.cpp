/*
 * Arduino_skal.cpp
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "Arduino_skal".
 *
 * Model version              : 1.1
 * Simulink Coder version : 9.5 (R2021a) 14-Nov-2020
 * C++ source code generated on : Thu Apr 15 15:56:50 2021
 *
 * Target selection: grt.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objective: Debugging
 * Validation result: Not run
 */

#include "Arduino_skal.h"
#include "Arduino_skal_private.h"

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
void Arduino_skalModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = static_cast<ODE3_IntgData *>(rtsiGetSolverData(si));
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  Arduino_skal_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  Arduino_skal_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  this->step();
  Arduino_skal_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Arduino_skalModelClass::step()
{
  const real_T *tmp_3;
  real_T currentTime;
  real_T tmp;
  real_T tmp_0;
  real_T tmp_1;
  real_T tmp_2;
  real_T u0;
  int32_T i;
  int32_T i_0;
  if (rtmIsMajorTimeStep((&Arduino_skal_M))) {
    /* set solver stop time */
    if (!((&Arduino_skal_M)->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&(&Arduino_skal_M)->solverInfo, (((&Arduino_skal_M
        )->Timing.clockTickH0 + 1) * (&Arduino_skal_M)->Timing.stepSize0 *
        4294967296.0));
    } else {
      rtsiSetSolverStopTime(&(&Arduino_skal_M)->solverInfo, (((&Arduino_skal_M
        )->Timing.clockTick0 + 1) * (&Arduino_skal_M)->Timing.stepSize0 +
        (&Arduino_skal_M)->Timing.clockTickH0 * (&Arduino_skal_M)
        ->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep((&Arduino_skal_M))) {
    (&Arduino_skal_M)->Timing.t[0] = rtsiGetT(&(&Arduino_skal_M)->solverInfo);
  }

  if (rtmIsMajorTimeStep((&Arduino_skal_M))) {
    /* Constant: '<S1>/X0' */
    Arduino_skal_B.X0[0] = Arduino_skal_P.X0_Value[0];
    Arduino_skal_B.X0[1] = Arduino_skal_P.X0_Value[1];
    Arduino_skal_B.X0[2] = Arduino_skal_P.X0_Value[2];
    Arduino_skal_B.X0[3] = Arduino_skal_P.X0_Value[3];
  }

  /* Integrator: '<S1>/MemoryX' */
  if (Arduino_skal_DW.MemoryX_IWORK != 0) {
    Arduino_skal_X.MemoryX_CSTATE[0] = Arduino_skal_B.X0[0];
    Arduino_skal_X.MemoryX_CSTATE[1] = Arduino_skal_B.X0[1];
    Arduino_skal_X.MemoryX_CSTATE[2] = Arduino_skal_B.X0[2];
    Arduino_skal_X.MemoryX_CSTATE[3] = Arduino_skal_B.X0[3];
  }

  /* Integrator: '<S1>/MemoryX' */
  Arduino_skal_B.MemoryX[0] = Arduino_skal_X.MemoryX_CSTATE[0];

  /* Gain: '<Root>/Gain' */
  u0 = Arduino_skal_P.K[0] * Arduino_skal_B.MemoryX[0];

  /* Integrator: '<S1>/MemoryX' */
  Arduino_skal_B.MemoryX[1] = Arduino_skal_X.MemoryX_CSTATE[1];

  /* Gain: '<Root>/Gain' */
  u0 += Arduino_skal_P.K[1] * Arduino_skal_B.MemoryX[1];

  /* Integrator: '<S1>/MemoryX' */
  Arduino_skal_B.MemoryX[2] = Arduino_skal_X.MemoryX_CSTATE[2];

  /* Gain: '<Root>/Gain' */
  u0 += Arduino_skal_P.K[2] * Arduino_skal_B.MemoryX[2];

  /* Integrator: '<S1>/MemoryX' */
  Arduino_skal_B.MemoryX[3] = Arduino_skal_X.MemoryX_CSTATE[3];

  /* Gain: '<Root>/Gain' */
  u0 += Arduino_skal_P.K[3] * Arduino_skal_B.MemoryX[3];

  /* Gain: '<Root>/Gain' */
  Arduino_skal_B.Gain = u0;
  if (rtmIsMajorTimeStep((&Arduino_skal_M))) {
    /* MATLAB Function: '<S51>/SqrtUsedFcn' incorporates:
     *  Constant: '<S2>/CovarianceZ'
     *  Constant: '<S51>/isSqrtUsed'
     */
    /* :  if isSqrtUsed */
    if (Arduino_skal_P.isSqrtUsed_Value) {
      /* :  P = u*u.'; */
      for (i = 0; i < 4; i++) {
        for (i_0 = 0; i_0 < 4; i_0++) {
          Arduino_skal_B.P[i_0 + (i << 2)] = 0.0;
          Arduino_skal_B.P[i_0 + (i << 2)] +=
            Arduino_skal_P.CovarianceZ_Value[i_0] *
            Arduino_skal_P.CovarianceZ_Value[i];
          Arduino_skal_B.P[i_0 + (i << 2)] +=
            Arduino_skal_P.CovarianceZ_Value[i_0 + 4] *
            Arduino_skal_P.CovarianceZ_Value[i + 4];
          Arduino_skal_B.P[i_0 + (i << 2)] +=
            Arduino_skal_P.CovarianceZ_Value[i_0 + 8] *
            Arduino_skal_P.CovarianceZ_Value[i + 8];
          Arduino_skal_B.P[i_0 + (i << 2)] +=
            Arduino_skal_P.CovarianceZ_Value[i_0 + 12] *
            Arduino_skal_P.CovarianceZ_Value[i + 12];
        }
      }
    } else {
      /* :  else */
      /* :  P = u; */
      std::memcpy(&Arduino_skal_B.P[0], &Arduino_skal_P.CovarianceZ_Value[0],
                  sizeof(real_T) << 4U);
    }

    /* End of MATLAB Function: '<S51>/SqrtUsedFcn' */
  }

  /* Product: '<S22>/A[k]*xhat[k|k-1]' incorporates:
   *  Constant: '<S1>/A'
   */
  tmp_3 = &Arduino_skal_P.A_Value[0];
  tmp = Arduino_skal_B.MemoryX[0];
  tmp_0 = Arduino_skal_B.MemoryX[1];
  tmp_1 = Arduino_skal_B.MemoryX[2];
  tmp_2 = Arduino_skal_B.MemoryX[3];
  for (i = 0; i < 4; i++) {
    u0 = tmp_3[i] * tmp;
    u0 += tmp_3[i + 4] * tmp_0;
    u0 += tmp_3[i + 8] * tmp_1;
    u0 += tmp_3[i + 12] * tmp_2;

    /* Product: '<S22>/A[k]*xhat[k|k-1]' */
    Arduino_skal_B.Akxhatkk1[i] = u0;
  }

  /* End of Product: '<S22>/A[k]*xhat[k|k-1]' */

  /* Step: '<Root>/Step' */
  currentTime = (&Arduino_skal_M)->Timing.t[0];
  if (currentTime < Arduino_skal_P.Step_Time) {
    /* Step: '<Root>/Step' */
    Arduino_skal_B.Step = Arduino_skal_P.Step_Y0;
  } else {
    /* Step: '<Root>/Step' */
    Arduino_skal_B.Step = Arduino_skal_P.Step_YFinal;
  }

  /* End of Step: '<Root>/Step' */

  /* Gain: '<Root>/Kr' */
  Arduino_skal_B.Kr = Arduino_skal_P.Kr * Arduino_skal_B.Step;

  /* Sum: '<Root>/Sum5' */
  Arduino_skal_B.Sum5 = Arduino_skal_B.Kr - Arduino_skal_B.Gain;

  /* Saturate: '<Root>/Saturation' */
  u0 = Arduino_skal_B.Sum5;
  tmp = Arduino_skal_P.Saturation_LowerSat;
  tmp_0 = Arduino_skal_P.Saturation_UpperSat;
  if (u0 > tmp_0) {
    /* Saturate: '<Root>/Saturation' */
    Arduino_skal_B.Saturation = tmp_0;
  } else if (u0 < tmp) {
    /* Saturate: '<Root>/Saturation' */
    Arduino_skal_B.Saturation = tmp;
  } else {
    /* Saturate: '<Root>/Saturation' */
    Arduino_skal_B.Saturation = u0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Product: '<S22>/B[k]*u[k]' incorporates:
   *  Constant: '<S1>/B'
   */
  currentTime = Arduino_skal_B.Saturation;
  u0 = Arduino_skal_P.B_Value[0];

  /* Product: '<S22>/B[k]*u[k]' */
  Arduino_skal_B.Bkuk[0] = u0 * currentTime;

  /* Product: '<S22>/B[k]*u[k]' incorporates:
   *  Constant: '<S1>/B'
   */
  u0 = Arduino_skal_P.B_Value[1];

  /* Product: '<S22>/B[k]*u[k]' */
  Arduino_skal_B.Bkuk[1] = u0 * currentTime;

  /* Product: '<S22>/B[k]*u[k]' incorporates:
   *  Constant: '<S1>/B'
   */
  u0 = Arduino_skal_P.B_Value[2];

  /* Product: '<S22>/B[k]*u[k]' */
  Arduino_skal_B.Bkuk[2] = u0 * currentTime;

  /* Product: '<S22>/B[k]*u[k]' incorporates:
   *  Constant: '<S1>/B'
   */
  u0 = Arduino_skal_P.B_Value[3];

  /* Product: '<S22>/B[k]*u[k]' */
  Arduino_skal_B.Bkuk[3] = u0 * currentTime;

  /* Outputs for Enabled SubSystem: '<S22>/MeasurementUpdate' incorporates:
   *  EnablePort: '<S53>/Enable'
   */
  if (rtmIsMajorTimeStep((&Arduino_skal_M)) && rtmIsMajorTimeStep
      ((&Arduino_skal_M))) {
    /* Constant: '<S1>/Enable' */
    if (Arduino_skal_P.Enable_Value) {
      Arduino_skal_DW.MeasurementUpdate_MODE = true;
    } else if (Arduino_skal_DW.MeasurementUpdate_MODE) {
      /* Disable for Product: '<S53>/Product3' incorporates:
       *  Outport: '<S53>/L*(y[k]-yhat[k|k-1])'
       */
      Arduino_skal_B.Product3[0] = Arduino_skal_P.Lykyhatkk1_Y0;
      Arduino_skal_B.Product3[1] = Arduino_skal_P.Lykyhatkk1_Y0;
      Arduino_skal_B.Product3[2] = Arduino_skal_P.Lykyhatkk1_Y0;
      Arduino_skal_B.Product3[3] = Arduino_skal_P.Lykyhatkk1_Y0;
      Arduino_skal_DW.MeasurementUpdate_MODE = false;
    }

    /* End of Constant: '<S1>/Enable' */
  }

  if (Arduino_skal_DW.MeasurementUpdate_MODE) {
    /* Product: '<S53>/C[k]*xhat[k|k-1]' incorporates:
     *  Constant: '<S1>/C'
     *  Product: '<S53>/Product3'
     */
    tmp_3 = &Arduino_skal_P.C_Value[0];
    tmp = Arduino_skal_B.MemoryX[0];
    tmp_0 = Arduino_skal_B.MemoryX[1];
    tmp_1 = Arduino_skal_B.MemoryX[2];
    tmp_2 = Arduino_skal_B.MemoryX[3];

    /* Product: '<S53>/D[k]*u[k]' */
    currentTime = Arduino_skal_B.Saturation;
    for (i = 0; i < 2; i++) {
      /* Product: '<S53>/C[k]*xhat[k|k-1]' */
      u0 = tmp_3[i] * tmp;
      u0 += tmp_3[i + 2] * tmp_0;
      u0 += tmp_3[i + 4] * tmp_1;
      u0 += tmp_3[i + 6] * tmp_2;

      /* Product: '<S53>/C[k]*xhat[k|k-1]' */
      Arduino_skal_B.Ckxhatkk1[i] = u0;

      /* Product: '<S53>/D[k]*u[k]' incorporates:
       *  Constant: '<S1>/D'
       */
      u0 = Arduino_skal_P.D_Value[i];

      /* Product: '<S53>/D[k]*u[k]' */
      Arduino_skal_B.Dkuk[i] = u0 * currentTime;

      /* Sum: '<S53>/Add1' incorporates:
       *  Product: '<S53>/D[k]*u[k]'
       */
      Arduino_skal_B.yhatkk1[i] = Arduino_skal_B.Ckxhatkk1[i] +
        Arduino_skal_B.Dkuk[i];

      /* Sum: '<S53>/Sum' incorporates:
       *  Constant: '<Root>/Constant'
       *  Sum: '<S53>/Add1'
       */
      Arduino_skal_B.Sum[i] = Arduino_skal_P.Constant_Value[i] -
        Arduino_skal_B.yhatkk1[i];
    }

    /* Product: '<S53>/Product3' incorporates:
     *  Constant: '<S2>/KalmanGainL'
     *  Product: '<S53>/C[k]*xhat[k|k-1]'
     *  Sum: '<S53>/Sum'
     */
    tmp_3 = &Arduino_skal_P.KalmanGainL_Value[0];
    tmp = Arduino_skal_B.Sum[0];
    tmp_0 = Arduino_skal_B.Sum[1];
    for (i = 0; i < 4; i++) {
      /* Product: '<S53>/Product3' */
      Arduino_skal_B.Product3[i] = 0.0;
      Arduino_skal_B.Product3[i] += tmp_3[i] * tmp;
      Arduino_skal_B.Product3[i] += tmp_3[i + 4] * tmp_0;
    }
  }

  /* End of Outputs for SubSystem: '<S22>/MeasurementUpdate' */

  /* Sum: '<S22>/Add' incorporates:
   *  Product: '<S22>/B[k]*u[k]'
   *  Product: '<S53>/Product3'
   */
  Arduino_skal_B.Add[0] = (Arduino_skal_B.Bkuk[0] + Arduino_skal_B.Akxhatkk1[0])
    + Arduino_skal_B.Product3[0];
  Arduino_skal_B.Add[1] = (Arduino_skal_B.Bkuk[1] + Arduino_skal_B.Akxhatkk1[1])
    + Arduino_skal_B.Product3[1];
  Arduino_skal_B.Add[2] = (Arduino_skal_B.Bkuk[2] + Arduino_skal_B.Akxhatkk1[2])
    + Arduino_skal_B.Product3[2];
  Arduino_skal_B.Add[3] = (Arduino_skal_B.Bkuk[3] + Arduino_skal_B.Akxhatkk1[3])
    + Arduino_skal_B.Product3[3];
  if (rtmIsMajorTimeStep((&Arduino_skal_M))) {
    /* Matfile logging */
    rt_UpdateTXYLogVars((&Arduino_skal_M)->rtwLogInfo, ((&Arduino_skal_M)
      ->Timing.t));
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&Arduino_skal_M))) {
    /* Update for Integrator: '<S1>/MemoryX' */
    Arduino_skal_DW.MemoryX_IWORK = 0;
  }                                    /* end MajorTimeStep */

  if (rtmIsMajorTimeStep((&Arduino_skal_M))) {
    /* signal main to stop simulation */
    {                                  /* Sample time: [0.0s, 0.0s] */
      if ((rtmGetTFinal((&Arduino_skal_M))!=-1) &&
          !((rtmGetTFinal((&Arduino_skal_M))-((((&Arduino_skal_M)
               ->Timing.clockTick1+(&Arduino_skal_M)->Timing.clockTickH1*
               4294967296.0)) * 0.2)) > ((((&Arduino_skal_M)->Timing.clockTick1+
              (&Arduino_skal_M)->Timing.clockTickH1* 4294967296.0)) * 0.2) *
            (DBL_EPSILON))) {
        rtmSetErrorStatus((&Arduino_skal_M), "Simulation finished");
      }
    }

    rt_ertODEUpdateContinuousStates(&(&Arduino_skal_M)->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick0 and the high bits
     * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++(&Arduino_skal_M)->Timing.clockTick0)) {
      ++(&Arduino_skal_M)->Timing.clockTickH0;
    }

    (&Arduino_skal_M)->Timing.t[0] = rtsiGetSolverStopTime(&(&Arduino_skal_M)
      ->solverInfo);

    {
      /* Update absolute timer for sample time: [0.2s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.2, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       * Timer of this task consists of two 32 bit unsigned integers.
       * The two integers represent the low bits Timing.clockTick1 and the high bits
       * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
       */
      (&Arduino_skal_M)->Timing.clockTick1++;
      if (!(&Arduino_skal_M)->Timing.clockTick1) {
        (&Arduino_skal_M)->Timing.clockTickH1++;
      }
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Arduino_skalModelClass::Arduino_skal_derivatives()
{
  XDot_Arduino_skal_T *_rtXdot;
  _rtXdot = ((XDot_Arduino_skal_T *) (&Arduino_skal_M)->derivs);

  /* Derivatives for Integrator: '<S1>/MemoryX' */
  _rtXdot->MemoryX_CSTATE[0] = Arduino_skal_B.Add[0];
  _rtXdot->MemoryX_CSTATE[1] = Arduino_skal_B.Add[1];
  _rtXdot->MemoryX_CSTATE[2] = Arduino_skal_B.Add[2];
  _rtXdot->MemoryX_CSTATE[3] = Arduino_skal_B.Add[3];
}

/* Model initialize function */
void Arduino_skalModelClass::initialize()
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&(&Arduino_skal_M)->solverInfo, &(&Arduino_skal_M)
                          ->Timing.simTimeStep);
    rtsiSetTPtr(&(&Arduino_skal_M)->solverInfo, &rtmGetTPtr((&Arduino_skal_M)));
    rtsiSetStepSizePtr(&(&Arduino_skal_M)->solverInfo, &(&Arduino_skal_M)
                       ->Timing.stepSize0);
    rtsiSetdXPtr(&(&Arduino_skal_M)->solverInfo, &(&Arduino_skal_M)->derivs);
    rtsiSetContStatesPtr(&(&Arduino_skal_M)->solverInfo, (real_T **)
                         &(&Arduino_skal_M)->contStates);
    rtsiSetNumContStatesPtr(&(&Arduino_skal_M)->solverInfo, &(&Arduino_skal_M)
      ->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&Arduino_skal_M)->solverInfo,
      &(&Arduino_skal_M)->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&Arduino_skal_M)->solverInfo,
      &(&Arduino_skal_M)->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&Arduino_skal_M)->solverInfo,
      &(&Arduino_skal_M)->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&Arduino_skal_M)->solverInfo, (&rtmGetErrorStatus
      ((&Arduino_skal_M))));
    rtsiSetRTModelPtr(&(&Arduino_skal_M)->solverInfo, (&Arduino_skal_M));
  }

  rtsiSetSimTimeStep(&(&Arduino_skal_M)->solverInfo, MAJOR_TIME_STEP);
  (&Arduino_skal_M)->intgData.y = (&Arduino_skal_M)->odeY;
  (&Arduino_skal_M)->intgData.f[0] = (&Arduino_skal_M)->odeF[0];
  (&Arduino_skal_M)->intgData.f[1] = (&Arduino_skal_M)->odeF[1];
  (&Arduino_skal_M)->intgData.f[2] = (&Arduino_skal_M)->odeF[2];
  (&Arduino_skal_M)->contStates = ((X_Arduino_skal_T *) &Arduino_skal_X);
  rtsiSetSolverData(&(&Arduino_skal_M)->solverInfo, static_cast<void *>
                    (&(&Arduino_skal_M)->intgData));
  rtsiSetSolverName(&(&Arduino_skal_M)->solverInfo,"ode3");
  rtmSetTPtr((&Arduino_skal_M), &(&Arduino_skal_M)->Timing.tArray[0]);
  rtmSetTFinal((&Arduino_skal_M), 10.0);
  (&Arduino_skal_M)->Timing.stepSize0 = 0.2;
  rtmSetFirstInitCond((&Arduino_skal_M), 1);

  /* Setup for data logging */
  {
    static RTWLogInfo rt_DataLoggingInfo;
    rt_DataLoggingInfo.loggingInterval = (NULL);
    (&Arduino_skal_M)->rtwLogInfo = &rt_DataLoggingInfo;
  }

  /* Setup for data logging */
  {
    rtliSetLogXSignalInfo((&Arduino_skal_M)->rtwLogInfo, (NULL));
    rtliSetLogXSignalPtrs((&Arduino_skal_M)->rtwLogInfo, (NULL));
    rtliSetLogT((&Arduino_skal_M)->rtwLogInfo, "tout");
    rtliSetLogX((&Arduino_skal_M)->rtwLogInfo, "");
    rtliSetLogXFinal((&Arduino_skal_M)->rtwLogInfo, "");
    rtliSetLogVarNameModifier((&Arduino_skal_M)->rtwLogInfo, "rt_");
    rtliSetLogFormat((&Arduino_skal_M)->rtwLogInfo, 4);
    rtliSetLogMaxRows((&Arduino_skal_M)->rtwLogInfo, 0);
    rtliSetLogDecimation((&Arduino_skal_M)->rtwLogInfo, 1);
    rtliSetLogY((&Arduino_skal_M)->rtwLogInfo, "");
    rtliSetLogYSignalInfo((&Arduino_skal_M)->rtwLogInfo, (NULL));
    rtliSetLogYSignalPtrs((&Arduino_skal_M)->rtwLogInfo, (NULL));
  }

  /* Matfile logging */
  rt_StartDataLoggingWithStartTime((&Arduino_skal_M)->rtwLogInfo, 0.0,
    rtmGetTFinal((&Arduino_skal_M)), (&Arduino_skal_M)->Timing.stepSize0,
    (&rtmGetErrorStatus((&Arduino_skal_M))));

  /* Start for Constant: '<S1>/X0' */
  Arduino_skal_B.X0[0] = Arduino_skal_P.X0_Value[0];
  Arduino_skal_B.X0[1] = Arduino_skal_P.X0_Value[1];
  Arduino_skal_B.X0[2] = Arduino_skal_P.X0_Value[2];
  Arduino_skal_B.X0[3] = Arduino_skal_P.X0_Value[3];

  /* InitializeConditions for Integrator: '<S1>/MemoryX' */
  if (rtmIsFirstInitCond((&Arduino_skal_M))) {
    Arduino_skal_X.MemoryX_CSTATE[0] = 0.0;
    Arduino_skal_X.MemoryX_CSTATE[1] = 0.0;
    Arduino_skal_X.MemoryX_CSTATE[2] = 0.0;
    Arduino_skal_X.MemoryX_CSTATE[3] = 0.0;
  }

  Arduino_skal_DW.MemoryX_IWORK = 1;

  /* End of InitializeConditions for Integrator: '<S1>/MemoryX' */

  /* SystemInitialize for Enabled SubSystem: '<S22>/MeasurementUpdate' */
  /* SystemInitialize for Product: '<S53>/Product3' incorporates:
   *  Outport: '<S53>/L*(y[k]-yhat[k|k-1])'
   */
  Arduino_skal_B.Product3[0] = Arduino_skal_P.Lykyhatkk1_Y0;
  Arduino_skal_B.Product3[1] = Arduino_skal_P.Lykyhatkk1_Y0;
  Arduino_skal_B.Product3[2] = Arduino_skal_P.Lykyhatkk1_Y0;
  Arduino_skal_B.Product3[3] = Arduino_skal_P.Lykyhatkk1_Y0;

  /* End of SystemInitialize for SubSystem: '<S22>/MeasurementUpdate' */

  /* set "at time zero" to false */
  if (rtmIsFirstInitCond((&Arduino_skal_M))) {
    rtmSetFirstInitCond((&Arduino_skal_M), 0);
  }
}

/* Model terminate function */
void Arduino_skalModelClass::terminate()
{
  /* (no terminate code required) */
}

/* Constructor */
Arduino_skalModelClass::Arduino_skalModelClass() :
  Arduino_skal_B(),
  Arduino_skal_DW(),
  Arduino_skal_X(),
  Arduino_skal_M()
{
  /* Currently there is no constructor body generated.*/
}

/* Destructor */
Arduino_skalModelClass::~Arduino_skalModelClass()
{
  /* Currently there is no destructor body generated.*/
}

/* Real-Time Model get method */
RT_MODEL_Arduino_skal_T * Arduino_skalModelClass::getRTM()
{
  return (&Arduino_skal_M);
}
