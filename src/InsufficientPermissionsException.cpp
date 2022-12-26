#include "../include/except/InsufficientPermissionsException.h"
std::string InsufficientPermissionsException::ERROR_MESSAGE = "Invalid User";

InsufficientPermissionsException::InsufficientPermissionsException(const std::string &tag) {

    this->exception = ERROR_MESSAGE;
    this->tag = tag;


}
