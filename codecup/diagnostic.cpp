#include <iostream>
#include <chrono>
#include <stdio.h>
#include <cstdlib>
#include <string.h>
#define LOG(x) std::cout << x << std::endl

//this program was used to see how fast the codecup server was compared to my computer

#define BOARD_SIZE 6
#define PLAY_GAMES 100

#define START_SIZE 5
const char start[START_SIZE + 1] = "Start";

#define QUIT_SIZE 4
const char quit[QUIT_SIZE + 1] = "Quit";

#define THEIR_MOVE_SIZE 15
const char theirMove[THEIR_MOVE_SIZE + 1] = 	"Their move:    ";

#define MY_MOVE_SIZE 15
const char myMove[MY_MOVE_SIZE + 1] = 			"My Move:       ";

#define TIME_SIZE 15
const char timeStr[TIME_SIZE + 1] = 			"Time:          ";

#define AMOUNT_SIZE 15
const char amountStr[AMOUNT_SIZE + 1] = 		"Moves left:    ";

#define WIN_PERCENTAGE 15
const char winStr[WIN_PERCENTAGE + 1] = 		"Winpercentage: ";

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

void printMiniBoard(Board *board, FILE *file) {
	char output[BOARD_SIZE * BOARD_SIZE + 1];
	output[BOARD_SIZE * BOARD_SIZE] = '\0';
	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {
			unsigned int index = x * BOARD_SIZE + y;
			output[index] = 0;
			output[index] |= board->points[x][y].up 	? 0b001 : 0;
			output[index] |= board->points[x][y].right 	? 0b010 : 0;
			output[index] |= board->points[x][y].boxed 	? 0b100 : 0;
			output[index] += '0';
		}
	}
	std::cerr << output << std::endl;
}

void copyBoard(Board *source, Board *destination) {
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

void counterClockWiseEdge(int x, int y, char dir, bool selected[BOARD_SIZE][BOARD_SIZE], const char line[BOARD_SIZE][BOARD_SIZE], const Board *board){
	if (selected[x][y]) return;

	if (line[x][y] == 'u' && dir != 'd'){
		selected[x][y] = true;
		counterClockWiseEdge(x, y + 1, 'u', selected, line, board);

	} else if (line[x][y] == 'r' && dir != 'l'){
		selected[x][y] = false;
		counterClockWiseEdge(x + 1, y, 'r', selected, line, board);

	} else if (line[x][y] == 'd' && dir != 'u'){
		selected[x][y] = dir == 'l';
		counterClockWiseEdge(x, y - 1, 'd', selected, line, board);

	} else if (line[x][y] == 'l' && dir != 'r'){
		selected[x][y] = dir != 'd';
		counterClockWiseEdge(x - 1, y, 'l', selected, line, board);
	}
}

void clockWiseEdge(int x, int y, char dir, bool selected[BOARD_SIZE][BOARD_SIZE], const char line[BOARD_SIZE][BOARD_SIZE], const Board *board){
	if (selected[x][y]) return;

	if (line[x][y] == 'u' && dir != 'd'){
		selected[x][y] = false;
		clockWiseEdge(x, y + 1, 'u', selected, line, board);

	} else if (line[x][y] == 'r' && dir != 'l'){
		selected[x][y] = true;
		clockWiseEdge(x + 1, y, 'r', selected, line, board);

	} else if (line[x][y] == 'd' && dir != 'u'){
		selected[x][y] = dir != 'l';
		clockWiseEdge(x, y - 1, 'd', selected, line, board);

	} else if (line[x][y] == 'l' && dir != 'r'){
		selected[x][y] = dir == 'd';
		clockWiseEdge(x - 1, y, 'l', selected, line, board);
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
				counterClockWiseEdge(i, j, 'l', selected, line, &move->board);
				goto afteredge;
			} else if (line[i][j] == 'r'){
				clockWiseEdge(i, j, 'd', selected, line, &move->board);
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

void deleteMoves(Move *first) {
	Move *next;
	for (;;) {
		next = first->next;
		delete first;
		first = next;
		if (first == nullptr) return;
	}
}

class Player {
protected:
	Board *board;
	Move *first = nullptr;

public:
	~Player() {
		Clean();
	}

	void setBoard(Board *board) {
		this->board = board;
	}

	Move *makeMove() {
		unsigned char amount = getMoves(this->first, this->board);
		if (amount == 0) return nullptr;
		Move *selected = selectMove(this->first, amount);
		copyBoard(&selected->board, this->board);
		return selected;
	}

	virtual Move *selectMove(Move *first, unsigned char amount) {
		return first;
	}

	virtual void Clean() {
		if (first == nullptr) return;
		deleteMoves(first);
		first = nullptr;
	}
};

bool MonteCarlo(Board *b, bool turn) {
	Move *first;
	unsigned char amount = getMoves(first, b);
	if (amount == 0) return !turn;

	int random = rand() % amount;
	Move *selected = first;
	for (int i = 0;; selected = selected->next, i++) {
		if (i == random) break;
	}

	bool mon = MonteCarlo(&selected->board, !turn);
	deleteMoves(first);
	return mon;
}

template<class ToDuration>
struct Timer {
	std::chrono::time_point<std::chrono::steady_clock> before;
	int *time;

	Timer(int *time) {
		this->time = time;
		*time = 0;
	}

	void start() {
		before = std::chrono::steady_clock::now();
	}

	void stop() {
		std::chrono::time_point<std::chrono::steady_clock> after = std::chrono::steady_clock::now();;
		*time += std::chrono::duration_cast<ToDuration>(after - before).count();
	}

	void getTime() {
		stop();
		start();
	}
};

typedef Timer<std::chrono::milliseconds> MilliTimer;

#define ITERATE1 (T > 28000 ? 10 : (amount > 40 ? 30 : (amount > 20 ? 100 : 180)))
class AlgoPlayer : public Player {
public:

	int T;
	MilliTimer t;

	AlgoPlayer() : t(&this->T){
		
	}

	Move *selectMove(Move *first, unsigned char amount) {
		t.start();
		Move *best = nullptr;
		int biggestValue = -1;
		for (;; first = first->next) {
			if (T > 29500) {
				best = first;
				break;
			}

			int wins = 0;
			for (int i = 0; i < ITERATE1; i++) {
				wins += MonteCarlo(&first->board, false) ? 1 : 0;
			}

			if (wins > biggestValue) {
				biggestValue = wins;
				best = first;
			}
			if (first->next == nullptr) {
				int winPer = (wins * 100) / ITERATE1;
				std::cerr << winStr << winPer << std::endl;
				std::cerr << amountStr << (int)amount << std::endl;
				break;
			}
		}
		t.stop();
		return best;
	}
};

class ConsolePlayer : public Player {
	char in[10];
	Move *other;

public:
	Move *makeMove() {
		other = new Move;
		std::cin.getline(in, 10);

		if (memcmp(in, start, START_SIZE) == 0) {
			return other;
		}
		if (memcmp(in, quit, QUIT_SIZE) == 0) {
			return nullptr;
		}

		other->y = in[0] - 'A';
		other->x = in[1] - '1';
		other->vert = in[2] == 'v';

		if (checkMove(other, this->board)) {
			copyBoard(&other->board, this->board);
			return other;
		} else {
			return nullptr;
		}
	}

	void Clean() {
		if (other == nullptr) return;
		delete other;
		other = nullptr;
	}
};

class RandomPlayer : public Player {
public:
	Move *selectMove(Move *first, unsigned char amount) {
		int number = rand() % amount;
		for (int i = 0;; i++, first = first->next) {
			if (i == number) {
				return first;
			}
		}
		return first;
	}
};

int main() {
	std::cerr << start << std::endl;
	srand(time(0));
	std::chrono::time_point<std::chrono::steady_clock> before = std::chrono::steady_clock::now();

	Board b;
	fillBoard(&b);

	ConsolePlayer console;
	RandomPlayer me;

	console.setBoard(&b);
	me.setBoard(&b);

	char out[4];
	for (int i = 0;; i++) {
		std::cerr << i << std::endl;
		if (console.makeMove() == nullptr) {
			break;
		}
		fprintf(stderr, theirMove);
		printMiniBoard(&b, stderr);

		Move *mine = me.makeMove();
		if (mine == nullptr) {
			break;
		}
		fprintf(stderr, myMove);
		printMiniBoard(&b, stderr);

		int time;
		Timer<std::chrono::microseconds> timer(&time);
		timer.start();
		for (int i = 0; i < 1000; i++){
			Move *first = nullptr;
			getMoves(first, &b);
			if (first != nullptr) deleteMoves(first);
		}
		timer.stop();
		std::cerr << "getMoves time: " << time << std::endl;


		out[0] = mine->y + 'A';
		out[1] = mine->x + '1';
		out[2] = mine->vert ? 'v' : 'h';
		out[3] = '\0';

		std::cout << out << std::endl;

		std::cerr << std::endl;
		std::cout.flush();
		std::cerr.flush();

		me.Clean();
		console.Clean();
	}
	std::chrono::time_point<std::chrono::steady_clock> after = std::chrono::steady_clock::now();
	int seconds = std::chrono::duration_cast<std::chrono::seconds>(after - before).count();
	std::cerr << timeStr << seconds << 's' << std::endl;
}