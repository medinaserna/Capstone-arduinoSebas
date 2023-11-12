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

*/


#include <Servo.h>

Servo rthumb, rindex, rmajeur, rpinky, rring, rbicep, rrotate, rshoulder, rclavi;

//global variables
char rMagnetInUse = 0;
char restPosition = 1;

//functions defintions
void rUseMagnet(void);
void goToHover0(void);


void setup() {
  rthumb.attach(2);
  rindex.attach(3);
  rmajeur.attach(4);
  rpinky.attach(6);
  rring.attach(7);
  rbicep.attach(8);  //sep 2023: signal ok from arduino, servo not responding
  rrotate.attach(9);
  rshoulder.attach(10);
  rclavi.attach(11);  //sep 2023: signal ok from arduino, servo not responding
  Serial.begin(9600);


  pinMode(31, OUTPUT);  //this pin is the one to turn on/off the magnet

  //all the servos to rest position

  rthumb.write(90);
  rindex.write(90);
  rrotate.write(80);
  rshoulder.write(60);
  rbicep.write(110);
  rclavi.write(105);
 // rclavi.write(98);

  //
  //rUseMagnet(void); //at rest the magnet should be off
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int newPosition;

    // move  from the rest and go to catch disc in pillar 1
    if (input == '1') {
      
if (restPosition == 1){
goToHover0();
restPosition = 0;
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
      delay(2000);
      //turn on the magnet to catch the disc
      rUseMagnet();
      delay(2000);
      
      // hover1
        rshoulder.write(120);
           rrotate.write(40);
            delay(2000);
        rclavi.write(120);
      delay(1000);
      rbicep.write(135);
      delay(1000);
    }

    // from hover1 to pillar 2
    else if (input == '2') {

if (restPosition == 1){
goToHover0();
restPosition = 0;
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

      delay(2000);
      rUseMagnet();
delay(1000);


      //go to hover pillar2
      
       rshoulder.write(120);
    rclavi.write(105);
    rbicep.write(135);
      delay(2000);
      rrotate.write(30);
      delay(2000);

    }

    else if (input == '3') {
      
      if (restPosition == 1){
goToHover0();
restPosition = 0;
}
      
      
      // got to hover 3
      rshoulder.write(120);
      rclavi.write(95);
      rbicep.write(135);
      delay(2000);
       rrotate.write(0);
       delay(2000);
      
      
      //go to pillar 3

      rrotate.write(0);
      delay(2000);
      rshoulder.write(93);
      delay(2000);
      rUseMagnet();
delay (1000);


      //go to hover3
      rshoulder.write(120);
      rclavi.write(95);
      rbicep.write(135);
      delay(2000);
rrotate.write(0);

    }

    else if (input == '4') {
//go to hover 0
      rclavi.write(120);
      delay(1000);
      rshoulder.write(130);
       rrotate.write(80);
      delay(3000);
rbicep.write(110);
delay(1000);

//go to M0 or rest

  rrotate.write(80);
  rshoulder.write(60);
  rbicep.write(110);
  rclavi.write(105);
restPosition = 1;

    }

    else if (input == '5') {
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
    digitalWrite(31, HIGH);
    // digitalWrite(33, HIGH);
    rMagnetInUse = 1;
    Serial.println("magnets on");

  } else {
    digitalWrite(31, LOW);
    //digitalWrite(33, LOW);
    rMagnetInUse = 0;
    Serial.println("magnets off");
  }
}


void goToHover0() {
//go to hover 0
      rclavi.write(120);
      delay(1000);
      rshoulder.write(130);
       rrotate.write(80);
      delay(3000);
rbicep.write(110);
delay(1000);


}
