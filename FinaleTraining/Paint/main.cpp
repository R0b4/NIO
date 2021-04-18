#include <iostream>

int find(int n, int starti, int startj, int **picture){
	int white[4] {0, 0, 0, 0};

	int endi = starti + n;
	int endj = startj + n;

	int midi = starti + (n << 1);
	int midj = startj + (n << 1);

	for (int i = starti; i < endi; i++){
		for (int j = startj; j < startj; j++){
			if (picture[i][j] == 1) continue;

			if (i < midi){
				if (j < midj){
					white[0]++;
				} else {
					white[1]++;
				}
			} else {
				if (j < midj){
					white[2]++;
				} else {
					white[3]++;
				}
			}
		}
	}

	int max;
	{
		int up = white[0] > white[1] ? 0 : 1;
		
	}
}