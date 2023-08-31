/*
 * File: 01201013769_Task1_2.c
 * Author: Ziad Mohamed Elsayed
 * Description: Count down starting from user input number.
 * Date: 8/12
 */

/* Header Files */
#include <stdio.h> // Standard I/O functions
#include <time.h>  // Standard time functions

/* Function prototypes */
void delay(int);

/* Main Function */
int main()
{
    int countdown_start;
    printf("Start the countdown from: ");

    while (scanf("%d", &countdown_start) != 1 || countdown_start < 0) // Check input
    {
        printf("Invalid input.\n");
        printf("Start the countdown from: ");
    }

    // Loop to countdown from 'start' to 1
    for (int i = countdown_start; i > 0; i--)
    {
        printf("%d\n", i);
        delay(1); // Delay for 1 second
    }

    printf("Blast off to the moon!");
    return 0;
}

// Function to introduce a delay in seconds
void delay(int number_of_seconds)
{
    // Converting time into milliseconds
    int milli_seconds = 1000 * number_of_seconds;

    // Storing start time
    clock_t start_time = clock();

    // Looping until the required time passes
    while (clock() < start_time + milli_seconds)
        ;
}
