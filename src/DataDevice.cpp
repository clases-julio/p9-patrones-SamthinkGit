// ------------------- DataDevice - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file DataDevice.cpp
  @date 12/11/2022
  @grade Software Robotics (Software Design)

*/
#include "../include/DataDevice.h"

// ----- Declarations ------
DataDevice* DataDevice::allDataDevices;
std::string* DataDevice::allDataDeviceNames;
int DataDevice::numSensors = 0;
int DataDevice::numSensorsActive = 0;


// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------


// --- [Empty Constructor] DataDevice ---
DataDevice::DataDevice() {
    this->name = "";
    this->id = INVALID_DEVICE;
    this->isDataDevice = true;

};

// --- [Constructor] DataDevice ---
DataDevice::DataDevice(std::string name, int id,std::vector<void(*)()>* skillVector, std::string* skillNames) {

    // ----- Counting Devices ------
    std::cout << "[DataDevice] New Device Detected: 0x" << id << std::endl;
    numSensors++;

    // ----- Property assignation ------
    this->name = name;
    this->id = id;
    this->skills = skillVector;
    this->skillNames = skillNames;
    this->isDataDevice = true;
    this->numSkills = skillVector->size();
    this->isActive = true;
}

// --- [Getter] getNumSensors ---
int DataDevice::getNumSensors(){
    return numSensors;
};


// --- [Method] appendNewData ---
void DataDevice::appendNewData() {
    auto clock = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(clock);
    std::string time_stamp = std::ctime(&time);
    this->collectedData.push_back(this->dataGenerator());
    this->collectedTimes.push_back(time_stamp);
}


// ------------------------------------------------------
//                  PRIVATE FUNCTIONALITIES             |
// ------------------------------------------------------

// --- [Method] setLimit ---
void DataDevice::setLimit(int* limitArray) {
    this->limit = limitArray;
    this->needsLimit = true;
}


// --- [Setter] setAllDataDevices ---
void DataDevice::setAllDataDevices(DataDevice* allDevices){
    allDataDevices = allDevices;
    allDataDeviceNames = new std::string[numSensors];

    for (int i = 0; i < numSensors; i++){
        allDataDeviceNames[i] = allDevices[i].getName();
    }
}
