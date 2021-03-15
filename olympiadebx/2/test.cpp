#include <iostream>

int main(int argc, char **argv){
	int length = atoi(argv[1]);
	int max = atoi(argv[2]);

	srand(clock());

	printf("%i ", length);
	for (int i = 0; i < length; i++){
		printf("%i ", ((rand() - INT32_MAX / 2) * 2) % max);
	}

	fflush(stdout);
}