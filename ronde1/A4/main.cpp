#include <iostream>
#include <stdio.h>
#include <string.h>
#define ELEMENTS 118
#define WORDS 10

//ik heb dit gegeneerd met een python script
const char *elements[ELEMENTS] = {"h", "he", "li", "be", "b", "c", "n", "o", "f", "ne", "na", "mg", "al", "si", "p", "s", "cl", "ar", "k", "ca", "sc", "ti", "v", "cr", "mn", "fe", "co", "ni", "cu", "zn", "ga", "ge", "as", "se", "br", "kr", "rb", "sr", "y", "zr", "nb", "mo", "tc", "ru", "rh", "pd", "ag", "cd", "in", "sn", "sb", "te", "i", "xe", "cs", "ba", "la", "ce", "pr", "nd", "pm", "sm", "eu", "gd", "tb", "dy", "ho", "er", "tm", "yb", "lu", "hf", "ta", "w", "re", "os", "ir", "pt", "au", "hg", "tl", "pb", "bi", "po", "at", "rn", "fr", "ra", "ac", "th", "pa", "u", "np", "pu", "am", "cm", "bk", "cf", "es", "fm", "md", "no", "lr", "rf", "db", "sg", "bh", "hs", "mt", "ds", "rg", "cn", "nh", "fl", "mc", "lv", "ts", "og"};
const int lengths[ELEMENTS] = {1, 2, 2, 2, 1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 1, 1, 2, 2, 1, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2};

const char *ja = "ja";
const char *nee = "nee";

bool checkString(char *str, size_t length) {
	for (int i = 0; i < ELEMENTS; i++) {
		if (lengths[i] > length) continue;
		if (memcmp(str, elements[i], lengths[i]) == 0) {
			if (lengths[i] == length) return true;
			if (checkString(str + lengths[i], length - lengths[i])) {
				return true;
			}
		}
	}
	return false;
}

int main() {
	std::string words[WORDS];
	for (int i = 0; i < WORDS; i++) {
		std::getline(std::cin, words[i]);
	}

	for (int i = 0; i < WORDS; i++) {
		if (checkString((char *)words[i].c_str(), words[i].length())) {
			std::cout << ja << std::endl;
		} else {
			std::cout << nee << std::endl;
		}
	}
	std::cout.flush();

	return 0;
}