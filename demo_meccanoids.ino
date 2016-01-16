#include <MeccaBrain.h>

//To try this example you'll need the following:
//0) Meccanoid G15 in its human form
//1) Any Arduino
//2) Motor shield or motor driver, to drive robot's wheels. I tried the one based on L293D and it was quite decent
//3) Tamiya Mini male connector with wires - to connect to the robots' battery
//4) Male connectors: CWF-2 to connect one motor and PLS-2 to connect another
//5) 3 resistors of 22 kOhm and 3 resistors of 1 kOhm - to make pullup resistors (according to the manual)
//6) Download the library: http://cdn.meccano.com/open-source/meccanoid-library.zip
//7) You can also check out the reference material, to understand, how do the Smart Modules work
//   http://cdn.meccano.com/open-source/Meccano_SmartModuleProtocols_2015.pdf

//Pins to connect Meccanoids' servos, where chain 1 is left arm, chain 2 is head and chain 3 is right arm
//pins can be any digital pins, not necessary PWM
const int chainPin1 = 5;
const int chainPin2 = 6;
const int chainPin3 = 7;

//pins to set speed on motor driver
const int leftSpeedPin = 10;
const int rightSpeedPin = 11;

//pins to set direction on motor driver
const int leftDirPin = 12;
const int rightDirPin = 13;

MeccaBrain chain1(chainPin1); //each chain allows to plug up to 4 smart modules
MeccaBrain chain2(chainPin2);
MeccaBrain chain3(chainPin3);

//Commands for driving robots' motors
void turnLeft(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, 0);
  digitalWrite(leftDirPin, LOW);
  digitalWrite(rightDirPin, HIGH);
}

void turnRight(int speed)
{
  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, HIGH);
  digitalWrite(rightDirPin, LOW);
}

void rotateLeft(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, LOW);
  digitalWrite(rightDirPin, HIGH);
}

void rotateRight(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, HIGH);
  digitalWrite(rightDirPin, LOW);
}

void goForward(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, HIGH);
  digitalWrite(rightDirPin, HIGH);
}

void goBackward(int speed)
{
  analogWrite(leftSpeedPin, speed);
  analogWrite(rightSpeedPin, speed);
  digitalWrite(leftDirPin, LOW);
  digitalWrite(rightDirPin, LOW);
}

void stay()
{
  analogWrite(leftSpeedPin, 0);
  analogWrite(rightSpeedPin, 0);
}

//Joints mapping:
//Chain 1 - Left Arm. 1.0 is Arm Roll, 1.1 is Arm Pitch, 1.2 is Elbow
//Chain 2 - Head. 2.0 is Head Yaw, 2.1 is Head Roll, 2.2 is LEDs
//Chain 3 - Right Arm. 3.0 is Arm Roll, 3.1 is Arm Pitch, 3.2 is Elbow

const byte LEFT_ARM_ROLL=0; 
const byte LEFT_ARM_PITCH=1; 
const byte LEFT_ARM_ELBOW=2;
const byte HEAD_YAW=3; 
const byte HEAD_ROLL=4;
const byte RIGHT_ARM_ROLL=5; 
const byte RIGHT_ARM_PITCH=6; 
const byte RIGHT_ARM_ELBOW=7;

//jointName is LEFT_ARM_ROLL etc
//pos is 0...255
void setJoint(byte jointName, byte pos)
{
  switch(jointName){
    case LEFT_ARM_ROLL:
      chain1.setServoPosition(0, pos);
      chain1.communicate();
      break;
    case LEFT_ARM_PITCH:
      chain1.setServoPosition(1, pos);
      chain1.communicate();
      break;
    case LEFT_ARM_ELBOW:
      chain1.setServoPosition(2, pos);
      chain1.communicate();
      break;
    case HEAD_YAW:
      chain2.setServoPosition(0, pos);
      chain2.communicate();
      break;
    case HEAD_ROLL:
      chain2.setServoPosition(1, pos);
      chain2.communicate();
      break;      
    case RIGHT_ARM_ROLL:
      chain3.setServoPosition(0, pos);
      chain3.communicate();
      break;
    case RIGHT_ARM_PITCH:
      chain3.setServoPosition(1, pos);
      chain3.communicate();
      break;
    case RIGHT_ARM_ELBOW:
      chain3.setServoPosition(2, pos);
      chain3.communicate();
      break;
  }
}

//Set the color of eye LEDS. red, green and blue are from 0 to 7 (0 - no color, 7 - max color). 
//fadetime is from 0 to 7 and means the speed of color change (0 - immediate change, 7 - longest change)
//example: setColor(7,0,0,3) means change color to red with average speed
void setEyesColor(byte red, byte green, byte blue, byte fadetime)
{
  chain2.setLEDColor(red, green, blue, fadetime);
  chain2.communicate();
}

//Servo colors
const byte JOINT_BLACK=0xF0;  
const byte JOINT_RED=0xF1; 
const byte JOINT_GREEN=0xF2; 
const byte JOINT_BROWN=0xF3; 
const byte JOINT_BLUE=0xF4; 
const byte JOINT_VIOLET=0xF5; 
const byte JOINT_SEA=0xF6; 
const byte JOINT_WHITE=0xF7;

//set the servo color
//for example, setJointColor(RIGHT_ARM_ELBOW, JOINT_VIOLET)
void setJointColor(byte jointName, byte color)
{
  switch(jointName){
    case LEFT_ARM_ROLL:
      chain1.setServoColor(0, color);
      chain1.communicate();
      break;
    case LEFT_ARM_PITCH:
      chain1.setServoColor(1, color);
      chain1.communicate();
      break;
    case LEFT_ARM_ELBOW:
      chain1.setServoColor(2, color);
      chain1.communicate();
      break;
    case HEAD_YAW:
      chain2.setServoColor(0, color);
      chain2.communicate();
      break;
    case HEAD_ROLL:
      chain2.setServoColor(1, color);
      chain2.communicate();
      break;      
    case RIGHT_ARM_ROLL:
      chain3.setServoColor(0, color);
      chain3.communicate();
      break;
    case RIGHT_ARM_PITCH:
      chain3.setServoColor(1, color);
      chain3.communicate();
      break;
    case RIGHT_ARM_ELBOW:
      chain3.setServoColor(2, color);
      chain3.communicate();
      break;
  }
}

void setup() {
  pinMode(chainPin1, OUTPUT);
  pinMode(chainPin2, OUTPUT);
  pinMode(chainPin3, OUTPUT);
  pinMode(leftSpeedPin, OUTPUT);
  pinMode(rightSpeedPin, OUTPUT);
  pinMode(leftDirPin, OUTPUT);
  pinMode(rightDirPin, OUTPUT);
  Serial.begin(9600);

  //"Discover" all the modules (make them blue-colored instead of green-colored)
  //for some unknown reason, I have to repeat it from time to time
  for (int i = 0; i < 50; i++)
  {
    chain1.communicate();
    chain2.communicate();
    chain3.communicate();
  }
  //delay to be sure that all modules are ready
  //if some module is "not discovered" than it will remain green and later this module will behave strangely
  delay(2000);
}

void loop() {

  //make every joint of the robot a different color just for fun
  //so that we cycle through all the possible colors and joints
  for(int i=0; i<7; i++)
  {
    setJointColor(i, JOINT_BLACK+i);
  }

  //move forward, backward, left and right
  goForward(255);
  delay(3000);
  stay();
  delay(1000);
  
  goBackward(255);
  delay(2000);
  stay();
  delay(1000);

  rotateLeft(255);
  delay(2000);
  stay();
  delay(1000);

  rotateRight(255);
  delay(2000);
  stay();
  delay(1000);

  //move some joints 

  //first, put head into middle position
  setJoint(HEAD_ROLL, 120);
  delay(1000);

  //look around
  setJoint(HEAD_YAW, 50);
  delay(1000);
  setJoint(HEAD_YAW, 210);
  delay(1000);
  setJoint(HEAD_YAW, 128);
  delay(1000);

  //Make funny head jestures
  setJoint(HEAD_ROLL, 60);
  delay(500);
  setJoint(HEAD_ROLL, 120);
  delay(500);
  setJoint(HEAD_ROLL, 180);
  delay(500);
  setJoint(HEAD_ROLL, 120);
  delay(1000);

//bring both arms down. They are inverted, so that left arm mirrors right arm
  setJoint(LEFT_ARM_ROLL, 255);
  setJoint(RIGHT_ARM_ROLL, 0);

//set both elbows in middle position
  setJoint(LEFT_ARM_ELBOW, 127);
  setJoint(RIGHT_ARM_ELBOW, 127);
  delay(1000);

//raise arms  
  setJoint(LEFT_ARM_ROLL, 0);
  setJoint(RIGHT_ARM_ROLL, 255);
  delay(3000);

//bring both arms to the middle
  setJoint(LEFT_ARM_ROLL, 127);
  setJoint(RIGHT_ARM_ROLL, 127);

//move elbows as if he was fighting
  setJoint(LEFT_ARM_ELBOW, 127);
  delay(500);

  setJoint(LEFT_ARM_ELBOW, 0);
  setJoint(RIGHT_ARM_ELBOW, 127);
  delay(500);

  setJoint(LEFT_ARM_ELBOW, 127);
  setJoint(RIGHT_ARM_ELBOW, 255);
  delay(500);

  setJoint(LEFT_ARM_ELBOW, 0);
  setJoint(RIGHT_ARM_ELBOW, 127);
  delay(500);

//set both elbows in middle position
  setJoint(LEFT_ARM_ELBOW, 127);
  setJoint(RIGHT_ARM_ELBOW, 127);
  delay(1000);

//bring both arms down
  setJoint(LEFT_ARM_ROLL, 255);
  setJoint(RIGHT_ARM_ROLL, 0);
  delay(1000); 

  //loop through all the possible eyes colors
  //We have 3 bits per channel
  for(int j=0; j<512; j++)
  {
    byte red = (j >> 4) & 0x07;
    byte green = (j >> 2) & 0x07;
    byte blue = j & 0x07;
    setEyesColor(red, green, blue, 0);        
  }

}
