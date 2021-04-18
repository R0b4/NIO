#include <iostream>

#define SIZE 1000
#define AMOUNT 10

int main(){
	FILE *f = fopen("in.txt", "wb");

	for (int j = 0; j < AMOUNT * 2; j++){
		for (int i = 0; i < SIZE; i++){
			unsigned int r = rand();
			r %= 95;
			r += 32;

			putc(r, f);
		}
		putc('\n', f);
	}
}