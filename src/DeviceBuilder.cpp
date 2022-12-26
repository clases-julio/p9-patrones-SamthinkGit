// ------------------- DeviceBuilder - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file DeviceBuilder.cpp
  @date 12/11/2022
  @grade Software Robotics (Software Design)

*/
#include "../include/DeviceBuilder.h"


// ----- Declarations ------
std::vector<DeviceBuilder*> DeviceBuilder::allBuilders;
std::vector<Device> DeviceBuilder::allDevices;
std::vector<DataDevice> DeviceBuilder::allDataDevices;
std::vector<KernelDevice> DeviceBuilder::allKernelDevices;
int DeviceBuilder::deviceCounter;

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------

// --- [Static] buildDisplay ---
SimpleDisplay* DeviceBuilder::buildDisplay(){

    SimpleDisplay* display = new SimpleDisplay();
    display->setDataDevices(allDataDevices.size());
    display->setKernelDevices(allKernelDevices.size());
    display->setSecurityConnected(true);
    display->setSecurityStatus(true);
    return display;

}


// --- [Static] buildAllDevices ---
void DeviceBuilder::buildAllDevices() {

    // ----- Initializing ------
    std::cout << "[BUILDER] Sending " << allBuilders.size() << " Devices to Kernel" << std::endl;

    // ----- Declarations ------
    std::string *deviceNames = new std::string[allBuilders.size()]; // Array to Store Device names
    int numBuilders = allBuilders.size();

    // ----- Building All Devices Saved as Kernel or Data Device ------
    for (int i = 0; i < numBuilders; i++){

        // Saving device name in array
        deviceNames[i] = (*allBuilders[i]).name;

        // Building as Data or Kernel Device
        (*allBuilders[i]).buildDKDevice();
    }

    std::cout << "[BUILDER] Optimizing property access" << std::endl;
    // ----- All Devices Vector to Array ------
    Device *deviceArray = new Device[allDevices.size()];
    for (int i = 0; i < allDevices.size(); i++){
        deviceArray[i] = allDevices[i];
    }

    // ----- All DataDevices Vector to Array ------
    DataDevice *dataDeviceArray = new DataDevice[allDataDevices.size()];
    for (int i = 0; i < allDataDevices.size(); i++){
        dataDeviceArray[i] = allDataDevices[i];
    }


    // ----- All KernelDevices Vector to Array ------
    KernelDevice *kernelDeviceArray = new KernelDevice[allKernelDevices.size()];
    for (int i = 0; i < allKernelDevices.size(); i++){
        kernelDeviceArray[i] = allKernelDevices[i];
    }

    // ----- Storing Arrays ------
    std::cout << "[BUILDER] Storing General properties to Kernel..." << std::endl;
    Device::setAllDevices(deviceArray, deviceNames,numBuilders);
    DataDevice::setAllDataDevices(dataDeviceArray);
    KernelDevice::setAllKernelDevices(kernelDeviceArray);

}

// --- [Static] clearAll ---
void DeviceBuilder::clearAll(){

    // ----- Cleaning Vectors ------
    std::cout << "[BUILDER] Cleaning Builder..." << std::endl;

    allDataDevices.clear();
    allDevices.clear();
    allKernelDevices.clear();
}

// --- [Constructor] DeviceBuilder ---
DeviceBuilder::DeviceBuilder(const std::string& name) {

    // ----- Name Assign ------
    std::cout << "[BUILDER] Building " << name << std::endl;
    this->name = name;

    // ----- Storing Builder Pointer------
    DeviceBuilder* devicePointer = this;
    allBuilders.push_back(devicePointer);

    // ----- Settling Device ID ------
    enum {FANCY_ID = 55324,FANCY_SUM = 37};
    //Shhh.. It looks cooler with strange nums
    this->id = deviceCounter + FANCY_ID;
    deviceCounter += FANCY_SUM;

};

// --- [Method] setSkill ---
void DeviceBuilder::setSkill(void(*skill)(), const std::string& skillName) {

    // ----- Storing Device Skills ------
    this->skillVector.push_back(skill);
    this->skillNamesVector.push_back(skillName);
}

// --- [Method] setLimit ---
void DeviceBuilder::setLimit(int* newLimit) {

    // ----- Settling Device Limit ------
    this->limit = newLimit;
}

// --- [Setter] setAsDataDevice ---
void DeviceBuilder::setAsDataDevice() {
    this->isDataDevice = true;
}


// --- [Setter] setAsKernelDevice ---
void DeviceBuilder::setAsKernelDevice() {
    this->isDataDevice = false;
}
// --- [Method] setDataGenerator ---
void DeviceBuilder::setDataGenerator(int (*dataGenerator)()) {
    this->dataGenerator = dataGenerator;
}

void DeviceBuilder::setSecurityGenerator(bool (*securityGenerator)()) {
    this->securityGenerator = securityGenerator;
}

// ------------------------------------------------------
//                  PRIVATE FUNCTIONALITIES             |
// ------------------------------------------------------

// --- [Method] buildDKDevice---
void DeviceBuilder::buildDKDevice() {

    // ----- Skills to Dynamic Vector (so it doesn't get deleted when builder dies) ------
    std::vector<void(*)()>* dynamicSkillVector = new std::vector<void(*)()>;
    dynamicSkillVector->assign(skillVector.begin(), skillVector.end());

    // ----- SkillNames to Array (Optimizing data) ------
    std::string *skillNamesArray = new std::string[skillNamesVector.size()];
    for (int i = 0; i < this->skillNamesVector.size(); i++){
        skillNamesArray[i] = skillNamesVector[i];
    }

    // ----- Building DataDevice ------
    if (this->isDataDevice) {
        DataDevice *dataDev = new DataDevice(this->name, this->id, dynamicSkillVector, skillNamesArray);

        // Setting DataDevice limit (optional)
        if (this->limit != nullptr)
            (*dataDev).setLimit(this->limit);

        (*dataDev).dataGenerator = this->dataGenerator;

        // Saving Device Pointers
        allDevices.push_back(*dataDev);
        allDataDevices.push_back(*dataDev);

    // ----- Building KernelDevice ------
    }else {

        KernelDevice* kernDev = new KernelDevice(this->name, this->id);

        (*kernDev).securityGenerator = this->securityGenerator;

        // Saving Device Pointers
        allDevices.push_back(*kernDev);
        allKernelDevices.push_back(*kernDev);
    }

}


