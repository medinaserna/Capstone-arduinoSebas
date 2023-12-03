/*

*/

// include the library code:
//#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
//const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
//LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  // set up the LCD's number of columns and rows:
  // lcd.begin(16, 2);
  // Print a message to the LCD to test is working
  // lcd.print("hello, world!");
  // delay(2000);
  // open the serial port:
  Serial.begin(115200);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  // lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

 // digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on (HIGH is the voltage level)

//  delay(5000);                      // wait for a second
 // digitalWrite(LED_BUILTIN, LOW);   // turn the LED off by making the voltage LOW
 // delay(3000);
  //digitalWrite(2, LOW);   // turn the LED on (HIGH is the voltage level)
  //digitalWrite(3, LOW);   // turn the LED on (HIGH is the voltage level)


  // read serial msg send from the pyhton code.
  if (Serial.available() > 0) {
    //String msg = Serial.readString();


    char input = Serial.read();


    switch (input) {

      case 'a':
        digitalWrite(2, HIGH);
        break;

      case 'b':
        digitalWrite(3, HIGH);
        break;


      case 'c':

        digitalWrite(2, LOW);
        break;


      case 'd':
        digitalWrite(3, LOW);
        break;
    }

    /*
    if (input == 'a') {


      digitalWrite(2, HIGH);


    }

    else if (input == 'b') {

      digitalWrite(3, HIGH);


    }

    else if (input == 'c') {

      digitalWrite(2, LOW);


    } else if (input == 'd') {

      digitalWrite(3, LOW);
    }
*/

    //lcd.print(msg);
  }
}
