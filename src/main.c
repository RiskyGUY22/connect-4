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
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/* Lots of implementation is here, for ref: src/functions.c */
#include <functions.h>

/* Main game function which calls all the necessary subprograms needed */
int game_logic(char board[][7][4], struct instance *player1, struct instance *player2, int round_number)
{
    /* Variables for the x/y location on the game board */
    int x, y;

    /* Create a file pointer and open the file in write mode */
    FILE *fp;
    fp = fopen("data.txt", "w");

    /* Check we have opened the file successfully */
    if (fp == NULL) {
        printf("Error opening data.txt, check the program is being run from the correct directory and the data.txt exists!\n");
        return 1;
    }

    print_board(board); /* Initial display of the board */

    /* Loop through the game until a player has won, which breaks the loop
       by returning rather than breaking.
    */
    while (1)
    {
        /* Get Player 1 Input, and modify the board value accordingly */
        getPlayersInput(&x, &y, board, player1);
        changeBoardValue(board, x, y, player1);
        print_board(board);

        /* Check if Player 1 has won */
        if (checkPlayerWon(board))
        {
            printf(RED "\nGAME OVER!\n\nPlayer 1 has won!");
            player1->score += 1;
            printf("\nPlayer 1's score is now %d\n" RESET, player1->score);
            sleep(2);

            if(!play_again(player1, player2, &round_number))
            {

                printf("\nSaving game data to a file...\n" RESET);

                fprintf(fp, "Round: %d\n", round_number);
                fprintf(fp, "Player 1 score: %d\n", player1->score);
                fprintf(fp, "Player 2 score: %d\n", player2->score);

                fclose(fp);

                exit(1);
            }

            clear_board(board);
            print_board(board);
            getPlayersInput(&x, &y, board, player1);
            changeBoardValue(board, x, y, player1);
            print_board(board);
        }

        /* Get Player 2 Input, and modify the board value accordingly */
        getPlayersInput(&x, &y, board, player2);
        changeBoardValue(board, x, y, player2);
        print_board(board);

        /* Check if Player 2 has won */
        if (checkPlayerWon(board))
        {
            printf(RED "\nGAME OVER!\n\nPlayer 2 has won!" );
            player2->score += 1;
            printf("\nPlayer 2's score is now %d\n" RESET, player2->score);
            sleep(2);
            
            if(!play_again(player1, player2, &round_number))
            {

                printf("\nSaving game data to a file...\n" RESET);

                fprintf(fp, "Round: %d\n", round_number);
                fprintf(fp, "Player 1 score: %d\n", player1->score);
                fprintf(fp, "Player 2 score: %d\n", player2->score);

                fclose(fp);

                exit(1);
            }

            clear_board(board);
            print_board(board);
        }
    }
}

/* Main function which C will naturally run first, the main point of this
   is to call our gameLogic function and a few other things needed at the
   start of runtime.
*/
int main()
{

    /* Define the array to represent the board and initialize it with dotted circles
       *NOTE* essentially with Unicode in C, one arguement is worth "4" values so we,
       need to make it a 3D array.
    */
    char board[6][7][4] = {
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"}};

    /* Initialise player instances, this will be used later on to store player related,
       data efficiently rather than using seperate variables (similar to classes) in an
       object orientated programming language.
    */
    struct instance player1;
    struct instance player2;

    /* Keep track of what round the game is on. */
    int round_number = 1;

    /* Call the function which will give our instances data */
    initInstance(&player1, "Player1", "TT", 0, 0);
    initInstance(&player2, "Player2", "Computer", 0, 0);

    /* Call the function to display our Main menu and get the user's choice */
    char choice[8];
    getMenuChoice(choice);
    printf("\n");

    /* Robust Programming: this code will use a function from the C lib string.h
       to compare the values of the choice variable and check it has the correct data,
       if not we will re ask the user for the correct data.
    */
    while (strcmp(choice, "1") != 0 && strcmp(choice, "2") != 0 && strcmp(choice, "3") != 0)
    {
        printf(RED "Invalid input!\n\n" RESET);
        sleep(2);
        getMenuChoice(choice);
    }

    /* This code will run the main game logic */
    if (strcmp(choice, "1") == 0)
    {
        game_logic(board, &player1, &player2, round_number);
    }
    else if (strcmp(choice, "2") == 0)
    {
        /* Display to the user how to play the game */
        howToPlay();
        printf("Waiting 5 seconds...\n\n" RESET);
        sleep(5);
        getMenuChoice(choice);

        while (strcmp(choice, "1") != 0 && strcmp(choice, "2") != 0 && strcmp(choice, "3") != 0)
        {
            printf(RED "Invalid input!\n\n" RESET);
            sleep(2);
            getMenuChoice(choice);
        }

        if (strcmp(choice, "1") == 0)
        {
            game_logic(board, &player1, &player2, round_number);
        }
        else if (strcmp(choice, "2") == 0)
        {
            howToPlay();
        }
        else if (strcmp(choice, "3") == 0)
        {
            printf(RED "Goodbye!\n" RESET);
            exit(1);
        }
    }
    else if (strcmp(choice, "3") == 0)
    {
        /* Exit the program */
        printf(RED "Goodbye!\n" RESET);
        exit(1);
    }

    // Return 0 to show that the program has run successfully
    return 0;
}
