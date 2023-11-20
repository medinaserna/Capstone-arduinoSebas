/* 
This code is to move the left arm. The pillar approach is used for the discs
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

#define lMagnetPin 31

// servo name declaration
Servo lthumb, lindex, lmajeur, lpinky, lring, lbicep, lrotate, lshoulder, lclavi, jaw, head, head_rotate, toolPulley;

//global variables
char lMagnetInUse = 0;   // indicates if the magnet is on or off
char lRestPosition = 1;  // indicates if the robot arm is in rest position


//functions defintions
void lUseMagnet(void);   //function used to turn on or off the magnet
void lGoToHover0(void);  //function that send commands to the servomotors to go to the hover0 position

void setup() {


  //attach all the the servos names to a specific pin in the board (MEGA)
  lring.attach(2);
  lindex.attach(3);
  lmajeur.attach(4);
  jaw.attach(5);
  lpinky.attach(6);
  lthumb.attach(7);
  lbicep.attach(8);
  lrotate.attach(9);
  lshoulder.attach(10);
  lclavi.attach(11);
  head.attach(12);
  head_rotate.attach(13);
  // toolPulley.attach(45);
  Serial.begin(9600);

  //set up the controls pins for the magnets
  pinMode(lMagnetPin, OUTPUT);


  //BE CAREFUL. these are the rest positions
  lrotate.write(90);
  lshoulder.write(10);
  lbicep.write(60);
  lclavi.write(105);
  head.write(100);
  jaw.write(60);
  head_rotate.write(90);
  // toolPulley.write(90);
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int newPosition;

    // move from rest and go to the hover0 position
    if (input == '1') {


      if (lRestPosition == 1) {
        lGoToHover0();
        lRestPosition = 0;
      }


    }


    // go to pillar 3
    else if (input == '2') {

      //this code is for prevention, from going from a p0 position directly to the hover 1, or hover 2 or hover 3. This causes a crash with the arm and the shelves
      if (lRestPosition == 1) {
        lGoToHover0();
        lRestPosition = 0;
      }

      // hover 3 with left arm
      lshoulder.write(60);
      lclavi.write(120);
      lbicep.write(90);
      delay(2000);
      lrotate.write(35);
      delay(2000);

      // go to pillar 3
      lshoulder.write(30);
      delay(2000);
      lUseMagnet();
      delay(1000);

      // hover 3 with left arm
      lshoulder.write(60);
      lclavi.write(120);
      lbicep.write(90);
      delay(2000);
      lrotate.write(35);
      delay(2000);



    }


//go and catch pillar 2
    else if (input == '3') {

      // hover 2 with left arm
      lshoulder.write(70);
      lclavi.write(100);
      lbicep.write(60);
      delay(2000);
      lrotate.write(20);
      delay(2000);

      // go to pillar 2
      lshoulder.write(50);
      delay(2000);
      lUseMagnet();
      delay(1000);

      // hover 2 with left arm
      lshoulder.write(70);
      lclavi.write(100);
      lbicep.write(60);
      delay(2000);
      lrotate.write(20);
      delay(2000);

    }



    else if (input == '4') {

      // GO to hover0 and then go to rest
      lGoToHover0();


      //go to p0
      lclavi.write(110);
      lrotate.write(90);
      delay(3000);

      lshoulder.write(10);
      lbicep.write(60);
      lRestPosition = 1;

    }


    else if (input == '5') {
      // GO FOR disc red from pillar 2 to pillar 1

      lrotate.write(50);  // up the arm and hoover over 2nd pillar

      delay(2000);

      lshoulder.write(45);  //down the arm


      delay(2000);
      digitalWrite(31, HIGH);  //pick up the disc

      lshoulder.write(70);  //up the arm

      lrotate.write(20);  // go over 1pillar
      delay(3000);

      lshoulder.write(60);  //lower the arm
      delay(2000);
      digitalWrite(31, LOW);  //drop off the disc

      lshoulder.write(70);  //up the arm
    }

    else if (input == '6') {

      // GO FOR disc yellow from pillar 2 to pillar 3

      lrotate.write(50);  // up the arm and hoover over 2nd pillar

      delay(2000);

      lshoulder.write(45);  //down the arm


      delay(2000);
      digitalWrite(31, HIGH);  //pick up the disc

      lshoulder.write(70);  //up the arm

      lrotate.write(80);  // go over 3pillar
      delay(3000);


      lbicep.write(100);
      lshoulder.write(36);  //lower the arm
      delay(2000);
      digitalWrite(31, LOW);  //drop off the disc

      lshoulder.write(60);  //up the arm
      lbicep.write(95);     // relax the bicep

    }


    else if (input == '8') {
      //Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;

      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 400) {
        lbicep.write(newPosition);
        Serial.println("BICEP position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }


    else if (input == '9') {
      //Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 400) {
        lrotate.write(newPosition);
        Serial.println("ROTATE position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'A') {
      //Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;

      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lshoulder.write(newPosition);
        Serial.println("SHOULDER position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'B') {
      //Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lclavi.write(newPosition);
        Serial.println("CLAVI position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'C') {  // test pulley
      Serial.println("Enter position for Servo pulley (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 60 && newPosition <= 140) {
        toolPulley.write(newPosition);
        delay(400);            //lower or up the tool for 1 second
        toolPulley.write(90);  // stop the servo continuos
        Serial.println("Servo 9 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 70 and 120.");
      }
    }

    else if (input == 'D') {  // activate the magnet or deactivate

      /* if (magnets_on == 0) {
        digitalWrite(31, HIGH);
        // digitalWrite(33, HIGH);
        //magnets_on = 1;
        Serial.println("magnets on");

      } else {
        digitalWrite(31, LOW);
        //digitalWrite(33, LOW);
       // magnets_on = 0;
        Serial.println("magnets off");
      }*/
    }

    else if (input == 'E') {  // go to rest position

      lclavi.write(100);
      delay(2000);
      lrotate.write(90);
      delay(3000);
      lshoulder.write(10);
      lbicep.write(60);

    }

    else if (input == 'F') {  // go to catch position
                              //mini demo movements

      lshoulder.write(85);  //este 85 parece que es muy alto y recalienta el servo
      lbicep.write(95);
      delay(2000);
      lrotate.write(20);
      delay(3000);
    }
  }
}


void lUseMagnet() {

  if (lMagnetInUse == 0) {
    digitalWrite(lMagnetPin, HIGH);
    // digitalWrite(33, HIGH);
    lMagnetInUse = 1;
    Serial.println("magnets on");

  } else {
    digitalWrite(lMagnetPin, LOW);
    //digitalWrite(33, LOW);
    lMagnetInUse = 0;
    Serial.println("magnets off");
  }
}


void lGoToHover0() {
  //go to hover 0
  lclavi.write(109);
  delay(1000);
  lshoulder.write(45);
  lrotate.write(90);
  lbicep.write(100);
  delay(2000);
}
