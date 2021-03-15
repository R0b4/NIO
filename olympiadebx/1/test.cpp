#include <iostream>

int main(int argc, char **argv){
	int length = atoi(argv[1]);
	std::cout << length << std::endl;
	for (int i = 0; i < length; i++){
		std::cout << i << std::endl;
	}

	std::cout.flush();
}