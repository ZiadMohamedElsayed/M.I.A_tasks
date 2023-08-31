/*
 * File: 01201013769_Task1_4.c
 * Author: Ziad Mohamed Elsayed
 * Description: Sensor Fusion.
 * Date: 8/13
 */

/* Header Files */
#include <stdio.h> // Standard I/O functions

/* Macros */
#define mpu6050_ACCURACY 0.79
#define bno55_ACCURACY 0.92
#define NUM_MEASUREMENTS 10

// Sensor measurements
float mpu6050[NUM_MEASUREMENTS] = {0.0, 11.68, 18.95, 23.56, 25.72, 25.38, 22.65, 18.01, 10.14, -0.26};
float bno55[NUM_MEASUREMENTS] = {0.0, 9.49, 16.36, 21.2, 23.16, 22.8, 19.5, 14.85, 6.79, -2.69};

// Kalman filter variables
float estimatedValue = 0.0;
float estimatedError = 1.0;
float measurementError = 0.1;

/* Function prototypes */
void printArray(float[], int);
float kalmanFilter(float);

/* Main Function */
int main()
{
    printf("Output rating:\n\n");

    // Fair: Simple averaging
    float fairOutput[NUM_MEASUREMENTS];
    for (int i = 0; i < NUM_MEASUREMENTS; i++)
    {
        fairOutput[i] = (mpu6050[i] + bno55[i]) / 2;
    }

    printf("1. Fair:\n");
    printArray(fairOutput, NUM_MEASUREMENTS);
    printf("\n\n");

    // Good: Weighted averaging considering accuracy
    float goodOutput[NUM_MEASUREMENTS];
    for (int i = 0; i < NUM_MEASUREMENTS; i++)
    {
        goodOutput[i] = (mpu6050[i] * mpu6050_ACCURACY + bno55[i] * bno55_ACCURACY) / (mpu6050_ACCURACY + bno55_ACCURACY);
    }

    printf("2. Good:\n");
    printArray(goodOutput, NUM_MEASUREMENTS);
    printf("\n\n");

    // Hero: Kalman filter
    float heroOutput[NUM_MEASUREMENTS];
    for (int i = 0; i < NUM_MEASUREMENTS; i++)
    {
        heroOutput[i] = kalmanFilter(mpu6050[i] * mpu6050_ACCURACY + bno55[i] * bno55_ACCURACY);
    }
    printf("3. Hero (Kalman Filter):\n");
    printArray(heroOutput, NUM_MEASUREMENTS);
    printf("\n");

    return 0;
}

void printArray(float array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%.2f ", array[i]);
    }
}

float kalmanFilter(float measurement)
{
    float kalmanGain = estimatedError / (estimatedError + measurementError);
    estimatedValue = estimatedValue + kalmanGain * (measurement - estimatedValue);
    estimatedError = (1 - kalmanGain) * estimatedError;

    return estimatedValue;
}