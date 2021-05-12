//LQR-stuff
//#include "Arduino_skal.h"

// | ///////////////////////////////////
// | //Row 24-52 in Arduino_skal_data.cpp
// v ///////////////////////////////////

  // Expression: A
  //  Referenced by: '<Root>/Gain4'

const double matrix_A [16] = { 0.0, 0.0, 0.0, 0.0, 
  1.0, -0.20780947085442231, 0.0, -0.52810302415000854,
  0.0, 13.239785742831822, 0.0, 58.601480177829842, 
  0.0, 0.0, 1.0, 0.0 };

//const double matrix_A [16] = {0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0,0.0};

  // Expression: C
  //  Referenced by: '<Root>/Gain6'

const double matrix_C [8] = { 1.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
//const double matrix_C [8] = { 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  // Expression: L
  //  Referenced by: '<Root>/Gain2'

const double matrix_L [8] = { 56.7847, 799.5294, -1.4914, -57.4160, 
  -1.0363, -16.1071, 57.0075, 870.8172 };
const double matrix_L_old [8] = { 116.63033952875418, 3387.8673967111704, -1.4473912197449676,
    -115.34372132703447, -1.0534041975488044, -48.223441605702455,
    117.16185100039935, 3490.0480780568214 };
//const double matrix_L [8] = { 116.63033952875418, 338.78673967111704, -1.4473912197449676,
//    -115.34372132703447, -1.0534041975488044, -48.223441605702455,
//    117.16185100039935, 34.900480780568214 };

  // Expression: B
  //  Referenced by: '<Root>/Gain3'

const double matrix_B [4] = { 0.0, 2.078094708544223, 0.0, 5.2810302415000852 };


const double matrix_K_old [4] = {-31.622776601683942,   -21.286439360075747,   80.789376267003959,    13.42463576551093};
const double matrix_K [4] = {-0.0316,   -0.3938,   22.9455,    3.0629};

// | ///////////////////////////////////
// | //Row 261-264 in Arduino_skal.cpp
// v ///////////////////////////////////
double Integrator1_CSTATE [4] = {0.0, 0.0, 0.0, 0.0};
double Sum3[4];
double Sum4[4];

// | ///////////////////////////////////
// | //Row 123-124 in Arduino_skal.cpp
// v ///////////////////////////////////

double tmp[2];
double rtb_Saturation = 0.0;

// | ///////////////////////////////////
// | //Row 140-143 in Arduino_skal.cpp
// v ///////////////////////////////////

// Denna funktion bör anropas när styrka + riktning till motorer ska bestämmas.
double saturatedSignalToMotors(){
  rtb_Saturation = ((matrix_K[0] * Integrator1_CSTATE[0] +
             matrix_K[1] * Integrator1_CSTATE[1]) +
             matrix_K[2] * Integrator1_CSTATE[2]) +
             matrix_K[3] * Integrator1_CSTATE[3];
  
  if (0.0 - rtb_Saturation > 11.5) {
    rtb_Saturation = 3.0;
  } else if (0.0 - rtb_Saturation < -11.5) {
    rtb_Saturation = -3.0;
  } else {
    rtb_Saturation = 0.0 - rtb_Saturation;
  }
  Serial.print("Saturation  = "); Serial.println(rtb_Saturation);
  return rtb_Saturation;
}
// | ///////////////////////////////////
// | //Row 165-188 in Arduino_skal.cpp
// v ///////////////////////////////////
double inputToControlSystem(float position_m, float angle_r){
  float posAndAng[] = {position_m, angle_r};
  for (int i = 0; i < 2; i++) {
    tmp[i] = posAndAng[i] - (((matrix_C[i + 2] *
      Integrator1_CSTATE[1] + matrix_C[i] *
      Integrator1_CSTATE[0]) + matrix_C[i + 4] *
      Integrator1_CSTATE[2]) + matrix_C[i + 6] *
      Integrator1_CSTATE[3]);
  }

  // End of Sum: '<Root>/Sum2'
  for (int i = 0; i < 4; i++) {
    // Sum: '<Root>/Sum4' incorporates:
    //   Gain: '<Root>/Gain2'
    //   Gain: '<Root>/Gain3'
    //   Gain: '<Root>/Gain4'
    //   Integrator: '<Root>/Integrator1'
    //   Sum: '<Root>/Sum3'
  
  
    Sum3[i] = ((matrix_L[i + 4] * tmp[1] + matrix_L[i]
            * tmp[0]) + matrix_B[i] * rtb_Saturation);
      
    Sum4[i] = Sum3[i] +
            (matrix_A[i + 12] * Integrator1_CSTATE[3] +
            (matrix_A[i + 8] * Integrator1_CSTATE[2] +
            (matrix_A[i + 4] * Integrator1_CSTATE[1] +
            matrix_A[i] * Integrator1_CSTATE[0])));
  }
  Serial.print("Sum3 0 = "); Serial.println(Sum3[0]);
  Serial.print("Sum3 1 = "); Serial.println(Sum3[1]);
  Serial.print("Sum3 2 = "); Serial.println(Sum3[2]);
  Serial.print("Sum3 3 = "); Serial.println(Sum3[3]);
  
  Serial.print("Sum4 0 = "); Serial.println(Sum4[0]);
  Serial.print("Sum4 1 = "); Serial.println(Sum4[1]);
  Serial.print("Sum4 2 = "); Serial.println(Sum4[2]);
  Serial.print("Sum4 3 = "); Serial.println(Sum4[3]);
  
  Arduino_skal_derivatives();
  return saturatedSignalToMotors();
}

// | ///////////////////////////////////
// | //Row 215-225 in Arduino_skal.cpp
// v ///////////////////////////////////

void Arduino_skal_derivatives()
{
  /*
  XDot *_rtXdot;
  _rtXdot = ((XDot *) (&rtM)->derivs);
  // Derivatives for Integrator: '<Root>/Integrator1'
  _rtXdot->Integrator1_CSTATE[0] = Sum4[0];
  _rtXdot->Integrator1_CSTATE[1] = Sum4[1];
  _rtXdot->Integrator1_CSTATE[2] = Sum4[2];
  _rtXdot->Integrator1_CSTATE[3] = Sum4[3];
  
  Integrator1_CSTATE[0] = Sum4[0] * (fastTimer/1000.0);
  Integrator1_CSTATE[1] = Sum4[1] * (fastTimer/1000.0);
  Integrator1_CSTATE[2] = Sum4[2] * (fastTimer/1000.0);
  Integrator1_CSTATE[3] = Sum4[3] * (fastTimer/1000.0);
*/
  // Derivatives for Integrator: '<Root>/Integrator1'
  for (int i = 0; i < 4; i++) {
    Integrator1_CSTATE[i] = Sum4[i] * fastTimer/1000.0;
    Serial.print("Integrator: "); Serial.println(Integrator1_CSTATE[i]);
  }
}
