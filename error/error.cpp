//
// Created by alexey on 8/27/21.
//

#include "error.h"

result::result(bool success, std::string text) : itsSuccess(success), itsText(text) { }

inline bool result::isSuccess() const {
    return itsSuccess;
}

void result::log() {
    if (isSuccess()) {
        std::cout << itsText;
        return;
    }
    std::cerr << itsText;
}
