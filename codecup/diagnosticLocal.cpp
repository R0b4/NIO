#include "zuniq.hpp"
#include <stdio.h>
#include <chrono>
#include <iostream>

//this program was used to see how fast the codecup server was compared to my computer

void convertToBoard(char *board, Board *newBoard) {
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

#define STR_SIZE 15
const char getMovesStr[STR_SIZE + 1] = 	"getMoves time: ";
const char myMoveStr[STR_SIZE + 1] = 	"My Move:       ";

int serverTime = 0;
int localTime = 0;

int main() {
	FILE *f = fopen("data.txt", "rb");
	fseek(f, 0, SEEK_END);
	long fsize = ftell(f);
	fseek(f, 0, SEEK_SET);  /* same as rewind(f); */

	char *string = (char *)malloc(fsize + 1);
	fread(string, 1, fsize, f);
	fclose(f);

	string[fsize] = '\0';

	char *pos = string;
	for (;;){
		if (memcmp(pos, myMoveStr, STR_SIZE) == 0){
			Board b;
			convertToBoard(pos + STR_SIZE, &b);

			int myTime;
			Timer<std::chrono::microseconds> timer(&myTime);
			timer.start();
			for (int i = 0; i < 1000; i++){
				Move *first = nullptr;
				getMoves(first, &b);
				if (first != nullptr) deleteMoves(first);
			}
			timer.stop();
			std::cerr << "getMoves time: " << myTime << std::endl;
			localTime += myTime;

		} else if (memcmp(pos, getMovesStr, STR_SIZE) == 0){
			int time = std::atoi(pos + STR_SIZE);
			std::cerr << "Server getMoves time: " << time << std::endl;
			serverTime += time;
		}

		for (int i = 0;; i++){
			if ( ((pos - string) + i) == fsize) goto after;

			if (*(pos + i) == '\n'){
				pos += i + 1;
				break;
			}
		}
	}
	after:

	std::cerr << "Total local time: " << localTime << std::endl;
	std::cerr << "Total server time: " << serverTime << std::endl;
}