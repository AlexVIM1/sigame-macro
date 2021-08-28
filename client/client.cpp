//
// Created by alexey on 8/27/21.
//

#include "client.h"

client::client(BROWSER browser) : itsBrowser(browser), isRunning(false) { }

client::~client() {
    std::cerr << "\nclient::~client()\n";
    delete webDriver;
}

result client::start() {
    if (!isRunning) {
        if (itsBrowser == FIREFOX) {
            try {
                webDriver = new webdriverxx::WebDriver(webdriverxx::Firefox());
            }
            catch (std::runtime_error &re) {
                return result(false, "\nFailed to start WebDriver:\n\n" + std::string(re.what()));
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
            isRunning = true;
            return result(true, "\nSuccess.\n");
        }
        return result(false, "\nIncorrect option.\n");
    }
    return result(false, "\nProgram is already running.\n");
}

result client::login(std::string nickname) {
    if (!isRunning) {
        return result(false, "\nWeb driver is not running.\n");
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
    return result(true, "\nSuccess.\n");
}
