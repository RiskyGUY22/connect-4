#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Define Unicode formmating for the game
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"

// Define Unicode formmating for the game
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"

#define LINED_CIRCLE "\xE2\x97\x8B"

void print_board(char board[][7][4]);

void changeBoardValue(char *board[][7][4], int *x, int *y);

// Define a struct to hold player data
struct instance
{
    char player[100];
    char player_name[4096];
};

void initInstance(struct instance *instance, char *player, char *player_name);
void checkValidX(int *x);
void checkValidY(int *y);
void getInput(int *x, int *y);
int getMenuChoice(int *choice);

#endif /* FUNCTIONS_H */
