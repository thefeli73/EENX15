//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: Arduino_skal.h
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
#ifndef RTW_HEADER_Arduino_skal_h_
#define RTW_HEADER_Arduino_skal_h_
//#include <cstring>
#include "rtwtypes.h"
//#include "rtw_continuous.h"
//#include "rtw_solver.h"

// Model Code Variants

// Macros for accessing real-time model data structure
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

#ifndef ODE3_INTG
#define ODE3_INTG

// ODE3 Integration Data
struct ODE3_IntgData {
  real_T *y;                           // output
  real_T *f[3];                        // derivatives
};

#endif

// Class declaration for model Arduino_skal
class Arduino_skalModelClass {
  // public data and function members
 public:
  // Block signals and states (default storage) for system '<Root>'
  struct DW {
    real_T Sum4[4];                    // '<Root>/Sum4'
  };

  // Continuous states (default storage)
  struct X {
    real_T Integrator1_CSTATE[4];      // '<Root>/Integrator1'
  };

  // State derivatives (default storage)
  struct XDot {
    real_T Integrator1_CSTATE[4];      // '<Root>/Integrator1'
  };

  // State disabled
  struct XDis {
    boolean_T Integrator1_CSTATE[4];   // '<Root>/Integrator1'
  };

  // Constant parameters (default storage)
  struct ConstP {
    // Expression: [100;200]
    //  Referenced by: '<Root>/vartejag'

    real_T vartejag_Value[2];

    // Expression: A
    //  Referenced by: '<Root>/Gain4'

    real_T Gain4_Gain[16];

    // Expression: C
    //  Referenced by: '<Root>/Gain6'

    real_T Gain6_Gain[8];

    // Expression: L
    //  Referenced by: '<Root>/Gain2'

    real_T Gain2_Gain[8];

    // Expression: B
    //  Referenced by: '<Root>/Gain3'

    real_T Gain3_Gain[4];
  };

  // Real-time Model Data Structure
  struct RT_MODEL {
    const char_T *errorStatus;
    //RTWSolverInfo solverInfo;
    X *contStates;
    int_T *periodicContStateIndices;
    real_T *periodicContStateRanges;
    real_T *derivs;
    boolean_T *contStateDisabled;
    boolean_T zCCacheNeedsReset;
    boolean_T derivCacheNeedsReset;
    boolean_T CTOutputIncnstWithState;
    real_T odeY[4];
    real_T odeF[3][4];
    ODE3_IntgData intgData;

    //
    //  Sizes:
    //  The following substructure contains sizes information
    //  for many of the model attributes such as inputs, outputs,
    //  dwork, sample times, etc.

    struct {
      int_T numContStates;
      int_T numPeriodicContStates;
      int_T numSampTimes;
    } Sizes;

    //
    //  Timing:
    //  The following substructure contains information regarding
    //  the timing information for the model.

    struct {
      uint32_T clockTick0;
      time_T stepSize0;
      uint32_T clockTick1;
      SimTimeStep simTimeStep;
      boolean_T stopRequestedFlag;
      time_T *t;
      time_T tArray[2];
    } Timing;
  };

  // model initialize function
  void initialize();

  // model step function
  void step();

  // Constructor
  Arduino_skalModelClass();

  // Destructor
  ~Arduino_skalModelClass();

  // Real-Time Model get method
  Arduino_skalModelClass::RT_MODEL * getRTM();

  // private data and function members
 private:
  // Block signals and states
  DW rtDW;
  X rtX;                               // Block continuous states

  // Real-Time Model
  RT_MODEL rtM;

  // Continuous states update member function
  //void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  // Derivatives member function
  void Arduino_skal_derivatives();
};

// Constant parameters (default storage)
extern const Arduino_skalModelClass::ConstP rtConstP;

//-
//  These blocks were eliminated from the model due to optimizations:
//
//  Block '<Root>/Kr' : Eliminated nontunable gain of 1


//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'Arduino_skal'

#endif                                 // RTW_HEADER_Arduino_skal_h_

//
// File trailer for generated code.
//
// [EOF]
//