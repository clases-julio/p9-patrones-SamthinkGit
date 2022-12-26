// ------------------- User - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file User.h
* @date 04/11/2022
*/
#ifndef USER_H
#define USER_H
#include "../include/lib.h"

/**
* @brief This class will be the responsible for storing
* and managing the user's data. Also is able to create an
* abstract user object to ease data access
*/
class User {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // [Enum]
    enum {
        INVALID_USER = -2,
        INVALID_PASS = -2,
        USER_COLUMN = 0,
        PASS_COLUMN = 1,
        ADMIN_COLUMN = 2,
        ADMIN_IDENTIFIER = 1,
        TOTAL_COLUMNS = 3,
        DEVELOPER_USER = -1
    };

    // -----------------  DYNAMIC  ----------------------

    // [Methods]

    /** @brief Empty constructor (not recommended) */
    User();

    /** @brief Build a new ACTIVE user. Only use to ease user
    * information access. Auto sets the admin role according
    * to data stored in file.
    * @param id user identification (5-digit num) */
    User(int id);

    // [Variables]

    /** @brief Returns User's username */
    int getUser();

    /** @brief Returns User's admin status */
    bool getAdminStatus();

    // -----------------  STATIC  ----------------------

    // [Functions]

    /** @brief Check if id and password are valid.
    * Needs to access to datafile.
    * @param id user identification (5-digit num)
    * @param pass user password (8-digit num)
    * @return True if id and pass are valid */
    static bool check(int id, int pass);

    /** @brief Reads the datafile, then store users in a
    * 2 dimensional array (allUsers) setting each column
    * according to the columns setted in User.h class.
    * Sorted by
    * id for efficiency.
    * @throw InvalidUserException User not valid/found
    * @throw InvalidFileException File not valid/not Accessible */
    static void updateUserData();

     /** @brief Saves all data saved in the set vector to a .dat file
     * @note Path file can be changed with USERFILE
     * @note This function should be only called at the end of the program */
    static void saveUserData();

     /** @brief Adds new user to allUsers
     * @param id user identification (5-digit num)
     * @param pass user password (8-digit num)
     * @param isAdmin Admin Status. (True) Admin. (False) Guest. */
    static void addUser(int id, int pass, bool isAdmin);

    /** @brief Removes a user from allUsers
    * @param id user identification */
    static void rmUser(int id);

    /** @brief Prints all registered users */
    static void printUsers();

    // [Variables]

    static std::string EXECUTABLE_DIR;

// -----------------------------------------------
//                  PROTECTED                    |
// -----------------------------------------------
protected:

    // -----------------  DYNAMIC  ----------------------

    // [Variables]

    /** @brief User identifier (5-digit-int)
     * @note root and developer don't need to use 5-digit numbers */
    int id;
    /** @brief Admin Status. False by defect */
    bool isAdmin;
    /** @brief Password to access the account */
    int pass;

    // -----------------  STATIC  ----------------------

    // [Functions]

    /** @brief Finds a user by giving the id as a key . Maximum
    * complexity of O(n). Returns the properties of the user
    * as a pointer to array.
    * @param id key for searching user
    * @note Complexity of O(log(n)) is possible, not
    * implemented yet.
    * @throw UserNotFoundException User not found */
    static int* find(int id);

    // [DEPRECATED] static std::vector<int> find(int id);

    // [Variables]

    /**  @brief Character to separate tokens in file */
    static char SEPARATOR;
    /**  @brief Name of the Class (for exception calling) */
    static std::string TAG;
    /**  @brief Set of integers to store all users. */
    static std::set<int*> allUsers;
    /** @brief [DEPRECATED] Path of userdata file */
    static std::string DATAFILE;
    /** @brief Path to userdata file */
    static std::string USERFILE;
};


#endif //USER_H
