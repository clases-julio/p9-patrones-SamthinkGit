#include "../include/except/InvalidFileException.h"
std::string InvalidFileException::ERROR_MESSAGE = "Invalid File";

InvalidFileException::InvalidFileException(const std::string &tag) {

    this->exception = ERROR_MESSAGE;
    this->tag = tag;
}
