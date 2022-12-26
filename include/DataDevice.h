// ------------------- DataDevice - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file DataDevice.h
* @date 12/11/2022
*/
#ifndef DATADEVICE_H
#define DATADEVICE_H
#include "Device.h"

/**
* @brief This class will contain specific properties of
* output devices and a set of functionalities for managing and
* checking their data. It inherits properties from Device class.
*/
class DataDevice : public Device{

    // This class will build all DataDevices
    friend class DeviceBuilder;
    friend class AI;
    friend class IODi;

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    // [Methods]

    /** @brief Creates a New DataDevice. It uses invalid properties
    * by default. Not recommended. */
    DataDevice();

    /** @brief Creates a new DataDevice and assign its basic properties
    * @param name: public name for user
    * @param id: private identifier for AI
    * @param skillVector: Vector with all skills
    * implemented in the devices as pointers to functions
    * @param skillNames: Names for the skills implemented.
    * @note Skills and skill-names must be in the same order so the
    * kernel can show them to the user. */
    DataDevice(const std::string &name, int id,std::vector<void(*)()>* skill, std::string* skillNames);

    // [Variables]

    /** @brief Collect new measurement from main data generator and
    * saves it in data vectors */
    void appendNewData();

    // -----------------  STATIC  ----------------------

    // [Functions]

    /**  @brief Pointers to all Data Devices built */
    static DataDevice* allDataDevices;
    /**  @brief Pointers to all Data Device names */
    static std::string* allDataDeviceNames;

    // [Variables]

    /** @brief Returns the current number of DataDevices detected
    * @return Number of detected Sensors */
    static int getNumSensors();


// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  DYNAMIC  ----------------------

    // [Methods]

    /** @brief Sets a Warning limit for the device. This limit will
    * be supervised by AI.
    * @warning It can cause conflict with other processes, recommended
    * only with builder implementation
    * @param limitArray array of values to supervise. */
    void setLimit(int* limitArray);

    // [Variables]

    /** @brief vector with all measurements collected from the sensor */
    std::vector<int> collectedData;
    /** @brief Vector with all time-stamps of the measurements */
    std::vector<std::string> collectedTimes;
    /** @brief Main generator of measurements/data of the sensor */
    int(*dataGenerator)();
    /** @brief Distinguish between Data Devices which uses or not Limits */
    bool needsLimit = false;
    /** @brief Limit to control by AI */
    int* limit;

    // -----------------  STATIC  ----------------------

    // [Functions]

    /** @brief Sets all pointers to DataDevices. Used for general
    * Data Device control.
    * @warning It can cause conflict with other processes, recommended
    * only with builder implementation. */
    static void setAllDataDevices(DataDevice* allDevices);

    // [Variables]

    /**  @brief Number of DataDevices stablished */
    static int numSensors;
    /**  @brief Number of DataDevices turned on */
    static int numSensorsActive;

};


#endif //DATADEVICE_H
