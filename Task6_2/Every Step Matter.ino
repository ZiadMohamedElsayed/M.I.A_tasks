/*
 * File: Every Step Matter.ino
 * Author: Ziad Mohamed Elsayed
 * Description: Interface with rotary Encoder and get the number of counts.
 * Date: 9/5
 */

// Define the pins for the rotary encoder
const int encoderPinA = 2;
const int encoderPinB = 3;

int counter = 0;
bool aState;
bool aLastState;

void setup()
{
    // Initialize the pins
    pinMode(encoderPinA, INPUT_PULLUP);
    pinMode(encoderPinB, INPUT_PULLUP);

    // Read the initial state of the A signal
    aLastState = digitalRead(encoderPinA);

    // Attach interrupt to the A pin to detect both rising and falling edges
    attachInterrupt(digitalPinToInterrupt(encoderPinA), updateEncoder, CHANGE);

    // Initialize Serial communication
    Serial.begin(9600);
}

void loop()
{
}

void updateEncoder()
{
    // Read the current state of the A signal
    aState = digitalRead(encoderPinA);

    // Check if the A signal has changed
    if (aState != aLastState)
    {
        // If the B signal is different from the A signal, increment the count
        if (digitalRead(encoderPinB) != aState)
        {
            counter++;
        }
        else
        {
            counter--;
        }
    }

    // Update the last state of the A signal
    aLastState = aState;

    Serial.println(counter); // Print the current count for testing
}
