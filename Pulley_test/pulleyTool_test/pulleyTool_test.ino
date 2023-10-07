// This program is to test the continuos servo that will work with the hand tool for the magnet tool


#include <Servo.h>

Servo toolPulley;

void setup() {
  toolPulley.attach(9);

  Serial.begin(9600);


//all the servos to rest position
toolPulley.write(90);


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
       toolPulley.write(newPosition);
        Serial.println("Servo 1 position set to: " + String(newPosition));
      } else {
        Serial.println("Invalid position. Please enter a value between 0 and 180.");
      }
    }

    
  }
}
