#include <iostream>
#include <string.h>
#include <stdio.h>

struct StringSegment{
	char *start;
	int size;
};

bool find2(StringSegment str, StringSegment goal){
	int count = 0;
	for (int i = 0; i < (str.size - goal.size + 1); i++){
		if (memcmp(str.start + i, goal.start, goal.size) == 0) {
			count++;
			if (count > 1) return true;
		}
	}
	return false;
}

bool priority(StringSegment a, StringSegment b){
	if (a.size < b.size) return true;
	if (a.size == b.size) {
		for (int i = 0; i < a.size; i++){
			if (a.start[i] < b.start[i]) return false;
			else if (a.start[i] > b.start[i]) return true;
		}
	}

	return false;
}

StringSegment findBiggestDuplicate(StringSegment str){
	StringSegment out {str.start, 1};

	StringSegment goal;
	for (int i = 0; i < str.size; i++){
		goal.start = str.start + i;

		for (goal.size = out.size; goal.size < (str.size - i); goal.size++){
			printf("%i %i\n", i, goal.size);

			if (find2(str, goal)) if (priority(out, goal)){
				fwrite(goal.start, goal.size, sizeof(char), stdout);
				printf("\n");
				memcpy(&out, &goal, sizeof(StringSegment));
			}
		}
	}

	return out;
}

int main(){
	
}