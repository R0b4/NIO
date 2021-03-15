#pragma once
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#include <iostream>
#define LOG(x) std::cout << x << std::endl
#define BOARD_SIZE 6

//base code for zuniq

struct Point {
	bool up;
	bool right;

	bool boxed;
};

struct Board {
	Point points[BOARD_SIZE][BOARD_SIZE];
	bool sizeTaken[(BOARD_SIZE - 1) * (BOARD_SIZE - 1)];
};

struct Move {
	Board board;
	unsigned char boxes;

	unsigned char x;
	unsigned char y;
	bool vert;
	Move *next;
};

void printBoard(Board *board, FILE *file) {
	char output[BOARD_SIZE * 2 + 1];
	output[BOARD_SIZE * 2] = '\0';
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int k = 0; k < 2; k++) {
			for (int x = 0; x < BOARD_SIZE; x++) {
				if (k == 1) {
					output[x * 2] = board->points[x][y].up ? '|' : ' ';
					output[x * 2 + 1] = ' ';
				} else {
					output[x * 2] = board->points[x][y].boxed ? 'x' : 'o';
					output[x * 2 + 1] = board->points[x][y].right ? '=' : ' ';
				}
			}
			std::cerr << output << std::endl;
			std::cerr.flush();
		}
	}
}

void printMiniBoard(Board *board, FILE *file){
	char output[BOARD_SIZE * BOARD_SIZE + 1];
	output[BOARD_SIZE * BOARD_SIZE] = '\0';
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			unsigned int index = x * BOARD_SIZE + y;
			output[index] = 0;
			output[index] += board->points[x][y].up ? 1 : 0;
			output[index] += board->points[x][y].right ? 2 : 0;
			output[index] += board->points[x][y].boxed ? 4 : 0;
			output[index] += '0';
		}
	}
	std::cerr << output << std::endl;
}

void copyBoard(Board *source, Board *destination){
	memcpy(destination->points, source->points, BOARD_SIZE * BOARD_SIZE * sizeof(Point));
	memcpy(destination->sizeTaken, source->sizeTaken, (BOARD_SIZE - 1) * (BOARD_SIZE - 1) * sizeof(bool));
}

bool floodFill(int x, int y, bool selected[BOARD_SIZE][BOARD_SIZE], const char line[BOARD_SIZE][BOARD_SIZE]){
	if (selected[x][y] || line[x][y] != '\0') return false;
	if (x == 0 || y == 0 || x == BOARD_SIZE - 1 || y == BOARD_SIZE - 1) return true;

	selected[x][y] = true;
	if (floodFill(x + 1, y, selected, line)) return true;
	if (floodFill(x - 1, y, selected, line)) return true;
	if (floodFill(x, y + 1, selected, line)) return true;
	if (floodFill(x, y - 1, selected, line)) return true;

	return false;
}

void counterClockWiseEdge(int x, int y, char dir, bool selected[BOARD_SIZE][BOARD_SIZE], const char line[BOARD_SIZE][BOARD_SIZE]){
	if (selected[x][y]) return;

	if (line[x][y] == 'u' && dir != 'd'){
		selected[x][y] = true;

		counterClockWiseEdge(x, y + 1, 'u', selected, line);

	} else if (line[x][y] == 'r' && dir != 'l'){
		selected[x][y] = false;

		counterClockWiseEdge(x + 1, y, 'r', selected, line);

	} else if (line[x][y] == 'd' && dir != 'u'){
		selected[x][y] = dir == 'l';

		counterClockWiseEdge(x, y - 1, 'd', selected, line);

	} else if (line[x][y] == 'l' && dir != 'r'){
		selected[x][y] = dir != 'd';

		counterClockWiseEdge(x - 1, y, 'l', selected, line);
	}
}

void clockWiseEdge(int x, int y, char dir, bool selected[BOARD_SIZE][BOARD_SIZE], const char line[BOARD_SIZE][BOARD_SIZE]){
	if (selected[x][y]) return;

	if (line[x][y] == 'u' && dir != 'd'){
		selected[x][y] = false;
		clockWiseEdge(x, y + 1, 'u', selected, line);
	} else if (line[x][y] == 'r' && dir != 'l'){
		selected[x][y] = true;

		clockWiseEdge(x + 1, y, 'r', selected, line);
	} else if (line[x][y] == 'd' && dir != 'u'){
		selected[x][y] = dir != 'l';

		clockWiseEdge(x, y - 1, 'd', selected, line);
	} else if (line[x][y] == 'l' && dir != 'r'){
		selected[x][y] = dir == 'd';

		clockWiseEdge(x - 1, y, 'l', selected, line);
	}
}

bool countBoxes(char line[BOARD_SIZE][BOARD_SIZE], Move *move){
	bool selected[BOARD_SIZE][BOARD_SIZE];
	memset(selected, false, BOARD_SIZE * BOARD_SIZE);

	bool selectedBuff[BOARD_SIZE][BOARD_SIZE];
	memset(selectedBuff, false, BOARD_SIZE * BOARD_SIZE);

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (line[i][j] == '\0') {
				if (floodFill(i, j, selectedBuff, line)) memcpy(selectedBuff, selected, BOARD_SIZE * BOARD_SIZE);
				else memcpy(selected, selectedBuff, BOARD_SIZE * BOARD_SIZE);
			}
		}
	}


	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (line[i][j] == 'u'){
				counterClockWiseEdge(i, j, 'l', selected, line);
				goto afteredge;
			} else if (line[i][j] == 'r'){
				clockWiseEdge(i, j, 'd', selected, line);
				goto afteredge;
			}
		}
	}
	afteredge:

	unsigned char boxes = 0;
	Board tester;
	copyBoard(&move->board, &tester);

	for (int i = 0; i < BOARD_SIZE; i++){
		for (int j = 0; j < BOARD_SIZE; j++){
			if (selected[i][j]){
				if (tester.points[i][j].boxed) return false;
				tester.points[i][j].boxed = true;
				boxes++;
			}
		}
	}

	//getchar();
	move->boxes = boxes;
	tester.sizeTaken[boxes - 1] = true;
	copyBoard(&tester, &move->board);
	return true;
}

bool traceLine(char line[BOARD_SIZE][BOARD_SIZE], Move *move, unsigned char x, unsigned char y, char direction) {

	if (line[x][y] != '\0') {
		if (x != move->x || y != move->y) return false;
		return countBoxes(line, move);
	}

	if (move->board.points[x][y].up && direction != 'd') {
		line[x][y] = 'u';
		if (traceLine(line, move, x, y + 1, 'u')) return true;
	}
	if (move->board.points[x][y].right && direction != 'l') {
		line[x][y] = 'r';
		if (traceLine(line, move, x + 1, y, 'r')) return true;
	}
	if (y > 0 && move->board.points[x][y - 1].up && direction != 'u') {
		line[x][y] = 'd';
		if (traceLine(line, move, x, y - 1, 'd')) return true;	
	}
	if (x > 0 && move->board.points[x - 1][y].right && direction != 'r') {
		line[x][y] = 'l';
		if (traceLine(line, move, x - 1, y, 'l')) return true;
	}

	line[x][y] = '\0';
	return false;
}

bool checkMove(Move *move, Board *board) {
	if (move->vert ? board->points[move->x][move->y].up : board->points[move->x][move->y].right) return false;
	if (board->points[move->x][move->y].boxed) return false;

	char line[BOARD_SIZE][BOARD_SIZE];
	memset(line, '\0', sizeof(bool) * BOARD_SIZE * BOARD_SIZE);
	copyBoard(board, &move->board);

	if (move->vert) {
		move->board.points[move->x][move->y].up = true;
	} else {
		move->board.points[move->x][move->y].right = true;
	}

	if (traceLine(line, move, move->x, move->y, '0')) {
		return !board->sizeTaken[move->boxes - 1];
	}

	return true;
}

//used to get a linked list of all possible moves
unsigned char getMoves(Move *& first, Board *board) {
	Move *last = nullptr;
	unsigned char length = 0;
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			for (int k = 0; k < 2; k++) {
				Move *move = new Move;
				move->x = x;
				move->y = y;
				move->next = nullptr;

				if (k == 0 ? y < BOARD_SIZE - 1 : x < BOARD_SIZE - 1) {
					move->vert = k == 0;
					if (checkMove(move, board)) {
						length++;

						if (last == nullptr) {
							first = move;
							last = move;
						} else {
							last->next = move;
							last = last->next;
						}
					} else {
						delete move;
					}
				} else {
					delete move;
				}
			}
		}
	}
	return length;
}

//used to empty a board
void fillBoard(Board *b) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			b->points[i][j].up = false;
			b->points[i][j].right = false;
			b->points[i][j].boxed = false;
		}
	}
	for (int i = 0; i < (BOARD_SIZE - 1) * (BOARD_SIZE - 1); i++) {
		b->sizeTaken[i] = false;
	}
}

//deletes a linked list of moves
void deleteMoves(Move *first) {
	Move *next;
	for (;;) {
		next = first->next;
		delete first;
		first = next;
		if (first == nullptr) return;
	}
}


//base class for a zuniq player
class Player{
protected:
	Board *board;
	Move *first = nullptr;

public:
	~Player(){
		Clean();
	}

	void setBoard(Board *board){
		this->board = board;
	}

	Move *makeMove(){
		unsigned char amount = getMoves(this->first, this->board);
		if (amount == 0) return nullptr;
		Move *selected = selectMove(this->first, amount);
		copyBoard(&selected->board, this->board);
		return selected;
	}

	virtual Move *selectMove(Move *first, unsigned char amount){
		return first;
	}

	virtual void Clean(){
		if (first == nullptr) return;
		deleteMoves(first);
		first = nullptr;
	}
};