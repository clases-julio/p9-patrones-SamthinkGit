// ------------------- BaseException - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file BaseException.h
* @date 20/12/2022
* @inherit std::exception
*/
#ifndef BASE_EXCEPTION_H
#define BASE_EXCEPTION_H
#include <string>
#include <exception>

/**
* @brief This class establishes a basic format for JVH exceptions.
*/
class BaseException : public std::exception {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

     /** @brief Builds a new BaseException */
    BaseException();

     /** @brief Prints the cause of the exception with the tag of the owner.
     * @return Exception info */
    const char* what();

// -----------------------------------------------
//                  PROTECTED                    |
// -----------------------------------------------
protected:

    /** @brief Owner/Causant of the exception */
    std::string tag;
    /** @brief Description of the exception */
    std::string exception;


};

#endif //BASE_EXCEPTION_H
