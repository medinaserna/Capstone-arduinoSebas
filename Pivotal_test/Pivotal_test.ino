// This program is to test the servos of the left arm of the Inmoov robot.
//The addition is a basic operation of the grab tool
//Grab tool includes the continuos servo and the magnets.


#include <Servo.h>

Servo lthumb, lindex, lmajeur, lpinky, lring, lbicep, lrotate, lshoulder, lclavi, jaw, head, head_rotate, toolPulley;

char magnets_on = 0;

void setup() {
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
  head_rotate.attach(13);  // When this is attached full noise cames from the head. still in revision
  toolPulley.attach(45);
  Serial.begin(9600);

  //set up the controls pins for the magnets
  pinMode(31, OUTPUT);






  //BE CAREFUL. these are the rest positions
  lrotate.write(90);
  lshoulder.write(10);
  lbicep.write(60);
  lclavi.write(100);
  head.write(100);
  jaw.write(60);
  head_rotate.write(90);
  toolPulley.write(90);

  
  /*
  // BE CAREFUL. WHEN TESTING PULLEY MOVEMENTS, THIS IS THE CATCH POSITION

  lrotate.write(20);    // the different
  lshoulder.write(85);  // the different
  lbicep.write(95);     // the different

  lclavi.write(100);
  head.write(100);
  jaw.write(60);
  head_rotate.write(90);
  toolPulley.write(90);

*/


}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int newPosition;

    // 2 DISCS MOVEMENT DEMO
    if (input == '1') {

     //pick up the red
      toolPulley.write(80);  //lower the tool
      delay(1200);           //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, HIGH);
      toolPulley.write(120);  //up the tool
      delay(1200);            //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(130);

      delay(3000);

      toolPulley.write(80);  //down the tool
      delay(400);            //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, LOW);
      
      // go for the green

      toolPulley.write(120);  //up the tool
      delay(800);             //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(100);

      delay (3000);

      toolPulley.write(80);  //down the tool
      delay(1600);           //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, HIGH);

      toolPulley.write(120);  //up the tool
      delay(1600);            //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(155);

      delay (4000);

      toolPulley.write(80);  //down the tool
      delay(400);            //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, LOW);

      // GO FOR the red again
      toolPulley.write(120);  //up the tool
      delay(400);             //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(130);

      delay (3000);

      toolPulley.write(80);  //down the tool
      delay(800);            //
      toolPulley.write(90);  // stop the servo continuos
      digitalWrite(31, HIGH);

      toolPulley.write(120);  //up the tool
      delay(800);             //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(155);

      delay (2000);

      toolPulley.write(80);  //down the tool
      delay(400);            //
      toolPulley.write(90);  // stop the servo continuos
      digitalWrite(31, LOW);

      toolPulley.write(120);  //up the tool
      delay(400);             //
      toolPulley.write(90);   // stop the servo continuos


      lclavi.write(100);  // GO TO REST
       toolPulley.write(80);  //down the tool
      delay(400);            //
      toolPulley.write(90);  // stop the servo continuos

    }


    // Read the position for rindex
    else if (input == '2') {

//pick up the red
      toolPulley.write(80);  //lower the tool
      delay(1200);           //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, HIGH);
      toolPulley.write(120);  //up the tool
      delay(1200);            //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(130);

      delay(3000);

      toolPulley.write(80);  //down the tool
      delay(400);            //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, LOW);

    }

    else if (input == '3') {

// go for the green

      toolPulley.write(120);  //up the tool
      delay(800);             //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(100);

      delay (3000);

      toolPulley.write(80);  //down the tool
      delay(1600);           //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, HIGH);

      toolPulley.write(120);  //up the tool
      delay(1600);            //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(155);

      delay (4000);

      toolPulley.write(80);  //down the tool
      delay(400);            //
      toolPulley.write(90);  // stop the servo continuos

      digitalWrite(31, LOW);

    }

   

    else if (input == '4') {
      
// GO FOR the red again
      toolPulley.write(120);  //up the tool
      delay(400);             //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(130);

      delay (3000);

      toolPulley.write(80);  //down the tool
      delay(800);            //
      toolPulley.write(90);  // stop the servo continuos
      digitalWrite(31, HIGH);

      toolPulley.write(120);  //up the tool
      delay(800);             //
      toolPulley.write(90);   // stop the servo continuos

      lclavi.write(155);

      delay (2000);

      toolPulley.write(80);  //down the tool
      delay(400);            //
      toolPulley.write(90);  // stop the servo continuos
      digitalWrite(31, LOW);

      toolPulley.write(120);  //up the tool
      delay(400);             //
      toolPulley.write(90);   // stop the servo continuos


      lclavi.write(100);  // GO TO REST


    }


     else if (input == '5') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lpinky.write(newPosition);
        Serial.println("Servo 4 position set to: " + String(newPosition));
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
        lbicep.write(newPosition);
        Serial.println("bicep position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '9') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available())
        ;
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 400) {
        lrotate.write(newPosition);
        Serial.println("rotate position set to: " + String(newPosition));
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
        lshoulder.write(newPosition);
        Serial.println("Shoulder position set to: " + String(newPosition));
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
        lclavi.write(newPosition);
        Serial.println("clavi position set to: " + String(newPosition));
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

      if (magnets_on == 0) {
        digitalWrite(31, HIGH);
        // digitalWrite(33, HIGH);
        magnets_on = 1;
        Serial.println("magnets on");

      } else {
        digitalWrite(31, LOW);
        //digitalWrite(33, LOW);
        magnets_on = 0;
        Serial.println("magnets off");
      }
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

      lshoulder.write(85);
      lbicep.write(95);
      delay(2000);
      lrotate.write(20);
      delay(3000);
    }
  }
}
