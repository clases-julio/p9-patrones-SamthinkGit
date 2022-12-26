// ------------------- Login - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file Login.cpp
  @date 03/11/2022
  @grade Software Robotics (Software Design)

*/
#include "../include/Login.h"
// ----- Declarations ------
int Login::SLEEP_TIME = 1;
int Login::EXIT_REQUEST = -1;

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------

// --- [Constructor] Login() ---
Login::Login() {};



// --- [Method] startLogin() ---
User Login::startLogin() {


    // ----- Declarations ------
    bool badAccess = false;          // Bool to detect if input is not correct.

    // ----- Logger Bucle ------
    do {

        //  Checking Bad Inputs
        if (badAccess) {
            SimpleDisplay::cout("Bad Access");
            sleep(SLEEP_TIME);
        }

        //  Reset Variables
        user = User::INVALID_USER;
        pass = User::INVALID_PASS;

        //  Prompt user
        SimpleDisplay::printLoginInterface(user, pass, User::INVALID_USER, User::INVALID_PASS);
        SimpleDisplay::cout("\nKeyboard: ");
        std::cin >> user;

        if (user == EXIT_REQUEST) raise(SIGINT);

        //  Prompt password
        SimpleDisplay::printLoginInterface(user, pass, User::INVALID_USER, User::INVALID_PASS);
        SimpleDisplay::cout("\nKeyboard: ");
        std::cin >> pass;

        if (pass == EXIT_REQUEST) raise(SIGINT);

        //  Print checking interface
        SimpleDisplay::printLoginInterface(user, pass, User::INVALID_USER, User::INVALID_PASS);
        SimpleDisplay::printChecking();

        //  Prepare next logger (if needed)
        badAccess = true;
        sleep(SLEEP_TIME);

        //  Clear bad inputs
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        //  Loop until the user and password are valid
    } while (!User::check(user, pass));

    // Return Admin (If needed)
    if (Admin::adminStatus(user))
        return Admin(user);

    // ----- Returning User ------
    return User(user);
};


