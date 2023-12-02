/* 
This code is to move the right arm. The pillar approach is used for the discs
The total movements should be implemented on both arms.
Project: Hanoi Droid Capstone
Camosun College
Fall 2023

Righ arm pillars movements:
1 to 3, 1 to 2,  2 to 1, 
Left arm:
3 to 2, 2 to 3.
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

p0 is the rest position, and p1, p2 and p3 the pillars respectively


**Note: beacuse many functions will be mirrored based on the arm, they will have the same name and the difference will be the 'r' o 'l' letter precendent to the name. ie: rGoToHover0(), rUseMagnet()


*/


#include <Servo.h>

#define rMagnetPin A0


// servo name declaration
Servo rthumb, rindex, rmajeur, rpinky, rring, rbicep, rrotate, rshoulder, rclavi;

//global variables
char rMagnetInUse = 0;  // indicates if the magnet is on or off
char rRestPosition = 1;  // indicates if the robot arm is in rest position

//functions declaration
void rUseMagnet(void);  //function used to turn on or off the magnet
void rGoToHover0(void);  //function that send commands to the servomotors to go to the hover0 position


void setup() {

  //attach all the the servos names to a specific pin in the board (UNO)
  rthumb.attach(2);
  rindex.attach(3);
  rmajeur.attach(4);
  rpinky.attach(6);
  rring.attach(7);
  rbicep.attach(8);
  rrotate.attach(9);
  rshoulder.attach(10);
  rclavi.attach(11);

  Serial.begin(9600);


  pinMode(rMagnetPin, OUTPUT);  //this pin is the one to turn on/off the magnet


  //all the servos to rest position or p0
  rthumb.write(90);
  rindex.write(90);
  rrotate.write(80);
  rshoulder.write(60);
  rbicep.write(110);
  rclavi.write(105);
  // rclavi.write(98);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int newPosition;

    
    if (input == '1') {

              rGoToHover0();
        rRestPosition = 0;
      
    }
    
    // move  from the rest and go to catch disc in pillar 1
   else if (input == '2') {

      if (rRestPosition == 1) {
        rGoToHover0();
        rRestPosition = 0;
      }


      //go to hover1
      rshoulder.write(120);
      rrotate.write(40);
      delay(2000);
      rclavi.write(120);
      delay(1000);
      rbicep.write(135);
      delay(1000);




      //go to pillar 1
      rrotate.write(20);
      delay(2000);
      rshoulder.write(90);
      delay(3000);
      //turn on the magnet to catch the disc
      rUseMagnet();
      delay(2000);

      // hover1
      rshoulder.write(120);
      rrotate.write(40);
      delay(2000);
      rclavi.write(115);
      delay(1000);
      rbicep.write(135);
      delay(1000);
    }

    // from hover1 to pillar 2


//  IMPORTANT NOTE: the following commented code is for a pillar that position was causing problems when reaching pillar3, using right arm
// the uncommented code the pillar 2 is lowe
  /*  //  catch disc in pillar 2 
  else if (input == '2') {

//this code is for prevention, from going from a p0 position directly to the hover 1, or hover 2 or hover 3.
      if (rRestPosition == 1) {
        rGoToHover0();
        rRestPosition = 0;
      }


      //hover 2
      rshoulder.write(120);
      rclavi.write(105);
      rbicep.write(135);
      delay(2000);
      rrotate.write(30);
      delay(2000);

      //go to pillar 2

      rclavi.write(105);
      rrotate.write(25);
      delay(1000);
      rshoulder.write(95);
      delay(3000);
      rUseMagnet();
      delay(1000);


      //go to hover2
      rshoulder.write(120);
      rclavi.write(105);
      rbicep.write(135);
      delay(2000);
      rrotate.write(30);
      delay(2000);

    } */

// go and catch pillar2 disc
 else if (input == '3') {

//this code is for prevention, from going from a p0 position directly to the hover 1, or hover 2 or hover 3.
      if (rRestPosition == 1) {
        rGoToHover0();
        rRestPosition = 0;
      }


      //hover 2
      rshoulder.write(120);
      rclavi.write(97);
      rbicep.write(120);
      delay(2000);
      rrotate.write(25);
      delay(2000);

      //go to pillar 2

      rclavi.write(97);
      rrotate.write(25);
      delay(1000);
      rshoulder.write(95);
      delay(3000);
      rUseMagnet();
      delay(1000);


      //go to hover2
      rshoulder.write(120);
      rclavi.write(97);
      rbicep.write(120);
      delay(2000);
      rrotate.write(25);
      delay(2000);

    }


    else if (input == '4') {  // GO TO PILLAR 3

      if (rRestPosition == 1) {
        rGoToHover0();
        rRestPosition = 0;
      }


      // got to hover 3
      rshoulder.write(120);
      rclavi.write(95);
      rbicep.write(135);
      delay(2000);
      rrotate.write(10);
      delay(2000);


      //go to pillar 3
      rrotate.write(10);
      delay(2000);
      rshoulder.write(93);
      delay(3000);
      rUseMagnet();
      delay(1000);


      //go to hover3
      rshoulder.write(120);
      rclavi.write(95);
      rbicep.write(135);
      delay(2000);
      rrotate.write(10);
      delay(2000);

    }

    else if (input == '5') {  // GO TO REST

      rGoToHover0();

      //go to p0 or rest

      rrotate.write(80);
      rshoulder.write(60);
      rbicep.write(110);
      rclavi.write(105);
      rRestPosition = 1;

    }

    else if (input == '6') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        rring.write(newPosition);
        Serial.println("Servo 5 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '8') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        rbicep.write(newPosition);
        Serial.println("BICEP position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '9') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        rrotate.write(newPosition);
        Serial.println("ROTATE position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'A') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        rshoulder.write(newPosition);
        Serial.println("SHOULDER position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'B') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        rclavi.write(newPosition);
        Serial.println("CLAVI position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }
  }
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


void rGoToHover0() {
  //go to hover 0
  
  rshoulder.write(110);
   rclavi.write(120);
  delay(1000);

  rrotate.write(80);
  rbicep.write(130);
  delay(2000);
}
