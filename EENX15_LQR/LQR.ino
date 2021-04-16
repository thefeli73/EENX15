//LQR-stuff
#include "Arduino_skal.h"

// | ///////////////////////////////////
// | //Row 24-52 in Arduino_skal_data.cpp
// v ///////////////////////////////////
const double Arduino_skalModelClass::ConstP rtConstP = {
  // Expression: [100;200]
  //  Referenced by: '<Root>/vartejag'

  { 100.0, 200.0 },

  // Expression: A
  //  Referenced by: '<Root>/Gain4'

  { 0.0, 0.0, 0.0, 0.0, 1.0, -0.20780947085442231, 0.0, -0.52810302415000854,
    0.0, 13.239785742831822, 0.0, 58.601480177829842, 0.0, 0.0, 1.0, 0.0 },

  // Expression: C
  //  Referenced by: '<Root>/Gain6'

  { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 },

  // Expression: L
  //  Referenced by: '<Root>/Gain2'

  { 116.63033952875418, 3387.8673967111704, -1.4473912197449676,
    -115.34372132703447, -1.0534041975488044, -48.223441605702455,
    117.16185100039935, 3490.0480780568214 },

  // Expression: B
  //  Referenced by: '<Root>/Gain3'

  { 0.0, 2.078094708544223, 0.0, 5.2810302415000852 }
};

// | ///////////////////////////////////
// | //Row 261-264 in Arduino_skal.cpp
// v ///////////////////////////////////

rtX.Integrator1_CSTATE[0] = 0.0;
rtX.Integrator1_CSTATE[1] = 0.0;
rtX.Integrator1_CSTATE[2] = 0.0;
rtX.Integrator1_CSTATE[3] = 0.0;

// | ///////////////////////////////////
// | //Row 123-124 in Arduino_skal.cpp
// v ///////////////////////////////////

real_T tmp[2];
int rtb_Saturation;

// | ///////////////////////////////////
// | //Row 140-143 in Arduino_skal.cpp
// v ///////////////////////////////////

// Denna funktion bör anropas när styrka + riktning till motorer ska bestämmas.
int saturatedSignalToMotors(){
  rtb_Saturation = ((-31.622776601683942 * rtX.Integrator1_CSTATE[0] +
             -21.286439360075747 * rtX.Integrator1_CSTATE[1]) +
             80.789376267003959 * rtX.Integrator1_CSTATE[2]) +
             13.42463576551093 * rtX.Integrator1_CSTATE[3];
  
  if (0.0 - rtb_Saturation > 11.5) {
    rtb_Saturation = 11.5;
  } else if (0.0 - rtb_Saturation < -11.5) {
    rtb_Saturation = -11.5;
  } else {
    rtb_Saturation = 0.0 - rtb_Saturation;
  }
  return rtb_Saturation;
}
// | ///////////////////////////////////
// | //Row 165-188 in Arduino_skal.cpp
// v ///////////////////////////////////
int inputToControlSystem(float position_m, float angle_r){
  float posAndAng[] = {position_m, angle_r};
  for (i = 0; i < 2; i++) {
    tmp[i] = rtConstP.posAndAng[i] - (((rtConstP.Gain6_Gain[i + 2] *
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
  /*
  Integrator1_CSTATE[0] = rtDW.Sum4[0];
  Integrator1_CSTATE[1] = rtDW.Sum4[1];
  Integrator1_CSTATE[2] = rtDW.Sum4[2];
  Integrator1_CSTATE[3] = rtDW.Sum4[3];
  */
  return saturatedSignalToMotors();
}

// | ///////////////////////////////////
// | //Row 215-225 in Arduino_skal.cpp
// v ///////////////////////////////////

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
