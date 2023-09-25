//This code is set to test the right side of the inmoov robot
//it is part for the capstone project Hanoi Droid sep 2023


#include <Servo.h>

Servo rthumb, rindex, rmajeur, rpinky, rring, rbicep, rrotate, rshoulder, rclavi;

void setup() {
  rthumb.attach(2);
  rindex.attach(3);
  rmajeur.attach(4);
  rpinky.attach(6);
  rring.attach(7);
  rbicep.attach(8); //sep 2023: signal ok from arduino, servo not responding
  rrotate.attach(9);
  rshoulder.attach(10);
  rclavi.attach(11); //sep 2023: signal ok from arduino, servo not responding
  Serial.begin(9600);


//all the servos to rest position

rthumb.write(90);
rindex.write(90);
rrotate.write(80);
rshoulder.write(60);
rbicep.write(110);
rclavi.write(100);



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
        rthumb.write(newPosition);
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
        rindex.write(newPosition);
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
        rmajeur.write(newPosition);
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
        rpinky.write(newPosition);
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
        rring.write(newPosition);
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
        rbicep.write(newPosition);
        Serial.println("Servo 6 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    else if (input == '9') {
      Serial.println("Enter position for Servo 2 (0-180):");
      while (!Serial.available());
      newPosition = Serial.parseInt();
      if (newPosition >= 0 && newPosition <= 180) {
        rrotate.write(newPosition);
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
        rshoulder.write(newPosition);
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
        rclavi.write(newPosition);
        Serial.println("Servo 9 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }


  }
}