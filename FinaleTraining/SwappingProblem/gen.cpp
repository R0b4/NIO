#include <iostream>

#define N 200000
#define MAX_NUM 100

int main(){
	FILE *f = fopen("gin.txt", "wb");

	fprintf(f, "%i\n", N);
	for (int i = 0; i < N; i++){
		fprintf(f, "%i ", rand() % MAX_NUM);
	}
	fprintf(f, "\n");
	for (int i = 0; i < N; i++){
		fprintf(f, "%i ", rand() % MAX_NUM);
	}
	fprintf(f, "\n");
}