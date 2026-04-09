/* Dispatcher will look at first element of the array and make function calls for exemple print etc ..."for now" */


#include "Dispatcher.h"
#include "Color.h"
#include <unordered_set>

const std::unordered_set<std::string> ERROR_WORDS = { "error", "unknown", "failed" };

enum Command {
    print,
    ls,
    cat,
    mkdir,
    unknown
};

Command getCommand(const std::string& cmd) {
    static std::unordered_map<std::string, Command> map = {
        {"print", print},
        {"ls", ls},
        {"cat", cat},
        {"mkdir", mkdir}
    };

    auto it = map.find(cmd);
    if (it != map.end()) {
        return it->second;
    }
    return unknown;
}

// How to use 'print "text"'
// TODO convert .txt or any programming extention to string and print it
void printFunc(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        setColor(RED);
        std::cerr << "[Error] No arguments provided!\n";
        resetColor();
        return;
    }

    for (std::string arg : arguments) {
        if (arg.front() == '"' && arg.back() == '"') {
            arg.erase(std::remove(arg.begin(), arg.end(), '"'), arg.end());

            setColor(GREEN);  
            std::cout << arg << " \n";
            resetColor();
        }
        else {
            setColor(RED);
            std::cerr << "[Error] Bad argument: ";
            resetColor();

            setColor(YELLOW);
            std::cerr << arg << "\n";
            resetColor();
        }
    }
}

void dispatchCommand(std::vector<std::string> tokens) {
    if (tokens.empty()) return;

    Command cmd = getCommand(tokens[0]);
        switch (cmd) {
        case print: {
            tokens.erase(tokens.begin());
            printFunc(tokens);
            break;
        }
        case ls:
            std::cout << "ls command" << std::endl;
            break;

        case cat:
            std::cout << "cat command" << std::endl;
            break;

        case mkdir:
            std::cout << "mkdir command" << std::endl;
            break;

        default:
            std::cerr << "Unknown command" << std::endl;
            break;
        }
    
   
}