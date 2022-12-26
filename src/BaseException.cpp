#include "../include/except/BaseException.h"
BaseException::BaseException() {}

const char* BaseException::what() {

    return ("[" + tag + "] " + exception).c_str();

}


