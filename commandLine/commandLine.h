//
// Created by alexey on 8/28/21.
//

#ifndef SIGAME_MACRO_COMMANDLINE_H
#define SIGAME_MACRO_COMMANDLINE_H

#define COMMANDS


#include "../client/client.h"

#include <iostream>

class commandLine {
public:
    commandLine(int c, char *v[]);
    ~commandLine();
    result execute(std::string cmd);
    void init();

public COMMANDS:
    result start();
    
private:
    bool track;
    bool listen;
    unsigned short int level;
    std::string helpMessage;
    std::string prompt;
    std::string commands[4] = { "start", "macro-mode", "exit", "help" };
    client *webClient;
};


#endif //SIGAME_MACRO_COMMANDLINE_H
