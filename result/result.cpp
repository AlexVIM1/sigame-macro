//
// Created by alexey on 8/27/21.
//

#include "result.h"

result::result(bool success, std::string text) : itsSuccess(success), itsText(text) { }

inline bool result::isSuccess() const {
    return itsSuccess;
}

std::string result::viewLog() {
    return itsText;
}

void result::log() {
    if (isSuccess()) {
        std::cout << itsText;
        return;
    }
    std::cerr << itsText;
}
