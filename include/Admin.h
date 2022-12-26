// ------------------- Admin - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file Admin.h
* @date 20/12/2022
* @inherit User.h
*/

#ifndef JVH_SYSTEMS_ADMIN_H
#define JVH_SYSTEMS_ADMIN_H
#include "User.h"

/**
* @brief This class is the responsible for instantiating an Admin object to
* distinguish between Users and Admins.
*/
class Admin : public User {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    /** @brief Builds a new Admin object
    * @param id Admin identificator */
    Admin(int id);

    // -----------------  STATIC  ----------------------

     /** @brief Gets current object status
     * @param id User Identifier
     * @return (True) is Admin. (False) is Guest */
    static bool adminStatus(int id);

};

#endif //JVH_SYSTEMS_ADMIN_H
