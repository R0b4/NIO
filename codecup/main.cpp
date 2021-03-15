#include "zuniq.hpp"
#include <iostream>
#include <math.h>
#include <chrono>

#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//used to test different algorithms and parameters

#define BOARD_SIGHT 1

#define LOG(x) std::cout << x << std::endl

#define PLAY_GAMES 50

#define START_SIZE 5
const char *start = "Start";

#define QUIT_SIZE 4
const char *quit = "Quit";

#define THEIR_MOVE_SIZE 13
const char theirMove[THEIR_MOVE_SIZE] = "Their move:\n";

#define MY_MOVE_SIZE 10
const char myMove[MY_MOVE_SIZE] = "My Move:\n";

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

class AlgoPlayer : public Player {
public:
int T;
	MilliTimer t;

	AlgoPlayer() : t(&this->T){

	}

	Move *selectMove(Move *first, unsigned char amount) {
		t.start();
		//std::cerr << "amount: " << (unsigned short)amount << std::endl;
		Move *best;
		int biggestValue = -1;
		for (;; first = first->next) {
			if (T > 29000) {
				best = first;
				break;
			}

			int wins = 0;
			for (int i = 0; i < (T > 27500 ? 10 : (amount > 40 ? 30 : 90)); i++) {
				wins += MonteCarlo(&first->board, false) ? 1 : 0;
			}

			if (wins > biggestValue) {
				biggestValue = wins;
				best = first;
			}
			if (first->next == nullptr) break;
		}
		std::cout << T << std::endl;
		t.stop();
		return best;
	}
};

// (amount > 50 ? 30 : (amount > 40 ? 40 : (amount > 30 ? 90 : (amount > 20 ? 110 : (amount > 10 ? 200 : 500)))))
class AlgoPlayer2 : public Player {
public:
#if 1
	int T;
	MilliTimer t;

	AlgoPlayer2() : t(&this->T){
		
	}

	Move *selectMove(Move *first, unsigned char amount) {
		t.start();
		std::cerr << "amount: " << (unsigned short)amount << std::endl;
		Move *best;
		int biggestValue = -1;
		for (;; first = first->next) {
			if (T > 29000) {
				best = first;
				break;
			}

			int wins = 0;
			for (int i = 0; i < (T > 28000 ? 10 : (amount > 40 ? 35 : (amount > 20 ? 100 : 180))); i++) {
				wins += MonteCarlo(&first->board, false) ? 1 : 0;
			}

			if (wins > biggestValue) {
				biggestValue = wins;
				best = first;
			}
			if (first->next == nullptr) break;
		}
		std::cout << T << std::endl;
		t.stop();
		return best;
	}
#endif
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
	FILE *file = fopen("output.err", "w");
	dup2(fileno(file), STDERR_FILENO);

	LOG("start");
	srand((unsigned)clock());
	int wins = 0;
	int losses = 0;
	for (int i = 0; i < PLAY_GAMES; i++) {
		std::chrono::time_point<std::chrono::steady_clock> before = std::chrono::steady_clock::now();

		Board b;
		fillBoard(&b);

		AlgoPlayer console;
		AlgoPlayer2 me;

		console.setBoard(&b);
		me.setBoard(&b);

		char out[4];
		int time;
		for (;;) {
			Move *mine;
			if ((i & 1) == 0) {
				{
					MilliTimer t(&time);
					t.start();
					mine = me.makeMove();
					if (mine == nullptr) {
						losses++;
						LOG("LOSS");
						break;
					}
					t.stop();
				}


#if BOARD_SIGHT == 1
				std::cerr << "time: " << time << std::endl;
				fprintf(stderr, myMove);
				printBoard(&b, stderr);
#endif

				{
					MilliTimer t(&time);
					t.start();
					if (console.makeMove() == nullptr) {
						wins++;
						LOG("WIN");
						break;
					}
					t.stop();
				}

#if BOARD_SIGHT == 1
				fprintf(stderr, theirMove);
				printBoard(&b, stderr);
#endif
			} else {

				{
					MilliTimer t(&time);
					t.start();
					if (console.makeMove() == nullptr) {
						wins++;
						LOG("WIN");
						break;
					}
					t.stop();
				}

#if BOARD_SIGHT == 1
				fprintf(stderr, theirMove);
				printBoard(&b, stderr);
#endif

				{
					MilliTimer t(&time);
					t.start();
					mine = me.makeMove();
					if (mine == nullptr) {
						losses++;
						LOG("LOSS");
						break;
					}
					t.stop();
				}

#if BOARD_SIGHT == 1
				std::cerr << "time: " << time << std::endl;
				fprintf(stderr, myMove);
				printBoard(&b, stderr);
#endif
			}

			out[0] = mine->y + 'A';
			out[1] = mine->x + '1';
			out[2] = mine->vert ? 'v' : 'h';
			out[3] = '\0';

			//std::cout << out << std::endl;
			std::cout.flush();

			me.Clean();
			console.Clean();
			//getchar();
		}
		std::chrono::time_point<std::chrono::steady_clock> after = std::chrono::steady_clock::now();

		LOG(i << '/' << PLAY_GAMES);
		int seconds = std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count();
		LOG("time: " << seconds << 's' << std::endl);
		//getchar();
	}

	LOG("Wins: " << wins);
	LOG("Losses: " << losses);
}