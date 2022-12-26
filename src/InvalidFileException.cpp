#include "../headers/except/InvalidFileException.h"
std::string InvalidFileException::ERROR_MESSAGE = "Invalid File";

InvalidFileException::InvalidFileException(std::string &tag) {

    this->exception = ERROR_MESSAGE;
    this->tag = tag;
}
