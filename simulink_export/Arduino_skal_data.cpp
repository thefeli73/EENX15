/*
 * Arduino_skal_data.cpp
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

/* Block parameters (default storage) */
P_Arduino_skal_T Arduino_skalModelClass::Arduino_skal_P = {
  /* Variable: K
   * Referenced by: '<Root>/Gain'
   */
  { -31.622776601683942, -21.286439360075747, 80.789376267003959,
    13.42463576551093 },

  /* Variable: Kr
   * Referenced by: '<Root>/Kr'
   */
  1.0,

  /* Expression: 0
   * Referenced by: '<S53>/L*(y[k]-yhat[k|k-1])'
   */
  0.0,

  /* Expression: [1,1]
   * Referenced by: '<Root>/Constant'
   */
  { 1.0, 1.0 },

  /* Expression: pInitialization.X0
   * Referenced by: '<S1>/X0'
   */
  { 0.0, 0.0, 0.0, 0.0 },

  /* Expression: pInitialization.A
   * Referenced by: '<S1>/A'
   */
  { 0.0, 0.0, 0.0, 0.0, 1.0, -0.20780947085442231, 0.0, -0.52810302415000854,
    0.0, 13.239785742831822, 0.0, 58.601480177829842, 0.0, 0.0, 1.0, 0.0 },

  /* Expression: pInitialization.B
   * Referenced by: '<S1>/B'
   */
  { 0.0, 2.078094708544223, 0.0, 5.2810302415000852 },

  /* Expression: pInitialization.C
   * Referenced by: '<S1>/C'
   */
  { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 },

  /* Expression: pInitialization.Z
   * Referenced by: '<S2>/CovarianceZ'
   */
  { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    0.0 },

  /* Expression: pInitialization.L
   * Referenced by: '<S2>/KalmanGainL'
   */
  { 2.829363352293504, 6.8371369304528766, 2.3809613355962305,
    17.882971156218495, 2.3809613355962278, 24.153756408336502,
    14.825995823889082, 112.73956452579047 },

  /* Expression: pInitialization.D
   * Referenced by: '<S1>/D'
   */
  { 0.0, 0.0 },

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 0
   * Referenced by: '<Root>/Step'
   */
  0.0,

  /* Expression: 11.5
   * Referenced by: '<Root>/Saturation'
   */
  11.5,

  /* Expression: -11.5
   * Referenced by: '<Root>/Saturation'
   */
  -11.5,

  /* Expression: pInitialization.isSqrtUsed
   * Referenced by: '<S51>/isSqrtUsed'
   */
  0,

  /* Expression: true()
   * Referenced by: '<S1>/Enable'
   */
  1
};
