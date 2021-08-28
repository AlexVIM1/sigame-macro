//
// Created by alexey on 8/28/21.
//

#include "commandLine.h"

commandLine::commandLine(int c, char *v[], std::string prompt) : level(0), prompt(prompt) {
    BROWSER choice = FIREFOX;
    if (c > 0) {
        if (v[1] == "--chrome") {
            choice = CHROME;
        }
    }
    webClient = new client(choice);
}

commandLine::~commandLine() {
    delete webClient;
}

result commandLine::start() {
    std::string nick;
    std::cout << "Enter nickname: ";
    std::getline(std::cin, nick);
    auto startExit = webClient->start();
    if (!startExit.isSuccess()) {
        return result(false, "\nFailed to start WebDriver:\n\n" + startExit.viewLog());
    }
    auto loginExit = webClient->login(nick);
    if (!loginExit.isSuccess()) {
        return result(false, "\nFailed to open/login SIGame:\n\n" + loginExit.viewLog());
    }
    return result(true, "\nSuccess.\n");
}

result commandLine::execute(std::string cmd) {
    short int command = -1;
    for (short int i = 0; i < sizeof(commands)/sizeof(commands[0]); i++) {
        if (cmd == commands[i]) {
            command = i;
            break;
        }
    }
    
    switch (command) {
        case 0:
            this->start().log();
            break;
        case 1:
        case 2:
        case 3:
        default:
            return result(false, "\nIncorrect command (127).\n");
    }
    
    return result(true, "\nSuccess.\n");
}

void commandLine::init() {
    std::string com;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, com);
        auto executeExit = execute(com);
        if (!executeExit.isSuccess()) {
            executeExit.log();
        }
    }
}
