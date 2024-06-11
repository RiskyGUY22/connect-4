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



// Define Unicode formmating for the game
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define UNDERLINE "\033[4m"

// Define Unicode formmating for the game
#define RED     "\033[0;31m"
#define GREEN   "\033[0;32m"
#define YELLOW  "\033[0;33m"
#define BLUE    "\033[0;34m"

void print_board(char board[][7][4]) {
    // Print column numbers
    printf("    ");
    for (int col = 1; col <= 7; col++) {
        printf("%-4d", col); // Adjusted spacing for alignment
    }
    printf("\n");

    // Print the board
    for (int row = 0; row < 6; row++) {
        printf("%-2d", row + 1); // Adjusted spacing for alignment
        for (int col = 0; col < 7; col++) {
            printf("| %s ", board[row][col]);
        }
        printf("|\n");
    }
}

// Define a struct to hold player data
struct instance {
	char player[100];
	char player_name[4096];
};

/* The players and their data will be handled by structs, 
   this functions is used to define that data.*/

void initInstance(struct instance *instance, char *player, char *player_name) {
	strcpy(instance->player, player);
	strcpy(instance->player_name, player_name);
}

// Simple function to get the user's choice from the menu
int getMenuChoice(int *choice) {

    printf(GREEN"Welcome to my Connect-4 Game!\n\n" RESET);
    printf(BLUE " 1. Start\n" RESET);
    printf(YELLOW " 2. Options\n" RESET);
    printf(RED " 3. Quit\n" RESET);

    printf(BLUE  "\nOPTION: " RESET);

	// Check for invalid inputs
    if (scanf("%d", choice) != 1) {
        fprintf(stderr, "Invalid input\n");
        return 1;
    }

	// Program has run successfully
    return 0;
}

void game_logic() {
	// Implement game logic here
}

int main() {

	// Define the array to represent the board and initialize it with dotted circles
	// *NOTE* essentially with Unicode in C, one arguement is worth "4" values so we need to make it a 3D array.
    char board[6][7][4] = {
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"},
        {"\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C", "\xE2\x97\x8C"}
    };

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
	switch (choice) {
	    case 1:
	        print_board(board);
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
