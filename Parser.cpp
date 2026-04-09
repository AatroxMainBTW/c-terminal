#include "Parser.h"

/* Parser will parse the string into words and put them into a table to be dispatched */

std::vector<std::string> parseLine(std::string line) {
	std::vector<std::string> tokens;
	std::stringstream ss(line);
	std::string word;
	while (ss >> word) {
		tokens.push_back(word);
	}
	return tokens;
}


