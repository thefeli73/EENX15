//temporary variable to measure main loops
int temp_loops;

//lqr stuff
const uint8_t statesNumber = 4;
/** Low pass filter angular Position*/
float angularPositionLP = 0;
/** Zumo's angular position */
float angularPosition = 0;
/** Corrected angular position */
float correctedAngularPosition = 0;
/** Zumo's angular speed */
float angularSpeed = 0;
/** Motor's angular position */
float motorAngularPosition = 0;
/** Motor's angular speed */
float motorAngularSpeed = 0;
/** PWM signal applied to the motor's driver 400 is 100% cicle and -400 100% but inverse direction */
int32_t speed;


//gyro stuff
float AccX, AccY, AccZ;
float GyroX, GyroY, GyroZ;
float accAngleX, accAngleY, gyroAngleX, gyroAngleY, gyroAngleZ;
float roll, pitch, yaw;
float AccErrorX, AccErrorY, GyroErrorX, GyroErrorY, GyroErrorZ;
float elapsedTime, currentTime, previousTime;
int gyro_x, gyro_y, gyro_z;
long gyro_x_cal, gyro_y_cal, gyro_z_cal;
boolean set_gyro_angles;

long acc_x, acc_y, acc_z, acc_total_vector;
float angle_roll_acc, angle_pitch_acc;

float angle_pitch, angle_roll;
int angle_pitch_buffer, angle_roll_buffer;
float angle_pitch_output, angle_roll_output;

long loop_timer;
int temp;

//motor stuff
const int MotorPinA = 12;
const int MotorSpeedA = 3;
const int MotorBrakeA = 9;

const int MotorPinB = 13;
const int MotorSpeedB = 11;
const int MotorBrakeB = 8;

const int CCW = HIGH;
const int CW = LOW;

volatile byte half_revolutionsA;
volatile byte half_revolutionsB;
unsigned int rpmA;
unsigned int rpmB;
unsigned long timeoldA;
unsigned long timeoldB;

void setup() {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  
  gyro_setup();
  
  //motor
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorSpeedA, OUTPUT);
  pinMode(MotorBrakeA, OUTPUT);
  
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorSpeedB, OUTPUT);
  pinMode(MotorBrakeB, OUTPUT);

  attachInterrupt(0, magnet_detectA, RISING);
  //attachInterrupt(1, magnet_detectB, RISING);
  half_revolutionsA = 0;
  rpmA = 0;
  timeoldA = 0;
  
  half_revolutionsB = 0;
  rpmB = 0;
  timeoldB = 0;
}

void loop() {
  gyro_loop();
  
  if(temp_loops>100){
    Serial.println("");
    Serial.print(" pitch Angle  = "); Serial.println(angle_pitch_output);
    Serial.print(" pitch Angle abs = "); Serial.println(abs(int(angle_pitch_output)));
    Serial.print(" pitch Angle measured = "); Serial.println(angle_pitch);
    temp_loops = 0;
  }
  else {
    temp_loops++;
  }

  if(angle_pitch_output!=0 && (abs(angle_pitch_output))<50 ){
    digitalWrite(MotorBrakeB, LOW);
    digitalWrite(MotorBrakeA, LOW);
    if(angle_pitch_output<0){
      digitalWrite(MotorPinB, CW);
      digitalWrite(MotorPinA, CCW);
    }
    else{
      digitalWrite(MotorPinB, CCW);
      digitalWrite(MotorPinA, CW);
    }
    if((abs(int(angle_pitch_output))*8 + 30)<250){
      analogWrite(MotorSpeedB,30 + 8*abs(int(angle_pitch_output))); //Wheel close to connections
      analogWrite(MotorSpeedA,30 + 8*abs(int(angle_pitch_output))); //First experiment wheel
    }
    else{
      analogWrite(MotorSpeedB,250); //Wheel close to connections
      analogWrite(MotorSpeedA,250); //First experiment wheel
    }
  }
  else{
    digitalWrite(MotorBrakeB, HIGH);
    digitalWrite(MotorBrakeA, HIGH);
    analogWrite(MotorSpeedB,0);
    analogWrite(MotorSpeedA,0);
  } 
}

void magnet_detectA()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   half_revolutionsA++;
   Serial.println("detect");
 }
 void magnet_detectB()//This function is called whenever a magnet/interrupt is detected by the arduino
 {
   half_revolutionsB++;
   //Serial.println("detect");
 }
