#include "../include/except/UserNotFoundException.h"
std::string UserNotFoundException::ERROR_MESSAGE = "User not Found";

UserNotFoundException::UserNotFoundException(const std::string &tag) {

    this->tag = tag;
    this->exception = ERROR_MESSAGE;

};


