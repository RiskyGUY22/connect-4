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

// This function finds the lowest available position in the specified column
int findLowestAvailableRow(int column, char board[][COLS][4])
{
    for (int row = ROWS - 1; row >= 0; row--)
    {
        if (strcmp(board[row][column], BLANK_CIRCLE) == 0)
        {
            return row;
        }
    }
    return -1; // Column is full
}

void checkValid(int *x, int *y, char board[][COLS][4])
{
    // Ensure the column and row are within valid range and check gravity
    while (*x < 1 || *x > COLS || *y < 1 || *y > ROWS || 
           strcmp(board[*y - 1][*x - 1], BLANK_CIRCLE) != 0 || 
           (*y < ROWS && strcmp(board[*y][*x - 1], BLANK_CIRCLE) == 0))
    {
        if (*x < 1 || *x > COLS || *y < 1 || *y > ROWS)
        {
            printf(RED "\nInvalid set of coordinated entered, Please re-enter!\n" RESET);

            printf(BLUE "Enter your x coordinate : ");
            scanf("%d", x);
            printf("Enter your y coordinate : ");
            scanf("%d", y);
        }
        else if (strcmp(board[*y - 1][*x - 1], BLANK_CIRCLE) != 0)
        {
            printf(RED "\nLocation already taken!!\n" RESET);

            printf(BLUE "Enter your x coordinate : ");
            scanf("%d", x);
            printf("Enter your y coordinate : ");
            scanf("%d", y);
        }
        else if (*y < ROWS && strcmp(board[*y][*x - 1], BLANK_CIRCLE) == 0)
        {
            printf(RED "\nDon't defy gravity!!\n" RESET);

            printf(BLUE "Enter your x coordinate : ");
            scanf("%d", x);
            printf("Enter your y coordinate : ");
            scanf("%d", y);
        }
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

bool checkLine(char board[][COLS][4], int startX, int startY, int dx, int dy, const char playerCircle[])
{
    int count = 0;
    for (int i = 0; i < 4; i++)
    {
        int x = startX + i * dx;
        int y = startY + i * dy;
        if (x >= 0 && x < ROWS && y >= 0 && y < COLS && strcmp(board[x][y], playerCircle) == 0)
        {
            count++;
        }
        else
        {
            break;
        }
    }
    return count == 4;
}

// Main loop to check if a player has won
bool checkPlayerWon(char board[][COLS][4])
{
    // Check horizontal lines
    for (int row = 0; row < ROWS; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            if (checkLine(board, row, col, 0, 1, LINED_CIRCLE) || checkLine(board, row, col, 0, 1, FILLED_CIRCLE))
            {
                return true;
            }
        }
    }

    // Check vertical lines
    for (int row = 0; row <= ROWS - 4; row++)
    {
        for (int col = 0; col < COLS; col++)
        {
            if (checkLine(board, row, col, 1, 0, LINED_CIRCLE) || checkLine(board, row, col, 1, 0, FILLED_CIRCLE))
            {
                return true;
            }
        }
    }

    // Check descending diagonals
    for (int row = 0; row <= ROWS - 4; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            if (checkLine(board, row, col, 1, 1, LINED_CIRCLE) || checkLine(board, row, col, 1, 1, FILLED_CIRCLE))
            {
                return true;
            }
        }
    }

    // Check ascending diagonals
    for (int row = 3; row < ROWS; row++)
    {
        for (int col = 0; col <= COLS - 4; col++)
        {
            if (checkLine(board, row, col, -1, 1, LINED_CIRCLE) || checkLine(board, row, col, -1, 1, FILLED_CIRCLE))
            {
                return true;
            }
        }
    }

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
