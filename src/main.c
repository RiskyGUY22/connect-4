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
# limitations under the License.*/

// Include the necessary libraries
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Lots of implementation is here, for ref: src/functions.c
#include <functions.h>

void game_logic(char board[][7][4], struct instance *player1, struct instance *player2)
{
	// Implement game logic here

	// Create x and y coordinated for the user's input
	int x, y;

	print_board(board); // Initial display of the board

	while (1)
	{
		// Get Player 1 Input, and change the board value
		getPlayersInput(&x, &y, board, player1);
		changeBoardValue(board, x, y, player1);
		print_board(board);

        // Check if Player 1 has won
        if (checkPlayerWon(board)) {
            printf(RED "\nGAME OVER!\nPlayer 1 has won!\n" RESET);
            return;
        }

		// Get Player 2 Input, and change the board value
		getPlayersInput(&x, &y, board, player2);
		changeBoardValue(board, x, y, player2);
		print_board(board);

        // Check if Player 2 has won
        if (checkPlayerWon(board)) {
            printf(RED "\nGAME OVER!\nPlayer 2 has won!\n" RESET);
            return;
        }
	}
}

int main()
{

	// Define the array to represent the board and initialize it with dotted circles
	// *NOTE* essentially with Unicode in C, one arguement is worth "4" values so we need to make it a 3D array.
	char board[6][7][4] = {
		{"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
		{"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
		{"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
		{"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
		{"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
		{"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"}};

	// Initialise player instances
	struct instance player1;
	struct instance player2;

	// Set player names
	initInstance(&player1, "Player1", "TT");
	initInstance(&player2, "Player2", "Computer");

	// Call the menu function to get input from user
	char choice[8];
	getMenuChoice(choice);

	printf("\n");

    while (strcmp(choice, "1") != 0 && strcmp(choice, "2") != 0 && strcmp(choice, "3") != 0) {
        printf(RED "Invalid input!\n\n" RESET);
        sleep(2);
        getMenuChoice(choice);
    }

    if (strcmp(choice, "1") == 0) {
        game_logic(board, &player1, &player2);
    } else if (strcmp(choice, "2") == 0) {
        howToPlay();
        printf("Waiting 5 seconds...\n\n" RESET);
        sleep(5);
        getMenuChoice(choice);
        if (strcmp(choice, "1") == 0) {
            game_logic(board, &player1, &player2);
        } else if (strcmp(choice, "2") == 0) {
            howToPlay();
        } else if (strcmp(choice, "3") == 0) {
            printf(RED "Goodbye!\n" RESET);
            return 1;
        }
    } else if (strcmp(choice, "3") == 0) {
        // Exit program
        printf(RED "Goodbye!\n" RESET);
        return 1;
    }

	// Return 0 to show that the program has run successfully
	return 0;
}
