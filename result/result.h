//
// Created by alexey on 8/27/21.
//

#ifndef SIGAME_MACRO_ERROR_H
#define SIGAME_MACRO_ERROR_H

#include <iostream>


class result {
public:
    result(bool success, std::string text);
    void log();
    inline bool isSuccess() const;
private:
    bool itsSuccess;
    std::string itsText;
};


#endif //SIGAME_MACRO_ERROR_H
