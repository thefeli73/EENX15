//gyroscope stuff
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;

//temporary variable to measure main loops
int temp_loops;

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
  //gyroscope
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_4_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_184_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);

  calibrateGyro();
  
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
  
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);


   //Subtract the offset values from the raw gyro values
  gyro_x = g.gyro.x;
  gyro_y = g.gyro.y;
  gyro_z = g.gyro.z;

  acc_x = a.acceleration.x;
  acc_y = a.acceleration.y;
  acc_z = a.acceleration.z;

  gyro_x -= gyro_x_cal;                                                
  gyro_y -= gyro_y_cal;                                                
  gyro_z -= gyro_z_cal;   
    previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds                                             
         
  //Gyro angle calculations 
  angle_pitch += gyro_x * elapsedTime * 180/PI;                                   //Calculate the traveled pitch angle and add this to the angle_pitch variable, rad/s ---> degrees
  angle_roll += gyro_y * elapsedTime * 180/PI ;                                    //Calculate the traveled roll angle and add this to the angle_roll variable
  //0.000001066 = 0.0000611 * (3.142(PI) / 180degr) sin function is in radians
  angle_pitch += angle_roll * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the roll angle to the pitch angel
  angle_roll -= angle_pitch * sin(gyro_z * 0.000001066);               //If the IMU has yawed transfer the pitch angle to the roll angel
  
  //Accelerometer angle calculations
  acc_total_vector = sqrt((acc_x*acc_x)+(acc_y*acc_y)+(acc_z*acc_z));  //Calculate the total accelerometer vector
  //57.296 = 1 / (3.142 / 180) The Arduino asin function is in radians
  angle_pitch_acc = asin((float)acc_y/acc_total_vector)* 57.296;       //Calculate the pitch angle
  angle_roll_acc = asin((float)acc_x/acc_total_vector)* -57.296;       //Calculate the roll angle
  
  angle_pitch_acc -= 0.0;                                              //Accelerometer calibration value for pitch
  angle_roll_acc -= 0.0;                                               //Accelerometer calibration value for roll

  if(set_gyro_angles){                                                 //If the IMU is already started
    angle_pitch = angle_pitch * 0.96 + angle_pitch_acc * 0.04;     //Correct the drift of the gyro pitch angle with the accelerometer pitch angle
    angle_roll = angle_roll * 0.96 + angle_roll_acc * 0.04;        //Correct the drift of the gyro roll angle with the accelerometer roll angle
  }
  else{                                                                //At first start
    angle_pitch = angle_pitch_acc;                                     //Set the gyro pitch angle equal to the accelerometer pitch angle 
    angle_roll = angle_roll_acc;                                       //Set the gyro roll angle equal to the accelerometer roll angle 
    set_gyro_angles = true;                                            //IMU started flag
  }
  
  // complementary filter
  angle_pitch_output = angle_pitch_output * 0.8 + angle_pitch * 0.2;   //Take 90% of the output pitch value and add 10% of the raw pitch value
  angle_roll_output = angle_roll_output * 0.8 + angle_roll * 0.2;      //Take 90% of the output roll value and add 10% of the raw roll value

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

void calibrateGyro() {
  for (int cal_int = 0; cal_int < 1000 ; cal_int ++){                  //Read the raw acc and gyro data from the MPU-6050 for 1000 times
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  gyro_x = g.gyro.x;
  gyro_y = g.gyro.y;
  gyro_z = g.gyro.z;
                                                 
    gyro_x_cal += g.gyro.x  ;                                            //Add the gyro x offset to the gyro_x_cal variable
    gyro_y_cal += g.gyro.y  ;                                           //Add the gyro y offset to the gyro_y_cal variable
    gyro_z_cal += g.gyro.z  ;                                            //Add the gyro z offset to the gyro_z_cal variable

    delay(3);                                                          //Delay 3us to have 250Hz for-loop
  }

  // divide by 1000 to get avarage offset
  gyro_x_cal /= 1000;                                                 
  gyro_y_cal /= 1000;                                                 
  gyro_z_cal /= 1000;                                                 

  loop_timer = micros();                                               //Reset the loop timer

  if (half_revolutionsA >= 20) { 
     rpmA = 30*1000/(millis() - timeoldA)*half_revolutionsA;
     timeoldA = millis();
     half_revolutionsA = 0;
     Serial.println(rpmA);
     Serial.print(" pitch Angle  = "); Serial.println(angle_pitch_output);
   }

 if (half_revolutionsB >= 20) { 
     rpmB = 30*1000/(millis() - timeoldB)*half_revolutionsB;
     timeoldB = millis();
     half_revolutionsB = 0;
     Serial.println(rpmB);
     Serial.print(" pitch Angle  = "); Serial.println(angle_pitch_output);
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
