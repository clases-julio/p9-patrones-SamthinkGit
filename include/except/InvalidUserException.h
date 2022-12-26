// ------------------- InvalidUserException - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file InvalidUserException.h
* @date 20/12/2022
* @inherit BaseException.h
*/
#ifndef INVALIDUSEREXCEPTION_H
#define INVALIDUSEREXCEPTION_H
#include "BaseException.h"

/**
* @brief This class lets the program throw an exception when the selected user is
* not valid
*/
class InvalidUserException : BaseException{

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

     /** @brief Throws main exception.
     * @param tag Founder of the exception */
    explicit InvalidUserException(const std::string &tag);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    /**  @brief Message to display in what() */
    static std::string ERROR_MESSAGE;

};


#endif //INVALIDUSEREXCEPTION_H
