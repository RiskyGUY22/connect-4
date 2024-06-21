/*
# Copyright (C) 2024-2024 Connect-4 Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
*/

/* Include the necessary libraries */
#include <functions.h>
#include <stdio.h>
#include <string.h>

/* Function to print the game board */
void print_board(char board[][COLS][4])
{
    /* Print the columns */
    printf("    ");
    for (int col = 1; col <= COLS; col++)
    {
        printf("%-4d", col); /* Adjusted spacing for alignment */
    }
    printf("\n");

    /* Print the rows */
    for (int row = 0; row < 6; row++)
    {
        printf("%-2d", row + 1); /* Adjusted spacing for alignment */
        for (int col = 0; col < COLS; col++)
        {
            printf("| %s ", board[row][col]);
        }
        printf("|\n");
    }
}

void clear_board(char board[][COLS][4])
{

}

void play_again()
{

	char choice[4096];
	printf("Do you want to play again?: ");
	scanf("%s", choice);

	if(strcmp(choice, "Y") == 0)
	{
		printf("Starting the next round...");
		printf("Player 1 score: ");
		printf("Player 2 score: ");
		
	}
	printf("\n\n");
}

/* Function which will take the x and y coordinated as well as the Player as inputs,
   To modify the array with a different value. This is the main usage for the struct.
*/
void changeBoardValue(char board[][COLS][4], int x, int y, struct instance *instance)
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
   this functions is used to define that data.
*/
void initInstance(struct instance *instance, char *player, char *player_name, int score, int high_score)
{
    strcpy(instance->player, player);
    strcpy(instance->player_name, player_name);
	instance->score = score;
	instance->high_score = high_score;
}

/* Functions which manages all validation in the program, will check
   for any typos and irraneous data.
*/
void checkValid(int *x, int *y, char board[][COLS][4])
{
    /* Ensure the column and row are within valid range.*/
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
        /* Gravity impl */
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
   to save memory in our program and prevent potential memory leaks. Also we will use
   structs to keep track of the player's data, and so we don't need seperate functions
   for each player.
*/
void getPlayersInput(int *x, int *y, char board[][COLS][4], struct instance *instance)
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

/* Function used for checking if a player has won. */
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

/* Main loop to check if a player has won */
bool checkPlayerWon(char board[][COLS][4])
{
    /* Check for a horizontal line win */
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

    /* Check for a vertical line win */
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

    /* Check for a descending diagonals win */
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

    /* Check for a ascending diagonals win */
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

    /* By default we will return false so that our loop in the game_logic
       function knows to keep running.
    */
    return false;
}

/* Very simple function which displays text to the screen on how to play. */
void howToPlay()
{
    printf(BLUE "\nThe game is played on a grid that's 7 columns by 6 rows.\n");
    printf("Two players take turns to drop their circles into the grid.\n");
    printf("The first player to get four circles in a row (either vertically, horizontally or diagonally) wins!\n\n");
}

/* Simple function to get the user's choice and display the menu */
int getMenuChoice(char choice[8])
{
    printf(GREEN "Welcome to my Connect-4 Game!\n\n" RESET);
    printf(BLUE " 1. Start\n" RESET);
    printf(YELLOW " 2. How-To-Play\n" RESET);
    printf(RED " 3. Quit\n" RESET);

    printf(BLUE "\nOPTION: " RESET);

    scanf("%s", choice);

    /* Indicate the Program has run successfully */
    return 0;
}
