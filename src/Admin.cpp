#include "../headers/Admin.h"

// ------------------------------------------------------
//                  PUBLIC FUNCTIONALITIES              |
// ------------------------------------------------------

// --- [Constructor] Admin() ---
Admin::Admin(int id) : User(id){

    this->isAdmin = true;

}

// --- [Static] adminStatus() ---
bool Admin::adminStatus(int id) {

    try{
        int* userData = find(id);
        return (userData[ADMIN_COLUMN] == ADMIN_IDENTIFIER);

    // User not found
    }catch(UserNotFoundException &e){
        return false;
    }
}