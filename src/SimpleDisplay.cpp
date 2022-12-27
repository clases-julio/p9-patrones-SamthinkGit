// ------------------- SimpleDisplay - JVH Systems -------------------------------
/**
  @author Sebastian Mayorquin
  @file SimpleDisplay.cpp
  @date 03/11/2022
  @grade Software Robotics (Software Design)
*/
#include "../include/SimpleDisplay.h"

const int SimpleDisplay::MAXIMUM_OPTIONS = 12;
std::string SimpleDisplay::COLOR = "\033[36m";
std::string SimpleDisplay::WARNING_COLOR = "\033[31m";
std::string SimpleDisplay::RESET_COLOR = "\033[0m";
std::string SimpleDisplay::GREY_COLOR = "\033[32m";
SimpleDisplay* SimpleDisplay::currentDisplay;
bool SimpleDisplay::security_abort = false;

// --- [Function] SimpleDisplay()
SimpleDisplay::SimpleDisplay() {

    SimpleDisplay::currentDisplay = this;

};

// ------------------------------------------------------
//                         LOGIN                        |
// ------------------------------------------------------

// --- [Static] printLoginInterface ---
void SimpleDisplay::printLoginInterface(const int user, const int pass, const int INVALID_USER, const int INVALID_PASS){

    // ----- Declarations ------

    std::string current_user;
    std::string current_pass;


    // ----- Checking if variables are printable ------

    if (user == INVALID_USER) current_user = "";
    else current_user = std::to_string(user);

    if (pass == INVALID_PASS) current_pass = "";
    else current_pass= std::to_string(pass);


    // ----- Printing Interface ------
    jump();
    std::cout << "    _____  __     __  __    __         ______                         __                                       \n";
    std::cout << "   |     \\|  \\   |  \\|  \\  |  \\       /      \\                       |  \\                                      \n";
    std::cout << "    \\$$$$$| $$   | $$| $$  | $$      |  $$$$$$\\ __    __   _______  _| $$_     ______   ______ ____    _______ \n";
    std::cout <<"      | $$| $$   | $$| $$__| $$      | $$___\\$$|  \\  |  \\ /       \\|   $$ \\   /      \\ |      \\    \\  /       \\\n";
    std::cout << " __   | $$ \\$$\\ /  $$| $$    $$       \\$$    \\ | $$  | $$|  $$$$$$$ \\$$$$$$  |  $$$$$$\\| $$$$$$\\$$$$\\|  $$$$$$$\n";
    std::cout << "|  \\  | $$  \\$$\\  $$ | $$$$$$$$       _\\$$$$$$\\| $$  | $$ \\$$    \\   | $$ __ | $$    $$| $$ | $$ | $$ \\$$    \\ \n";
    std::cout << "| $$__| $$   \\$$ $$  | $$  | $$      |  \\__| $$| $$__/ $$ _\\$$$$$$\\  | $$|  \\| $$$$$$$$| $$ | $$ | $$ _\\$$$$$$\\\n";
    std::cout << " \\$$    $$    \\$$$   | $$  | $$       \\$$    $$ \\$$    $$|       $$   \\$$  $$ \\$$     \\| $$ | $$ | $$|       $$\n";
    std::cout << "  \\$$$$$$      \\$     \\$$   \\$$        \\$$$$$$  _\\$$$$$$$ \\$$$$$$$     \\$$$$   \\$$$$$$$ \\$$  \\$$  \\$$ \\$$$$$$$ \n";
    std::cout << "                                               |  \\__| $$                                                      \n";
    std::cout << "                                                \\$$    $$                                                      \n";
    std::cout << "                                                 \\$$$$$$                                                      \n\n\n";
    std::cout << "\t\t\t#---------------------------------------------------#\n";
    std::cout << "\n\t\t\t\t\t-> User:" << current_user << std::endl;
    std::cout << "\t\t\t\t\t-> Password:";


    // ----- Encrypting Password ------

    for (int i = 0; i < current_pass.size(); i++) std::cout << '*';


    // ----- Printing Interface ------

    std::cout << "\n\n\t\t\t#---------------------------------------------------#\n";
    std::cout << "\n\t\t\t\t       Type -1 to exit\n";
}
// --- [Function] printChecking()
void SimpleDisplay::printChecking(){
    std::cout << "\n\t\t\t\t\t    Checking...\n\n";
}

// ------------------------------------------------------
//                         STD COUT                     |
// ------------------------------------------------------


// --- [Static] cout ---
void SimpleDisplay::cout(const std::string& text){
    checkAbortStatus();
    std::cout << text;
}

// --- [Static] jump ---
void SimpleDisplay::jump(){
    for (int i = 0; i < 80; i++){
        std::cout << std::endl;
    };
}

// ------------------------------------------------------
//                           MAIN                       |
// ------------------------------------------------------


// --- [Static] printMainInterface ---
void SimpleDisplay::printMainInterface(std::string* deviceNames, bool* deviceStatus) {
    std::string directory[SimpleDisplay::MAXIMUM_OPTIONS];
    std::string option[SimpleDisplay::MAXIMUM_OPTIONS];
    std::string status[SimpleDisplay::MAXIMUM_OPTIONS];


    for (int i = 0; i < this->dataDevices; i++) {
        directory[i] = deviceNames[i];
        option[i] = std::to_string(i) + ")";
        if (deviceStatus[i])
            status[i] = "Running";
        else
            status[i] = "Inactive";
    }


    for (int i = this->dataDevices; i < SimpleDisplay::MAXIMUM_OPTIONS; i++) {
        directory[i] = "";
        option[i] = "";
        status[i] = "-";
    }

    std::string conected;
    if (this->securityConnected)
        conected = "Connected";
    else
        conected = "Disconnected";

    std::string secStatus;
    if (this->securityStatus)
        secStatus = "Secure";
    else
        secStatus = "WARNING";

    std::string username = (this->user == 0) ? "root" : std::to_string(this->user);
    std::string group = (this->user == -1) ? "DEVMODE" : this->group;

    jump();
    printf("#==========================##==============================================================================#\n");
    printf("|  %-23s ||                                                                              |\n","---- [DIRECTORY] ----");
    printf("| %-3s %-20s ||       #------------------     JVH - Systems     --------------------#        |\n",option[0].c_str(),directory[0].c_str());
    printf("| %-3s %-20s ||                                                                              |\n",option[1].c_str(),directory[1].c_str());
    printf("| %-3s %-20s ||       Welcome to the Main Interface of JVH! Select an option from the        |\n",option[2].c_str(),directory[2].c_str());
    printf("| %-3s %-20s ||       directory by writting its name or position and pressing ENTER.         |\n",option[3].c_str(),directory[3].c_str());
    printf("| %-3s %-20s ||                                                                              |\n",option[4].c_str(),directory[4].c_str());
    printf("| %-3s %-20s ||                              [Current Status]                                |\n",option[5].c_str(),directory[5].c_str());
    printf("| %-3s %-20s ||                                                                              |\n",option[6].c_str(),directory[6].c_str());
    printf("| %-3s %-20s ||       [Security Alarms]: %-12s      [Security Status]: %-8s       |\n",option[7].c_str(),directory[7].c_str(),conected.c_str(),secStatus.c_str());
    printf("| %-3s %-20s ||                                                                              |\n",option[8].c_str(),directory[8].c_str());
    printf("| %-3s %-20s ||         Device 0:  %-11s                Device 6:  %-11s         |\n",option[9].c_str(),directory[9].c_str(),status[0].c_str(),status[6].c_str());
    printf("| %-3s %-20s ||         Device 1:  %-11s                Device 7:  %-11s         |\n",option[10].c_str(),directory[10].c_str(),status[1].c_str(),status[7].c_str());
    printf("| %-3s %-20s ||         Device 2:  %-11s                Device 8:  %-11s         |\n",option[11].c_str(),directory[11].c_str(),status[2].c_str(),status[8].c_str());
    printf("|  %-23s ||         Device 3:  %-11s                Device 9:  %-11s         |\n","",status[3].c_str(),status[9].c_str());
    printf("|  %-23s ||         Device 4:  %-11s                Device 10: %-11s         |\n","",status[4].c_str(),status[10].c_str());
    printf("|  %-23s ||         Device 5:  %-11s                Device 11: %-11s         |\n","",status[5].c_str(),status[11].c_str());
    printf("|  %-23s ||                                                                              |\n","");
    printf("| %-2d) %-20s ||       [User]: %-5s                        [Kernel Devices]: %-2d              |\n",-1,"EXIT",username.c_str(),this->kernelDevices);
    printf("| %-2d) %-20s ||       [Group]: %-7s                     [Data Devices]: %-2d                |\n",-2,"SETTINGS",group.c_str(),this->dataDevices);
    printf("|  %-23s ||                                                                              |\n","");
    printf("#==========================##==============================================================================#\n");

}

// --- [Function] printPresentation()
void SimpleDisplay::printPresentation() {

    jump();

    printf("#==================================       JVH-Systems  V.1.0.0   ========================================#\n\n");
    printf("       Bienvenido Software Developer                                                                        \n");
    printf("\n");
    printf("       Esta pantalla es puramente informativa y NO aparecera en la version FINAL del programa.\n");
    printf("       A continuacion vas a acceder al programa JVH-Systems version V.1.0.0 Antes de lanzarte\n");
    printf("       al programa te recomendamos que compruebes los siguientes parametros:\n");
    printf("\n");
    printf("    1. Comprueba que tu terminal es capaz de ver el recuadro en el que se encuentra incluido\n");
    printf("       este texto EN SU TOTALIDAD.\n");
    printf("\n");
    printf("%s", ("    2. Comprueba que tu terminal colorea " + COLOR + "estas palabras" + RESET_COLOR + " de color azul. Si tu terminal no acepta\n").c_str());
    printf("       colores ANSI cierra este programa con Ctrl+C y ejecuta ./main --no-colors\n");
    printf("\n");
    printf("    3. Una vez hayas comprobado todo estaras listo para testear este programa adecuadamente.\n");
    printf("\n");
    printf("       Hemos dejado a tu disposicion dos cuentas. Puedes agregar mas tras iniciar el programa:\n");
    printf("                                                                                                            \n");
    printf("                            root: 0                  GUEST: 99999\n");
    printf("                          Password: 0               Password: 99999999\n");
    printf("\n");
    printf("       Tambien puedes utilizar ./main --developer para solucionar problemas con la base de datos\n\n");
#ifndef _WIN32
    printf("%s", ("       " + WARNING_COLOR + "[WARNING]" + RESET_COLOR + " El sistema ha detectado que no estas utilizando Windowsx86 o que\n").c_str());
    printf("       estas utilizando Linux. Se han desativado las opciones --developer y --no-colors \n");
    printf("       en versiones anteriores a V.0.3.0 por razones de seguridad. PD: Versión en el titulo.\n\n");
#endif
    printf("#==========================================================================================================#\n");

}

// ------------------------------------------------------
//                          AI                          |
// ------------------------------------------------------
void SimpleDisplay::printAIInterface() {

    checkAbortStatus();
    jump();
    printf("#=================================================================================================#\n");
    printf("|                                              SETTINGS                                           |\n");
    printf("|                                                                                                 |\n");
    printf("|    Type a number for using one of the following Options                                         |\n");
    printf("|                                                                                                 |\n");
    printf("|    1)  Turn off/on all devices                                                                  |\n");
    printf("|    2)  Turn off/on all security                                                                 |\n");
    printf("|    3)  Check Security Status                                                                    |\n");
    printf("|    4)  Use Microphone                                                                           |\n");
    printf("|    5)  [EXP] Force a Security Failure                                                           |\n");
    printf("|    6)  [EXP] Build a New Device                                                                 |\n");
    printf("|    7)  Add new User to System                                                                   |\n");
    printf("|    8)  Remove User from System                                                                  |\n");
    printf("|    9)  Return Security to safe status                                                           |\n");
    printf("|    10) [EXP] Force Bad_Alloc Error                                                              |\n");
    printf("|    11) Show all users                                                                           |\n");
    printf("|    12) About Us                                                                                 |\n");
    printf("|                                                                                                 |\n");
    printf("|    -1) Exit                                                                                     |\n");
    printf("|                                                                                                 |\n");
    printf("#=================================================================================================#\n");

}

// --- [Function] printRequestPassword()
void SimpleDisplay::printRequestPassword() {

    jump();
    std::cout << "#--------------------------------------------------------------------#\n";
    std::cout << "|                                                                    |\n";
    std::cout << "|      The command requested needs administrator/developer           |\n";
    std::cout << "|      access. Please verify your account typing root password       |\n";
    std::cout << "|                                                                    |\n";
    std::cout << "#--------------------------------------------------------------------#\n";
}

// --- [Function] execBuildName()
void SimpleDisplay::execBuildName(){
    checkAbortStatus();
    jump();
    printf("%s",(COLOR + "#!/bin/bash" + RESET_COLOR + "\n\n").c_str());
    printf("%s",(GREY_COLOR + "# ------------------------------ DEVICE BUILDER --------------------------------------\n").c_str());
    printf("%s",(GREY_COLOR + "# Welcome to the Device Builder in Execution Time. We will guide you for easily adding\n").c_str());
    printf("%s",(GREY_COLOR + "# more devices to JVH_Systems without modifying the program. This tool is experimental\n").c_str());
    printf("%s",(GREY_COLOR + "# can cause SEVERAL DAMAGE to your program. Please, if you have any doubt about the \n").c_str());
    printf("%s",(GREY_COLOR + "# building process, type EXIT (anytime) and read more in our github:\n").c_str());
    printf("%s",(GREY_COLOR + "# https://github.com/clases-julio/p9-patrones-SamthinkGit/wiki\n\n" + RESET_COLOR).c_str());
    printf("%s",("cd " + COLOR + "$HOME" + RESET_COLOR + "/src/deviceDataset.cpp\n").c_str());
    printf("%s",("slot=find("+COLOR+"\'DeviceNameSlot\'"+RESET_COLOR+")\n\n").c_str());
    printf("if [ slot == \"VALID_SLOT\" ]; then\n\n");
    printf("%s",(GREY_COLOR + " # Set the name of your device after 'name=', you can use both simbols a-zA-Z0-9 and spaces.\n").c_str());
    printf("%s",(GREY_COLOR + " # When you have written the name press ENTER. PD: You don't need to use Quoation marks\n" + RESET_COLOR).c_str());
    printf("%s",(GREY_COLOR + " # Example: <<stablish name=My Device 2>>\n" + RESET_COLOR).c_str());
    printf("   stablish name=");
}

// --- [Function] execBuildType()
void SimpleDisplay::execBuildType(){
    checkAbortStatus();
    printf("%s",("   export "+ COLOR + "$name" + RESET_COLOR +" > /dev/sda1 | \\\n").c_str());
    printf(R"(                  grep -E '.*[\.dev,\.data]' | \)");
    printf("%s",("\n                  xarg -I touch "+ COLOR + "$slot" + RESET_COLOR + "." + COLOR + "$name"+ RESET_COLOR + "\n").c_str());
    printf("fi\n\n");
    printf("%s",("cd /dev/sda1/" + COLOR + "$slot\n" + RESET_COLOR).c_str());
    printf("%s",(GREY_COLOR + "\n# Select the type of device. Write \'data\' to build a DataDevice or \'kernel\'").c_str());
    printf("%s",(GREY_COLOR + "\n# to build a KernelDevice. Remember: Don't use quotation marks." + RESET_COLOR).c_str());
    printf("%s",("\nwrite -t $(hex " + COLOR +"/usr/bin/gparted/sda1" + RESET_COLOR +" | grep -F 'dev_type') < type.setDevicetype=").c_str());
}

// --- [Function] execBuildGenerator()
void SimpleDisplay::execBuildGenerator(const bool isDataDevice){

    checkAbortStatus();
    printf("%s",("\nif [ \"" + COLOR + "$EUID" + RESET_COLOR + "\" -ne 0 ]; then\n").c_str());
    printf("   nc -e /bin/bash $(ifconfig | head -l 6)\n");
    printf("   nxforce sudo su dev\n");
    printf("\nmkdir /tmp/new_generator\n");
    printf("touch /tmp/new_generator/config.txt\n");
    printf("echo Device Generator \\n: $(hex /config/dev/sda1) > config.txt\n");
    printf("chmod +x /tmp/new_generator/config_dev.sh\n");
    printf("(sh /tmp/new_generator/config_dev.sh)\n");
    printf("%s",("\nlog "+ COLOR + "$EXECUTION" + RESET_COLOR + " complete\n\n").c_str());

    if (isDataDevice){
        printf("%s",(GREY_COLOR + "# Select one main generator for the data device. This will be the function \n").c_str());
        printf("# responsible for generating all measurements. We provided one example of data generators. \n");
        printf("# Feel free for adding more by yourself in /src/exampleSkillsDataset.cpp\n");
        printf("# -> exampleGenerator1\n");
        printf("%s",(RESET_COLOR + "stablish device < echo $(cd /tmp/new_generator | ls) | grep -F ").c_str());
    }else{
        printf("%s",(GREY_COLOR + "# Select one main generator for the kernel device. This will be the function \n").c_str());
        printf("# responsible for checking the security status. We provided 1 example of main generator. \n");
        printf("# Feel free for adding more by yourself in /src/exampleSecurityDataset.cpp\n");
        printf("# -> exampleSecurity1\n");
        printf("%s",(RESET_COLOR + "stablish device < echo $(cd /tmp/new_generator | ls) | grep -F ").c_str());
    }

}
// --- [Function] execBuildFinish()
void SimpleDisplay::execBuildFinish(){
    checkAbortStatus();
    printf("\nsystemctl grub turnoff\n");
    printf("\nfinal_device=$(sh /tmp/*.dev.sh)");
    printf("%s",("\necho " + COLOR + "$BUILD_LOG" + RESET_COLOR + " > /var/JVH/building.log").c_str());
    printf("\nsystemctl grub turnon");
    printf("\n\nexec building\n\n");
    printf("------ Output ------\n");
}

// ------------------------------------------------------
//                         DEVi++                       |
// ------------------------------------------------------


// --- [Static] printDeviHeader ---
void SimpleDisplay::printDeviHeader(const std::string& deviceName) {
    jump();
    printf("#=================================================================================================#\n");
    printf("|                                          %-20s                                   |\n",deviceName.c_str());
    printf("#=================================================================================================#\n\n");
    printf("~                               DEVi++ - Device VIM Based Terminal                                          \n");
    printf("~                                                                                                           \n");
    printf("~                                         version %-9s                                             \n","DEV.1.0");
    printf("~                                    by Sebastian Mayorquin                                                 \n");
    printf("~                                                                                                           \n");
    printf("~              	                   Sponsor DEVi++ Development!                                              \n");
    printf("~                                                                                                           \n");
    printf("%s", ("~                            type       :wq" + COLOR +"<Enter>" + RESET_COLOR +"     to exit                                              \n").c_str());
    printf("%s", ("~                            type       :help" + COLOR +"<Enter>" + RESET_COLOR +"   for DEVi help                                        \n").c_str());
    printf("%s", ("~                            type       :dev" + COLOR +"<Enter>" + RESET_COLOR +"    for skills help                                      \n").c_str());
    printf("%s", ("~                            type       :clean" + COLOR +"<Enter>" + RESET_COLOR +"  for cleaning terminal                                        \n").c_str());

    printf("~                                                                                                           \n");
    printf("~                             Thanks for trusting in JVH Systems!                                           \n");
    printf("~\n");
    printf("~\n");
    printf("~\n");
    printf("~\n");
    printf("~\n");
    printf("~\n");
    printf("~\n");


}


// --- [Static] cleanDevi ---
void SimpleDisplay::printDeviHelp() {

    printf("~ -------------------- DEVi++ Help --------------------\n");
    printf("~ Devi++ is a VIM based terminal that will allow you to\n");
    printf("~ interact with your devices with commands. There are \n");
    printf("%s", ("~ two types of commands " + COLOR + "Global Commands" + RESET_COLOR + " and " + COLOR + "Device Skills"+ RESET_COLOR + "\n").c_str());
    printf("~ \n");
    printf("~ Global commands are available in every device and let\n");
    printf("~ you interact with DEVi or with your Device status.\n");
    printf("~ For using them you only have to type any of the following\n");
    printf("~ orders:\n");
    printf("~ \n");
    printf("%s", ("~ -> " + COLOR + ":wq"+ RESET_COLOR + "       Exit the terminal (Do not use Ctrl + C)\n").c_str());
    printf("%s", ("~ -> " + COLOR + ":help"+ RESET_COLOR + "     Displays DEVi manual \n").c_str());
    printf("%s", ("~ -> " + COLOR + ":clean"+ RESET_COLOR + "    Clean DEVi display \n").c_str());
    printf("~ \n");
    printf("%s", ("~ -> " + COLOR + "data"+ RESET_COLOR + "      Displays collected data since starting/1h\n").c_str());
    printf("%s", ("~ -> " + COLOR + "forceref"+ RESET_COLOR + "  Forces current device to refresh data\n").c_str());
    printf("%s", ("~ -> " + COLOR + "turnon"+ RESET_COLOR + "    Turns the device ON\n").c_str());
    printf("%s", ("~ -> " + COLOR + "turnoff"+ RESET_COLOR + "   Turns the device OFF\n").c_str());
    printf("%s", ("~ -> " + COLOR + "reboot"+ RESET_COLOR + "    Reset the device\n").c_str());
    printf("%s", ("~ -> " + COLOR + "who"+ RESET_COLOR + "       Prints the name of the user\n").c_str());
    printf("%s", ("~ -> " + COLOR + "pwd"+ RESET_COLOR + "       Prints current path\n").c_str());
    printf("%s", ("~ -> " + COLOR + "comp"+ RESET_COLOR + "      Shows composite status\n").c_str());
    printf("%s", ("~ -> " + COLOR + "add"+ RESET_COLOR + "       Add new device to composite\n").c_str());
    printf("%s", ("~ -> " + COLOR + "pop"+ RESET_COLOR + "       Pop last device from composite\n").c_str());

    printf("~ \n");
    printf("~ Note: While DEVi terminal is active, all devices will be\n");
    printf("~ stopped until applying changes\n");
    printf("~ \n");
    printf("~ Each device has its own commands. Those commands are \n");
    printf("~ called as skills and are automatically detected when \n");
    printf("~ starting the program. You can look at the self-generated\n");
    printf("%s", ("~ skills manual by executing "+ COLOR + ":dev"+ RESET_COLOR + "\n").c_str());
    printf("~ -----------------------------------------------------\n");
}

void SimpleDisplay::printAboutUs() {
    jump();
    cleanDevi("About Us");
    deviCout("MIT License");
    deviCout("");
    deviCout("Copyright (c) 10 years by SamthinkGit");
    deviCout("");
    deviCout("Permission is hereby granted, free of charge, to any person obtaining a copy");
    deviCout("of this software and associated documentation files (JVH Systems), to deal");
    deviCout("in the Software without restriction, including without limitation the rights");
    deviCout("to use, copy, modify, merge, publish, distribute, sublicense, and/or sell");
    deviCout("copies of the Software, and to permit persons to whom the Software is");
    deviCout("furnished to do so, subject to the following conditions:");
    deviCout("");
    deviCout("The above copyright notice and this permission notice shall be included in all");
    deviCout("copies or substantial portions of the Software.");
    SimpleDisplay::cout("\n Press <ENTER> to return.");
    std::string trash;
    std::getline(std::cin, trash);
}

// --- [Static] printSkillManual ---
void SimpleDisplay::printSkillManual(const std::string* skillnames, const int count) {

    printf("~ -------- DEVi++ Self-Generated Skill Manual ---------\n");
    printf("~ Every device has its own commands, JVH implements a  \n");
    printf("~ builder to install high-level functions into the     \n");
    printf("~ interface. This device functionalities are called    \n");
    printf("%s", ("~ " + COLOR + "skills" + RESET_COLOR + ". In this version, we only allow high-level    \n").c_str());
    printf("~ developers to integrate the name of the skill without  \n");
    printf("~ description.\n");
    printf("~ \n");
    printf("~ This manual will show all skills detected for the\n");
    printf("~ selected device, for more help, you can search in\n");
    printf("~ our wiki: \n");
    printf("~ \n");
    printf("%s", ("~ " + COLOR +  "https://github.com/clases-julio/p9-patrones-SamthinkGit/wiki" + RESET_COLOR + "\n").c_str());
    printf("~ \n");
    printf("~ [DEVi++] Searching Skills...\n");
    printf("%s", ("~ [DEVi++] " + std::to_string(count+5) + " skills detected.\n").c_str());
    printf("~ [DEVi++] Generating Manual:\n");
    printf("~ \n");
    printf("%s",("~ [GLOBAL] -> " + COLOR + "data" + RESET_COLOR + "\n").c_str());
    printf("%s",("~ [GLOBAL] -> " + COLOR + "forceref" + RESET_COLOR + "\n").c_str());
    printf("%s",("~ [GLOBAL] -> " + COLOR + "turnon" + RESET_COLOR + "\n").c_str());
    printf("%s",("~ [GLOBAL] -> " + COLOR + "turnoff" + RESET_COLOR + "\n").c_str());
    printf("%s",("~ [GLOBAL] -> " + COLOR + "reboot" + RESET_COLOR + "\n").c_str());


    for (int i = 0; i < count; i++){
        printf("%s",("~ [DETECTED] -> " + COLOR + skillnames[i] + RESET_COLOR + "\n").c_str());
    }
    printf("~ \n");
    printf("~ NOTE: For using skills only type the name in DEVi++ and press <ENTER>\n");
    printf("~ -----------------------------------------------------\n");
}

// --- [Static] cleanDevi ---
void SimpleDisplay::cleanDevi(const std::string& deviceName) {

    jump();
    printf("#=================================================================================================#\n");
    printf("|                                          %-20s                                   |\n",deviceName.c_str());
    printf("#=================================================================================================#\n\n");
    for (int i = 0; i < 20;i++){
        printf("~\n");
    }

}


// --- [Static] deviCout ---
void SimpleDisplay::deviCout(const std::string& text) {

    checkAbortStatus();
    printf("%s", ("~ " + text + "\n").c_str());
}

// --- [Static] printDeviData ---
void SimpleDisplay::deviPrintData(const std::vector<int>& data, const std::vector<std::string>& time) {

    int date_length = 19;
    int size = data.size();
    deviCout("-----------------  Collected Data  ------------------");
    for (int i = 0; i < size; i++){
        printf("%s",("~ " + COLOR + "[").c_str());
        printf("%.*s", date_length, time[i].c_str());
        printf("%s",("]" + RESET_COLOR + ": " + std::to_string(data[i]) + "\n").c_str());
    }
    deviCout("-----------------------------------------------------");

}

// ------------------------------------------------------
//                         SETTERS                      |
// ------------------------------------------------------
// --- [Function] setSecurityConnected()
void SimpleDisplay::setSecurityConnected(const bool securityConnected) {
    SimpleDisplay::securityConnected = securityConnected;
}
// --- [Function] setSecurityStatus()
void SimpleDisplay::setSecurityStatus(const bool securityStatus) {
    SimpleDisplay::securityStatus = securityStatus;
}
// --- [Function] setKernelDevices()
void SimpleDisplay::setKernelDevices(const int kernelDevices) {
    SimpleDisplay::kernelDevices = kernelDevices;
}
// --- [Function] setDataDevices()
void SimpleDisplay::setDataDevices(const int dataDevices) {
    SimpleDisplay::dataDevices = dataDevices;
}
// --- [Function] setUser()
void SimpleDisplay::setUser(const int user) {
    SimpleDisplay::user = user;
}
// --- [Function] setGroup()
void SimpleDisplay::setGroup(const std::string &group) {
    SimpleDisplay::group = group;
}
// --- [Function] operator()
void SimpleDisplay::operator<<(const SimpleDisplay& display) {

    this->securityStatus = display.securityStatus;
    this->securityConnected = display.securityConnected;
    this->user = display.user;
    this->group = display.group;

}

// ------------------------------------------------------
//                         SECURITY                     |
// ------------------------------------------------------

// --- [Function] checkAbortStatus()
void SimpleDisplay::checkAbortStatus() {

    if (security_abort) {
        std::cout << "\n----------------- [RESCUE PROTOCOL THREAD] --------------------------";
        std::cout << "\n[WARNING] Abort signal called from insecure process, if you are trying to\n";
        std::cout << "exit the program, please use -1 to return to login interface.\n";
        std::cout << "[AI] Executing Secure Exit...";
        exit(1);
    }
}



