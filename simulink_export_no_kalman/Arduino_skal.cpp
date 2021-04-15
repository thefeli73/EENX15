//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Arduino_skal.cpp
//
// Code generated for Simulink model 'Arduino_skal'.
//
// Model version                  : 1.1
// Simulink Coder version         : 9.5 (R2021a) 14-Nov-2020
// C/C++ source code generated on : Thu Apr 15 22:06:00 2021
//
// Target selection: ert.tlc
// Embedded hardware selection: AMD->x86-64 (Windows64)
// Code generation objectives:
//    1. Execution efficiency
//    2. RAM efficiency
// Validation result: Not run
//
#include "Arduino_skal.h"

// Private macros used by the generated code to access rtModel
#ifndef rtmIsMajorTimeStep
#define rtmIsMajorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MAJOR_TIME_STEP)
#endif

#ifndef rtmIsMinorTimeStep
#define rtmIsMinorTimeStep(rtm)        (((rtm)->Timing.simTimeStep) == MINOR_TIME_STEP)
#endif

#ifndef rtmSetTPtr
#define rtmSetTPtr(rtm, val)           ((rtm)->Timing.t = (val))
#endif

// private model entry point functions
extern void Arduino_skal_derivatives();

//
// This function updates continuous states using the ODE3 fixed-step
// solver algorithm
//
void Arduino_skalModelClass::rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  // Solver Matrices
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

  // Save the state values at time t in y, we'll use x as ynew.
  (void) std::memcpy(y, x,
                     static_cast<uint_T>(nXc)*sizeof(real_T));

  // Assumes that rtsiSetT and ModelOutputs are up-to-date
  // f0 = f(t,y)
  rtsiSetdX(si, f0);
  Arduino_skal_derivatives();

  // f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*));
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  this->step();
  Arduino_skal_derivatives();

  // f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*));
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

  // tnew = t + hA(3);
  // ynew = y + f*hB(:,3);
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

// Model step function
void Arduino_skalModelClass::step()
{
  real_T tmp[2];
  real_T rtb_Saturation;
  int32_T i;
  if (rtmIsMajorTimeStep((&rtM))) {
    // set solver stop time
    rtsiSetSolverStopTime(&(&rtM)->solverInfo,(((&rtM)->Timing.clockTick0+1)*
      (&rtM)->Timing.stepSize0));
  }                                    // end MajorTimeStep

  // Update absolute time of base rate at minor time step
  if (rtmIsMinorTimeStep((&rtM))) {
    (&rtM)->Timing.t[0] = rtsiGetT(&(&rtM)->solverInfo);
  }

  // Gain: '<Root>/Gain' incorporates:
  //   Integrator: '<Root>/Integrator1'

  rtb_Saturation = ((-31.622776601683942 * rtX.Integrator1_CSTATE[0] +
                     -21.286439360075747 * rtX.Integrator1_CSTATE[1]) +
                    80.789376267003959 * rtX.Integrator1_CSTATE[2]) +
    13.42463576551093 * rtX.Integrator1_CSTATE[3];

  // Saturate: '<Root>/Saturation' incorporates:
  //   Gain: '<Root>/Gain'
  //   Step: '<Root>/Step'
  //   Sum: '<Root>/Sum5'

  if (0.0 - rtb_Saturation > 11.5) {
    rtb_Saturation = 11.5;
  } else if (0.0 - rtb_Saturation < -11.5) {
    rtb_Saturation = -11.5;
  } else {
    rtb_Saturation = 0.0 - rtb_Saturation;
  }

  // End of Saturate: '<Root>/Saturation'

  // Sum: '<Root>/Sum2' incorporates:
  //   Constant: '<Root>/vartejag'
  //   Gain: '<Root>/Gain6'
  //   Integrator: '<Root>/Integrator1'

  for (i = 0; i < 2; i++) {
    tmp[i] = rtConstP.vartejag_Value[i] - (((rtConstP.Gain6_Gain[i + 2] *
      rtX.Integrator1_CSTATE[1] + rtConstP.Gain6_Gain[i] *
      rtX.Integrator1_CSTATE[0]) + rtConstP.Gain6_Gain[i + 4] *
      rtX.Integrator1_CSTATE[2]) + rtConstP.Gain6_Gain[i + 6] *
      rtX.Integrator1_CSTATE[3]);
  }

  // End of Sum: '<Root>/Sum2'
  for (i = 0; i < 4; i++) {
    // Sum: '<Root>/Sum4' incorporates:
    //   Gain: '<Root>/Gain2'
    //   Gain: '<Root>/Gain3'
    //   Gain: '<Root>/Gain4'
    //   Integrator: '<Root>/Integrator1'
    //   Sum: '<Root>/Sum3'

    rtDW.Sum4[i] = ((rtConstP.Gain2_Gain[i + 4] * tmp[1] + rtConstP.Gain2_Gain[i]
                     * tmp[0]) + rtConstP.Gain3_Gain[i] * rtb_Saturation) +
      (rtConstP.Gain4_Gain[i + 12] * rtX.Integrator1_CSTATE[3] +
       (rtConstP.Gain4_Gain[i + 8] * rtX.Integrator1_CSTATE[2] +
        (rtConstP.Gain4_Gain[i + 4] * rtX.Integrator1_CSTATE[1] +
         rtConstP.Gain4_Gain[i] * rtX.Integrator1_CSTATE[0])));
  }

  if (rtmIsMajorTimeStep((&rtM))) {
    rt_ertODEUpdateContinuousStates(&(&rtM)->solverInfo);

    // Update absolute time for base rate
    // The "clockTick0" counts the number of times the code of this task has
    //  been executed. The absolute time is the multiplication of "clockTick0"
    //  and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
    //  overflow during the application lifespan selected.

    ++(&rtM)->Timing.clockTick0;
    (&rtM)->Timing.t[0] = rtsiGetSolverStopTime(&(&rtM)->solverInfo);

    {
      // Update absolute timer for sample time: [0.2s, 0.0s]
      // The "clockTick1" counts the number of times the code of this task has
      //  been executed. The resolution of this integer timer is 0.2, which is the step size
      //  of the task. Size of "clockTick1" ensures timer will not overflow during the
      //  application lifespan selected.

      (&rtM)->Timing.clockTick1++;
    }
  }                                    // end MajorTimeStep
}

// Derivatives for root system: '<Root>'
void Arduino_skalModelClass::Arduino_skal_derivatives()
{
  Arduino_skalModelClass::XDot *_rtXdot;
  _rtXdot = ((XDot *) (&rtM)->derivs);

  // Derivatives for Integrator: '<Root>/Integrator1'
  _rtXdot->Integrator1_CSTATE[0] = rtDW.Sum4[0];
  _rtXdot->Integrator1_CSTATE[1] = rtDW.Sum4[1];
  _rtXdot->Integrator1_CSTATE[2] = rtDW.Sum4[2];
  _rtXdot->Integrator1_CSTATE[3] = rtDW.Sum4[3];
}

// Model initialize function
void Arduino_skalModelClass::initialize()
{
  // Registration code
  {
    // Setup solver object
    rtsiSetSimTimeStepPtr(&(&rtM)->solverInfo, &(&rtM)->Timing.simTimeStep);
    rtsiSetTPtr(&(&rtM)->solverInfo, &rtmGetTPtr((&rtM)));
    rtsiSetStepSizePtr(&(&rtM)->solverInfo, &(&rtM)->Timing.stepSize0);
    rtsiSetdXPtr(&(&rtM)->solverInfo, &(&rtM)->derivs);
    rtsiSetContStatesPtr(&(&rtM)->solverInfo, (real_T **) &(&rtM)->contStates);
    rtsiSetNumContStatesPtr(&(&rtM)->solverInfo, &(&rtM)->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&(&rtM)->solverInfo, &(&rtM)
      ->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&(&rtM)->solverInfo, (&rtmGetErrorStatus((&rtM))));
    rtsiSetRTModelPtr(&(&rtM)->solverInfo, (&rtM));
  }

  rtsiSetSimTimeStep(&(&rtM)->solverInfo, MAJOR_TIME_STEP);
  (&rtM)->intgData.y = (&rtM)->odeY;
  (&rtM)->intgData.f[0] = (&rtM)->odeF[0];
  (&rtM)->intgData.f[1] = (&rtM)->odeF[1];
  (&rtM)->intgData.f[2] = (&rtM)->odeF[2];
  (&rtM)->contStates = ((X *) &rtX);
  rtsiSetSolverData(&(&rtM)->solverInfo, static_cast<void *>(&(&rtM)->intgData));
  rtsiSetSolverName(&(&rtM)->solverInfo,"ode3");
  rtmSetTPtr((&rtM), &(&rtM)->Timing.tArray[0]);
  (&rtM)->Timing.stepSize0 = 0.2;

  // InitializeConditions for Integrator: '<Root>/Integrator1'
  rtX.Integrator1_CSTATE[0] = 0.0;
  rtX.Integrator1_CSTATE[1] = 0.0;
  rtX.Integrator1_CSTATE[2] = 0.0;
  rtX.Integrator1_CSTATE[3] = 0.0;
}

// Constructor
Arduino_skalModelClass::Arduino_skalModelClass() :
  rtDW(),
  rtX(),
  rtM()
{
  // Currently there is no constructor body generated.
}

// Destructor
Arduino_skalModelClass::~Arduino_skalModelClass()
{
  // Currently there is no destructor body generated.
}

// Real-Time Model get method
Arduino_skalModelClass::RT_MODEL * Arduino_skalModelClass::getRTM()
{
  return (&rtM);
}

//
// File trailer for generated code.
//
// [EOF]
//
