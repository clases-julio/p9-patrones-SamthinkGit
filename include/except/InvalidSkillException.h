// ------------------- InvalidSkillException - JVH Systems -------------------------------
/**
* @author Sebastian Mayorquin (Software Design)
* @file InvalidSkillException.h
* @date 20/12/2022
* @inherit BaseException.h
*/
#ifndef INVALIDSKILLEXCEPTION_H
#define INVALIDSKILLEXCEPTION_H
#include "BaseException.h"

/**
* @brief This class lets the program throw an exception when the selected skill is
* not valid
*/
class InvalidSkillException : BaseException {

// -----------------------------------------------
//                    PUBLIC                     |
// -----------------------------------------------
public:

     /** @brief Throws main exception.
     * @param tag Founder of the exception */
    explicit InvalidSkillException(const std::string &tag);

// -----------------------------------------------
//                   PRIVATE                     |
// -----------------------------------------------
private:

    /**  @brief Message to display in what() */
    static std::string ERROR_MESSAGE;

};


#endif //INVALIDSKILLEXCEPTION_H
