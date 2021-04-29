#include <iostream>
#include <stack>
#include <stdio.h>

#define MAX_SIZE 1000000

int findWordSize(char *str){
	int size = 0;
	for (int i = 0;; i++){
		if (str[i] < 123 && str[i] > 96) size++;
		else return size;
	}
}

int main(){
	char *arr = new char[MAX_SIZE];

	fgets(arr, MAX_SIZE, stdin);

	int pos = 0;
	fwrite(arr, pos = findWordSize(arr), 1, stdout);

	for (;;){
		if (arr[pos] < 32) break;

		char op = arr[pos];
		pos++;

		putchar(' ');
		int size = findWordSize(arr + pos);
		fwrite(arr + pos, size, 1, stdout);
		pos += size;
		putchar(' ');
		putchar(op);
	}

	putchar('\n');
}