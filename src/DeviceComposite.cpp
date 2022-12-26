#include "../headers/DeviceComposite.h"
// ----- Declarations -----
std::string CALL_KEYWORD = "add";

DeviceComposite::DeviceComposite() {}

// --- [Method] add
void DeviceComposite::add(std::string &name) {

    // -----  Intantiating new IODi -----
    IODi iodi;

    // -----  Adding device to IODi -----
    try{
        iodi.setCurrentDevice(name);
    }catch(InvalidDeviceException &e){
        throw;
        return;
    }

    // -----  Saving IODi -----
    this->allIODis.push_back(iodi);
}
void DeviceComposite::pop() {
    this->allIODis.pop_back();
}

// --- [Method] requestSkill
void DeviceComposite::requestSkill(std::string skill) {

    // -----  Check if skill is a keyword to add to composite -----
    if (skill == ::CALL_KEYWORD){

        std::string answer;
        SimpleDisplay::deviCout("Device Name: ");
        std::getline(std::cin,answer);
        try{
            this->add(answer);
            return;
        }catch(InvalidDeviceException &e){
            SimpleDisplay::deviCout("Invalid Device");
            return;
        }
    }

    // -----  Else the keyword is for IODIs -----
    for (int i = 0; i < this->allIODis.size(); i++)
        this->allIODis[i].requestSkill(skill);
}

// --- [Method] clear
void DeviceComposite::clear() {

    this->allIODis.clear();

}

std::string DeviceComposite::toString() {

    // -----  Declarations -----
    std::string stringBuilder = "[ ";

    for (int i = 0; i < this->allIODis.size(); i++){

        // -----  Replacing name spaces with underscores. -----
        std::string name = allIODis[i].requestCurrentDeviceName();
        std::replace(name.begin(), name.end(), ' ', '_');

        // -----  Appending name -----
        stringBuilder += name + " ";
    }

    // -----  Finishing string -----
    stringBuilder += "]";
    return stringBuilder;
}
