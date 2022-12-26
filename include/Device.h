// ------------------- Device - JVH Systems -------------------------------
/**
*  @author Sebastian Mayorquin (Software Design)
*  @file Device.h
*  @date 12/11/2022
*/
#ifndef DEVICE_H
#define DEVICE_H
#include "lib.h"

/**
* @brief This class will contain every device as a general
*  low-level definition, containing the skills, properties and
*  a set of functionalities for managing all devices or modifying
*  them individually. Every device will be built from the builder
*  and the data managed will be managed from AI and IODi. This
*  class will also be the base for constructing DataDevices and
*  KernelDevices.
*/
class Device {

    friend class DeviceBuilder;
    friend class IODi;
    friend class AI;

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    // [Methods]

    /** @brief Builds a New Device. Sets Invalid properties by default.
    * Not recommended */
    Device();

    /** @brief Creates a New Device and assign a identifier
    * @param name Public name for device
    * @param id Private identifier for device */
    Device(const std::string& deviceName, const int deviceId);

    // [Operators]

    /** @brief Uses a built-in device-skill calling it by its name
    * @param skillName Name of the skill
    * @throw InvalidSkillException Skill-index not valid/found */
    void operator[](const int index);

    /** @brief  Uses a built-in device-skill calling it by its position
    * @param index Position of the skill (order of implementation)
    * @throw InvalidSkillException Skill-name not valid */
    void operator[](const std::string& skillName);

     /** @brief Checks if device is active
     * @return Status of the device. (True) Active. (False) Inactive. */
    bool operator~();

    // [Variables]

    /** @brief  Returns the name of the device
    * @return Name of device */
    std::string getName();

     /** @brief Returns number of skills of the device
     * @return Number of skills */
    int getNumSkills();

    // -----------------  STATIC  ----------------------

    /**  @brief Pointer to array with all Devices built */
    static Device* allDevices;

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  STATIC  ----------------------

    // [Functions]

    /**  @brief Name of class (for exception throwing) */
    static const std::string TAG;
    /**  @brief Pointers to every Device built */
    static std::string* allDeviceNames;
    /**  @brief Number of Devices built */
    static int numDevices;

    /** @brief Sets all pointers to Devices. Used to general
    * device control, recommended only for DeviceBuilder.
    * @param allNewDevices Array with pointers to all Devices
    * @param Array with names for each Device
    * @param numDevices Number of devices to be setted */
    static void setAllDevices(Device* allNewDevices, std::string* allNewDeviceNames, int numDevices);

    /** @brief Sets number of Detected Devices. Used to general
    * device control, recommended only for DeviceBuilder.
    * @param num Number of devices (total) */
    static void setDeviceCounter(int num);

// -----------------------------------------------
//                  PROTECTED                    |
// -----------------------------------------------
protected:

    // -----------------  DYNAMIC  ----------------------

    // [Enum]

    enum{
        INVALID_DEVICE = -1  // Change to set invalid ID of devices
    };

    // [Variables]

    /** @brief Distinguish between Data Devices and other Devices */
    bool isDataDevice;
    /** @brief (True). Is turned ON. (False). Is turned OFF. */
    bool isActive;
    /** @brief Kernel number of identification */
    int id;
    /** @brief Number of skills detected for the device */
    int numSkills;
    /** @brief Pointers to names of each skill
     * @warning Must have the same order that numSkills */
    std::string* skillNames;
    /** @brief Name of the device */
    std::string name;
    /** @brief Pointer to all functions (skills) build */
    std::vector<void(*)()>* skills;

};

#endif //DEVICE_H
