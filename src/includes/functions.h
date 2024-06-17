#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

// Define Unicode formmating for the game
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

// Define Unicode formmating for the game
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"

#define BLANK_CIRCLE "\xE2\x97\x8C"
#define LINED_CIRCLE "\xE2\x97\x8B"
#define FILLED_CIRCLE "\xE2\x97\x8F"

void print_board(char board[][7][4]);

// Define a struct to hold player data
struct instance
{
    char player[100];
    char player_name[4096];
};

void changeBoardValue(char board[][7][4], int x, int y, struct instance *instance);
void initInstance(struct instance *instance, char *player, char *player_name);
void checkValid(int *x, int *y, char board[][7][4]);
void getPlayersInput(int *x, int *y, char board[][7][4], struct instance *instance);
int getMenuChoice(int *choice);
bool checkPlayerWon();

#endif /* FUNCTIONS_H */
