// ------------------- KernelDevice - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file KernelDevice.cpp
  @date 12/11/2022
  @grade Software Robotics (Software Design)

*/
#include "../headers/KernelDevice.h"


// ----- Declarations ------
KernelDevice* KernelDevice::allKernelDevices;
int KernelDevice::numKerns = 0;

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------

// --- [Empty Constructor] KernelDevice ---
KernelDevice::KernelDevice() {
    this->name = "";
    this->isActive = false;
    this->id = INVALID_DEVICE;
    this->isDataDevice = false;
    this->securityHasBeenBroken = false;
};

// --- [Constructor] KernelDevice ---
KernelDevice::KernelDevice(std::string name, int id) {

    std::cout << "[KernelDevice] New Device Detected: 0x" << id << std::endl;

    numKerns++;

    this->name = name;
    this->id = id;
    this->isDataDevice = false;
    this->isActive = true;
    this->securityHasBeenBroken = false;
}

// ------------------------------------------------------
//                  PRIVATE FUNCTIONALITIES             |
// ------------------------------------------------------

// --- [Setter] setAllKernelDevices ---
void KernelDevice::setAllKernelDevices(KernelDevice* allDevices){
    allKernelDevices = allDevices;
}

