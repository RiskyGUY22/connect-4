#include <stdio.h>
#include <wchar.h>
#include <locale.h>

void print_board() {

	setlocale(LC_CTYPE, "");
	wchar_t character = 0X25CC;

	for(int i=0; i < 6; i++) {

		for(int j=0; j < 7; j++) {

			wprintf(L"%lc", character);

		}
		wprintf(L"\n");
	}
}

int main() {

	int choice;

	printf("Welcome to my Connect-4 Game!\n");
	printf("1. Start\n");
	printf("2. Options\n");
	printf("3. Quit\n");

	printf("\nOPTION: ");
	scanf("%d", &choice);


	print_board();
	if(choice == 1) {
		print_board();
	}
	else if(choice == 2) {
		printf("Not implemented\n");
	}
	else if(choice == 3) {
		printf("Not implemented\n");
	}

	return 0;
}
