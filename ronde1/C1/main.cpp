#include <iostream>
#include <string.h>
#define BOARD_SIZE 6
//Ik heb eerst D gedaan, dus er zouden nog onnodige dingen tussen kunnen zitten

struct Point {
	bool up;
	bool right;
};

struct Board {
	Point points[BOARD_SIZE][BOARD_SIZE];
};

struct Move {
	Board board;

	unsigned char x;
	unsigned char y;
	bool vert;
};

void copyBoard(Board *source, Board *destination){
	memcpy(destination->points, source->points, BOARD_SIZE * BOARD_SIZE * sizeof(Point));
}

bool traceLine(bool line[BOARD_SIZE][BOARD_SIZE], Move *move, unsigned char x, unsigned char y, char direction) {

	if (line[x][y]) {
		if (x != move->x || y != move->y) return false;
		return true;
	}
	line[x][y] = true;

	if (move->board.points[x][y].up && direction != 'd') {
		if (traceLine(line, move, x, y + 1, 'u')) return true;
	}
	if (move->board.points[x][y].right && direction != 'l') {
		if (traceLine(line, move, x + 1, y, 'r')) return true;
	}
	if (y > 0 && move->board.points[x][y - 1].up && direction != 'u') {
		if (traceLine(line, move, x, y - 1, 'd')) return true;	
	}
	if (x > 0 && move->board.points[x - 1][y].right && direction != 'r') {
		if (traceLine(line, move, x - 1, y, 'l')) return true;
	}

	line[x][y] = false;
	return false;
}

bool checkMove(Move *move, Board *board) {
	if (move->vert ? board->points[move->x][move->y].up : board->points[move->x][move->y].right) return false;

	bool line[BOARD_SIZE][BOARD_SIZE];
	memset(line, 0, sizeof(bool) * BOARD_SIZE * BOARD_SIZE);
	copyBoard(board, &move->board);

	if (move->vert) {
		move->board.points[move->x][move->y].up = true;
	} else {
		move->board.points[move->x][move->y].right = true;
	}

	return traceLine(line, move, move->x, move->y, '0');
}

unsigned char getMoves(Board *board) {
	unsigned char length = 0;
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			for (int k = 0; k < 2; k++) {
				Move move;
				move.x = x;
				move.y = y;

				if (k == 0 ? y < BOARD_SIZE - 1 : x < BOARD_SIZE - 1) {
					move.vert = k == 0;
					if (checkMove(&move, board)) {
						length++;
					}
				}
			}
		}
	}
	return length;
}

void fillBoard(Board *b) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			b->points[i][j].up = false;
			b->points[i][j].right = false;
		}
	}
}

int main(){
	Board b;
	fillBoard(&b);

	char in[4];
	int amount;
	std::cin >> amount;
	std::cin.getline(in, 4);

	for (int i = 0; i < amount; i++){
		std::cin.getline(in, 4);
		if (in[2] == 'v'){
			b.points[in[1] - '1'][in[0] - 'A'].up = true;
		} else {
			b.points[in[1] - '1'][in[0] - 'A'].right = true;
		}
	}

	std::cout << (int)getMoves(&b) << std::endl;
	std::cout.flush();
}