// ------------------- Login - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file Login.h
* @date 04/11/2022
*/

#ifndef LOGIN_H
#define LOGIN_H
#include "Admin.h"

/**
* @brief This class is the responsible for superimposing a login interface
* to make the user log in as user. This will be a graphical interface belonging
* to the User class.
*
* Programmer Info: Designed as a logger obj. for multiple and simultaneous
* logger interfaces. Isn't any problem with changing to static functions.
*/
class Login {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    /** @brief Builds a logger
    * @note needed for use startLogin() */
    Login();

    /** @brief Creates a loop where the user must log in. It will never exit until the user
    * input a valid password and user (data obtained from User.h class)
    * @return Valid User */
    User startLogin();

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  STATIC  ----------------------

    /**  @brief Time to sleep between bad inputs */
    static int SLEEP_TIME;
    /**  @brief Value of exit request. -1 by default. */
    static int EXIT_REQUEST;

    // -----------------  DYNAMIC  ----------------------

    /** @brief Current user entry */
    int user;
    /** @brief Current password entry */
    int pass;

};


#endif //LOGIN_H
