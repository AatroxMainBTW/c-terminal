/* Dispatcher will look at first element of the array and make function calls for exemple print etc ..."for now" */


#include "Dispatcher.h"
#include "Color.h"
#include <unordered_set>
#include "FileSystem.h"

const std::unordered_set<std::string> ERROR_WORDS = { "error", "unknown", "failed" };

Command getCommand(const std::string& cmd) {
    static std::unordered_map<std::string, Command> map = {
        {"print", print},
        {"ls", ls},
        {"cd", cd},
        {"cat", cat},
        {"mkdir", mkdir},
        {"rm",rm},
        { "clear", clear }
    };

    auto it = map.find(cmd);
    if (it != map.end()) {
        return it->second;
    }
    return unknown;
}

bool error_zero_arg(std::vector<std::string> arguments) {
    if (arguments.empty()) {
        setColor(RED);
        std::cerr << "[Error] No arguments provided!\n";
        resetColor();
        return true;
    }
    return false;
}

void error_bad_arg(std::string arg) {
    setColor(RED);
    std::cerr << "[Error] Bad argument: ";
    resetColor();

    setColor(YELLOW);
    std::cerr << arg << "\n";
    resetColor();
}

bool error_too_many_arg(std::vector<std::string> arguments) {
    if (arguments.size() > 1) {
        setColor(RED);
        std::cerr << "[Error] Too many arguments provided!\n";
        resetColor();
        return true;
    }
    return false;
}

// How to use 'print "text"'
// TODO convert .txt or any programming extention to string and print it
void printFunc(std::vector<std::string> arguments) {

    bool hasZeroArg = error_zero_arg(arguments);
    if (hasZeroArg) {
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
            error_bad_arg(arg);
        }
    }
}

void NavigateFileSystemFunc(std::vector<std::string> arguments) {
    bool hasZeroArg = error_zero_arg(arguments);
    if (hasZeroArg) {
        return;
    }
    bool hasTooManyArg = error_too_many_arg(arguments);
    if (hasTooManyArg) {
        return;
    }
    std::string arg = arguments[0];
    if (arg == "..") {
        goToParentPath();
    }else {
        changeFilePath(arg);
    }

}

void clearScreen() {
    // Calling system function and passing cls as argument
    system("cls");
}


void createDirectory(std::vector<std::string> arguments) {

    bool hasZeroArg = error_zero_arg(arguments);
    if (hasZeroArg) {
        return;
    }
    bool hasTooManyArg = error_too_many_arg(arguments);
    if (hasTooManyArg) {
        return;
    }

    createFolder(arguments[0]);
  
}


void removeDirectoryOrFile(std::vector<std::string> arguments) {

    bool hasZeroArg = error_zero_arg(arguments);
    if (hasZeroArg) {
        return;
    }
    bool hasTooManyArg = error_too_many_arg(arguments);
    if (hasTooManyArg) {
        return;
    }

    removeFolderOrDocument(arguments[0]);

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
            getFoldersAndDocumentsInCurrentPath();
            break;

        case cd:
            tokens.erase(tokens.begin());
            NavigateFileSystemFunc(tokens);
            break;

        case cat:
            std::cout << "cat command" << std::endl;
            break;

        case mkdir:
            tokens.erase(tokens.begin());
            createDirectory(tokens);
            break;
        case rm:
            tokens.erase(tokens.begin());
            removeDirectoryOrFile(tokens);
            break;
        case clear:
            clearScreen();
            std::cout << "TERMINAL" << std::endl;
            break;
        default:
            std::cerr << "Unknown command" << std::endl;
            break;
        }
    
   
}