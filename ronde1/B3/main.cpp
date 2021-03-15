#include <iostream>
#include <string.h>
#define WORD_LENGTH 10

const char word[WORD_LENGTH + 1] = "GESCHREVEN";

struct node{
	char value[3];
	node *next;
};

int main(){
	node *first = new node;
	node *last = first;

	first->value[0] = 'z';
	first->value[0] = 'z';
	first->value[0] = 'z';
	first->next = nullptr;

	char code[3];
	int num = 0;
	for (int i = 0; i < WORD_LENGTH; i++){
		code[0] = word[i];
		for (int j = 1 + i; j < WORD_LENGTH; j++){
			code[1] = word[j];
			for (int k = 1 + j; k < WORD_LENGTH; k++){
				code[2] = word[k];

				node *current = first;
				for (;; current = current->next){
					if (memcmp(code, current->value, 3) == 0) break;
					if (current->next == nullptr){
						printf(code, 3);
						std::cout << std::endl;
						num++;

						node *New = new node;
						memcpy(New->value, code, 3);
						New->next = nullptr;
						last->next = New;
						last = New;

						break;
					}
				}

				//std::cout << i << j << k << std::endl;
			}
		}
	}
	std::cout << num << std::endl;
}