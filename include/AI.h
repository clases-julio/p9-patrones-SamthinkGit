// ------------------- Automatic Interface - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file AI.h
* @date 16/11/2022
*/

#ifndef AI_H
#define AI_H

#include "Login.h"
#include "lib.h"
#include "DataDevice.h"
#include "KernelDevice.h"
#include "IODi.h"
#include "../src/deviceDataset.cpp"
/**
* @brief  This class will be the responsible for interpreting
* global commands requested from the main class and checking the
* proper functioning of the devices. Thus, it will be implemented
* by the main class and can't live without Device class.
* Will be settled by the builder.
*/
class AI {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    // [Methods]

    /** @brief Creates a new Automatic Interface ready for controlling
    * device and main program status. */
    AI();

    /** @brief Search for every DataDevice and fills all its data
    * storage with measurements.
    * @warning All devices must be built before
    * using this function. */
    void startCollectingData();

     /** @brief Refresh last data to every device built */
    void refreshData();

    /** @brief Throws a process-like demon, which will be updating
    * the DataDevice measurements while waiting for key-interruption. */
    void throwDemon();

    // -----------------  STATIC  ----------------------

    // [Function]

     /** @brief Requests an option from main settings interface.
     * @param opt Option to select
     * @param isAdmin Admin status of current user */
    static void requestOption(const std::string &opt,bool isAdmin);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    enum {
        TURNDEVICES = 1,
        TURNSECURITY = 2,
        CHECKSECURITY = 3,
        MICROPHONE = 4,
        FORCEERROR = 5,
        BUILDDEVICE = 6,
        ADDUSER = 7,
        REMOVEUSER = 8,
        RETURNSECURITY = 9,
        FORCEBADALLOC = 10,
        SHOWUSERS = 11,
        MORE = 12,
        EXIT = -1
    };


    // -----------------  STATIC  ----------------------

    // [Functions]

    /** @brief Turns all devices on/off */
    static void turnDevices();

    /** @brief Turns all security on/off */
    static void turnSecurity();

    /** @brief Checks and print current security status */
    static void checkSecurity();

    /** @brief Sends a message using the microphone */
    static void microphone();

    /** @brief Forces an error in all Security devices
    * @note Error can be restored with recoverSecurity() */
    static void forceError();

    /** @brief Calls the builder for starting a interface to build
    * a new device in execution time */
    static void buildDevice();

    /** @brief Recover all security breaches to safe status */
    static void recoverSecurity();

    /** @brief Calls User class to add a new user */
    static void addUser();

    /** @brief Calls User class to remove a existing user */
    static void removeUser();

     /** @brief Generates a bad_alloc exception in a safe environment */
    static void forceBadAlloc();

    /** @brief Calls to print all users registered */
    static void showAllUsers();

     /** Ensures Administrator Access to a function
     * @param isAdmin previous status of user. (True) is Admin. False (is Guest).
     * @throw InsufficientPermissionsException Administrator Authentication Failed */
    static void ensureAdminAccess(bool isAdmin);

     /** Function to end the program if the exit call is raised
     * @param signum Exit call
     * @warning Function should not be used directly. Will be controlled by AI */
    static void signalHandler(int signum);

    // [Variables]

    /**  @brief Name of class (for exception throwing) */
    static std::string TAG;
    /**  @brief Alerts if exit request has been detected */
    static bool abort;
    /**  @brief Sets maximum of data/measurements collected from Data Devices */
    static int MAX_DATA;
    /**  @brief Sets time to sleep between interactions */
    static int SLEEPTIME;
    /** @brief Used for counting number of time-stamps */
    int time_counter;
};


#endif //AI_H
