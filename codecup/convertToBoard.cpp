#include "zuniq.hpp"
#include <stdio.h>
#include <iostream>

//utillity program to convert the shorter representation of a board which was printed during competion to an actual board type
/*
compile with:
g++ convertToBoard.cpp -o convert

Example:

terminal? convert 772752667642673632662300362200010000

would print:
x=x=x=x=o=o 
|       |   
x=x=x=x=x=o 
|   |     | 
o=x=o=o=o=o 
  | |       
x=x=x=o=o=o 
|     |     
x x o=o o o 
|   |       
o=o=o=o o o 
            

*/

void convertToBoard(char *board, Board *newBoard){
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			unsigned int index = x * BOARD_SIZE + y;
			board[index] -= '0';
			newBoard->points[x][y].up = (board[index] & 1) == 0 ? false : true;
			newBoard->points[x][y].right = (board[index] & 2) == 0 ? false : true;
			newBoard->points[x][y].boxed = (board[index] & 4) == 0 ? false : true;
		}
	}
}

int main(int argc, char **argv){
	Board b;

	convertToBoard(argv[1], &b);
	printBoard(&b, stdout);
}