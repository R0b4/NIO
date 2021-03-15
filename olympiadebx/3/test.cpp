#include <iostream>

int main(int argc, char **argv){
	FILE *file = fopen(argv[1], "w+");

	int length = argc > 2 ? atoi(argv[2]) : 1000;
	int max = argc > 3 ? atoi(argv[3]) : 1000;

	srand(clock());

	fprintf(file, "%i\n", length);
	for (int i = 0; i < length; i++){
		fprintf(file, "%i\n", rand() % max);
	}

	fflush(file);
}