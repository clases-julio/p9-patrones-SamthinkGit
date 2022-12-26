#include "../include/except/InvalidSkillException.h"
std::string InvalidSkillException::ERROR_MESSAGE = "Invalid File";

InvalidSkillException::InvalidSkillException(const std::string &tag) {

    this->exception = ERROR_MESSAGE;
    this->tag = tag;

}
