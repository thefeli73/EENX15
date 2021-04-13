/** Control Law*/
const float K[statesNumber] = {0.55192, 8.9867, 0.194, 0.39237};

//K from our calculation
//const float K[statesNumber] = {-31.6228, -21.2864, 80.7894, 13.4246};

/** Correction factor */
const float scaleConst = 2.5;

/**
 * LQR control law
 */
void lqr() {
  speed = 0;
  
  speed -= motorAngularPosition * K[0];
  speed -= correctedAngularPosition * K[1];
  speed -= motorAngularSpeed * K[2];
  speed -= angularSpeed * K[3];

  speed = speed*scaleConst;
 
}

