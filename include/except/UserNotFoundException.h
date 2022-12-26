// ------------------- UserNotFoundException - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file UserNotFoundException.h
* @date 20/12/2022
* @inherit BaseException.h
*/
#ifndef USERNOTFOUND_H
#define USERNOTFOUND_H
#include "BaseException.h"

/**
* @brief This class lets the program throw an exception when the selected user has not
* been found
*/
class UserNotFoundException : public BaseException {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

     /** @brief Throws main exception.
     * @param tag Founder of the exception */
    explicit UserNotFoundException(const std::string &tag);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    /**  @brief Message to display in what() */
    static std::string ERROR_MESSAGE;

};


#endif //USERNOTFOUND_H
