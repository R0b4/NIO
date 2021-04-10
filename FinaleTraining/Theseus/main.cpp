#include <iostream>

#define CAVERN_AMOUNT ('Z' - 'A')

struct Passage{
	int otherCavern;
	Passage *next;

	Passage() : next(nullptr){}
	Passage(int value) : next(nullptr), otherCavern(value) {}

	~Passage(){
		if (next != nullptr) delete next;
	}
};

struct Cavern{
	int disToLight;
	int distanceToTheseus;

	Passage first;
	Passage *last;
};

void AddLight(Cavern *maze, int pos, int distance){
	if (maze[pos].disToLight <= distance) return;
	maze[pos].disToLight = distance;

	for (Passage *p = maze[pos].first.next; p != nullptr; p = p->next){
		AddLight(maze, p->otherCavern, distance + 1);
	}
}

int calcDanger(Cavern *maze, int pos){
	return maze[pos].disToLight < maze[pos].distanceToTheseus ? maze[pos].disToLight : maze[pos].distanceToTheseus;
}

int flee(Cavern *maze, int *minotaur, int pos){
	int minDanger;
	int other;

	for (Passage *p = maze[pos].first.next; p != nullptr; p = p->next){
		int danger = calcDanger(maze, p->otherCavern);
		if (danger > minDanger) continue;

		other = p->otherCavern;
		minDanger = danger;
	}

	if (minDanger) return 1;

	*minotaur = other;
	return 0;
}

void setDistanceToTheseusMax(Cavern *maze){
	for (int i = 0; i < CAVERN_AMOUNT; i++){
		maze[i].distanceToTheseus = INT32_MAX;
	}
}

void setDistanceToTheseus(Cavern *maze, int pos, int distance){
	if (maze[pos].distanceToTheseus <= distance) return;
	maze[pos].distanceToTheseus = distance;

	for (Passage *p = maze[pos].first.next; p != nullptr; p = p->next){
		AddLight(maze, p->otherCavern, distance + 1);
	}
}

void pursuit(Cavern *maze, int *theseus, int minotaur){
	*theseus = minotaur;

	setDistanceToTheseusMax(maze);
	setDistanceToTheseus(maze, minotaur, 0);
}

void innitMaze(Cavern *maze){
	for (int i = 0; i < CAVERN_AMOUNT; i++){
		maze[i].distanceToTheseus = INT32_MAX;
		maze[i].disToLight = INT32_MAX;

		if (maze[i].first.next != nullptr) delete maze[i].first.next;
		maze[i].last = nullptr;
	}
}

int simulate()

int main(){

}