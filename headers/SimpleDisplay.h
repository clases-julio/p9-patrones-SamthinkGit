// ------------------- SimpleDisplay - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file SimpleDisplay.h
* @date 04/11/2022
*/

#ifndef SIMPLE_DISPLAY_H
#define SIMPLE_DISPLAY_H
#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <unistd.h>

/**
* @brief This library will contain a set of methods implemented by the main for
* graphicating in screen the main interface. This class can be changed by any other
* library whose functionalities are named in the same way
*/
class SimpleDisplay {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    // [Methods]

     /** @brief Builds a SimpleDisplay object. Used for storing display
     * properties and fastering accessing. */
    SimpleDisplay();

    // [Setters]

    /** @brief Sets the connection status of the alarms.
    * @param securityConnected Status of alarms: (True) Connected. (False) Disconnected */
    void setSecurityConnected(bool securityConnected);

    /** @brief Sets the security status of the alarms.
    * @param securityStatus Status of alarms: (True) Secure. (False) Insecure */
    void setSecurityStatus(bool securityStatus);

    /** @brief Sets number of Kernel Devices
    * @param kernelDevices */
    void setKernelDevices(int kernelDevices);

    /** @brief Sets number of Data Devices
    * @param dataDevices */
    void setDataDevices(int dataDevices);

    /** @brief Sets current user identificator
    * @param user */
    void setUser(int user);

    /** @brief Sets current user group
    * @param group */
    void setGroup(const std::string &group);

    /** @brief Inherit configuration from other display.
    * @param display Display to be inherited from */
    void operator<<(SimpleDisplay display);

     /** @brief Prints the login interface (encrypted)
     * @param user username to be printed in screen
     * @param pass Password to encrypt and print in screen
     * @param INVALID_USER User to do NOT print user in screen. -1 as default.
     * @param INVALID_PASS Pass to do NOT print user in screen. -1 as default. */
    static void printLoginInterface(int user, int pass, int INVALID_USER=-1, int INVALID_PASS=-1);

    /** @brief Prints text "Checking..." */
    static void printChecking();

     /** @brief Prints presentation text before main program */
    static void printPresentation();

    // [MAIN]

    /** @brief Prints main interface to screen using SimpleDisplay
    * properties
    * @param deviceNames Names of every dataDevice to be printedç
    * @param deviceStatus */
    void printMainInterface(std::string* deviceNames, bool* deviceStatus);

    // -----------------  STATIC  ----------------------

    // [DEVi++]

    /** @brief Prints text to Screen using DEVi++ prefix
    * @param text String which contains the message to be printed. */
    static void deviCout(std::string text);

    /** @brief Prints Devi++ initial interface
    * @param deviceName Name of current device */
    static void printDeviHeader(std::string deviceName);

    /** @brief Prints Devi++ header without help information */
    static void cleanDevi(std::string deviceName);

     /** @brief Prints Devi++ help manual */
    static void printDeviHelp();

    /** @brief Prints a dataframe in screen using DEVi++ model
    * @param data array of integers collected
    * @param time array of prefixes to data. Generally time-stamps */
    static void deviPrintData(std::vector<int> data ,std::vector<std::string> time);

    /** @brief Prints a self-generated manual based in current
    * SimpleDisplay
    * @param skillnames array of names of current device skills
    * @param number of skills detected */
    static void printSkillManual(std::string* skillnames, int count);

    // [STD]

    /** @brief Cleans the display using '\\n' */
    static void jump();

    /** @brief Prints text to Screen */
    static void cout(std::string text);

    // [AI]

    /** @brief Prints AI interface */
    static void printAIInterface();

    /** @brief Prints Authentication Screen from AI */
    static void printRequestPassword();

    /** @brief Prints first section of ExecBuilding */
    static void execBuildName();

    /** @brief Prints second section of ExecBuilding */
    static void execBuildType();

    /** @brief Prints third section of ExecBuilding
    * @param isDataDevice Type of section. (True) Data. (False) Kernel */
    static void execBuildGenerator(bool isDataDevice);

    /** @brief Prints final section of ExecBuilding */
    static void execBuildFinish();

    // [Security Rescue]

    /** @brief Checks if abort status has jumped out. If so,
    * calls a Rescue Thread */
    static void checkAbortStatus();

    // [Variables]

    /**  @brief String to call bold font
    * @warning Can vary between terminals */
    static std::string COLOR;

    /**  @brief String to call secondary font
    * @warning Can vary between terminals */
    static std::string GREY_COLOR;

    /**  @brief String to call default font
    * @warning Can vary between terminals */
    static std::string RESET_COLOR;

    /**  @brief String to call warning color
    * @warning Can vary between terminals */
    static std::string WARNING_COLOR;

    /**  @brief Pointer to current Display */
    static SimpleDisplay* currentDisplay;

    /**  @brief Variable to jump if program fail. Default in False. */
    static bool security_abort;

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  STATIC  ----------------------

    /**  @brief Maximum options to display in main interface
    * @warning Display can make unestable if changing variable */
    static int MAXIMUM_OPTIONS;

    // -----------------  DYNAMIC  ----------------------

    // [Variables]

    /** @brief Conection status of alarms */
    bool securityConnected;

    /** @brief Security status of alarms */
    bool securityStatus;

    /** @brief Number of Kernel Devices detected */
    int kernelDevices;

    /** @brief Number of Data Devices detected */
    int dataDevices;

    /** @brief Identifier of current user */
    int user;

    /** @brief Group of current user */
    std::string group;

};


#endif //SIMPLE_DISPLAY_H
