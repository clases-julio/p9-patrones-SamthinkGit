#include "../headers/except/InsufficientPermissionsException.h"
std::string InsufficientPermissionsException::ERROR_MESSAGE = "Invalid User";

InsufficientPermissionsException::InsufficientPermissionsException(std::string &tag) {

    this->exception = ERROR_MESSAGE;
    this->tag = tag;


}
