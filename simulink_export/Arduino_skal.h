/*
 * Arduino_skal.h
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

#ifndef RTW_HEADER_Arduino_skal_h_
#define RTW_HEADER_Arduino_skal_h_
#include <cstring>
#include <cfloat>
#include <stddef.h>
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#include "rt_logging.h"
#include "Arduino_skal_types.h"

/* Shared type includes */
#include "multiword_types.h"
#include "rt_nonfinite.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetContStateDisabled
#define rtmGetContStateDisabled(rtm)   ((rtm)->contStateDisabled)
#endif

#ifndef rtmSetContStateDisabled
#define rtmSetContStateDisabled(rtm, val) ((rtm)->contStateDisabled = (val))
#endif

#ifndef rtmGetContStates
#define rtmGetContStates(rtm)          ((rtm)->contStates)
#endif

#ifndef rtmSetContStates
#define rtmSetContStates(rtm, val)     ((rtm)->contStates = (val))
#endif

#ifndef rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmGetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm) ((rtm)->CTOutputIncnstWithState)
#endif

#ifndef rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag
#define rtmSetContTimeOutputInconsistentWithStateAtMajorStepFlag(rtm, val) ((rtm)->CTOutputIncnstWithState = (val))
#endif

#ifndef rtmGetDerivCacheNeedsReset
#define rtmGetDerivCacheNeedsReset(rtm) ((rtm)->derivCacheNeedsReset)
#endif

#ifndef rtmSetDerivCacheNeedsReset
#define rtmSetDerivCacheNeedsReset(rtm, val) ((rtm)->derivCacheNeedsReset = (val))
#endif

#ifndef rtmGetFinalTime
#define rtmGetFinalTime(rtm)           ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetIntgData
#define rtmGetIntgData(rtm)            ((rtm)->intgData)
#endif

#ifndef rtmSetIntgData
#define rtmSetIntgData(rtm, val)       ((rtm)->intgData = (val))
#endif

#ifndef rtmGetOdeF
#define rtmGetOdeF(rtm)                ((rtm)->odeF)
#endif

#ifndef rtmSetOdeF
#define rtmSetOdeF(rtm, val)           ((rtm)->odeF = (val))
#endif

#ifndef rtmGetOdeY
#define rtmGetOdeY(rtm)                ((rtm)->odeY)
#endif

#ifndef rtmSetOdeY
#define rtmSetOdeY(rtm, val)           ((rtm)->odeY = (val))
#endif

#ifndef rtmGetPeriodicContStateIndices
#define rtmGetPeriodicContStateIndices(rtm) ((rtm)->periodicContStateIndices)
#endif

#ifndef rtmSetPeriodicContStateIndices
#define rtmSetPeriodicContStateIndices(rtm, val) ((rtm)->periodicContStateIndices = (val))
#endif

#ifndef rtmGetPeriodicContStateRanges
#define rtmGetPeriodicContStateRanges(rtm) ((rtm)->periodicContStateRanges)
#endif

#ifndef rtmSetPeriodicContStateRanges
#define rtmSetPeriodicContStateRanges(rtm, val) ((rtm)->periodicContStateRanges = (val))
#endif

#ifndef rtmGetRTWLogInfo
#define rtmGetRTWLogInfo(rtm)          ((rtm)->rtwLogInfo)
#endif

#ifndef rtmGetZCCacheNeedsReset
#define rtmGetZCCacheNeedsReset(rtm)   ((rtm)->zCCacheNeedsReset)
#endif

#ifndef rtmSetZCCacheNeedsReset
#define rtmSetZCCacheNeedsReset(rtm, val) ((rtm)->zCCacheNeedsReset = (val))
#endif

#ifndef rtmGetdX
#define rtmGetdX(rtm)                  ((rtm)->derivs)
#endif

#ifndef rtmSetdX
#define rtmSetdX(rtm, val)             ((rtm)->derivs = (val))
#endif

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

#ifndef rtmGetTFinal
#define rtmGetTFinal(rtm)              ((rtm)->Timing.tFinal)
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
struct B_Arduino_skal_T {
  real_T X0[4];                        /* '<S1>/X0' */
  real_T MemoryX[4];                   /* '<S1>/MemoryX' */
  real_T Gain;                         /* '<Root>/Gain' */
  real_T Akxhatkk1[4];                 /* '<S22>/A[k]*xhat[k|k-1]' */
  real_T Step;                         /* '<Root>/Step' */
  real_T Kr;                           /* '<Root>/Kr' */
  real_T Sum5;                         /* '<Root>/Sum5' */
  real_T Saturation;                   /* '<Root>/Saturation' */
  real_T Bkuk[4];                      /* '<S22>/B[k]*u[k]' */
  real_T Add[4];                       /* '<S22>/Add' */
  real_T Ckxhatkk1[2];                 /* '<S53>/C[k]*xhat[k|k-1]' */
  real_T Dkuk[2];                      /* '<S53>/D[k]*u[k]' */
  real_T yhatkk1[2];                   /* '<S53>/Add1' */
  real_T Sum[2];                       /* '<S53>/Sum' */
  real_T Product3[4];                  /* '<S53>/Product3' */
  real_T P[16];                        /* '<S51>/SqrtUsedFcn' */
};

/* Block states (default storage) for system '<Root>' */
struct DW_Arduino_skal_T {
  int_T MemoryX_IWORK;                 /* '<S1>/MemoryX' */
  boolean_T MeasurementUpdate_MODE;    /* '<S22>/MeasurementUpdate' */
};

/* Continuous states (default storage) */
struct X_Arduino_skal_T {
  real_T MemoryX_CSTATE[4];            /* '<S1>/MemoryX' */
};

/* State derivatives (default storage) */
struct XDot_Arduino_skal_T {
  real_T MemoryX_CSTATE[4];            /* '<S1>/MemoryX' */
};

/* State disabled  */
struct XDis_Arduino_skal_T {
  boolean_T MemoryX_CSTATE[4];         /* '<S1>/MemoryX' */
};

#ifndef ODE3_INTG
#define ODE3_INTG

/* ODE3 Integration Data */
struct ODE3_IntgData {
  real_T *y;                           /* output */
  real_T *f[3];                        /* derivatives */
};

#endif

/* Parameters (default storage) */
struct P_Arduino_skal_T_ {
  real_T K[4];                         /* Variable: K
                                        * Referenced by: '<Root>/Gain'
                                        */
  real_T Kr;                           /* Variable: Kr
                                        * Referenced by: '<Root>/Kr'
                                        */
  real_T Lykyhatkk1_Y0;                /* Expression: 0
                                        * Referenced by: '<S53>/L*(y[k]-yhat[k|k-1])'
                                        */
  real_T Constant_Value[2];            /* Expression: [1,1]
                                        * Referenced by: '<Root>/Constant'
                                        */
  real_T X0_Value[4];                  /* Expression: pInitialization.X0
                                        * Referenced by: '<S1>/X0'
                                        */
  real_T A_Value[16];                  /* Expression: pInitialization.A
                                        * Referenced by: '<S1>/A'
                                        */
  real_T B_Value[4];                   /* Expression: pInitialization.B
                                        * Referenced by: '<S1>/B'
                                        */
  real_T C_Value[8];                   /* Expression: pInitialization.C
                                        * Referenced by: '<S1>/C'
                                        */
  real_T CovarianceZ_Value[16];        /* Expression: pInitialization.Z
                                        * Referenced by: '<S2>/CovarianceZ'
                                        */
  real_T KalmanGainL_Value[8];         /* Expression: pInitialization.L
                                        * Referenced by: '<S2>/KalmanGainL'
                                        */
  real_T D_Value[2];                   /* Expression: pInitialization.D
                                        * Referenced by: '<S1>/D'
                                        */
  real_T Step_Time;                    /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_Y0;                      /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Step_YFinal;                  /* Expression: 0
                                        * Referenced by: '<Root>/Step'
                                        */
  real_T Saturation_UpperSat;          /* Expression: 11.5
                                        * Referenced by: '<Root>/Saturation'
                                        */
  real_T Saturation_LowerSat;          /* Expression: -11.5
                                        * Referenced by: '<Root>/Saturation'
                                        */
  boolean_T isSqrtUsed_Value;          /* Expression: pInitialization.isSqrtUsed
                                        * Referenced by: '<S51>/isSqrtUsed'
                                        */
  boolean_T Enable_Value;              /* Expression: true()
                                        * Referenced by: '<S1>/Enable'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Arduino_skal_T {
  const char_T *errorStatus;
  RTWLogInfo *rtwLogInfo;
  RTWSolverInfo solverInfo;
  X_Arduino_skal_T *contStates;
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

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    uint32_T clockTick1;
    uint32_T clockTickH1;
    boolean_T firstInitCondFlag;
    time_T tFinal;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Class declaration for model Arduino_skal */
class Arduino_skalModelClass {
  /* public data and function members */
 public:
  /* model initialize function */
  void initialize();

  /* model step function */
  void step();

  /* model terminate function */
  void terminate();

  /* Constructor */
  Arduino_skalModelClass();

  /* Destructor */
  ~Arduino_skalModelClass();

  /* Real-Time Model get method */
  RT_MODEL_Arduino_skal_T * getRTM();

  /* private data and function members */
 private:
  /* Tunable parameters */
  static P_Arduino_skal_T Arduino_skal_P;

  /* Block signals */
  B_Arduino_skal_T Arduino_skal_B;

  /* Block states */
  DW_Arduino_skal_T Arduino_skal_DW;
  X_Arduino_skal_T Arduino_skal_X;     /* Block continuous states */

  /* Real-Time Model */
  RT_MODEL_Arduino_skal_T Arduino_skal_M;

  /* Continuous states update member function*/
  void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si );

  /* Derivatives member function */
  void Arduino_skal_derivatives();
};

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S45>/Data Type Duplicate' : Unused code path elimination
 * Block '<S46>/Conversion' : Unused code path elimination
 * Block '<S46>/Data Type Duplicate' : Unused code path elimination
 * Block '<S47>/Conversion' : Unused code path elimination
 * Block '<S47>/Data Type Duplicate' : Unused code path elimination
 * Block '<S48>/Data Type Duplicate' : Unused code path elimination
 * Block '<S2>/KalmanGainM' : Unused code path elimination
 * Block '<S5>/Data Type Duplicate' : Unused code path elimination
 * Block '<S6>/Data Type Duplicate' : Unused code path elimination
 * Block '<S7>/Data Type Duplicate' : Unused code path elimination
 * Block '<S8>/Data Type Duplicate' : Unused code path elimination
 * Block '<S10>/Data Type Duplicate' : Unused code path elimination
 * Block '<S11>/Data Type Duplicate' : Unused code path elimination
 * Block '<S12>/Data Type Duplicate' : Unused code path elimination
 * Block '<S13>/Conversion' : Unused code path elimination
 * Block '<S13>/Data Type Duplicate' : Unused code path elimination
 * Block '<S14>/Data Type Duplicate' : Unused code path elimination
 * Block '<S15>/Data Type Duplicate' : Unused code path elimination
 * Block '<S16>/Data Type Duplicate' : Unused code path elimination
 * Block '<S18>/Data Type Duplicate' : Unused code path elimination
 * Block '<S19>/Data Type Duplicate' : Unused code path elimination
 * Block '<S1>/G' : Unused code path elimination
 * Block '<S1>/H' : Unused code path elimination
 * Block '<S1>/N' : Unused code path elimination
 * Block '<S1>/P0' : Unused code path elimination
 * Block '<S1>/Q' : Unused code path elimination
 * Block '<S1>/R' : Unused code path elimination
 * Block '<S43>/CheckSignalProperties' : Unused code path elimination
 * Block '<S44>/CheckSignalProperties' : Unused code path elimination
 * Block '<S45>/Conversion' : Eliminate redundant data type conversion
 * Block '<S48>/Conversion' : Eliminate redundant data type conversion
 * Block '<S18>/Conversion' : Eliminate redundant data type conversion
 * Block '<S22>/Reshape' : Reshape block reduction
 * Block '<S1>/ReshapeX0' : Reshape block reduction
 * Block '<S1>/Reshapeu' : Reshape block reduction
 * Block '<S1>/Reshapexhat' : Reshape block reduction
 * Block '<S1>/Reshapey' : Reshape block reduction
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Use the MATLAB hilite_system command to trace the generated code back
 * to the model.  For example,
 *
 * hilite_system('<S3>')    - opens system 3
 * hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'Arduino_skal'
 * '<S1>'   : 'Arduino_skal/Kalman Filter'
 * '<S2>'   : 'Arduino_skal/Kalman Filter/CalculatePL'
 * '<S3>'   : 'Arduino_skal/Kalman Filter/CalculateYhat'
 * '<S4>'   : 'Arduino_skal/Kalman Filter/CovarianceOutputConfigurator'
 * '<S5>'   : 'Arduino_skal/Kalman Filter/DataTypeConversionA'
 * '<S6>'   : 'Arduino_skal/Kalman Filter/DataTypeConversionB'
 * '<S7>'   : 'Arduino_skal/Kalman Filter/DataTypeConversionC'
 * '<S8>'   : 'Arduino_skal/Kalman Filter/DataTypeConversionD'
 * '<S9>'   : 'Arduino_skal/Kalman Filter/DataTypeConversionEnable'
 * '<S10>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionG'
 * '<S11>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionH'
 * '<S12>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionN'
 * '<S13>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionP'
 * '<S14>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionP0'
 * '<S15>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionQ'
 * '<S16>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionR'
 * '<S17>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionReset'
 * '<S18>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionX'
 * '<S19>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionX0'
 * '<S20>'  : 'Arduino_skal/Kalman Filter/DataTypeConversionu'
 * '<S21>'  : 'Arduino_skal/Kalman Filter/MemoryP'
 * '<S22>'  : 'Arduino_skal/Kalman Filter/Observer'
 * '<S23>'  : 'Arduino_skal/Kalman Filter/ReducedQRN'
 * '<S24>'  : 'Arduino_skal/Kalman Filter/Reset'
 * '<S25>'  : 'Arduino_skal/Kalman Filter/Reshapeyhat'
 * '<S26>'  : 'Arduino_skal/Kalman Filter/ScalarExpansionP0'
 * '<S27>'  : 'Arduino_skal/Kalman Filter/ScalarExpansionQ'
 * '<S28>'  : 'Arduino_skal/Kalman Filter/ScalarExpansionR'
 * '<S29>'  : 'Arduino_skal/Kalman Filter/UseCurrentEstimator'
 * '<S30>'  : 'Arduino_skal/Kalman Filter/checkA'
 * '<S31>'  : 'Arduino_skal/Kalman Filter/checkB'
 * '<S32>'  : 'Arduino_skal/Kalman Filter/checkC'
 * '<S33>'  : 'Arduino_skal/Kalman Filter/checkD'
 * '<S34>'  : 'Arduino_skal/Kalman Filter/checkEnable'
 * '<S35>'  : 'Arduino_skal/Kalman Filter/checkG'
 * '<S36>'  : 'Arduino_skal/Kalman Filter/checkH'
 * '<S37>'  : 'Arduino_skal/Kalman Filter/checkN'
 * '<S38>'  : 'Arduino_skal/Kalman Filter/checkP0'
 * '<S39>'  : 'Arduino_skal/Kalman Filter/checkQ'
 * '<S40>'  : 'Arduino_skal/Kalman Filter/checkR'
 * '<S41>'  : 'Arduino_skal/Kalman Filter/checkReset'
 * '<S42>'  : 'Arduino_skal/Kalman Filter/checkX0'
 * '<S43>'  : 'Arduino_skal/Kalman Filter/checku'
 * '<S44>'  : 'Arduino_skal/Kalman Filter/checky'
 * '<S45>'  : 'Arduino_skal/Kalman Filter/CalculatePL/DataTypeConversionL'
 * '<S46>'  : 'Arduino_skal/Kalman Filter/CalculatePL/DataTypeConversionM'
 * '<S47>'  : 'Arduino_skal/Kalman Filter/CalculatePL/DataTypeConversionP'
 * '<S48>'  : 'Arduino_skal/Kalman Filter/CalculatePL/DataTypeConversionZ'
 * '<S49>'  : 'Arduino_skal/Kalman Filter/CalculatePL/Ground'
 * '<S50>'  : 'Arduino_skal/Kalman Filter/CalculateYhat/Ground'
 * '<S51>'  : 'Arduino_skal/Kalman Filter/CovarianceOutputConfigurator/decideOutput'
 * '<S52>'  : 'Arduino_skal/Kalman Filter/CovarianceOutputConfigurator/decideOutput/SqrtUsedFcn'
 * '<S53>'  : 'Arduino_skal/Kalman Filter/Observer/MeasurementUpdate'
 * '<S54>'  : 'Arduino_skal/Kalman Filter/ReducedQRN/Ground'
 */
#endif                                 /* RTW_HEADER_Arduino_skal_h_ */
