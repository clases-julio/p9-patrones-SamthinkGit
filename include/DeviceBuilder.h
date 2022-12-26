// ------------------- DeviceBuilder - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file DeviceBuilder.h
* @date 12/11/2022
*/

#ifndef DEVICEBUILDER_H
#define DEVICEBUILDER_H
#include "lib.h"
#include "DataDevice.h"
#include "KernelDevice.h"

/**
* @brief This class lets a high-level programmer add easily more devices to the main
* program. You can use the implemented public functions wherever you need.
* For adding a new device you can follow this steps:
* -# Instantiate a deviceBuilder with DeviceBuilder();
* -# Set the type of device with setAsDataDevice() or setAsKernelDevice();
* -# Set the main generator (function where the device extracts data) with setDataGenerator()
* or setSecurityGenerator()
* -# (Optional) Add some skills (more functionalities) to your device with setSkill().
* -# (Optional) Set a warning if measurement surpasses a limit with setLimit()
* -# Repeat this process with as many devices as you need.
* -# Use buildAllDevices() to build every instance.
*
* @note This class must be inited by the main class and will configure 3 classes.
* First, the builder will set every input device into the main class and set their
* corresponding global commands. Then it will build every output device into the Device
* class assigning the high-level functionalities and properties. Finally, the builder
* will assign AI properties of devices into the AI class if requested. When the
* relationships between high and low layer are established, the builder can be destroyed.
*/
class DeviceBuilder {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    /** @brief Creates a temporal builder for specific device.
    * @param name Name for the device.
    * @note ID is assigned by kernel.
    * @warning Device must be set as kernel or data device for being able to be built. */
    DeviceBuilder(const std::string& name = "STD_DEVICE");

    /** @brief Build one skill into the device Builder. All names and skills of
    * each device will be ordered and used in kernel.
    * @param Pointer to function (definition of skill)
    * @param skillName Name of skill (only for user) */
    void setSkill(void(*skill)(), const std::string& skillName);

    /** @brief Builds limits into the device Builder. All limits will be
    * controlled and implemented in execution by the kernel.
    * @warning KernelDevices can't use limits.
    * @param newLimit Array of ints to be checked */
    void setLimit(int* newLimit);

    /** @brief Sets type of Device as DataDevice */
    void setAsDataDevice();

    /** @brief Sets type of Device as KernelDevice */
    void setAsKernelDevice();

    /** @brief Sets the main data generator for DataDevices
    * @warning Data Devices could not work properly without generator.
    * @note Generator must return an integer.
    * @param dataGenerator Pointer to function (to generate data) */
    void setDataGenerator(int(*dataGenerator)());

     /** @brief Sets the security generator for KernelDevices
     * @warning Kernel Devices could not work properly without generator.
     * @note Generator must return a boolean
     * @param securityGenerator Pointer to function (to generate data) */
    void setSecurityGenerator(bool(*securityGenerator)());

    // -----------------  STATIC  ----------------------

    /** @brief Builds every builder instances.
    * @warning This function should only be called before starting or resetting the main program. */
    static void buildAllDevices();

    /** @brief Builds and returns a new SimpleDisplay object with properties
    * according to builder devices.
    * @return Display with properties
    * @note Must be used after buildAllDevices() */
    static SimpleDisplay* buildDisplay();

    /** @brief Kills every builder instances.
    * @warning Builder's will not work anymore after cleaning until built again. */
    static void clearAll();

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  DYNAMIC  ----------------------

    // [Methods]

    /** @brief Builds selected device as data or kernel device into the
    * kernel.
    * @warning This will NOT kill the builder.
    * @warning All properties must be settled before using. */
    void buildDKDevice();

    // [Variables]

    /** @brief Name of Device. */
    std::string name = "STD Device";
    /** @brief Skills of the Device */
    std::vector<void(*)()> skillVector;
    /** @brief Skill-names of each skill */
    std::vector<std::string> skillNamesVector;
    /** @brief Device's function to generate data */
    int (*dataGenerator)();
    /** @brief Kernel's Devices function to check security */
    bool (*securityGenerator)();
    /** @brief Identifier of Device */
    int id;
    /** @brief Limits of the Device*/
    int* limit = nullptr;
    /** @brief Type of device. (True) Data Device. (False) Kernel Device */
    bool isDataDevice;

    // -----------------  STATIC  ----------------------

    // [Variables]

    /**  @brief Vector with all builders instantiated */
    static std::vector<DeviceBuilder*> allBuilders;
    /**  @brief Vector with all Devices instantiated */
    static std::vector<Device> allDevices;
    /**  @brief Vector with all Data Devices instantiated */
    static std::vector<DataDevice> allDataDevices;
    /**  @brief Vector with all Kernel Devices instantiated */
    static std::vector<KernelDevice> allKernelDevices;
    /**  @brief Number of devices detected */
    static int deviceCounter;


};


#endif //DEVICEBUILDER_H
