#include <iostream>

#define LIST_SIZE 7

const char *symbols[] = {"M", "D", "C", "L", "X", "V", "I"};
const int amounts[] = {1000, 500, 100, 50, 10, 5, 1};

int main(){
	uint32_t num;
	std::cin >> num;

	for (uint32_t i = 0; i < LIST_SIZE; i++){
		uint32_t amount = num / amounts[i];
		num %= amounts[i];

		if (amount == 4) {
			fputs(symbols[i], stdout);
			fputs(symbols[i - 1], stdout);
		}
		else for (uint32_t j = 0; j < amount; j++) fputs(symbols[i], stdout);
	}
	
	putchar('\n');
}