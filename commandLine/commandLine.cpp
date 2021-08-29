//
// Created by alexey on 8/28/21.
//

#include "commandLine.h"

commandLine::commandLine(int c, char *v[]) : level(0), listen(true), track(false), prompt("\ncommand$ "),
                                            helpMessage("\nNormal mode:\n"
                                                        "'start' - starts WebDriver and opens SIGame.\n"
                                                        "'macro-mode' - entering macro-mode with own commands (read below).\n"
                                                        "'exit' - closes the program.\n"
                                                        "'help' - displays this message\n"
                                                        "\nMacro-mode:\n"
                                                        "[any message] - enables (or disables whether it already has enabled) handler that checking is you may answer and pushing red button if it is.\n"
                                                        "'exit' - switches macro-mode to normal mode.\n"
                                                        "\nsigame-macro  Copyright (C) 2021  Alexey Zlobin (alexvim / AlexVIM1)\n"
                                                        "Licensed by GPLv3\n"
                                                        "\nvk.com/alexvimdev\n"
                                                        "github.com/AlexVIM1/sigame-macro\n") {
    BROWSER choice = FIREFOX;
    if (c > 1) {
        if (std::string(v[1]) == "--chrome") {
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
    std::cout << "\nEnter nickname: ";
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
    
    if (level == 0) {
        switch (command) {
            case 0:
                return result(false, this->start().viewLog());
            case 1:
                if (webClient->isClientRunning()) {
                    prompt = "\ncommand<macro-mode>$ ";
                    level = 1;
                    return result(true,
                                  "\nEntered to macro-mode.\nEnter any key to enable/disable red-button tracking.\nEnter 'exit' to quit macro-mode.\n");
                }
                return result(false,"\nFailed to enter macro-mode:\nWebDriver (client) in not running. Try to 'start'.\n");
            case 2:
                level = -1;
                listen = false;
                return result(true, "\nQuiting program...\n");
            case 3:
                std::cout << helpMessage;
                return result(true,"");
            default:
                return result(false, "\nIncorrect command (127).\n");
        }
    }
    else if (level == 1) {
        switch (command) {
            case 2:
                prompt = "\ncommand$ ";
                level = 0;
                return result(true, "\nTracking and pushing red-button disabled.\nQuiting macro-mode...\n");
            default:
                if (track) {
                    track = false;
                    return result(true, "\nTracking and pushing red-button disabled.\n");
                }
                track = true;
                return result(true, "\nTracking and pushing red-button enabled.\n");
        }
    }
    
    return result(true, "\nSuccess.\n");
}

void commandLine::init() {
    std::cout << helpMessage;
    std::string com;
    while (listen) {
        std::cout << prompt;
        std::getline(std::cin, com);
        auto executeExit = execute(com);
        executeExit.log();
    }
}
