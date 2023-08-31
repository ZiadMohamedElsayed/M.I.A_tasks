/*
 * File: 01201013769_Task1_3.c
 * Author: Ziad Mohamed Elsayed
 * Description: A simple Task Manager program.
 * Date: 8/13
 */

/* Header Files */
#include <stdio.h>  // Standard I/O functions
#include <string.h> // Standard string functions

/* Macros */
#define MAX_TASKS 100

/* Struct Declarations */
struct Task
{
    int id;
    char description[100];
    int state; // 0: Incomplete, 1: Complete
};

/* Function prototypes */
void addTask(struct Task[], int *);
void viewTasks(struct Task[], int);
void removeTask(struct Task[], int *, int);

/* Main Function */
int main()
{
    struct Task tasks[MAX_TASKS]; // Array to store tasks
    printf("Minions Task Manager\n");
    printf("1. Add Task\n");
    printf("2. View Tasks\n");
    printf("3. Complete task\n");
    printf("4. Remove Task\n");
    printf("5. Exit\n");

    int numTasks = 0; // Number of tasks
    while (1)
    {
        int option;
        printf("\nSelect an option: ");
        while (scanf("%d", &option) != 1 || option > 5 || option < 1) // Check input
        {
            printf("Invalid input");
            printf("\nSelect an option: ");
        }

        switch (option)
        {
        case 1:
            addTask(tasks, &numTasks);
            break;
        case 2:
            viewTasks(tasks, numTasks);
            break;
        case 3:
        {
            int completeID;
            printf("Enter task ID to mark as complete: ");
            scanf("%d", &completeID);
            completeID--; // Make ID array

            if (completeID >= numTasks)
                printf("Task not found!\n");
            else
            {
                tasks[completeID].state = 1; // Mark the task as complete
                printf("Task marked as complete successfully!\n");
            }
            break;
        }
        case 4:
        {
            int removeID;
            printf("Enter task ID to remove: ");
            scanf("%d", &removeID);
            removeTask(tasks, &numTasks, removeID);
            break;
        }
        case 5:
            printf("Exiting Minions Task Manager. Have a great day!\n");
            return 0;
        default:
            printf("Invalid option. Please select a valid option.\n");
        }
    }
    return 0;
}

void addTask(struct Task tasks[], int *numTasks)
{
    printf("\nEnter task description: ");

    getchar(); // Clear newline character from previous input
    fgets(tasks[*numTasks].description, sizeof(tasks[*numTasks].description), stdin);
    tasks[*numTasks].description[strlen(tasks[*numTasks].description) - 1] = '\0'; // Remove newline character

    tasks[*numTasks].id = *numTasks + 1;
    tasks[*numTasks].state = 0; // New tasks are marked as incomplete

    (*numTasks)++; // Increment number of tasks
    printf("Task added successfully!\n");
}

void viewTasks(struct Task tasks[], int numTasks)
{
    // Print tasks in taple format
    printf("Task ID\t|%-40s\t|State\n", "Description");
    for (int i = 0; i < numTasks; i++)
    {
        printf("%d\t|", tasks[i].id);
        printf("%-40s\t|", tasks[i].description);

        if (tasks[i].state == 0)
            printf("incomplete");
        else if (tasks[i].state == 1)
            printf("complete");

        printf("\n");
    }
}

void removeTask(struct Task tasks[], int *numTasks, int removeID)
{
    removeID--;
    if (removeID >= *numTasks) // Check ID
        printf("Task not found!\n");
    else
    {
        for (int i = removeID; i < *numTasks; i++)
        {
            tasks[i] = tasks[i + 1]; // Shift tasks to fill the gap
            tasks[i].id--;           // Shift tasks' ID
        }

        (*numTasks)--; // Decrement number of tasks
        printf("Task removed successfully!\n");
    }
}
