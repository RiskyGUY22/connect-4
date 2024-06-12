#include <functions.h>
#include <stdio.h>
#include <string.h>

void print_board(char board[][7][4])
{
    // Print column numbers
    printf("    ");
    for (int col = 1; col <= 7; col++)
    {
        printf("%-4d", col); // Adjusted spacing for alignment
    }
    printf("\n");

    // Print the board
    for (int row = 0; row < 6; row++)
    {
        printf("%-2d", row + 1); // Adjusted spacing for alignment
        for (int col = 0; col < 7; col++)
        {
            printf("| %s ", board[row][col]);
        }
        printf("|\n");
    }
}

/* The players and their data will be handled by structs,
   this functions is used to define that data.*/

void initInstance(struct instance *instance, char *player, char *player_name)
{
    strcpy(instance->player, player);
    strcpy(instance->player_name, player_name);
}

void checkValidX(int *x)
{
    // Check input is an integer and is between 1 and 6 inclusive
    while (getchar() != '\n' || *x < 1 || *x > 7)
    {
        printf("Invalid input, re-enter x coordinate: ");
        scanf("%d", x);
    }
}

void checkValidY(int *y)
{
    // Check input is an integer and is between 1 and 6 inclusive
    while (getchar() != '\n' || *y < 1 || *y > 6)
    {
        printf("Invalid input, re-enter y coordinate: ");
        scanf("%d", y);
    }
}

/* Function to get the user's input, we will handle the x and y coordinates as pointers
   to save memory in our program and prevent potential memory leaks.*/
void getInput(int *x, int *y)
{
    printf("Enter your x coordinate : ");
    scanf("%d", x);

    checkValidX(x);

    printf("Enter your y coordinate : ");
    scanf("%d", y);

    checkValidY(y);
}

// Simple function to get the user's choice from the menu
int getMenuChoice(int *choice)
{

    printf(GREEN "Welcome to my Connect-4 Game!\n\n" RESET);
    printf(BLUE " 1. Start\n" RESET);
    printf(YELLOW " 2. Options\n" RESET);
    printf(RED " 3. Quit\n" RESET);

    printf(BLUE "\nOPTION: " RESET);

    // Check for invalid inputs
    if (scanf("%d", choice) != 1)
    {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

    // Program has run successfully
    return 0;
}