#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <regex>

enum Command {
    print,
    ls,
    cat,
    mkdir,
    cd,
    unknown
};

void dispatchCommand(std::vector<std::string> tokens);

void printFunc(std::vector<std::string> tokens);

void NavigateFileSystemFunc(std::vector<std::string> arguments);


bool error_zero_arg(std::vector<std::string> arguments);

void error_bad_arg(std::string arg);

bool error_too_many_arg(std::vector<std::string> arguments);