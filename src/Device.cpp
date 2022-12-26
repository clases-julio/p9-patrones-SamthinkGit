// ------------------- Device - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file Device.cpp
  @date 12/11/2022
  @grade Software Robotics (Software Design)

*/
#include "../include/Device.h"

// ----- Declarations ------
int Device::numDevices;
Device* Device::allDevices;
std::string* Device::allDeviceNames;
std::string Device::TAG = "Device";

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------

// --- [Empty Constructor] Device ---
Device::Device() : name(""),id(INVALID_DEVICE){};

// --- [Constructor] Device ---
Device::Device(std::string deviceName, int deviceId): name(deviceName),id(deviceId){}


// --- [Getter] getName ---
std::string Device::getName() {
    return this->name;
}

int Device::getNumSkills(){
    return this->numSkills;
}

// --- [Method] operator[] (int) ---
void Device::operator[](int index){
    try{
        (*this->skills)[index]();

    }catch (std::exception){
        throw InvalidSkillException(TAG);
    }
}

// --- [Method] operator[] (string) ---
void Device::operator[](std::string skillName){
    // ----- Set number of skills ------
    int skillSize = this->numSkills;

    // ----- Find and use Skill ------
    for (int i = 0; i < skillSize; i++){
        if (skillName == skillNames[i])
            try{
                (*this->skills)[i]();
                break;
            }catch (std::exception){
                throw InvalidSkillException(TAG);
            }

    }
};

// --- [Operator] ~ ---
bool Device::operator~() {
    return this->isActive;
}

// ------------------------------------------------------
//                  PRIVATE FUNCTIONALITIES             |
// ------------------------------------------------------


// --- [Setter] setAllDevices ---
void Device::setAllDevices(Device* allNewDevices, std::string* allNewDeviceNames, int numDevices) {

    // ----- Setting Device pointers and names ------
    std::cout << "[DEVICES] Collecting all devices: " << std::endl;
    Device::allDevices = allNewDevices;
    Device::allDeviceNames = allNewDeviceNames;
    Device::numDevices = numDevices;

    // ----- Log Success Device ------
    for (int i = 0; i < numDevices; i++){
        std::cout << "-> (SUCCESS) " << allNewDeviceNames[i] << std::endl;
    }

}

// --- [Setter] setDeviceCounter ---
void Device::setDeviceCounter(int num) {
    Device::numDevices = num;
}
