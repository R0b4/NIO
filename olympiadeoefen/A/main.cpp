#include <iostream>

#define LIST_SIZE 3

const char *symbols[] = {"@", "/\\", "|"};
const int amounts[] = {100, 10, 1};

int main(){
	uint32_t num;
	std::cin >> num;

	for (uint32_t i = 0; i < LIST_SIZE; i++){
		uint32_t amount = num / amounts[i];
		num %= amounts[i];

		for (uint32_t j = 0; j < amount; j++) fputs(symbols[i], stdout);
	}
	
	putchar('\n');
}