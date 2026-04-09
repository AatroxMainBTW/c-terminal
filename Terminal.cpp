#include "Parser.h"
#include "Dispatcher.h"

#include <iostream>
#include <windows.h>
#include <string>


int main()
{
    std::cout << "TERMINAL" << std::endl;

    std::string line;
    while (true) {
        std::cout << "> ";
        std::getline(std::cin, line);

        if (line.empty()) continue;

        std::vector<std::string> tokens = parseLine(line);
        dispatchCommand(tokens);
    }
}