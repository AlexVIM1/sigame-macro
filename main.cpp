#include "commandLine/commandLine.h"

int main(int argc, char *argv[]) {
    auto cmd = new commandLine(argc, argv);
    cmd->init();
    
    delete cmd;
    return 0;
}
