#include <iostream>

#define BASE 60
#define BUFFER_SIZE 1000

#define uchar uint_fast8_t
#define uint uint_fast32_t

char *printNum(uchar num, char *string){
	uchar amount = num % 10;
	num = (num - amount) / 10;

	for (int i = 0; i < amount; i++){
		*string = '|';
		string--;
	}

	for (int i = 0; i < num; i++){
		*string = '<';
		string--;
	}

	return string;
}

int main(){
	uint num;
	std::cin >> num;

	char buffer[BUFFER_SIZE + 1];
	buffer[BUFFER_SIZE] = '\0';

	char *string = buffer + BUFFER_SIZE - 1;

	for (;;){
		uchar amount = num % BASE;
		num = (num - amount) / BASE;

		if (amount == 0) break;

		string = printNum(amount, string);
	}

	puts(string + 1);
}