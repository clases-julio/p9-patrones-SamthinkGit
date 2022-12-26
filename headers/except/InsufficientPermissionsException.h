// ------------------- InsufficientPermissionException - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file InsufficientPermissionException.h
* @date 20/12/2022
*
* @inherit BaseException.h
*/
#ifndef INSUFFICIENTPERMISSIONSEXCEPTION_H
#define INSUFFICIENTPERMISSIONSEXCEPTION_H
#include "BaseException.h"
/**
* @brief This class lets the program throw an exception when the permissions of
* the user are not valid.
*/
class InsufficientPermissionsException :  BaseException {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

     /** @brief Throws main exception.
     * @param tag Founder of the exception */
    explicit InsufficientPermissionsException(std::string &tag);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    /**  @brief Message to display in what() */
    static std::string ERROR_MESSAGE;

};


#endif //INSUFFICIENTPERMISSIONSEXCEPTION_H
