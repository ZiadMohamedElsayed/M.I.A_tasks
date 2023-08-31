/*
 * File: Arduino_2.c
 * Author: Ziad Mohamed Elsayed
 * Description: Receive buttons' state and control the intensity of LED light.
 * Date: 8/20
 */

/* Header Files */
#include <Wire.h> // Allows you to communicate with I2C devices

const int ledPin = 9; // Pin for indicator LED

/* Function prototypes */
void receiveData(int byteCount);
int calculateLEDIntensity(int state1, int state2);
void printSerialMessage(int state1, int state2);

// Initialize LED and I2C communication
void setup()
{
  Wire.begin(9); // Address of this Arduino as I2C slave
  Wire.onReceive(receiveData);
  pinMode(ledPin, OUTPUT);
  Serial.begin(9600);
}

void loop()
{
  // The LED intensity and Serial messages will be controlled in the receiveData function
}

// Receive buttons' state from Arduino_1
void receiveData(int byteCount)
{
  if (byteCount >= 2)
  {
    int buttonState1 = Wire.read();
    int buttonState2 = Wire.read();

    // Control the intensity of the LED light and send massage
    int ledIntensity = calculateLEDIntensity(buttonState1, buttonState2);
    analogWrite(ledPin, ledIntensity);

    printSerialMessage(buttonState1, buttonState2);
  }
}

int calculateLEDIntensity(int state1, int state2)
{
  if (state1 == 0 && state2 == 0)
  {
    return 0; // 0% intensity
  }
  else if (state1 == 1 && state2 == 0)
  {
    return 128; // 50% intensity
  }
  else if (state1 == 0 && state2 == 1)
  {
    return 192; // 75% intensity
  }
  else
  {
    return 255; // 100% intensity
  }
}

void printSerialMessage(int state1, int state2)
{
  Serial.print("B1=");
  Serial.print(state1);
  Serial.print(", B2=");
  Serial.print(state2);

  if (state1 == 0 && state2 == 0)
  {
    Serial.println(" 0% of Maximum - No message");
  }
  else if (state1 == 1 && state2 == 0)
  {
    Serial.println(" 50% of Maximum - Vector focused");
  }
  else if (state1 == 0 && state2 == 1)
  {
    Serial.println(" 75% of Maximum - Vector distracted");
  }
  else
  {
    Serial.println(" 100% of Maximum - Glitch");
  }
}
