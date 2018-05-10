/*
Aufgabe		Game of Life
Autor		Florian Bopp
Datum		1.5.18

Kurzbeschreibung:	This program simulates the famous "Game Of Life" by Conway,
					it lets you choose a starting formation or lets you create your own
					formation.
					You decide how much time one generation lives and you can see the 
					screen current generation on top of the console window.
*/
#define _CRT_SECURE_NO_WARNINGS
#define CELL 219							//Define the character representing a cell.
typedef unsigned char UCHAR;

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>


/******************functionsprototypes**********************/
void flashStandardInput(void);
void newline(void);

void printBoard(UCHAR board[22][78]);

//formations
void blinker(UCHAR board[22][78]);
void block(UCHAR board[22][78]);
void beehive(UCHAR board[22][78]);
void beacon(UCHAR board[22][78]);
void glider(UCHAR board[22][78]);
void myFormation(UCHAR board[22][78]);
void gliderGun(UCHAR board[22][78]);

//functions for creting the next generation
void nextGen(UCHAR board[22][78], UCHAR board_next[22][78]);
int neighborCounter(UCHAR board[22][78], int i, int j);
void boardcpy(UCHAR board_source[22][78], UCHAR board_destination[22][78]);
void boardclr(UCHAR board[22][78]);

/******************Main function********************/
int main(void) { 
	char again[2] = { 0 };
	do {
		UCHAR board_now[22][78] = { 0 };		//two boards are needed so that changes dont affect the current board
		UCHAR board_next[22][78] = { 0 };
		double input = 0;
		int check = 0;
		int generation = 1;
		int speed = 1;
		int success = 0;

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
		switch ((int)input) {	//switchcase for coppying the starting formation to the board
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
		while (!_kbhit())
		{
			printf("%i. Generation:\n\n", generation++);
			nextGen(board_now, board_next);		//function to create the nextgen is called
			boardcpy(board_next, board_now);	//the nextgeneration board gets copied to the now board
			boardclr(board_next);				//the nextgeneration board gets cleared
			printBoard(board_now);				
			Sleep(speed);
			system("cls");
		}
		do
		{
			system("cls");
			printf("Game stopped...\nstart over? (y/n): ");
			success = scanf("%1[YNyn]", again);
			flashStandardInput();
			if (success != 1)
				printf("only Y or N is accepted input");
		} while (success != 1);
		
	} while (!strcmp(again, "y") || !strcmp(again, "Y"));
	
	return 0;
}

/******************Functions*******************/
void printBoard(UCHAR board[22][78]) {
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

void blinker(UCHAR board[22][78]) {
	board[11][38] = CELL;
	board[11][39] = CELL;
	board[11][40] = CELL;
}

void block(UCHAR board[22][78]) {
	board[11][38] = CELL;
	board[11][39] = CELL;
	board[12][38] = CELL;
	board[12][39] = CELL;
}

void beehive(UCHAR board[22][78]) {
	board[11][39] = CELL;
	board[12][38] = CELL;
	board[12][40] = CELL;
	board[13][38] = CELL;
	board[13][40] = CELL;
	board[14][39] = CELL;
}

void beacon(UCHAR board[22][78]) {
	board[11][39] = CELL;
	board[11][40] = CELL;
	board[12][40] = CELL;
	board[13][37] = CELL;
	board[14][37] = CELL;
	board[14][38] = CELL;
}

void glider(UCHAR board[22][78]) {
	board[11][39] = CELL;
	board[11][40] = CELL;
	board[12][38] = CELL;
	board[12][40] = CELL;
	board[13][40] = CELL;
}

void myFormation(UCHAR board[22][78]) {
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
		board[yCoord-1][xCoord-1] = CELL;
		system("cls");
		printf("Ok...  so far the board looks like this:\n");
		printBoard(board);
	} while (xCoord != 0 || yCoord != 0);
	system("cls");
}

void gliderGun(UCHAR board[22][78]) {
	board[5][14] = CELL;

	board[6][13] = CELL;
	board[6][15] = CELL;
	
	board[7][12] = CELL;
	board[7][16] = CELL;
	board[7][17] = CELL;
	board[7][26] = CELL;
	
	board[8][1] = CELL;
	board[8][2] = CELL;
	board[8][12] = CELL;
	board[8][16] = CELL;
	board[8][17] = CELL;
	board[8][23] = CELL;
	board[8][24] = CELL;
	board[8][25] = CELL;
	board[8][26] = CELL;
	board[8][31] = CELL;

	board[9][1] = CELL;
	board[9][2] = CELL;
	board[9][12] = CELL;
	board[9][16] = CELL;
	board[9][17] = CELL;
	board[9][22] = CELL;
	board[9][23] = CELL;
	board[9][24] = CELL;
	board[9][25] = CELL;
	board[9][31] = CELL;

	board[10][13] = CELL;
	board[10][15] = CELL;
	board[10][22] = CELL;
	board[10][25] = CELL;
	board[10][35] = CELL;
	board[10][36] = CELL;

	board[11][14] = CELL;
	board[11][22] = CELL;
	board[11][23] = CELL;
	board[11][24] = CELL;
	board[11][25] = CELL;
	board[11][35] = CELL;
	board[11][36] = CELL;

	board[12][23] = CELL;
	board[12][24] = CELL;
	board[12][25] = CELL;
	board[12][26] = CELL;

	board[13][26] = CELL;
}

void nextGen(UCHAR board[22][78], UCHAR board_next[22][78]){
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 78; j++)
		{
			if (board[i][j] == CELL)	//if the current cell is alive check for number of alive neighbors and fill the next generation board acordingly
			{
				if (neighborCounter(board, i, j) == 3 || neighborCounter(board, i, j) == 2)
					board_next[i][j] = CELL;
			}
			else if (board[i][j] == 0) //if the current cell is dead, check for number of alive neighbors and fill the next generation board acordingly
			{
				if (neighborCounter(board, i, j) == 3)
				{
					board_next[i][j] = CELL;
				}
			}
		}
	}
}

int neighborCounter(UCHAR board[22][78], int i, int j) {				//checks all direct neighbors of the current cell and returns the number of alive neighbors
	int neighbors = 0;
	if (board[i - 1][j - 1] == CELL && i-1 >= 0 && j-1 >= 0 )		//conditions to check neighbors and to check for walls of the board
	{
		neighbors++;
	}
	if (board[i - 1][j] == CELL && i - 1 >= 0)
	{
		neighbors++;
	}
	if (board[i - 1][j + 1] == CELL && i - 1 >= 0 && j + 1 < 78)
	{
		neighbors++;
	}
	if (board[i][j - 1] == CELL && j - 1 >= 0)
	{
		neighbors++;
	}
	if (board[i][j + 1] == CELL && j + 1 < 78)
	{
		neighbors++;
	}
	if (board[i + 1][j - 1] == CELL && i + 1 < 22 && j - 1 >= 0)
	{
		neighbors++;
	}
	if (board[i + 1][j] == CELL && i+1 < 22)
	{
		neighbors++;
	}
	if (board[i + 1][j + 1] == CELL && i + 1 <22 && j + 1 < 78)
	{
		neighbors++;
	}
	return neighbors;
}

void boardcpy(UCHAR board_source[22][78], UCHAR board_destination[22][78]) {
	for (int i = 0; i < 22; i++)
	{
		for (int j = 0; j < 78; j++)
		{
			board_destination[i][j] = board_source[i][j];
		}
	}

}

void boardclr(UCHAR board[22][78]) {
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

