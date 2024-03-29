#include <Wire.h>

int lastCorrectionTime = 0;
int lastPrintTime = 0;

static int fastTimer = 80; //ms
static int slowTimer = 800; //ms

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
volatile int countAold = 0;
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
float rpm = 0;
float rps = 0;

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
}
 
void loop() {
  gyro_loop();
  safe_angle = int(round(angle_pitch_output));

  int m = millis();
  
  if (m - lastCorrectionTime >= fastTimer) { //run this code ever 80ms (12.5hz)
    lastCorrectionTime = m;
    getSpeed();
    setSpeed();
  }
  if (m - lastPrintTime >= slowTimer) { //run this code ever 800ms (1.25hz)
    lastPrintTime = m;
    printInfo();
  }
}

void getSpeed() {
  float alpha = 2.0 / (3.0 + 1.0); //Alpha aka EMA length. 3 length = 3*80ms=0.24s
  float rpm_const = 1071.43/fastTimer; //60000ms(1min) / ticks per rotation / fasttimer
  float rps_const = 112.23/fastTimer; //1000ms(1s) / ticks per rotation / fasttimer
  
  int ticks = countA-countAold;
  float rpm_new = ticks*rpm_const;
  float rps_new = ticks*rps_const;
  rpm = rpm * (1-alpha) + rpm_new * alpha;
  rps = rps * (1-alpha) + rps_new * alpha;
  countAold = countA;
}

void printInfo(){
  Serial.println("");
  Serial.print("pitch Angle  = "); Serial.println(angle_pitch_output);
  Serial.print("pitch Angle abs = "); Serial.println(abs(safe_angle));
  Serial.print("pitch Angle measured = "); Serial.println(angle_pitch);
  Serial.print("Position: "); Serial.println(countA);
  Serial.print("Position (m): "); Serial.println(countA/174.76); //r*2pi
  Serial.print("Full Rotations: "); Serial.println(countA/56.0); //ca. 56 tick per rotation
  Serial.print("Rads rotated: "); Serial.println(countA/8.91); //ca. 56 tick per rotation, 6.26 rads per rotation
  Serial.print("RPM: "); Serial.println(rpm); //ca. 56 tick per rotation
  Serial.print("Rads per second: "); Serial.println(rps); //ca. 56 tick per rotation, 6.26 rads per rotation
}

void setSpeed(){
  if(abs(safe_angle)<50 ){
    //speed = 8*safe_angle;
    float position_m = countA/174.76;
    float angle_r = angle_pitch_output * 0.318;
    speed = inputToControlSystem(position_m, angle_r);
    speed *= 22;
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
    speed = constrain(speed, 0, 250);
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
