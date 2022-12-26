#include "../include/except/InvalidUserException.h"

std::string InvalidUserException::ERROR_MESSAGE = "Invalid User";

InvalidUserException::InvalidUserException(const std::string &tag) {

    this->exception = ERROR_MESSAGE;
    this->tag = tag;

}
