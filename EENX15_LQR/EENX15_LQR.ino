#include <Wire.h>

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

/** PWM signal applied to the motor's driver 255 is 100% */
int32_t speed;
int safe_angle;


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
#define encoderA1 2
#define encoderB1 3

#define encoderA2 4
#define encoderB2 7
volatile int countA = 0;
volatile int countB = 0;

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
  Wire.begin();
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  
  gyro_setup();
  
  //motor
  pinMode(encoderA1, INPUT_PULLUP);
  pinMode(encoderB1, INPUT_PULLUP);
  pinMode(encoderA2, INPUT_PULLUP);
  pinMode(encoderB2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(encoderA1), pulseA, RISING);
  //attachInterrupt(digitalPinToInterrupt(encoderB1), pulseB, RISING);
  
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorSpeedA, OUTPUT);
  pinMode(MotorBrakeA, OUTPUT);
  
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorSpeedB, OUTPUT);
  pinMode(MotorBrakeB, OUTPUT);

  half_revolutionsA = 0;
  rpmA = 0;
  timeoldA = 0;
  
  half_revolutionsB = 0;
  rpmB = 0;
  timeoldB = 0;
}

void loop() {
  gyro_loop();
  
  safe_angle = int(round(angle_pitch_output));
  
  if(temp_loops>250){
    Serial.println("");
    Serial.print(" pitch Angle  = "); Serial.println(angle_pitch_output);
    Serial.print(" pitch Angle abs = "); Serial.println(abs(safe_angle));
    Serial.print(" pitch Angle measured = "); Serial.println(angle_pitch);
    Serial.print("Position: "); Serial.println(countA);
    //Serial.print("A: "); Serial.println(countA);
    //Serial.print("B: "); Serial.println(countB);
    
    temp_loops = 0;
  }
  else {
    temp_loops++;
  }
  
  if(abs(safe_angle)<50 ){
    speed = 8*safe_angle;
    if(speed<0){
      digitalWrite(MotorPinB, CW);
      digitalWrite(MotorPinA, CCW);
      speed -= 30;
    }
    else if(speed>0){
      digitalWrite(MotorPinB, CCW);
      digitalWrite(MotorPinA, CW);
      speed += 30;
    }
    else {
      speed = 0;
    }
    speed = abs(speed);
    speed = constrain(speed, 0, 249);
    analogWrite(MotorSpeedB, speed); //Wheel close to connections
    analogWrite(MotorSpeedA, speed); //First experiment wheel
  }
  else{
    speed = 0;
    analogWrite(MotorSpeedB, speed);
    analogWrite(MotorSpeedA, speed);
  } 
}
int directionA(){
  if(digitalRead(encoderA2) ==  HIGH){                             
    return 1;  
  }
  else{
    return -1;
  }
}

int directionB(){
  if(digitalRead(encoderB2) ==  HIGH){                             
    return 1;  
  }
  else{
    return -1;
  }
}

void pulseA(){  
  countA += directionA();
}

void pulseB(){  
  countB += directionB();
}
