// ------------------- KernelDevice - JVH Systems -------------------------------
/**
*  @author Sebastian Mayorquin (Software Design)
*  @file KernelDevice.h
*  @date 12/11/2022
*/
#ifndef KERNELDEVICE_H
#define KERNELDEVICE_H
#include "Device.h"

/**
* @brief This class will contain specific properties
* of only kernel interacting devices and a set of functionalities
* for managing and checking their data. It also inherits properties
* from Device class.
*/
class KernelDevice : public Device {

    // This class will build all DataDevices
    friend class DeviceBuilder;
    friend class AI;

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    /** @brief Creates a New KernelDevice. It uses invalid properties
    *  by default. Not recommended. */
    KernelDevice();

    /** @brief Builds a new KernelDevice and assign its basic properties
    * @param name public name for user
    * @param id private identifier for AI */
    KernelDevice(const std::string& name, const int id);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  DYNAMIC  ----------------------

    // [Variables]

    /**  @brief Pointer to function to check security status */
    bool(*securityGenerator)();
    /**  @brief Pointer to function to check security status */
    bool securityHasBeenBroken;

    // -----------------  STATIC  ----------------------

    // [Variables]

    /**  @brief Pointer to array with all Kernel Devices */
    static KernelDevice* allKernelDevices;
    /**  @brief number of detected Kernel Devices */
    static int numKerns;

    // [Methods]

    /** @brief Sets all pointers to KernelDevices. Used for general
    * Kernel Device control, It can cause conflict with other
    * processes, recommended only with builder implementation. */
    static void setAllKernelDevices(KernelDevice* allDevices);

};


#endif //KERNELDEVICE_H
