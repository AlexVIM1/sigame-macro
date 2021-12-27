//
// Created by alexey on 8/27/21.
//

#include "client.h"

client::client(BROWSER browser) : itsBrowser(browser), isRunning(false), track(false) { }

client::~client() {
    delete webDriver;
}

bool client::isClientRunning() const {
    return isRunning;
}

result client::start() {
    if (!isRunning) {
        if (itsBrowser == FIREFOX) {
            try {
                webDriver = new webdriverxx::WebDriver(webdriverxx::Firefox());
            }
            catch (std::runtime_error &re) {
                return result(false, "\nFailed to start WebDriver:\n" + std::string(re.what()));
            }
            catch (std::exception &ex) {
                return result(false, "\nFailed to start WebDriver:\n" + std::string(ex.what()));
            }
            isRunning = true;
            return result(true, "\nSuccess.\n");
        }
        if (itsBrowser == CHROME) {
            try {
                webDriver = new webdriverxx::WebDriver(webdriverxx::Chrome());
            }
            catch (std::runtime_error &re) {
                return result(false, std::string(re.what()));
            }
            catch (std::exception &ex) {
                return result(false, std::string(ex.what()));
            }
            isRunning = true;
            return result(true, "\nSuccess.\n");
        }
        return result(false, "\nIncorrect option.\n");
    }
    return result(false, "\nProgram is already running.\n");
}

result client::login(std::string nickname) {
    if (!isRunning) {
        return result(false, "\nWebRriver (client) is not running. Try to 'start'.\n");
    }
    try {
        webDriver->Navigate("https://vladimirkhil.com/si/online/");
        auto nickInput = webDriver->FindElement(webdriverxx::ById("entername"));
        nickInput.SendKeys(nickname);
        auto submit = webDriver->FindElement(webdriverxx::ById("enter"));
        submit.Click();
    }
    catch (std::runtime_error &re) {
        return result(false, "\nFailed to lobin SIGame:\n" + std::string(re.what()));
    }
    catch (std::exception &ex) {
        return result(false, "\nFailed to lobin SIGame:\n" + std::string(ex.what()));
    }
    return result(true, "\nSuccess.\n");
}

void client::tick() {
    if (!isRunning) {
        return;
    }
    webdriverxx::Element button;
    try {
        button = webDriver->FindElement(webdriverxx::ByClass("playerButton"));
    }
    catch (std::exception &ex) {
        return;
    }
    catch (std::runtime_error &re) {
        return;
    }
    webdriverxx::Element anim;
    while (track) {
        try {
            anim = webDriver->FindElement(webdriverxx::ByClass("topBorder"));
        }
        catch (std::exception &ex) {
            continue;
        }
        catch (std::runtime_error &re) {
            continue;
        }
        button.Click();
    }
}
