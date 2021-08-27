#include "client/client.h"

#include <thread>

int main(int argc, char *argv[]) {
    BROWSER choice = FIREFOX;
    if (argv[1] == "--chrome") {
        choice = CHROME;
    }
    
    std::string nick;
    std::cout << "Enter nickname: ";
    std::getline(std::cin, nick);
    
    auto *c = new client(choice);
    auto startExit = c->start();
    if (!startExit.isSuccess()) {
        startExit.log();
        return 1;
    }
    
    auto loginExit = c->login(nick);
    if (!loginExit.isSuccess()) {
        loginExit.log();
        return 1;
    }
    
    
    return 0;
}
