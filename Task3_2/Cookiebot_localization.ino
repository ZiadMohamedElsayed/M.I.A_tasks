/*
 * File: Cookiebot_localization.c
 * Author: Ziad Mohamed Elsayed
 * Description: localize the position of a cookie bot.
 * Date: 8/21
 */

/* Macros */
#define LEFT_SENSOR 1
#define RIGHT_SENSOR 3
#define FRONT_SENSOR 0
#define REAR_SENSOR 2

const int numSensors = 4;
const int trigPins[numSensors] = {2, 3, 4, 5}; // Trigger pins for sensors
const int echoPins[numSensors] = {6, 7, 8, 9}; // Echo pins for sensors
const float chamberWidth = 500;                // Chamber width in centimeters
const float chamberLength = 600;               // Chamber length in centimeters

// Array to store distance measurements
float distances[numSensors];

// Position parameters
float X;
float Y;

/* Function prototypes */
void calculatePosition();
float readUltrasonic(int, int);
void printPosition();

// Initialize ultrasonic sensors
void setup()
{
    for (int i = 0; i < numSensors; i++)
    {
        pinMode(trigPins[i], OUTPUT);
        pinMode(echoPins[i], INPUT);
    }
    Serial.begin(9600);
}

void loop()
{
    calculatePosition();
    printPosition();
    delay(500);
}

void calculatePosition()
{
    // Put distances in array
    for (int i = 0; i < numSensors; i++)
    {
        distances[i] = readUltrasonic(trigPins[i], echoPins[i]);
    }

    // Calculate Position
    X = (distances[LEFT_SENSOR] + (chamberWidth - distances[RIGHT_SENSOR])) / 2;  // Lateral position (average of right and left sensors)
    Y = (distances[REAR_SENSOR] + (chamberLength - distances[FRONT_SENSOR])) / 2; // Forward position (average of front and rear sensors)
}

// Read distances from ultrasonic sensors
float readUltrasonic(int trigPin, int echoPin)
{
    // Emit the ultrasonic wave
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Calculate distance
    long duration = pulseIn(echoPin, HIGH);
    return (duration / 2) * 0.03432; // Convert to centimeters
}

// Print robot's position
void printPosition()
{
    Serial.print("Robot position (x, y): ");
    Serial.print(X);
    Serial.print(", ");
    Serial.println(Y);
}