//https://codeforces.com/problemset/problem/1512/F

#include <iostream>
#include <queue>
#include <algorithm>

#define MAX_INT 0x7FFFFFFF

struct State{
	int pos;
	int c;
	int days;
};

int solve(int cost, int *a, int *b, int n){
	std::queue<State> states;
	states.push({0, 0, 0});

	for (;;){
		State now = states.front();
		printf("%i %i %i\n", now.pos, now.c, now.days);
		printf("%lu\n", states.size());
		if (now.c >= cost) return now.days;

		if (b[now.pos] <= now.c && now.pos + 1 < n){
			states.push({now.pos, now.c + a[now.pos], now.days + 1});
			states.push({now.pos + 1, now.c - b[now.pos], now.days + 1});
		} else {
			if (states.size() == 1){
				int time = (std::min(now.pos + 1 == n ? MAX_INT : b[now.pos], cost) - now.c) / a[now.pos];
				states.push({now.pos, now.c + a[now.pos] * time, now.days + time});
			} else {
				states.push({now.pos, now.c + a[now.pos], now.days + 1});
			}
		}

		states.pop();
	}
}

int main(){
	int t;
	scanf("%i", &t);

	for (int i = 0; i < t; i++){
		int n, c;
		scanf("%i %i", &n, &c);

		int *a = new int[n];
		int *b = new int[n - 1];

		for (int i = 0; i < n; i++) scanf("%i", &a[i]);
		for (int i = 0; i < (n - 1); i++) scanf("%i", &b[i]);

		printf("\nstart case %i\n", i);
		int days = solve(c, a, b, n);
		printf("%i\n", days);

		delete [] a;
		delete [] b;
	}
}