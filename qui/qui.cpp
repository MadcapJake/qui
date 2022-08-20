// qui.cpp : Defines the entry point for the application.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

import Scanner;

void run(std::string source) {
    Quarrel::Scanner scanner = Quarrel::Scanner{ source };
    std::vector<Quarrel::Token> tokens = scanner.scanTokens();

    for (Quarrel::Token token : tokens) {
        try { std::cout << token << std::endl; }
        catch (std::invalid_argument& e) {
            scanner.error(e.what());
        }
    }
}


void runFile(std::string path) {
    std::ifstream file;
    std::string result;
    file.open(path);
    if (file.is_open()) {
        std::ostringstream ss;
        ss << file.rdbuf();
        result = ss.str();
    }
    run(result);
}

void runPrompt() {
    std::string line;
    for (;;) {
        std::cout << "> ";
        std::getline(std::cin, line);
        if (line.empty()) break;
        run(line);
    }
}

int main(int argc, char** argv) {
    if (argc > 2) {
        std::cout << "Usage: qui [script]" << std::endl;
    }
    else if (argc == 2) {
        runFile(argv[1]);
    }
    else {
        runPrompt();
    }
}