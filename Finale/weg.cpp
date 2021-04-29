#include <iostream>

#define MOD 1000000007

void fill(bool **grid,  char dir, int x, int y, int n, int m, int d){
	if (d == -1) return;
	if (x < 0 || x >= n) return;
	if (y < 0 || y >= m) return;

	grid[x][y] = false;
	if (dir != 'n') fill(grid, 's', x + 1, y, n, m, d - 1);
	if (dir != 's') fill(grid, 'n', x - 1, y, n, m, d - 1);
	if (dir != 'e') fill(grid, 'w', x, y + 1, n, m, d - 1);
	if (dir != 'w') fill(grid, 'e', x, y - 1, n, m, d - 1);
}

int goThrough(int **val, bool **grid, int x, int y, int n, int m){
	if (x < 0 || x >= n) return 0;
	if (y < 0 || y >= m) return 0;

	if (!grid[x][y]) {
		val[x][y] = 0;
		return 0;
	}

	if (x == (n - 1) && y == (m - 1)) return 1;
	if (val[x][y] > -1) return val[x][y];

	int sum = (goThrough(val, grid, x + 1, y, n, m) + goThrough(val, grid, x, y + 1, n, m)) % MOD;
	val[x][y] = sum;
	return sum;
}

int main(){
	int N, M, K, D;
	scanf("%i %i %i %i\n", &N, &M, &K, &D);

	bool **grid = new bool*[N];
	for (int i = 0; i < N; i++) {
		grid[i] = new bool[M];
		for (int j = 0; j < M; j++) grid[i][j] = true;
	}

	int **val = new int*[N];
	for (int i = 0; i < N; i++) {
		val[i] = new int[M];
		for (int j = 0; j < M; j++) val[i][j] = -1;
	}

	for (int i = 0; i < K; i++){
		int x, y;
		scanf("%i %i", &x, &y);

		fill(grid, ' ', x - 1, y - 1, N, M, D);
	}
	
	goThrough(val, grid, 0, 0, N, M);

	printf("%i\n", val[0][0]);
}