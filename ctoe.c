#include <stdio.h>
#include <stdlib.h>

#define SIZE 3

char board[SIZE][SIZE];
char player = 'X';
int nextPos;

char getAtPos(int pos);
void setAtPos(int pos, char token);
int isFilledAtPos(int pos);

void printBoard(char board[SIZE][SIZE]) {
	printf("\n %c | %c | %c \n-----------\n %c | %c | %c \n-----------\n %c | %c | %c \n\n", 
			board[0][0], board[0][1], board[0][2], board[1][0], board[1][1], board[1][2], board[2][0], board[2][1], board[2][2]);
}

// void initBoard() {
// 	for (int i = 0; i < SIZE; i++) {
// 		for (int j = 0; j < SIZE; j++) {
// 			board[i][j] = (i*SIZE + j + 1) + '0';
// 		}
// 	}
// }
void initBoard() {
	for (int i = 1; i <= SIZE*SIZE; i++) {
		setAtPos(i, i + '0');
	}
}

void getInputPos() {
	nextPos = -1;
	char tempString[10];
	while (1) {
		printf("%c: Choose a position: ", player);
		scanf("%s", tempString);
		nextPos = atoi(tempString);
		if (nextPos > 0 && nextPos <= SIZE*SIZE && !isFilledAtPos(nextPos)) {
			break;
		}
		printf("\033[31mInvalid Input\033[0m\n");
	}
}

int isWin(){
	int rIdx, cIdx, dIdx, xSum, oSum;
	for (rIdx = 0; rIdx < SIZE; rIdx++) {
		xSum = 0, oSum = 0;
		for (cIdx = 0; cIdx < SIZE; cIdx++) {
			if (board[rIdx][cIdx] == 'X') {xSum++;}
			if (board[rIdx][cIdx] == 'O') {oSum++;}
		}
		if (xSum == 3 || oSum == 3) return 1;
	}
	for (rIdx = 0; rIdx < SIZE; rIdx++) {
		xSum = 0, oSum = 0;
		for (cIdx = 0; cIdx < SIZE; cIdx++) {
			if (board[cIdx][rIdx] == 'X') {xSum++;}
			if (board[cIdx][rIdx] == 'O') {oSum++;}
		}
		if (xSum == 3 || oSum == 3) return 1;
	}
	// minor diagonal
	xSum = 0, oSum = 0;
	for (dIdx = 0; dIdx < SIZE; dIdx++) {
		if (board[dIdx][dIdx] == 'X') {xSum++;}
		if (board[dIdx][dIdx] == 'O') {oSum++;}
	}
	if (xSum == 3 || oSum == 3) return 1;
	// majour diagonal
	xSum = 0, oSum = 0;
	for (dIdx = 0; dIdx < SIZE; dIdx++) {
		if (board[dIdx][SIZE-dIdx-1] == 'X') {xSum++;}
		if (board[dIdx][SIZE-dIdx-1] == 'O') {oSum++;}
	}
	if (xSum == 3 || oSum == 3) return 1;
	return 0;
}

int isTie() {
	for (int pos = 1; pos <= SIZE*SIZE; pos++) {
		if (!isFilledAtPos(pos)) return 0;
	}
	return 1;
}

char getAtPos(int pos) {
	return board[(pos-1)/SIZE][(pos-1)%SIZE];
}

void setAtPos(int pos, char token) {
	board[(pos-1)/SIZE][(pos-1)%SIZE] = token;
}

int isFilledAtPos(int pos) {
	return getAtPos(pos) == 'X' || getAtPos(pos) == 'O';
}

void playTurn() {
	printBoard(board);
	getInputPos();
	setAtPos(nextPos, player);
}

int main(int argc, char const *argv[])
{
	initBoard();
	while (1) {
		playTurn();
		if (isTie()) {
			printf("\033[31;1mYou tied :(\033[0m\n");
			break;
		}
		if (isWin()) {
			printf("\033[36;1mPlayer %c wins!\033[0m\n", player);
			break;
		}
		player = (player == 'X') ? 'O' : 'X';	// change player
	}
	printBoard(board);
	return 0;
}
