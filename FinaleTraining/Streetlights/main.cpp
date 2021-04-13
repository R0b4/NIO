#include <iostream>
#include <queue>

struct Junction
{
	int parent;
	int setsize;
};

struct street{
	int x;
	int y;

	int distance;
};

struct Compare{
	bool operator()(const street &a, const street &b){
		return a.distance > b.distance;
	}
};

int findParent(Junction *list, int a){
	int result = a;
	for (;;){
		if (list[result].parent == result) break;
		else result = list[result].parent;
	}
	for (int i = a;;){
		if (i == result) break;
		else {
			list[i].parent = result;
			i = list[i].parent;
		}
	}
	return result;
}

bool addTo(Junction *list, int a, int b){
	a = findParent(list, a);
	b = findParent(list, b);

	if (a == b) return false;

	if (list[a].setsize < list[b].setsize) list[a].parent = b;
	else list[b].parent = a;

	return true;
}

int doLights(int n, int m, std::priority_queue<street, std::vector<street>, Compare> &streets){
	int savings = 0;

	Junction *j = new Junction[n];
	for (int i = 0; i < n; i++) {
		j[i].parent = i;
		j[i].setsize = 1;
	}

	for (street s = streets.top(); streets.size() != 0; streets.pop(), s = streets.top()){
		//printf("%i %i %i\n", s.x, s.y, s.distance);

		if (!addTo(j, s.x, s.y)){
			savings += s.distance;

			continue;
		}
	}

	return savings;
}

int main(){
	for (;;){
		int m, n;
		scanf("%i %i", &m, &n);
		if (m == 0 && n == 0) return 0;

		std::priority_queue<street, std::vector<street>, Compare> streets;
		for (int i = 0; i < n; i++){
			street s;
			scanf("%i %i %i", &s.x, &s.y, &s.distance);

			streets.push(s);
		}

		printf("%i\n", doLights(m, n, streets));
	}
}