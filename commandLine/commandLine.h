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
    commandLine(int c, char *v[], std::string prompt);
    ~commandLine();
    result execute(std::string cmd);
    void init();

public COMMANDS:
    result start();
    
private:
    unsigned short int level;
    std::string prompt;
    std::string commands[4] = { "start", "macro-mode", "exit", "help" };
    client *webClient;
};


#endif //SIGAME_MACRO_COMMANDLINE_H
