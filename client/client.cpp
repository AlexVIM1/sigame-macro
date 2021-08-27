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
    if (itsBrowser == FIREFOX) {
        webDriver = new webdriverxx::WebDriver(webdriverxx::Firefox());
        isRunning = true;
        return result(true, "\nSuccess.\n");
    }
    if (itsBrowser == CHROME) {
        webDriver = new webdriverxx::WebDriver(webdriverxx::Chrome());
        isRunning = true;
        return result(true, "\nSuccess.\n");
    }
    return result(false, "\nIncorrect option.\n");
}

result client::login(std::string &nickname) {
    if (!isRunning) {
        return result(false, "\nWeb driver is not running.\n");
    }
    webDriver->Navigate("https://vladimirkhil.com/si/online/");
    try {
        auto nickInput = webDriver->FindElement(webdriverxx::ById("entername"));
        nickInput.SendKeys(nickname);
        auto submit = webDriver->FindElement(webdriverxx::ById("enter"));
        submit.Click();
    }
    catch (std::exception &ex) {
        return result(false, ex.what());
    }
    return result(true, "\nSuccess.\n");
}
