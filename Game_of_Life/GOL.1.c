/*
Aufgabe		Game of Life
Autor		Florian Bopp
Datum		1.5.18

Kurzbeschreibung:	
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

/******************functionsprototypes**********************/
void flashStandardInput(void);
void newline(void);

void printBoard(char board[22][78]);

void blinker(char board[22][78]);
void block(char board[22][78]);
void beehive(char board[22][78]);
void beacon(char board[22][78]);
void glider(char board[22][78]);
void myFormation(char board[22][78]);
void gliderGun(char board[22][78]);

void nextGen(char board[22][78], char board_next[22][78], char board_before[22][78], int generation);
int neighborCounter(char board[22][78], int i, int j);
void boardcpy(char board_source[22][78], char board_destination[22][78]);
void boardclr(char board[22][78]);



/******************Main function********************/
int main(void) {
	char again[10] = { 0 };
	do
	{
		char board_now[22][78] = { 0 };
		char board_next[22][78] = { 0 };
		char board_before[22][78] = { 0 };
		double input = 0;
		int check = 0;
		int generation = 1;
		int speed = 1;

		do {
			printf("1 - Blinker\n");
			printf("2 - Block\n");
			printf("3 - Beehive\n");
			printf("4 - Beacon\n");
			printf("5 - Glider\n");
			printf("6 - my own formation\n");
			printf("7 - Glider Gun\n");

			printf("Choose your starting formation: ");
			check = scanf("%lf", &input);
			flashStandardInput();
			newline();
		} while (check == 0 || input < 1 || input > 7 || input != (int)input); //sichere Abfrage
		switch ((int)input) {
		case 1: blinker(board_now);
			break;
		case 2: block(board_now);
			break;
		case 3: beehive(board_now);
			break;
		case 4: beacon(board_now);
			break;
		case 5: glider(board_now);
			break;
		case 6: myFormation(board_now);
			break;
		case 7: gliderGun(board_now);
			break;
		default:
			break;
		}
		system("cls");
		printf("This is your starting formation...\n");
		printBoard(board_now);
		printf("\nLet's begin\n\n");
		printf("How much time do you want each generation to have?\n(in miliseconds)\n");
		scanf("%d", &speed);
		flashStandardInput();
		boardcpy(board_now, board_before);
		while (!_kbhit())
		{
			printf("%i. Generation:\n\n", generation);
			nextGen(board_now, board_next, board_before, generation);
			boardcpy(board_now, board_before);
			boardcpy(board_next, board_now);
			boardclr(board_next);
			printBoard(board_now);
			Sleep(speed);
			generation++;
			system("cls");
		}
		flashStandardInput();
		printf("Game stopped...\n start over? (y/n): ");
		scanf("%1[YNyn]", again);
	} while (again == "y" || again == "Y");
	
	return 0;
}

/******************Functions*******************/
void printBoard(char board[22][78]) {
	printf("________________________________________________________________________________\n");
	for (int i = 0; i < 22; i++)
	{
		printf("|");
		for (int j = 0; j < 78; j++)
		{
			printf("%c", board[i][j]);
		}
		printf("|\n");

	}
	printf("________________________________________________________________________________\n\n");

}

void blinker(char board[22][78]) {
	board[11][38] = 'X';
	board[11][39] = 'X';
	board[11][40] = 'X';
}

void block(char board[22][78]) {
	board[11][38] = 'X';
	board[11][39] = 'X';
	board[12][38] = 'X';
	board[12][39] = 'X';
}

void beehive(char board[22][78]) {
	board[11][39] = 'X';
	board[12][38] = 'X';
	board[12][40] = 'X';
	board[13][38] = 'X';
	board[13][40] = 'X';
	board[14][39] = 'X';
}

void beacon(char board[22][78]) {
	board[11][39] = 'X';
	board[11][40] = 'X';
	board[12][40] = 'X';
	board[13][37] = 'X';
	board[14][37] = 'X';
	board[14][38] = 'X';
}

void glider(char board[22][78]) {
	board[11][39] = 'X';
	board[11][40] = 'X';
	board[12][38] = 'X';
	board[12][40] = 'X';
	board[13][40] = 'X';
}

void myFormation(char board[22][78]) {
	int xCoord = 0;
	int yCoord = 0;
	printf("In order for you to make your own starting formation, you'll need to specify each coordinate.\nSo please enter the coordinates, and when you are done enter 0\n\n");
	do
	{
		do
		{
			printf("Enter the X-Coordinate (min 1, max 78): ");
			scanf("%i", &xCoord);
			if (xCoord==0)
				break;
			printf("\nEnter the y-Coordinate (min 1, max 22): ");
			scanf("%i", &yCoord);
		} while (xCoord	< 1 || xCoord > 78 || yCoord < 1 || yCoord > 22);
		if (xCoord == 0)
			break;
		board[yCoord-1][xCoord-1] = 'X';
		system("cls");
		printf("Ok...  so far the board looks like this:\n");
		printBoard(board);
	} while (xCoord != 0 || yCoord != 0);
	system("cls");
}

void gliderGun(char board[22][78]) {
	board[5][14] = 'X';

	board[6][13] = 'X';
	board[6][15] = 'X';
	
	board[7][12] = 'X';
	board[7][16] = 'X';
	board[7][17] = 'X';
	board[7][26] = 'X';
	
	board[8][1] = 'X';
	board[8][2] = 'X';
	board[8][12] = 'X';
	board[8][16] = 'X';
	board[8][17] = 'X';
	board[8][23] = 'X';
	board[8][24] = 'X';
	board[8][25] = 'X';
	board[8][26] = 'X';
	board[8][31] = 'X';

	board[9][1] = 'X';
	board[9][2] = 'X';
	board[9][12] = 'X';
	board[9][16] = 'X';
	board[9][17] = 'X';
	board[9][22] = 'X';
	board[9][23] = 'X';
	board[9][24] = 'X';
	board[9][25] = 'X';
	board[9][31] = 'X';

	board[10][13] = 'X';
	board[10][15] = 'X';
	board[10][22] = 'X';
	board[10][25] = 'X';
	board[10][35] = 'X';
	board[10][36] = 'X';

	board[11][14] = 'X';
	board[11][22] = 'X';
	board[11][23] = 'X';
	board[11][24] = 'X';
	board[11][25] = 'X';
	board[11][35] = 'X';
	board[11][36] = 'X';

	board[12][23] = 'X';
	board[12][24] = 'X';
	board[12][25] = 'X';
	board[12][26] = 'X';

	board[13][26] = 'X';
}

void nextGen(char board[22][78], char board_next[22][78], char board_before[22][78], int generation){
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 78; j++)
		{
			if (board[i][j] == 'X')	
			{
				if (neighborCounter(board, i, j) == 3 || neighborCounter(board, i, j) == 2)
					board_next[i][j] = 'X';
			}
			/*else if (generation > 1 && board[i][j] == 0 && board_before[i][j] == 'X' )	
			{
				if (neighborCounter(board, i, j) == 3 )
				{
					board_next[i][j] = 'X';
				}
			} 
			*/
			else if (board[i][j] == 0)
			{
				if (neighborCounter(board, i, j) == 3)
				{
					board_next[i][j] = 'X';
				}
			}
		}
	}
}

int neighborCounter(char board[22][78], int i, int j) {
	int neighbors = 0;
	if (board[i - 1][j - 1] == 'X' && i-1 >= 0 && j-1 >= 0 )
	{
		neighbors++;
	}
	if (board[i - 1][j] == 'X' && i - 1 >= 0)
	{
		neighbors++;
	}
	if (board[i - 1][j + 1] == 'X' && i - 1 >= 0 && j + 1 < 78)
	{
		neighbors++;
	}
	if (board[i][j - 1] == 'X' && j - 1 >= 0)
	{
		neighbors++;
	}
	if (board[i][j + 1] == 'X' && j + 1 < 78)
	{
		neighbors++;
	}
	if (board[i + 1][j - 1] == 'X' && i + 1 < 22 && j - 1 >= 0)
	{
		neighbors++;
	}
	if (board[i + 1][j] == 'X' && i+1 < 22)
	{
		neighbors++;
	}
	if (board[i + 1][j + 1] == 'X' && i + 1 <22 && j + 1 < 78)
	{
		neighbors++;
	}
	return neighbors;
}

void boardcpy(char board_source[22][78], char board_destination[22][78]) {
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 78; j++)
		{
			board_destination[i][j] = board_source[i][j];
		}
	}

}

void boardclr(char board[22][78]) {
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 78; j++)
		{
			board[i][j] = 0;
		}
	}
}

void flashStandardInput(void)
{
	int intCharacter;
	while ((intCharacter = getchar()) != '\n' && intCharacter != EOF);
}

void newline(void) {
	printf("\n");
}

/********************Sichere Abfrage*******************
do {
	printf("Bitte Dimension der Matrix eingeben (1, 2 oder 3 Dimensionen): ");
	check = scanf("%lf", &dimensionen);
	flashStandardInput();
	newline();
} while (check == 0 || dimensionen < 1 || dimensionen > 3 || dimensionen != (int)dimensionen); //sichere Abfrage
*/
