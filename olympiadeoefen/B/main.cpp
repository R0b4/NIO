#include <iostream>

#define BITS 32

#define uchar uint_fast8_t
#define uint uint_fast32_t

int main(){
	char string[BITS + 1];
	string[BITS] = '\0';

	char *print = (string + 31);

	uint num;
	std::cin >> num;

	for (uchar i = 0; i < BITS; i++){
		bool one = ((num >> i) & 1) == 1;
		if (one) print = string + BITS - 1 - i;
		string[31 - i] = one ? '1' : '0';
	}

	puts(print);
}