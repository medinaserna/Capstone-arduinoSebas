#include <Adafruit_PWMServoDriver.h>
#include <LiquidCrystal.h>

Adafruit_PWMServoDriver pwmr = Adafruit_PWMServoDriver(0x40);
Adafruit_PWMServoDriver pwml = Adafruit_PWMServoDriver(0x41);

#define SERVOMIN  80
#define SERVOMAX  600
#define SERVO_FREQ 50

uint8_t rthumb = 1; //thumb
uint8_t  rindex = 2; //index
uint8_t  rmajeur = 3; //majeur
uint8_t  rpinky = 4; //pinky
uint8_t  rring  = 5; //ring
uint8_t  rbicep = 6; //bicep
uint8_t  rrotate = 7; //rotate
uint8_t  rshoulder = 8; //shoulder
uint8_t  rclavi = 9; //clavi

uint8_t lthumb = 1; //thumb
uint8_t  lindex = 2; //index
uint8_t  lmajeur = 3; //majeur
uint8_t  lpinky = 4; //pinky
uint8_t  lring  = 5; //ring
uint8_t  lbicep = 6; //bicep
uint8_t  lrotate = 7; //rotate
uint8_t  lshoulder = 8; //shoulder
uint8_t  lclavi = 9; //clavi



uint8_t servonum = 0;
bool robotStarted = false;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  pwmr.begin();  
  pwmr.setOscillatorFrequency(27000000);
  pwmr.setPWMFreq(SERVO_FREQ);
  delay(10);
  //Serial.println("Servo Test");

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD to test is working
  lcd.print("hello, world!");
  delay(2000);
  // open the serial port:
  Serial.begin(9600);

  // Set initial positions for each servo (0 to 180 degrees)
  int initialPositionsr[] = {90, 120, 80, 60, 110, 90, 75, 135}; // Example positions

  for (int servoPinr = 0; servoPinr < 8; servoPinr++) {
    if (servoPinr < sizeof(initialPositionsr) / sizeof(initialPositionsr[0])) {
      int degreer = initialPositionsr[servoPinr];
      uint16_t initialPulser = map(degreer, 0, 180, SERVOMIN, SERVOMAX);
      pwmr.setPWM(servoPinr, 0, initialPulser);
    }
  }

    int initialPositionsl[] = {90, 120, 80, 60, 110, 90, 75, 135}; // Example positions

  for (int servoPinl = 0; servoPinl < 8; servoPinl++) {
    if (servoPinl < sizeof(initialPositionsl) / sizeof(initialPositionsl[0])) {
      int degreel = initialPositionsl[servoPinl];
      uint16_t initialPulsel = map(degreel, 0, 180, SERVOMIN, SERVOMAX);
      pwml.setPWM(servoPinl, 0, initialPulsel);
    }
  }

}
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
  Serial.println("Robot has started.");
  // Add any additional logic or commands needed when the robot starts
  return;  // Exit the function to prevent further execution in the loop
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
        return;
      }

      int servoPin = receivedChar - '0';  // Convert character to integer
      Serial.print("Received command for servoPin: ");
      Serial.println(servoPin);

      switch (servoPin) {
        case 0:
          // Rest to pillar 1
          Serial.println("Moving to Pillar 1");
          pwmr.setPWM(rclavi, 0, 427); // 120
          delay(1000);
          pwmr.setPWM(rshoulder, 0, 456); // 130
          delay(1000);
          pwmr.setPWM(rbicep, 0, 470); // 135
          delay(1000);
          pwmr.setPWM(rrotate, 0, 138); // 20
          delay(1000);
          pwmr.setPWM(rshoulder, 0, 340); // 90
          delay(1000);
          break;
        case 1:
          // Leaving pillar 1
          Serial.println("Leaving Pillar 1");
          pwmr.setPWM(rrotate, 0, 196); // 40
          delay(1000);
          pwmr.setPWM(rshoulder, 0, 398); // 110
          delay(1000);
          break;
        case 2:
          // Go to pillar 2
         //Srial.println("Moving to Pillar 2");
          pwmr.setPWM(rclavi, 0, 196); // 40
          delay(1000);
          pwmr.setPWM(rrotate, 0, 167); // 30
          delay(1000);
          pwmr.setPWM(rshoulder, 0, 354); // 95
          break;
        case 3:
          // Leave Pillar 2
          Serial.println("Leaving Pillar 2");
          pwmr.setPWM(rshoulder, 0, 398); // 110
          delay(1000);
          pwmr.setPWM(rclavi, 0, 354); // 95
          delay(1000);
          break;
        case 4:
          // Go to Pillar 3
          Serial.println("Moving to Pillar 3");
          pwmr.setPWM(rshoulder, 0, 80); // 0
          delay(1000);
          pwmr.setPWM(rclavi, 0, 369); // 100
          delay(1000);
          break;
        case 5:
          // Go to Pillar 3
          Serial.println("Moving to Pillar 3");
          pwmr.setPWM(rshoulder, 0, 427); // 120
          delay(1000);
          pwmr.setPWM(rrotate, 0, 311); // 80
          delay(1000);
          pwmr.setPWM(rclavi, 0, 383); // 105
          delay(1000);
          pwmr.setPWM(rshoulder, 0, 253); // 60
          delay(1000);
          pwmr.setPWM(rbicep, 0, 398); // 110
          delay(1000);
          break;
      }
    }
  
}
