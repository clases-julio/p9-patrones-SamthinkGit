#include "../headers/except/InvalidDeviceException.h"
std::string InvalidDeviceException::ERROR_MESSAGE = "Invalid User";

InvalidDeviceException::InvalidDeviceException(std::string &tag) {

    this->exception = ERROR_MESSAGE;
    this->tag = tag;

}
