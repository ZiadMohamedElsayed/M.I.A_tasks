/*
 * File: Arduino_1.c
 * Author: Ziad Mohamed Elsayed
 * Description: Read 2 buttons' state and send them to Arduino_2.
 * Date: 8/20
 */

/* Header Files */
#include <Wire.h> // Allows you to communicate with I2C devices

const int buttonPin1 = 2; // Pin for button 1
const int buttonPin2 = 3; // Pin for button 2

// Initialize buttons and I2C communication
void setup()
{
  Wire.begin();
  pinMode(buttonPin1, INPUT);
  pinMode(buttonPin2, INPUT);
}

void loop()
{
  // Read buttons' state
  int buttonState1 = digitalRead(buttonPin1);
  int buttonState2 = digitalRead(buttonPin2);

  Wire.beginTransmission(9); // Address of the receiver Arduino

  // Send buttons' state to Arduino_2
  Wire.write(buttonState1);
  Wire.write(buttonState2);

  Wire.endTransmission();
  delay(100);
}