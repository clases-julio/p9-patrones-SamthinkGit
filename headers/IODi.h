// ------------------- Input/Output Device Interface - JVH Systems -------------------------------
/**
* @file IODi.h
* @author Sebastian Mayorquin (Software Design)
* @date 12/11/2022
*/

#ifndef IODI_H
#define IODI_H
#include "DataDevice.h"

/**
* @brief This class will be the responsible for interpreting the status
* of the devices and sending proper information, and executing the requested
* skills for the main class when it needs to interact with any device. Thus,
* it will be implemented by the main class and can't exist without Device
* class.
*/
class IODi {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    enum{
        DEFAULT_ID = 33
    };

    // -----------------  DYNAMIC  ----------------------

    /** @brief Creates a new IOD interface ready for accessing to Device
    * properties. */
    IODi();

    /** @brief Requests all names of detected devices
    * @return Pointer to array with names of Devices */
    std::string* requestDeviceNames();

    /** @brief Requests all skill-names of current device
    * @return Pointer to array with name of every skill of
    * current device */
    std::string* requestDeviceSkills();

    /** @brief Requests name of current device
    * @return Name of current device */
    std::string requestCurrentDeviceName();

    /** @brief Requests number of Data Devices Detected
    * @return Number of DataDevices built */
    int requestNumberOfDataDevices();

    /** @brief Requests number of skill-names in current Device
    * @return Number of skills of current device */
    int requestNumberOfSkills();

    /** @brief Request status of all devices
     * @return Pointer to boolean with all status. True if it is turned on. Else False. */
    bool* requestAllStatus();

    /** @brief Uses a skill from selected device
    * @param skill Name of skill */
    void requestSkill(std::string skill);

    /** @brief Uses a skill from selected device
    * @param skill Position in SkillList of skill */
    void requestSkill(int skill);

    /** @brief Sets the id and position of current device inside IODi.
    * @param Name of device
    * @throw InvalidDeviceException Device settled not valid/built */
    void setCurrentDevice(std::string name);

    /** @brief Sets the id and position of current device inside IODi.
    * @param Position of device in allDevices
    * @throw InvalidDeviceException Device settled not valid/built */
    void setCurrentDevice(int pos);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  DYNAMIC  ----------------------

    // [Variables]

    /** @brief id of current IODi */
    int id;
    /** @brief Name of current device */
    std::string currentDeviceName;
    /** @brief Position of current device in allDevices */
    int currentDevicePos;

    // -----------------  STATIC  ----------------------

    // [Functions]

    /**  @brief Name of class (for exception throwing) */
    static std::string TAG;
    /**  @brief maximum IODi ID detected */
    static int maxID;

};


#endif// IODI_H
