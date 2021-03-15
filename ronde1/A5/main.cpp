#include <iostream>

bool checkPerson(int height, bool *&totem, int t) {
	for (int h = (height >= t ? t : height) - 1; h > -1; h--) {
		if (!totem[h]) {
			totem[h] = true;
			return true;
		}
	}
	return false;
}

int main() {
	std::string endline;
	int n;
	int t;
	std::cin >> n;
	std::getline(std::cin, endline);
	std::cin >> t;
	std::getline(std::cin, endline);

	int *people = new int[n];
	bool *totem = new bool[t];

	for (int i = 0; i < t; i++){
		totem[i] = false;
	}

	for (int i = 0; i < n; i++) {
		std::cin >> people[i];
		std::getline(std::cin, endline);
	}

	int amount = 0;
	for (int i = 0; i < n; i++) {
		if (checkPerson(people[i], totem, t)){
			amount++;
		}
	}

	std::cout << amount << std::endl;
	std::cout.flush();
	delete [] people;
	delete [] totem;
}