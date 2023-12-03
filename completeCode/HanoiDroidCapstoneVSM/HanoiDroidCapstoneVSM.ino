/*
The following code is part of the capstone HANOI DROID -  Camosun College. Term: Fall 2023
Purpose: control a set of servomotors that are part of the Inmoov Robot (https://inmoov.fr/), moving the arm to reach discs and solve the Hanoi Towers Game.
It is heavily supported with a Python program that using OpenCV detects the discs position 
Hardware: Ardunio Nano Every, Adafruit 16-Channel 12-bit PWM/Servo Driver - I2C interface - PCA9685

Hanoi complete set of movements:
1 to 3,  1 to 2, 3 to 2, 1 to 3, 2 to 1, 2 to 3, 1 to 3.


The strategy:

From the target position, we need to reach a hover position before, after, and between each target, the hover position is mandatory. I similar like a manual gearbox of a car, before moving between the gears,
it is necesary to go to a kind of transition level.


h0-----h1------h2------h3
|       |      |        |
|       |      |        |
|       |      |        |
p0      p1     p2       p3

p0 is the rest position, and p1, p2 and p3 the positions respectively

Command Codes for movements:

S (uppercase): start the robot: this for initalize the robot and rise the hand to start the movements. from p0 - h0. It is suppposed the Robot rest in p0
a:  movement disc from 1 to 3. This is h1-p1-h1-h3-p3-h3
b:  movement disc from 1 to 2. this is h1-p1-h1-h2-p2-h2
c:  movement disc from 3 to 2. this is h3-p3-h3-h2-p2-h2
d:  movement disc from 1 to 3. this is h1-p1-h1-h3-p3-h3
e:  movement disc from 2 to 1. this is h2-p2-h2-h1-p1-h1
f:  movement disc from 2 to 3. this is h2-p2-h2-h3-p3-h3
g:  movement disc from 1 to 3. this is h1-p1-h1-h3-p3-h3
R (uppercase): rest. Send the robot arm to the rest position. h0 - p0

*/

//---------LIBRARIES-------------
#include <Adafruit_PWMServoDriver.h>
//#include <LiquidCrystal.h>
//---------END OF LIBRARIES-------------




//----------MACROS -------------------
#define SERVOMIN 80
#define SERVOMAX 600
#define SERVO_FREQ 50
#define rMagnetPin 7  //Digital pin D7
//--------END OF MACROS-----------------------


//-------------OBJECTS DECLARATION-------------------
Adafruit_PWMServoDriver pwmr = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwml = Adafruit_PWMServoDriver(0x41);
//-------------END OF OBJECTS DECLARATION-------------------



//--------------GLOBAL VARIABLES--------------
uint8_t rthumb = 1;     //thumb
uint8_t rindex = 2;     //index
uint8_t rmajeur = 3;    //majeur
uint8_t rpinky = 4;     //pinky
uint8_t rring = 5;      //ring
uint8_t rbicep = 6;     //bicep
uint8_t rrotate = 7;    //rotate
uint8_t rshoulder = 8;  //shoulder
uint8_t rclavi = 9;     //clavi

uint8_t lthumb = 1;     //thumb
uint8_t lindex = 2;     //index
uint8_t lmajeur = 3;    //majeur
uint8_t lpinky = 4;     //pinky
uint8_t lring = 5;      //ring
uint8_t lbicep = 6;     //bicep
uint8_t lrotate = 7;    //rotate
uint8_t lshoulder = 8;  //shoulder
uint8_t lclavi = 9;     //clavi

uint8_t servonum = 0;
bool robotStarted = false;

//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

char rMagnetInUse = 0;  // indicates if the magnet is on or off

//--------END OF GLOBAL VARIABLES ---------------------------------

//---------FUNCTION DECLARATION--------------------
void rUseMagnet(void);      //function used to turn on or off the magnet -  right arm. this Function works in alternate mode.
void rGoToHover0(void);     //function that send commands to the servomotors to go to the hover0 position
void rGoToHover1(void);     //function that send commands to the servomotors to go to the hover1 position
void rGoToHover2(void);     //function that send commands to the servomotors to go to the hover2 position
void rGoToHover3(void);     //function that send commands to the servomotors to go to the hover3 position
void rGoToPosition0(void);  //function that send commands to the servomotors to go to the rest position
void rGoToPosition1(void);  //function that send commands to the servomotors to go to the disc1 position
void rGoToPosition2(void);  //function that send commands to the servomotors to go to the disc2 position
void rGoToPosition3(void);  //function that send commands to the servomotors to go to the disc3 position
//---------END OF FUNCTION DECLARATION--------------------


void setup() {


  //-----DEBUGGIN : DELETE WHEN FINISHES------------------

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);

  //-----END OF DEBUGGIN : DELETE WHEN FINISHES------------------

  
  pwmr.begin();
  pwmr.setOscillatorFrequency(27000000);
  pwmr.setPWMFreq(SERVO_FREQ);
  delay(10);
  //Serial.println("Servo Test");





  // set up the LCD's number of columns and rows:
  //lcd.begin(16, 2);
  // Print a message to the LCD to test is working
  //lcd.print("hello, world!");
  delay(2000);
  // open the serial port:
  Serial.begin(115200);

  //this pin is the one to turn on/off the magnet. It setup as digital output
  pinMode(rMagnetPin, OUTPUT);
  /*
  // Set initial positions for each servo (0 to 180 degrees)
  int initialPositionsr[] = { 90, 90, 90, 90, 90, 110, 80, 60, 110 };  // Rest positions to Right Arm
  int initialPositionsl[] = { 50, 50, 50, 50, 50, 60, 90, 10, 100 };   // Rest positions left arm

  for (int servoPinr = 0; servoPinr < 9; servoPinr++) {
    if (servoPinr < sizeof(initialPositionsr) / sizeof(initialPositionsr[0])) {
      int degreer = initialPositionsr[servoPinr];
      uint16_t initialPulser = map(degreer, 0, 180, SERVOMIN, SERVOMAX);
      pwmr.setPWM(servoPinr, 0, initialPulser);
    }
  }

  for (int servoPinl = 0; servoPinl < 9; servoPinl++) {
    if (servoPinl < sizeof(initialPositionsl) / sizeof(initialPositionsl[0])) {
      int degreel = initialPositionsl[servoPinl];
      uint16_t initialPulsel = map(degreel, 0, 180, SERVOMIN, SERVOMAX);
      pwml.setPWM(servoPinl, 0, initialPulsel);
    }
  }

  */
}


void loop() {
  /*
  lcd.setCursor(0, 1);
  
  if (Serial.available() > 0) {
    String msg = Serial.readString();
    lcd.print(msg);
  }
  */

  if (Serial.available() > 0) {

    char receivedChar = Serial.read();





    //Serial.print("Received character: ");
    //Serial.println(receivedChar);

    if (!robotStarted && receivedChar == 'S') {
      // Check for the "start" command sent by the Python script
      startRobot();
      rGoToHover0();


      digitalWrite(LED_BUILTIN, HIGH);  // DEBUGGING
      delay(2000);                      //DEBUGGING


      return;
    }


    //  Serial.print("Received command for servoPin: ");
    // Serial.println(commandMov);

    switch (receivedChar) {

      case 'a':  // movement disc from 1 to 3. This is h1-p1-h1-h3-p3-h3

    digitalWrite(rMagnetPin, HIGH);  // DEBUGGING
    delay(2000);            // DEBUGGING

        rGoToHover1();
        rGoToPosition1();
        rUseMagnet();
        delay(2000);
        rGoToHover1();
        rGoToHover3();
        rGoToPosition3();
        rUseMagnet();
        delay(1000);
        rGoToHover3();

                digitalWrite(2, HIGH);  // DEBUGGING
        delay(2000);            // DEBUGGING



        break;


      case 'b':  //movement disc from 1 to 2. this is h1-p1-h1-h2-p2-h2
       
        rGoToHover1();
        rGoToPosition1();
        rUseMagnet();
        delay(2000);
        rGoToHover1();
        rGoToHover2();
        rGoToPosition2();
        rUseMagnet();
        delay(1000);
        rGoToHover2();




        digitalWrite(3, HIGH);  // DEBUGGING
        delay(2000);            // DEBUGGING

        break;

      case 'c':  // movement disc from 3 to 2. this is h3-p3-h3-h2-p2-h2

        rGoToHover3();
        rGoToPosition3();
        rUseMagnet();
        delay(1000);
        rGoToHover3();
        rGoToHover2();
        rGoToPosition2();
        rUseMagnet();
        delay(1000);
        rGoToHover2();


        digitalWrite(LED_BUILTIN, LOW);  // DEBUGGING
        delay(2000);                     // DEBUGGING

        break;


      case 'd':  //movement disc from 1 to 3. this is h1-p1-h1-h3-p3-h3

        rGoToHover1();
        rGoToPosition1();
        rUseMagnet();
        delay(1000);
        rGoToHover1();
        rGoToHover3();
        rGoToPosition3();
        rUseMagnet();
        delay(1000);
        rGoToHover3();


        digitalWrite(2, LOW);  // DEBUGGING
        delay(2000);           // DEBUGGING

        break;

      case 'e':  //movement disc from 2 to 1. this is h2-p2-h2-h1-p1-h1


        rGoToHover2();
        rGoToPosition2();
        rUseMagnet();
        delay(1000);
        rGoToHover2();
        rGoToHover1();
        rGoToPosition1();
        rUseMagnet();
        delay(1000);
        rGoToHover1();

        digitalWrite(3, LOW);  // DEBUGGING
        delay(2000);           // DEBUGGING

        break;


      case 'f':  //movement disc from 2 to 3. this is h2-p2-h2-h3-p3-h3

        rGoToHover2();
        rGoToPosition2();
        rUseMagnet();
        delay(1000);
        rGoToHover2();
        rGoToHover3();
        rGoToPosition3();
        rUseMagnet();
        delay(1000);
        rGoToHover3();


        digitalWrite(LED_BUILTIN, HIGH);  // DEBUGGING



        break;

      case 'g':  //movement disc from 1 to 3. this is h1-p1-h1-h3-p3-h3

        rGoToHover1();
        rGoToPosition1();
        rUseMagnet();
        delay(2000);
        rGoToHover1();
        rGoToHover3();
        rGoToPosition3();
        rUseMagnet();
        delay(1000);
        rGoToHover3();

        digitalWrite(2, HIGH);  // DEBUGGING



        break;

      case 'R':  // Rest. Send the robot arm to the rest position. h0 - p0

        rGoToHover0();
        rGoToPosition0();
        digitalWrite(rMagnetPin, LOW);

        rMagnetInUse = 0;
        robotStarted = false;


        digitalWrite(3, HIGH);  // DEBUGGING

        break;

      default:
        break;
    }
  }
}

//------------- CUSTOM FUNCTION DEFINITIONS--------------

void setServoPulse(uint8_t n, double pulse) {
  double pulselength;
  pulselength = 1000000;
  pulselength /= SERVO_FREQ;
  pulselength /= 4096;
  pulse *= 1000;
  pulse /= pulselength;
  pwmr.setPWM(n, 0, pulse);
}

void startRobot() {
  // Implement your robot startup logic here
  robotStarted = true;
  // Add any necessary actions to start the robot

  // Add any additional logic or commands needed when the robot starts

  return;  // Exit the function to prevent further execution in the loop
}


void rGoToHover0() {
  pwmr.setPWM(rshoulder, 0, 398);  // 110
  pwmr.setPWM(rclavi, 0, 427);     // 120
  delay(1000);
  pwmr.setPWM(rrotate, 0, 311);  // 80
  pwmr.setPWM(rbicep, 0, 456);   // 130
  delay(2000);
}


void rGoToHover1() {
  pwmr.setPWM(rshoulder, 0, 427);  // 120
  pwmr.setPWM(rrotate, 0, 196);    // 40
  delay(2000);
  pwmr.setPWM(rclavi, 0, 427);  // 120
  delay(1000);
  pwmr.setPWM(rbicep, 0, 470);  // 135
  delay(1000);
}

void rGoToHover2() {

  pwmr.setPWM(rshoulder, 0, 427);  // 120
  pwmr.setPWM(rclavi, 0, 360);     // 97
  pwmr.setPWM(rbicep, 0, 427);     // 120
  delay(2000);
  pwmr.setPWM(rrotate, 0, 152);  // 25
  delay(2000);
}

void rGoToHover3() {

  pwmr.setPWM(rshoulder, 0, 427);  // 120
  pwmr.setPWM(rclavi, 0, 355);     // 95
  pwmr.setPWM(rbicep, 0, 470);     // 135
  delay(2000);
  pwmr.setPWM(rrotate, 0, 109);  // 10
  delay(2000);
}


void rGoToPosition0() {

  pwmr.setPWM(rrotate, 0, 311);    // 80
  pwmr.setPWM(rshoulder, 0, 253);  // 60
  pwmr.setPWM(rbicep, 0, 398);     // 110
  pwmr.setPWM(rclavi, 0, 398);     // 110
}


void rGoToPosition1() {

  pwmr.setPWM(rrotate, 0, 138);  // 20
  delay(2000);
  pwmr.setPWM(rshoulder, 0, 340);  // 90
  delay(3000);
}

void rGoToPosition2() {

  pwmr.setPWM(rclavi, 0, 360);   // 97
  pwmr.setPWM(rrotate, 0, 152);  // 25
  delay(1000);
  pwmr.setPWM(rshoulder, 0, 354);  // 95
  delay(3000);
}

void rGoToPosition3() {

  pwmr.setPWM(rrotate, 0, 109);  // 10
  delay(2000);
  pwmr.setPWM(rshoulder, 0, 349);  // 93
  delay(3000);
}

void rUseMagnet() {

  if (rMagnetInUse == 0) {
    digitalWrite(rMagnetPin, HIGH);
    // digitalWrite(33, HIGH);
    rMagnetInUse = 1;
    Serial.println("magnets on");

  } else {
    digitalWrite(rMagnetPin, LOW);
    //digitalWrite(33, LOW);
    rMagnetInUse = 0;
    Serial.println("magnets off");
  }
}

//------------- END OF CUSTOM FUNCTION DEFINITIONS--------------
