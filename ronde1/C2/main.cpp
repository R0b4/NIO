#include <iostream>
#define LOG(x) std::cout << x << std::endl;

struct Block {
	char xDir;
	char yDir;
	int value;

	Block() : xDir(0), yDir(0), value(0) {}
};

struct Field {
	Block *field;
	int n;

	Field(int n) {
		field = new Block[n * n];
		this->n = n;
	}

	~Field() {
		delete [] field;
	}

	Block *getIndex(int x, int y) {
		return &field[x * n + y];
	}
};

bool solve(Field *field, int x, int y, int value){

	Block *b = field->getIndex(x, y);
	if (b->value == field->n * field->n) return true;
	b->value = value;

	int j = y + b->yDir;
	int i = x + b->xDir;

	for (; i > -1 && j > -1 && i < field->n && j < field->n; 
			i += b->xDir, j += b->yDir){
		if (field->getIndex(i, j)->value == (value + 1)) return solve(field, i, j, value + 1);
	}

	j = y + b->yDir;
	i = x + b->xDir;
	for (; i > -1 && j > -1 && i < field->n && j < field->n; 
			i += b->xDir, j += b->yDir){
		if (field->getIndex(i, j)->value != 0) continue;
		if (solve(field, i, j, value + 1)) return true;
	}

	b->value = 0;
	return false;
}

int main() {
	int n;
	std::string in;
	std::cin >> n;
	std::getline(std::cin, in);

	Field field(n);

	for (int i = 0; i < n; i++) {
		std::getline(std::cin, in);

		const char *line = in.c_str();
		int length = in.length();

		for (int j = 0; j < n; j++) {
			Block *b = field.getIndex(j, i);
			b->value = std::atoi(line);
			if (b->value == n * n) break;

			for (int k = 0; k < length; k++){
				if (line[k] == ' '){
					line += k + 1;
					break;
				}
			}
			
			if (line[0] == 'O') {
				b->xDir = 1;
			} else if (line[0] == 'W') {
				b->xDir = -1;
			} else if (line[0] == 'N') {
				b->yDir = -1;
				if (line[1] != ';') b->xDir = line[1] == 'O' ? 1 : -1;
			} else {
				b->yDir = 1;
				if (line[1] != ';') b->xDir = line[1] == 'O' ? 1 : -1;
			}

			for (int k = 0; k < length; k++){
				if (line[k] == ';'){
					line += k + 1;
					break;
				}
			}
		}
	}

	solve(&field, 0, 0, 1);

	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			std::cout << field.getIndex(j, i)->value << ' ';
		}
		std::cout << std::endl;
	}
	std::cout.flush();
}