#include <iostream>
#define NUM 117

void partities(int num, unsigned long long partitie[NUM], int index, int &biggest){
	if (num == 0){
		int product = 1;
		for (int i = 0; i < index; i++){
			product *= partitie[i];
		}
		if (product > biggest){
			std::cout << product << std::endl;
			biggest = product;
		}
	}
	for (int i = 1; i <= num; i++){
		partitie[index] = i;
		partities(num - i, partitie, index + 1, biggest);
	}
}

int main(){
	unsigned long long partitie[NUM];
	int biggest = 0;
	partities(NUM, partitie, 0, biggest);
}