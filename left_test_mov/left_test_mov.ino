// This program is to test the servos of the left arm of the Inmoov robot. 
// At the end of the code, the F key is to develop a small movement


#include <Servo.h>

Servo lthumb, lindex, lmajeur, lpinky, lring, lbicep, lrotate, lshoulder, lclavi, jaw, head, head_rotate;

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
  //head_rotate.attach(13);  // When this is attached full noise cames from the head. still in revision
  Serial.begin(9600);


//all the servos to rest position
lrotate.write(90);
lshoulder.write(10);
lbicep.write(60);
lclavi.write(100);
head.write(100);
jaw.write(60);
//head_rotate.write(30);

}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    int newPosition;

    // Read the position for rthumb
    if (input == '1') {
      Serial.println("Enter position for Servo 1 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
       lring.write(newPosition);
        Serial.println("Servo 1 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    // Read the position for rindex
    else if (input == '2') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lindex.write(newPosition);
        Serial.println("Servo 2 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '3') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lmajeur.write(newPosition);
        Serial.println("Servo 3 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '5') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lpinky.write(newPosition);
        Serial.println("Servo 4 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '4') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lthumb.write(newPosition);
        Serial.println("Servo 5 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '8') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lbicep.write(newPosition);
        Serial.println("Servo 6 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '9') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 400) {
        lrotate.write(newPosition);
        Serial.println("Servo 7 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'A') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lshoulder.write(newPosition);
        Serial.println("Servo 8 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'B') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        lclavi.write(newPosition);
        Serial.println("Servo 9 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'C') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        jaw.write(newPosition);
        Serial.println("Servo 9 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'D') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        head.write(newPosition);
        Serial.println("Servo 9 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'E') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= -360 && newPosition <= 360) {
        head_rotate.write(newPosition);
        Serial.println("Servo 9 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == 'F') {
      //mini demo movements

       lshoulder.write(85);
      lbicep.write(95);
     delay(2000);
      lrotate.write(20);
      delay(3000);
 

    }


  }
}
