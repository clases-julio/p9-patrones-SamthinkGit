// ---------------------------- main - JVH Systems -------------------------------
/**
  @name main
  @author Sebastian Mayorquin
  @file main.cpp
  @date 04/11/2022
  @version v.0.2.1

  @brief This is the main Test Program, Running for testing snapshot

*/
#include "../headers/DeviceComposite.h"
/** Defining the different screens that the program can have. */
enum{
    MAIN_SCREEN = 0,
    DEVICE_SCREEN = 1,
    SETTINGS_SCREEN = 2
};


/**
 * @brief Main function to start and keep running JVH systems
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Argument vector.
 */
int main(int argc, char** argv)  {

    // ----- Checking Arguments ------
    bool IS_DEVELOPER = false;
    
    #ifdef _WIN32
    for (int i = 0; i < argc; i++){

        if (strcmp(argv[i], "--no-colors") == 0){
            SimpleDisplay::COLOR = "";
            SimpleDisplay::GREY_COLOR = "";
            SimpleDisplay::WARNING_COLOR = "";
            SimpleDisplay::RESET_COLOR = "";
        }
        if (strcmp(argv[i], "--developer") == 0)
            IS_DEVELOPER = true;
    }
    #else
        // Code for Linux
        for (int i = 0; i < argc; i++){
            if (strncmp(argv[i], "--no-colors", 11) == 0){
                SimpleDisplay::COLOR = "";
                SimpleDisplay::GREY_COLOR = "";
                SimpleDisplay::WARNING_COLOR = "";
                SimpleDisplay::RESET_COLOR = "";
            }
            if (strncmp(argv[i], "--developer", 11) == 0)
                IS_DEVELOPER = true;
        }
    #endif

    // ----- Initializing Builder + Display ------
    std::cout << "-------- [STARTING BUILDING] --------" << std::endl;
    deviceDataset::initDataset();
    DeviceBuilder::buildAllDevices();
    SimpleDisplay* display = DeviceBuilder::buildDisplay();

    // ----- Initializing AI------
    AI* ai = new AI();
    ai->startCollectingData();

    std::cout << "-------- [BUILDING SUCCESS] --------" << std::endl;

    // ----- Initializing IODi ------
    int screen_status = MAIN_SCREEN;
    std::string answer = "";
    IODi* iodi = new IODi();

    // ----- Initializig composite -----
    DeviceComposite* composite = new DeviceComposite;

    // ----- Initializing User Data------
    try {
        User::updateUserData();
    }catch (InvalidFileException &e){
        std::cout << "\n[Login] There has been an error updating user file, exiting...";
        exit(1);
    }catch (std::exception &e){
        std::cout << "\n[Login] There has been an error accessing the file, exiting...";
        exit(1);
    }
    // ----- Initializing Login ------
    Login* l = new Login();

    std::cout << "\nPress ENTER to start";
    std::cin.get();

    //  Clear bad inputs
    std::cin.clear();

    // ----- Checking Developer Status ------
    if (!IS_DEVELOPER) {
        SimpleDisplay::printPresentation();
        std::cout << "\nPress ENTER to start";
        std::cin.get();
    }

    //  Clear bad inputs
    std::cin.clear();

    // ----- Sending to Logger ------
    User user;
    if (!IS_DEVELOPER)
        user = l->startLogin();
    else {
        user = User(User::DEVELOPER_USER);
    }
    // ----- Setting User ------
    display->setUser(IS_DEVELOPER ? User::DEVELOPER_USER : user.getUser());
    display->setGroup((user.getAdminStatus() ? "ADMIN" : "GUEST"));

    // ----- [MAIN BUCLE] ------
    while(true){

        // ----- MAIN SCREEN ------
        if (screen_status == MAIN_SCREEN) {

            // Print Display
            std::string *deviceNames = iodi->requestDeviceNames();
            display->printMainInterface(deviceNames,iodi->requestAllStatus());

            // Request an entry
            SimpleDisplay::cout("Keyboard: ");
            ai->throwDemon(); // Update while not entry
            std::cin >> answer;

            // Exit if requested
            if (answer == "exit" || answer == "-1") {

                // Generating Logger
                user = l->startLogin();
                display->setUser(user.getUser());
                display->setGroup((user.getAdminStatus() ? "ADMIN" : "GUEST"));

            }

            // Go to Settings if requested
            else if (answer == "settings" || answer == "-2") {
                screen_status = SETTINGS_SCREEN;
            }

            // Entry not recognized, sending to IODi
            else
                try {

                    // Send to IODi and switch screen
                    composite->add(answer);
                    iodi->setCurrentDevice(answer);
                    screen_status = DEVICE_SCREEN;

                }catch (InvalidDeviceException &e){

                    //IODi hadn't found valid option, reset
                    SimpleDisplay::cout("INVALID OPTION");
                    sleep(1);
                }

        // ----- DEVi++ Terminal ------
        }else if (screen_status == DEVICE_SCREEN){

            // Print heeader and request entry
            SimpleDisplay::printDeviHeader(iodi->requestCurrentDeviceName());
            std::getline(std::cin,answer);

            // Don't exit the terminal until exit
            while (answer != ":wq") {

                // Request an entry
                SimpleDisplay::cout("~ ");
                std::getline(std::cin, answer);

                // Force refresh the devices if requested
                if (answer == "forceref") {
                    ai->refreshData();
                    SimpleDisplay::deviCout("[AI] Forced current Device to Refresh");
                }

                // Show the user if requested
                else if (answer == "who"){
                    SimpleDisplay::deviCout(std::to_string(user.getUser()));
                }

                // Show the composite status
                else if (answer == "comp")
                    SimpleDisplay::deviCout(composite->toString());

                else if (answer == "pop") {
                    composite->pop();
                    SimpleDisplay::deviCout("Last Device removed from composite");
                }

                // Command not recognized, sending to IODi
                else
                    composite->requestSkill(answer);
            }

            // When DEVi++ finish, switch to main screen
            composite->clear();
            screen_status = MAIN_SCREEN;

        }else if (screen_status == SETTINGS_SCREEN){

            while (answer != "-1") {

                SimpleDisplay::printAIInterface();
                SimpleDisplay::cout("Keyboard: ");
                std::getline(std::cin, answer);
                AI::requestOption(answer,user.getAdminStatus());
            }
            SimpleDisplay copy = *display;
            display = DeviceBuilder::buildDisplay();
            *display << copy;

            SimpleDisplay::currentDisplay = display;
            screen_status = MAIN_SCREEN;

        }
    }
}
