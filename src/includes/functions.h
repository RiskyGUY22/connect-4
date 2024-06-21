#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/* Library needed for checking if someone has won the game,
   a boolean value makes the most sense.
*/
#include <stdbool.h>

/* Define some ASCII values for better formatting */
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define UNDERLINE "\033[4m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"

/* Define some Unicode values for the game board */
#define BLANK_CIRCLE "\xE2\x97\x8C"  /* Blank */
#define LINED_CIRCLE "\xE2\x97\x8B"  /* Player 1 */
#define FILLED_CIRCLE "\xE2\x97\x8F" /* Player 2 */

/* Dimensions of our game board */
#define ROWS 6
#define COLS 7

/* Define a struct to hold player data */
struct instance
{
    char player[100];
    char player_name[4096];
};

/* All of the functions used in functions.c */
void print_board(char board[][COLS][4]);
void changeBoardValue(char board[][COLS][4], int x, int y, struct instance *instance);
void initInstance(struct instance *instance, char *player, char *player_name);
void checkValid(int *x, int *y, char board[][COLS][4]);
void getPlayersInput(int *x, int *y, char board[][COLS][4], struct instance *instance);
int getMenuChoice(char choice[8]);
bool checkLine(char board[][COLS][4], int startX, int startY, int dx, int dy, const char playerCircle[]);
bool checkPlayerWon(char board[][COLS][4]);
void howToPlay();

#endif /* FUNCTIONS_H */
