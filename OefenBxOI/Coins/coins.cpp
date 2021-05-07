#include <iostream>
#include <vector>

#define TAILS 2
#define HEADS 1

#define EMPTY 0
#define COIN 1

void remove(int i);
void reveal(int i);

void assistant(std::vector<int> coins){
	int count = 0;
	for (int i = coins.size() - 1; i > -1; i--){
		if (coins[i] == TAILS) count++;
		else {
			if (count > 0){
				remove(i);
				count--;
				coins[i] = EMPTY;
			}
		}
	}
	for (int i = coins.size() - 1; i > -1; i--){
		if (count == 0) break;
		if (coins[i] == TAILS) continue;
		if (coins[i] == EMPTY) continue;

		remove(i);
		count--;
		coins[i] = EMPTY;
	}
}

void magician(std::vector<int> coins){
	int count = 0;
	for (int i = 0; i < coins.size(); i++){
		if (coins[i] == EMPTY) count++;
		else {
			if (count > 0) count--;
		}
	}
	for (int i = 0; i < coins.size(); i++){
		if (coins[i] == EMPTY) count++;
		else {
			if (count > 0){
				count--;
			} else {
				reveal(i);
			}
		}
	}
}