/*
 * File: Precise Self-Localizing.ino
 * Author: Ziad Mohamed Elsayed
 * Description: Interface with IMU sensor MPU6050, and retrieve the Yaw angle.
 * Date: 9/5
 */

/* Header Files */
#include <Wire.h> // Allows you to communicate with I2C devices

// Constants for MPU6050 registers
const int MPU6050Address = 0x68; // MPU6050 I2C address
const int gyroConfigReg = 0x1B;  // Gyroscope configuration register
const int gyroXHighReg = 0x43;   // Gyroscope X-axis high byte register
const int gyroXLowReg = 0x44;    // Gyroscope X-axis low byte register
const int gyroYHighReg = 0x45;   // Gyroscope Y-axis high byte register
const int gyroYLowReg = 0x46;    // Gyroscope Y-axis low byte register
const int gyroZHighReg = 0x47;   // Gyroscope Z-axis high byte register
const int gyroZLowReg = 0x48;    // Gyroscope Z-axis low byte register

// Gyroscope readings and sensitivity scale factor
int16_t gyroX, gyroY, gyroZ;
float gyroScale = 131.0; // Sensitivity scale factor for gyroscope (datasheet value)

// Calibration values (adjust these based on sensor)
float gyroXOffset = 0.0;
float gyroYOffset = 0.0;
float gyroZOffset = 0.0;

float currentYaw = 0.0;                       // Current yaw angle (accumulated)
float elapsedTime, currentTime, previousTime; // Time parameters

/* Function prototypes */
void readGyroData();
void calculateYawAngle();
void calibrateGyro();
void Delay(unsigned long delayMs);

void setup()
{
    // Initialize communication
    Wire.begin();
    Serial.begin(9600);

    // Configure Gyro Sensitivity - Full Scale Range (default +/- 250deg/s)

    calibrateGyro(); // Perform gyro calibration
}

void loop()
{
    readGyroData();
    calculateYawAngle();
    Delay(500); // Delay for 0.5 second
}

void readGyroData()
{
    // Read gyroscope data
    Wire.beginTransmission(MPU6050Address);
    Wire.write(gyroXHighReg);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU6050Address, 6, true);

    while (wire.available() < 6)
        ;

    gyroX = (Wire.read() << 8) | Wire.read();
    gyroY = (Wire.read() << 8) | Wire.read();
    gyroZ = (Wire.read() << 8) | Wire.read();

    // Apply calibration offsets
    gyroX -= gyroXOffset;
    gyroY -= gyroYOffset;
    gyroZ -= gyroZOffset;
}

void calculateYawAngle()
{
    previousTime = currentTime;                        // Store previous time
    currentTime = millis();                            // Record current time
    elapsedTime = (currentTime - previousTime) / 1000; // Calculate time elapsed in seconds

    // Calculate Yaw angle change
    float gyroYaw = (gyroZ / gyroScale) * elapsedTime;

    // Accumulate the Yaw angle
    currentYaw += gyroYaw;

    // Ensure the angle wraps around at 360 degrees
    if (currentYaw >= 360.0)
    {
        currentYaw -= 360.0;
    }
    else if (currentYaw < 0.0)
    {
        currentYaw += 360.0;
    }

    // Print the current Yaw angle
    Serial.print("Yaw Angle (degrees): ");
    Serial.println(currentYaw);
}

void calibrateGyro()
{
    int numSamples = 1000; // Number of samples for calibration
    int32_t gyroXSum = 0, gyroYSum = 0, gyroZSum = 0;

    Serial.println("Calibrating gyro. Keep sensor still...");

    // Collect samples for calibration
    for (int i = 0; i < numSamples; i++)
    {
        Wire.beginTransmission(MPU6050Address);
        Wire.write(gyroXHighReg);
        Wire.endTransmission(false);
        Wire.requestFrom(MPU6050Address, 6, true);

        gyroXSum += (Wire.read() << 8) | Wire.read();
        gyroYSum += (Wire.read() << 8) | Wire.read();
        gyroZSum += (Wire.read() << 8) | Wire.read();

        Delay(5); // Delay between samples
    }

    // Calculate offsets
    gyroXOffset = (float)gyroXSum / numSamples;
    gyroYOffset = (float)gyroYSum / numSamples;
    gyroZOffset = (float)gyroZSum / numSamples;

    Serial.println("Gyro calibration complete.");
    Serial.print("Gyro X Offset: ");
    Serial.println(gyroXOffset);
    Serial.print("Gyro Y Offset: ");
    Serial.println(gyroYOffset);
    Serial.print("Gyro Z Offset: ");
    Serial.println(gyroZOffset);
}

// Custom delay function
void Delay(unsigned long delayMs)
{
    unsigned long startMs = millis();
    while (millis() - startMs < delayMs)
        ;
}
