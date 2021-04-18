#include <stdio.h>
#include <algorithm>

#define STR_SIZE 1000

int find(char *a, char *b, int **table){
	int max = 0;

	for (int i = 0; a[i] != '\n'; i++){
		for (int j = 1; b[j] != '\n'; j++){
			if (i == 0 || j == 0) table[i][j] = 0;
			else if (a[i - 1] == b[j - 1]) table[i][j] = table[i - 1][j - 1] + 1;
			else table[i][j] = std::max(table[i - 1][j], table[i][j - 1]);

			if (table[i][j] > max) max = table[i][j];
		}
	}

	return max;
}

int main(){
	char *str1 = new char[STR_SIZE];
	char *str2 = new char[STR_SIZE];
	size_t size = STR_SIZE;

	int **table = new int*[STR_SIZE + 1];
	for (int i = 0; i < STR_SIZE + 1; i++) table[i] = new int[STR_SIZE + 1];

	for (;;){
		getline(&str1, &size, stdin);
		getline(&str2, &size, stdin);

		printf("%i\n", find(str1, str2, table));
	}
}