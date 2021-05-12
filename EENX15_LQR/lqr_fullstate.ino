float lqr_fullstate(float position_m, float speed_ms, float angle_r, float angle_speed_rs){
//  const float matrix_K [4] = {-0.0316,   -0.3938,   22.9455,    3.0629};
//  const float matrix_K [4] = {-1.0000,   -1.8855,   26.6999,    3.8592};
//  const float matrix_K [4] = {-1.0000,   -1.9058,   27.0579,    3.8886};
//  const float matrix_K [4] = {-0.3162,   -1.0381,   24.6060,    3.4143};
//  const float matrix_K [4] = {-0.1054,   -0.6273,   23.5822,    3.1936};
//  const float matrix_K [4] = {-0.1054,   -0.5273,   23.5546,    3.1876};
//  const float matrix_K [4] = {-0.1054,   -0.5273,   23.5546,    3.1876};
//  const float matrix_K [4] = {-0.7071,   -1.5720,   26.0726,    3.7050};
//  const float matrix_K [4] = {-0.7071,   -1.5980,   26.6081,    4.3220};
    const float matrix_K [4] = {-0.7071,   -1.7751,   34.5368,    4.8793};
  
  float result;
  result = matrix_K[0] * position_m +
           matrix_K[1] * speed_ms +
           matrix_K[2] * angle_r +
           matrix_K[3] * angle_speed_rs;
  /*
  if (result > 0.29) {
    result = 0.29;
  } else if (result < -0.29) {
    result = -0.29;
  } else {
    result = result;
  }*/
  Serial.print("K calculation (force): "); Serial.println(result); 
  return result;
}
float calc_speed(float input, float angle_speed_rs) {
  /*
  float a = -2971;
  float b = -0.9929;
  float c = 90.75;
  float radps = a * pow(speed, b) + c; ////// the response graph
  */

  /*
  float scale = 1.5;
  input = abs(input)*0.30796; // scale down to rad/s (78,53/255)
  Serial.print("input: "); Serial.println(input); 
  float result = 3145.84/(pow((90.75 - input),1.00715)); // break out x from response graph
  result *= scale;
  Serial.print("calcspeed: "); Serial.println(result); 
  return result;
  */
  float I = (1/3)*1.74;
  float km = 0.91*0.01;
  float ke = 8.68*0.001*2*PI/60;
  float Ir = I;
  float Omega= angle_speed_rs;
  
  float result = (km*ke/(Ir*5-km))*Omega;
  Serial.print("RESULT");
  Serial.print(result);
  return result;
  
}
