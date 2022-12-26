// ------------------- User - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file User.cpp
  @date 03/11/2022
  @grade Software Robotics (Software Design)
*/
#include <libgen.h>
#include "../include/User.h"

// ----- Declarations ------
std::set<int*> User::allUsers;
char User::SEPARATOR = ',';
const std::string User::TAG = "User";
std::string User::EXECUTABLE_DIR;

//File for retrieving user info.
const std::string User::DATAFILE = "data/userdata.txt";
const std::string User::USERFILE = "../data/userdata.dat";

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------

// --- [Empty Constructor] User() ---
User::User() : id(INVALID_USER), isAdmin(false) {};


// --- [Constructor] User() ---
User::User(const int id) : id(id){

    if (id == DEVELOPER_USER ){
        this->pass = 0;
        this->isAdmin = true;
        return;
    }

    // ----- Initializing User info ------
    try {

        //  Find and Set admin status from data
        int* userData = find(id);
        this->pass = userData[PASS_COLUMN];
        this->isAdmin = userData[ADMIN_COLUMN];


    // ----- Catching invalid users ------
    }catch(InvalidUserException &e){

        this->id = INVALID_USER;
        this->isAdmin = 0;

    }
};



// --- [Getter] getUser() ---
int User::getUser(){
    return this->id;
}

// --- [Getter] getAdminStatus() ---
bool User::getAdminStatus(){
    return this->isAdmin;
}


// --- [Static] check() ---
bool User::check(const int id, const int pass){
    try{
        int* userData = find(id);
        return (userData[PASS_COLUMN] == pass);

    // User not found
    }catch(UserNotFoundException &e){
        return false;
    }
}
// --- [Static] updateUserData() ---
void User::updateUserData() {

    // ----- Declarations -----
    User user;

    // ----- Obtaining absolute_path -----
    std::string absolute_path = EXECUTABLE_DIR + "/" + USERFILE;

    // ---- Opening file ----
    std::ifstream file (absolute_path);

    // ---- Testing if file is correct ----
    if (!file)
        throw InvalidFileException(TAG);

    // ----- Reading every user in file -----
    while (file.read(reinterpret_cast <char *>(&user),sizeof (User))){

        int* newEntry = new int[TOTAL_COLUMNS];
        newEntry[USER_COLUMN] = user.id;
        newEntry[PASS_COLUMN] = user.pass;
        newEntry[ADMIN_COLUMN] = user.isAdmin;

        allUsers.insert(newEntry);
    }
    // ----- Closing file -----
    file.close();
}
/*
// --- [Static] updateUserData() ---
void User::updateUserData() {

    // ----- Declarations ------
    std::ifstream file(User::DATAFILE);
    std::string word;

    int line = 0; // Info for exception

    // ----- Reading File ------
    try {
        while (file.good()) {

            try {
                int *userdata = new int(TOTAL_COLUMNS);

                // Get user data delimited by commas
                for (int i = 0; i < TOTAL_COLUMNS - 1; i++) {

                    getline(file, word, SEPARATOR);
                    userdata[i] = std::stoi(word);
                }

                // Get last user element
                getline(file, word);
                userdata[TOTAL_COLUMNS - 1] = std::stoi(word);

                // Store user data
                allUsers.insert(userdata);
                line++;
            }catch (std::exception &e){
                std::cout << "\n[User] User in line " + std::to_string(line) + " is NOT valid,";
                std::cout << "\n[Info] Make sure there are no spaces or ENTER between or after the data.";
                throw InvalidUserException(TAG);
            }
        }

        // ----- Close file ------
        file.close();

        // ----- Sort Users ------
        // [DEPRECATED] std::sort(data.begin(), data.end());
    }catch (std::exception &e){
        std::cout << "\n[User] File located in " + DATAFILE + " is not valid as an User list.";
        throw InvalidFileException(TAG);
    }
}
*/

// ------------------------------------------------------
//                  PRIVATE FUNCTIONALITIES             |
// ------------------------------------------------------

// --- [Static] find()
// Usage: Find a user by giving the id as a key
// Maximum complexity of O(n)
// Note: Complexity of O(log(n)) is possible, not
// implemented yet.
int* User::find(int id){

    // ----- Creates iterator
    std::set<int*>::iterator it;

    // ----- Travel the set until find
    for (auto iterator = allUsers.begin(); iterator != allUsers.end(); ++iterator){

        if ((*iterator)[USER_COLUMN] == id)
            return *iterator;
    }

    // ----- User not found, send error

    // [DEPRECADTED] throw std::runtime_error("User not Found");
    throw UserNotFoundException(TAG);

}
// --- [Function] addUser()
void User::addUser(const int user, const int pass, const bool isAdmin) {

    int* newUser = new int[TOTAL_COLUMNS];
    newUser[USER_COLUMN] = user;
    newUser[PASS_COLUMN] = pass;
    newUser[ADMIN_COLUMN] = (isAdmin) ? ADMIN_IDENTIFIER : 0;

    allUsers.insert(newUser);

}

// --- [Function] rmUser()
void User::rmUser(const int id) {

    try {

        int *user = find(id);
        allUsers.erase(user);

    }catch(InvalidUserException &e){

        throw;

    };

}
// --- [Function] printUsers()
void User::printUsers() {

    for (auto iterator = allUsers.begin(); iterator != allUsers.end(); ++iterator){

            std::cout << ((*iterator)[ADMIN_COLUMN] == 0 ? "User: " : "Admin: ");
            std::cout << (*iterator)[USER_COLUMN] << std::endl;

    }

}

void User::saveUserData() {

    // ----- Obtaining absolute_path -----
    std::string absolute_path = EXECUTABLE_DIR + "/" + USERFILE;

    // ---- Opening file ----
    std::ofstream file (absolute_path);

    // ---- Testing if file is correct ----
    if (!file)
        throw InvalidFileException(TAG);

    // ----- Creates iterator -----
    std::set<int*>::iterator it;

    // ----- Saves all user data in allUsers to file  -----
    for (auto iterator = allUsers.begin(); iterator != allUsers.end(); ++iterator){

        User newUser = User((*iterator)[USER_COLUMN]);
        file.write(reinterpret_cast <const char *> (&newUser),sizeof (User));

    }

    // ----- Close the file -----
    file.close();

}

// --- [Static] find() [DEPRECATED] ---
// Usage: Finds a user from the data array using
// binary search. Throws a running_time exception
// if user doesn't exist.
// Note: This method can be used only with data
// contained into a double vector
/*
 std::vector<int> User::find(int id) {

    // ----- Declarations ------
    int begin = 0;
    int end = data.size() - 1;
    int mid;

    // ----- Searching ------
    while (begin < end){

        //  Fix for odd positions
        if (mid == (begin + end) / 2)
            begin++;

        //  Pointer to next analysis
        mid = (begin + end) / 2;

        //  Check if target is lower
        if (id < data[mid][USER_COLUMN])
            end = mid;

        //  Check if target is higher
        else if (id > data[mid][USER_COLUMN])
            begin = mid;

        //  Else, it is the target
        else
            return data[mid];
    };

    //  Throw exception if user is not found
    throw std::runtime_error("Not Valid User");
}
*/
