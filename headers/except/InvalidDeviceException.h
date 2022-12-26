// ------------------- InvalidDeviceException - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file InvalidDeviceException.h
* @date 20/12/2022
* @inherit BaseException.h
*/
#ifndef INVALIDDEVICE_H
#define INVALIDDEVICE_H
#include "BaseException.h"

/**
* @brief This class lets the program throw an exception when the selected device is
* not valid
*/
class InvalidDeviceException : public BaseException{

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

     /** @brief Throws main exception.
     * @param tag Founder of the exception */
    explicit InvalidDeviceException(std::string &tag);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    /**  @brief Message to display in what() */
    static std::string ERROR_MESSAGE;

};


#endif //INVALIDDEVICE_H
