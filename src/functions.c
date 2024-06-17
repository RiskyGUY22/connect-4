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

void changeBoardValue(char board[][7][4], int x, int y, struct instance *instance)
{
    if (strcmp(instance->player, "Player1") == 0)
    {
        strcpy(board[y - 1][x - 1], LINED_CIRCLE);
    }
    else if (strcmp(instance->player, "Player2") == 0)
    {
        strcpy(board[y - 1][x - 1], FILLED_CIRCLE);
    }
}

/* The players and their data will be handled by structs,
   this functions is used to define that data.*/

void initInstance(struct instance *instance, char *player, char *player_name)
{
    strcpy(instance->player, player);
    strcpy(instance->player_name, player_name);
}

void checkValid(int *x, int *y, char board[][7][4])
{
    // Check input is an integer and is between 1 and 6 inclusive
    // check both coordinated then ask for both of them again if one of them is invalid
    while (getchar() != '\n' || *x < 1 || *x > 7 || *y < 1 || *y > 6)
    {
        printf(RED "\nInvalid set of coordinated entered, Please re-enter!\n" RESET);

        printf(BLUE "Enter your x coordinate : ");
        scanf("%d", x);
        printf("Enter your y coordinate : ");
        scanf("%d", y);
    }

    // Seperately check if the place has already been taken to avoid confusing error messages
    while ((strcmp(board[*y - 1][*x - 1], BLANK_CIRCLE) != 0))
    {

        printf(RED "\nLocated already taken, Please re-enter!\n" RESET);

        printf(BLUE "Enter your x coordinate : ");
        scanf("%d", x);
        printf("Enter your y coordinate : ");
        scanf("%d", y);
    }
}

/* Function to get the user's input, we will handle the x and y coordinates as pointers
   to save memory in our program and prevent potential memory leaks.*/
void getPlayersInput(int *x, int *y, char board[][7][4], struct instance *instance)
{

    if (strcmp(instance->player, "Player1") == 0)
    {

        printf(BLUE "\nPlayer 1's turn!\n");
        printf("Enter your x coordinate : ");
        scanf("%d", x);

        printf("Enter your y coordinate : ");
        scanf("%d", y);

        checkValid(x, y, board);

        printf(RESET "\n");
    }
    else if (strcmp(instance->player, "Player2") == 0)
    {

        printf(GREEN "\nPlayer 2's turn!\n");
        printf("Enter your x coordinate : ");
        scanf("%d", x);

        printf("Enter your y coordinate : ");
        scanf("%d", y);

        checkValid(x, y, board);

        printf(RESET "\n");
    }
}

// Main loop to check if a player has won
bool checkPlayerWon()
{

    return false;
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
