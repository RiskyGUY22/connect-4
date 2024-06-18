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
	int choice;
	getMenuChoice(&choice);
	printf("\n");

	// Handle the user's input
	switch (choice)
	{
	case 1:
		game_logic(board, &player1, &player2);
		break;
	case 2:
		printf("Options not implemented\n");
		break;
	case 3:
		// Exit program
		printf(RED "Goodbye!\n" RESET);
		return 1;
		break;
	default:
		printf("Invalid choice\n");
		break;
	}

	// Return 0 to show that the program has run successfully
	return 0;
}
