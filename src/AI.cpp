// ------------------- Automatic Interface - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file AI.cpp
  @date 16/11/2022
  @grade Software Robotics (Software Design)

*/

#include "../headers/AI.h"

// ----- Declarations ------
int AI::MAX_DATA = 30;
int AI::SLEEPTIME = 1;
std::string AI::TAG = "AI";

bool AI::abort = false;

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------


// --- [Empty Constructor] AI() ---
AI::AI() {
    this->time_counter = 0;
    signal(SIGINT, signalHandler);

}

// --- [Method] startCollectingData ---
void AI::startCollectingData() {

    // ----- Intializing ------
    std::cout << "[AI] Collecting Data" << std::endl;
    int dataCounter = 0;

    // ----- Filling every device ------
    int numDevices = DataDevice::getNumSensors();
    for (int device = 0; device < numDevices; device++)
        for (int data = 0; data < MAX_DATA; data++) {
            DataDevice::allDataDevices[device].appendNewData();
            dataCounter++;
        }

    // ----- Sending Output ------
    std::cout << "[AI] Collected " << dataCounter << " measures" << std::endl;
}


// --- [Method] refreshData ---
void AI::refreshData() {

    // ----- Declarations ------
    int numDevices = DataDevice::getNumSensors();

    // ----- Refreshing every data device one time ------
    for (int i = 0; i < DataDevice::numSensors; i++) {

        DataDevice* target = &DataDevice::allDataDevices[i];

        // Check if it's active
        if (!~(*target)) continue;

        // Check if it is full
        if (target->collectedData.size() >= MAX_DATA) {

            // Remove oldest measurement
            target->collectedData.erase(target->collectedData.begin());

            // Remove oldest time
            target->collectedTimes.erase(target->collectedTimes.begin());

        }
        // Append new measurement and time
        target->appendNewData();
    }

    // ----- Refreshing every kernel device one time -----
    for (int i = 0; i < KernelDevice::numKerns; i++) {

        KernelDevice* k = &KernelDevice::allKernelDevices[i];
        // Check if it's active
        if (!~(*k)) continue;

        if (!(*k).securityGenerator() || k->securityHasBeenBroken) {
            k->securityHasBeenBroken = true;
            SimpleDisplay::currentDisplay->setSecurityStatus(false);
        }
    }

}

// --- [Method] throwDemon ---
void AI::throwDemon() {

#ifdef _WIN32

    while (true) {
        try {

            if (kbhit()) break;
            if (abort){
                SimpleDisplay::cout("[WARNING] You should not exit directly from main menu. Use -1 instead.\n");
                exit(0);
            }
            refreshData();
            sleep(SLEEPTIME);

        } catch (std::exception &e) {
            sleep(SLEEPTIME);
            continue;
        }
    }
#else
    while (true){
    try{

        if (kb::kbhit()) break;
        if (abort){
            SimpleDisplay::cout("[WARNING] You should not exit directly from main menu. Use -1 instead.\n");
            exit(0);
        }
        refreshData();
        sleep(SLEEPTIME);

    }catch (std::exception e){
        sleep(SLEEPTIME);
    }
}
#endif
}

void AI::requestOption(std::string opt, bool isAdmin) {
    try {
        int num = atoi(opt.c_str());

        switch (num) {

            case TURNDEVICES:
                turnDevices();
                break;

            case TURNSECURITY:
                turnSecurity();
                break;

            case CHECKSECURITY:
                checkSecurity();
                break;

            case MICROPHONE:
                microphone();
                break;

            case FORCEERROR: {
                try {
                    AI::ensureAdminAccess(isAdmin);
                }catch (InsufficientPermissionsException &e){
                    break;
                }

                forceError();
                break;
            }

            case BUILDDEVICE:{
                try {
                    AI::ensureAdminAccess(isAdmin);
                }catch (InsufficientPermissionsException &e){
                    break;
                }

                buildDevice();
                break;
            }

            case ADDUSER:{
                try {
                    AI::ensureAdminAccess(isAdmin);
                }catch(InsufficientPermissionsException &e){
                    break;
                }
                addUser();
                break;
            }

            case REMOVEUSER:{
                try{
                    AI::ensureAdminAccess(isAdmin);
                }catch(InsufficientPermissionsException &e){
                    break;
                }
                removeUser();
                break;
            }

            case RETURNSECURITY: {
                try {
                    AI::ensureAdminAccess(isAdmin);
                }catch (InsufficientPermissionsException &e){
                    break;
                }
                recoverSecurity();
                break;
            }

            case FORCEBADALLOC:{
                try {
                    AI::ensureAdminAccess(isAdmin);
                }catch (InsufficientPermissionsException &e){
                    break;
                }
                forceBadAlloc();
                break;
            }

            case SHOWUSERS: {
                try {
                    AI::ensureAdminAccess(isAdmin);
                } catch (InsufficientPermissionsException &e){
                    break;
                }
                showAllUsers();
                break;
            }

            case EXIT:
                break;
        }


    }catch (std::exception &e){
        SimpleDisplay::cout("Option NOT valid");
        sleep(1);
    }

}

void AI::ensureAdminAccess(bool isAdmin) {

    // ----- Checking Admin Status -----
    if (!isAdmin) {
        SimpleDisplay::cout("THIS ACTION REQUIRES ADMINISTRATOR ACCESS");
        sleep(SLEEPTIME*2);
        throw InsufficientPermissionsException(TAG);
    }

    // ----- Entering a console and requesting password -----
    try {
        std::string message;
        SimpleDisplay::printRequestPassword();
        SimpleDisplay::cout("Keyboard: ");
        std::getline(std::cin,message);

        // Checking input
        if (message != "0")
            throw InsufficientPermissionsException(TAG);

        // Invalid Input
        }catch(std::exception e){

            SimpleDisplay::cout("INVALID PASSWORD");
            sleep(SLEEPTIME);
            throw InsufficientPermissionsException(TAG);
        }

}

void AI::turnDevices() {

    // ----- Instantiating IODi for easy device control -----
    IODi iodi;

    // ----- Turning all Devices ON/OFF -----
    for (int i = 0; i < DataDevice::numSensors; i++) {
        iodi.setCurrentDevice(i);

        if (~DataDevice::allDataDevices[i])
            iodi.requestSkill("turnoff");
        else
            iodi.requestSkill("turnon");

    }

    // ----- Exiting... -----
    std::string none;
    SimpleDisplay::cout("Press ENTER to continue");
    getline(std::cin,none);
}

void AI::turnSecurity() {

    for (int i = 0; i < KernelDevice::numKerns; i++) {

        // Accessing Device
        KernelDevice *k = &KernelDevice::allKernelDevices[i];

        // Checking Status
        k->isActive = !~(*k);

        // Turning ON/OFF
        if (~(*k)) {
            SimpleDisplay::cout(k->getName() + " turned ON\n");
            SimpleDisplay::currentDisplay->setSecurityConnected(true);
        }
        else {
            SimpleDisplay::cout(k->getName() + " turned OFF\n");
            SimpleDisplay::currentDisplay->setSecurityConnected(false);
        }
    }

    // ----- Exiting -----
    std::string none;
    SimpleDisplay::cout("Press ENTER to continue");
    getline(std::cin,none);
}

void AI::checkSecurity(){

    for (int i = 0; i < KernelDevice::numKerns; i++) {

        // Acessing Device
        KernelDevice* k = &KernelDevice::allKernelDevices[i];

        // Displaying chart
        SimpleDisplay::cout("[AI] [" + k->getName() + "] ");

        if (~*(k))
            SimpleDisplay::cout("[RUNNING]: ");
        else
            SimpleDisplay::cout("[DISCONNECTED]: ");

        if (!k->securityHasBeenBroken)
            SimpleDisplay::cout("Security status correct");
        else
            SimpleDisplay::cout("[WARNING] Security FAILURE! Please check the logs.");

        SimpleDisplay::cout("\n");

    }
    // ----- Exiting... -----
    std::string none;
    SimpleDisplay::cout("Press ENTER to continue");
    getline(std::cin,none);

}

void AI::microphone(){


    try {
        std::string message;

        SimpleDisplay::cout("\nEnter a message: ");
        getline(std::cin, message);

        SimpleDisplay::cout("[AI] SENDING MESSAGE:\n");
        SimpleDisplay::cout("|| -> " + message);

        sleep(SLEEPTIME);

    }catch (std::exception &e){
        SimpleDisplay::cout("Input not valid");
    }

}

void AI::forceError(){

    SimpleDisplay::printAIInterface();
    SimpleDisplay::cout("Forcing FAILURE in all security devices");

    for (int i = 0; i < KernelDevice::numKerns; i++) {
        KernelDevice::allKernelDevices[i].securityHasBeenBroken = true;
    }
    SimpleDisplay::currentDisplay->setSecurityStatus(false);

    sleep(SLEEPTIME*2);
}

void AI::buildDevice(){

    SimpleDisplay::execBuildName();
    std::string name;
    std::getline(std::cin,name);
    if (name == "EXIT") {

        SimpleDisplay::cout("\n[AI] Exit Request");
        sleep(SLEEPTIME);
        return;
    }

    SimpleDisplay::execBuildType();
    std::string type;
    std::getline(std::cin,type);

    if (type != "data" && type != "kernel"){
        SimpleDisplay::cout("\n[AI] Exit Request");
        sleep(SLEEPTIME);
        return;
    }

    std::string generator;
    if (type == "data"){
        SimpleDisplay::execBuildGenerator(true);
        std::getline(std::cin,generator);
    }else{
        SimpleDisplay::execBuildGenerator(false);
        std::getline(std::cin,generator);
    }

    SimpleDisplay::execBuildFinish();
    sleep(SLEEPTIME*2);
    SimpleDisplay::cout("[AI] Testing Building...\n");
    sleep(SLEEPTIME*2);
    SimpleDisplay::cout("[AI] Testing Device...\n");
    sleep(SLEEPTIME*2);

    DeviceBuilder::clearAll();
    DeviceBuilder* newDevice = new DeviceBuilder(name);
    DataDevice::numSensors = 0;
    KernelDevice::numKerns = 0;
    Device::numDevices = 0;
    if (type == "data"){
        (*newDevice).setAsDataDevice();
        (*newDevice).setDataGenerator(generateRandomData);
        DeviceBuilder::buildAllDevices();
    }else{
        (*newDevice).setAsKernelDevice();
        (*newDevice).setSecurityGenerator(exampleTest);
        DeviceBuilder::buildAllDevices();

    }
    SimpleDisplay::cout("[AI] Building SUCCESS\n");
    std::cout << "\nPress ENTER to start";
    std::cin.get();
    std::cin.clear();

}

void AI::recoverSecurity() {

    SimpleDisplay::printAIInterface();
    SimpleDisplay::cout("Recovering all Devices to Secure Status...");

    for (int i = 0; i < KernelDevice::numKerns; i++) {
        KernelDevice::allKernelDevices[i].securityHasBeenBroken = false;
    }
    SimpleDisplay::currentDisplay->setSecurityStatus(true);

    sleep(SLEEPTIME*2);
}

void AI::addUser() {

    int user, password;
    bool isAdmin;
    std::string entry;

    SimpleDisplay::cout("[AI] Insert a NIF id: ");
    std::getline(std::cin, entry);

    try {
        user = std::stoi(entry);
    }catch (std::exception e){
        SimpleDisplay::cout("[AI] Input not valid");
        sleep(SLEEPTIME);
        return;
    }

    SimpleDisplay::cout("[AI] Insert a password: ");

    try {
        password = std::stoi(entry);
    }catch (std::exception e) {
        SimpleDisplay::cout("[AI] Input not valid");
        sleep(SLEEPTIME);
        return;
    }

    std::getline(std::cin, entry);
    do {
        SimpleDisplay::cout("[AI] Give the user Admin Status? [y/n]: ");
        std::getline(std::cin, entry);
    }while(entry!= "y" && entry!= "n");

    isAdmin = (entry == "y" ? 1 : 0);
    User::addUser(user,password,isAdmin);

}

void AI::removeUser() {

    std::string id, confirmation;

    SimpleDisplay::cout("[" + TAG + "] Insert the id of the user to be removed: ");
    std::getline(std::cin,id);
    do {
        SimpleDisplay::cout("[" + TAG + "] Are you sure to remove " + id
        + " from the User list?\nThis can't be undone [y/n]:");
        std::getline(std::cin,confirmation);
    }while(confirmation != "y" && confirmation != "n");

    if (confirmation == "y") {
        try {
            User::rmUser(std::stoi(id));
        } catch (InvalidUserException &e) {
            SimpleDisplay::cout("[" + TAG + "] User requested not found");
        }
    }
    sleep(SLEEPTIME);

}

void AI::forceBadAlloc() {

    SimpleDisplay::cout("\nBuilding Secure Environment...");
    sleep(SLEEPTIME);
    SimpleDisplay::cout("\nGenerating Error...");
    try {
        std::vector<int> vector;
        for (int i = 0; i > -1; i++)
            vector.push_back(i);
    }catch(std::exception &e) {
        SimpleDisplay::cout("\n[WARNING] Environment Failure: \n-> what(): ");
        SimpleDisplay::cout(e.what());
        SimpleDisplay::cout("\nReturning...");
        sleep(SLEEPTIME*4);
    }
}

void AI::signalHandler(int signum) {

    // ----- Save all data -----
    User::saveUserData();

    // ----- Send abortation signal -----
    abort = true;
    SimpleDisplay::security_abort = true;

    // ----- Display EXIT CODE -----
    std::cout << "[" + TAG + "] Exit call detected. Exiting JVH Systems...";
    sleep(SLEEPTIME);
    std::cout << "\n[" + TAG + "] Thank you for trusting us!\n\n";
    exit(0);

}

void AI::showAllUsers() {
    User::printUsers();

    std::cout << "\nPress ENTER to return";
    std::cin.get();

    //  Clear bad inputs
    std::cin.clear();

}


