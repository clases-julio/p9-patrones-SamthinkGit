#ifndef DEVICE_DATASET
#define DEVICE_DATASET
#include "../include/DeviceBuilder.h"
#include "exampleSkillsDataset.cpp"
#include "exampleSecurityDataset.cpp"

class deviceDataset {
public:

    static void initDataset(){

        // ----- Building All Devices ------
        std::cout << "[BUILDER] Calling Default builders..." << std::endl;
        DeviceBuilder* thermometer = new DeviceBuilder("Thermometer");
        DeviceBuilder* humiditySensor = new DeviceBuilder("Humidity Sensor");
        DeviceBuilder* airSensor = new DeviceBuilder("Air Sensor");
        DeviceBuilder* lightSensor = new DeviceBuilder("Light Sensor");
        DeviceBuilder* rgbCamera = new DeviceBuilder("RGB Camera");
        DeviceBuilder* thermalCamera = new DeviceBuilder("Thermal Camera");

        DeviceBuilder* securityCamera1 = new DeviceBuilder("Security Camera 1");
        DeviceBuilder* securityCamera2 = new DeviceBuilder("Security Camera 2");
        DeviceBuilder* laserDetector = new DeviceBuilder("Laser Detector");

        // ----- Building Device Skills ------
        std::cout << "[BUILDER] Building skills" << std::endl;

        // ----- Building Main Data Generator ------
        (*thermometer).setDataGenerator(generateRandomData);
        (*humiditySensor).setDataGenerator(generateRandomData);
        (*airSensor).setDataGenerator(generateRandomData);
        (*lightSensor).setDataGenerator(generateRandomData);
        (*rgbCamera).setDataGenerator(generateRandomData);
        (*thermalCamera).setDataGenerator(generateRandomData);

        (*securityCamera1).setSecurityGenerator(exampleTest);
        (*securityCamera2).setSecurityGenerator(exampleTest);
        (*laserDetector).setSecurityGenerator(exampleTest);

        // ----- Building Skills (Only for DataDevices) -----
        (*thermometer).setSkill(exampleSkill1, "calculate");
        (*thermometer).setSkill(exampleSkill2, "set celsius");

        (*humiditySensor).setSkill(exampleSkill3,"hum decrease");
        (*humiditySensor).setSkill(exampleSkill4,"hum increase");

        (*airSensor).setSkill(exampleSkill3,"air type --british");

        (*lightSensor).setSkill(exampleSkill4,"setmode blind");
        (*lightSensor).setSkill(exampleSkill4,"setmode colorful");
        (*lightSensor).setSkill(exampleSkill4,"setmode hacker");

        (*rgbCamera).setSkill(exampleSkill3,"print camera");
        (*rgbCamera).setSkill(exampleSkill4,"lookfor --myself");

        (*thermalCamera).setSkill(exampleSkill3,"tcconfig up");
        (*thermalCamera).setSkill(exampleSkill4,"tcconfig down");

        // ----- Building Device Limits (optional) ------
        std::cout << "[BUILDER] Building limits" << std::endl;

    //    int lim[3] = {1, 2, 3};
    //    (*test).setLimit(lim);

        // ----- Setting Device Types [Data/Kernel]
        std::cout << "[BUILDER] Settling Types" << std::endl;
        (*thermometer).setAsDataDevice();
        (*humiditySensor).setAsDataDevice();
        (*airSensor).setAsDataDevice();
        (*lightSensor).setAsDataDevice();
        (*rgbCamera).setAsDataDevice();
        (*thermalCamera).setAsDataDevice();

        (*securityCamera1).setAsKernelDevice();
        (*securityCamera2).setAsKernelDevice();
        (*laserDetector).setAsKernelDevice();
    }
};

#endif