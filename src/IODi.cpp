// ------------------- Input/Output Device Interface - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file IODi.cpp
  @date 16/11/2022
  @grade Software Robotics (Software Design)

*/

#include "../include/IODi.h"
#include "../include/AI.h"

// ----- Declarations ------
int IODi::maxID = 0;
std::string IODi::TAG = "IODi";

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------

// --- [Empty Constructor] IODi() ---
IODi::IODi(){
    this->id = DEFAULT_ID;
    maxID++;
};

// --- [Setter] setCurrentDevice ---
void IODi::setCurrentDevice(int pos) {

    // ----- If position is valid ------
    if (pos < IODi::requestNumberOfDataDevices()) {

        // Set position in current device
        this->currentDevicePos = pos;

        // Search and set name in current device
        this->currentDeviceName = DataDevice::allDataDeviceNames[pos];

    }
    else
        // ----- Argument not valid ------
        throw InvalidDeviceException(TAG);

}

// --- [Setter] setCurrentDevice ---
void IODi::setCurrentDevice(std::string name) {

    // ----- Check type argument is not a number ------
    if (std::isdigit(name[0])){

        this->setCurrentDevice(std::stoi(name));
        return;
    }

    // ----- Declarations ------
    int maxDevices = DataDevice::getNumSensors();

    // ----- Search Device ------
    for (int i = 0; i < maxDevices; i++){

        if (name == DataDevice::allDataDeviceNames[i]){

            // Save position and name in current device
            this->currentDevicePos = i;
            this->currentDeviceName = name;
            return;

        }

    }
    // ----- Device not valid ------
    throw InvalidDeviceException(TAG);

}


// --- [REQUEST] -> Name of all Devices
std::string* IODi::requestDeviceNames(){
    return DataDevice::allDataDeviceNames;
};

// --- [REQUEST] -> Number of all DataDevices
int IODi::requestNumberOfDataDevices(){
    return DataDevice::getNumSensors();
};

// --- [REQUEST] -> Number of Skills of current device
int IODi::requestNumberOfSkills(){
    return DataDevice::allDataDevices[this->currentDevicePos].getNumSkills();
}

// --- [REQUEST] -> Name of Skills of current device
std::string* IODi::requestDeviceSkills(){
    int numSkills = DataDevice::allDataDevices[this->currentDevicePos].getNumSkills();

    std::string* deviceSkills = new std::string[numSkills];

    for (int i = 0; i < numSkills; i++){
        deviceSkills[i] = DataDevice::allDataDevices[this->currentDevicePos].skillNames[i];
    }

    return deviceSkills;
};
// --- [Function] requestAllStatus()
bool* IODi::requestAllStatus() {

    bool* status = new bool[DataDevice::numSensors];

    for (int i = 0; i < DataDevice::numSensors; i++)
        status[i] = ~DataDevice::allDataDevices[i];

    return status;
};

// --- [REQUEST] -> Uses a skill given the position in device array
void IODi::requestSkill(int skill){
    try {
        DataDevice::allDataDevices[this->currentDevicePos][skill];
    }catch(InvalidSkillException &e){};
};

// --- [REQUEST] -> Name of current device
std::string IODi::requestCurrentDeviceName() {
    return this->currentDeviceName;
}

// --- [REQUEST] -> Uses a skill given the keyword
void IODi::requestSkill(std::string skill){

    // ----- Obtaining current device -----
    DataDevice* target = &DataDevice::allDataDevices[this->currentDevicePos];

    // ----- Switch between possible arguments ------
    if (skill == ":help")
        SimpleDisplay::printDeviHelp();

    else if (skill == ":dev")
        SimpleDisplay::printSkillManual(target->skillNames,\
                                        this->requestNumberOfSkills());
                                        // -> Vector with the name of skills
                                        // -> Int with the number of skills

    else if (skill == ":clean")
        SimpleDisplay::cleanDevi(this->currentDeviceName);

    else if (skill == "data")
        SimpleDisplay::deviPrintData(target->collectedData,\
                                     target->collectedTimes);
                                     // -> Vector with measurements
                                     // -> Vector with times of measurements

    else if(skill == "turnoff"){
        target->isActive = false;
        target->collectedData.resize(1);
        target->collectedData[0] = 0;
        target->collectedTimes.resize(1);
        target->collectedTimes[0] = "REBOOT";
        SimpleDisplay::deviCout("[IODi] " + target->getName() + " turned OFF");
    }

    else if(skill == "turnon"){
        target->isActive = true;
        SimpleDisplay::deviCout("[IODi] " + target->getName() + " turned ON");
    }

    else if (skill == "reboot"){
        this->requestSkill("turnoff");
        this->requestSkill("turnon");
    }

    else if (skill == "pwd")
        SimpleDisplay::deviCout("/home/devices/" + std::to_string(this->currentDevicePos));

    // ----- Frequent Invalid Commands ------

    else if (skill == "help")
        SimpleDisplay::deviCout("[IODi] Suggestion: Maybe you are looking for -> :help");

    else if (skill == "exit")
        SimpleDisplay::deviCout("[IODi] Suggestion: Maybe you are looking for -> :wq");

    else if (skill == "clear")
        SimpleDisplay::deviCout("[IODi] Suggestion: Maybe you are looking for -> :clean");

    else if (skill[0] == '\"' || skill[0] == '\'') {
        SimpleDisplay::deviCout("Are you trying to Inject SQL? Lol ok");
        SimpleDisplay::deviCout("[YOU HAVE BEEN BANNED]");
        exit(1);
    }

    // ----- Not Global command, request to current device ------
    else {
        try{
            (*target)[skill];
        }catch(InvalidSkillException &e){};
    }
}
