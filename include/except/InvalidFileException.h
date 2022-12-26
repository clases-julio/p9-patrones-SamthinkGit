// ------------------- InvalidFileException - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file InvalidFileException.h
* @date 20/12/2022
* @inherit BaseException.h
*/
#ifndef INVALIDFILEEXCEPTION_H
#define INVALIDFILEEXCEPTION_H
#include "BaseException.h"

/**
* @brief This class lets the program throw an exception when the File to be read is
* not valid
*/
class InvalidFileException : BaseException {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

     /** @brief Throws main exception.
     * @param tag Founder of the exception */
    explicit InvalidFileException(const std::string &tag);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    /**  @brief Message to display in what() */
    static std::string ERROR_MESSAGE;

};


#endif //INVALIDFILEEXCEPTION_H
