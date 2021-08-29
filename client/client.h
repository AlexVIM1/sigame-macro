//
// Created by alexey on 8/27/21.
//

#ifndef SIGAME_MACRO_CLIENT_H
#define SIGAME_MACRO_CLIENT_H

#include "../result/result.h"

#include <webdriverxx/webdriverxx.h>


enum BROWSER {
    FIREFOX,
    CHROME
};

class client {
public:
    explicit client(BROWSER browser);
    ~client();
    bool isClientRunning() const;
    bool track;
    result start();
    result login(std::string nickname);
    void tick();

private:
    bool isRunning;
    BROWSER itsBrowser;
    webdriverxx::WebDriver *webDriver;
};


#endif //SIGAME_MACRO_CLIENT_H
