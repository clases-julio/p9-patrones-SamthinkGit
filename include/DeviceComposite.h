/**
*  @author Sebastian Mayorquin (Software Design)
*  @file DeviceComposite.h
*  @date 26/12/2022
*/

#ifndef JVH_SYSTEMS_DEVICECOMPOSITE_H
#define JVH_SYSTEMS_DEVICECOMPOSITE_H
#include "AI.h"

/**
* @brief This class is the responsible of managing multiple orders to
* devices simultaneously. It will offer a easy interface to compose
* devices and send orders to them. */
class DeviceComposite {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

    // -----------------  DYNAMIC  ----------------------

    /** @brief Simple Composite construction. Empty as default */
    DeviceComposite();

    /** @brief Adds a new device to composite
     * @param name Name of device to search
     * @throw InvalidDeviceException If device not found */
    void add(const std::string &name);

    /** @brief Pops last device stacked */
    void pop();

    /** @brief Request a skill to all devices appended to
     * the composite.
     * @param skill Name of skill to use; */
     void requestSkill(const std::string& skill);

     /** @brief clears all devices inside the composite */
     void clear();

     /** @brief Search and find all device names inside the composite
      * @return String with the composite as a string */
     std::string toString();

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    // -----------------  DYNAMIC  ----------------------

    // [Variables]
    /** @brief Vector with all Device Managers (IODi's) */
    std::vector<IODi> allIODis;

    // -----------------  STATIC  ----------------------

    // [Variables]
    /** @brief Keyword for adding more devices */
    static const std::string CALL_KEYWORD;

};


#endif //JVH_SYSTEMS_DEVICECOMPOSITE_H
