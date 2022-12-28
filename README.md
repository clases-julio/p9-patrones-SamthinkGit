# JVH-Systems v.1.0.0

<p align="center">
  <img src="https://user-images.githubusercontent.com/92941012/209694449-932b635f-21df-438e-841b-bf66b41eccc8.png" width="800"/>
</p>

Welcome to the **JVH Systems repository**! This repository contains the source code for a simulated company's device management program, written in C++. The program allows employees to easily and quickly view the status of all devices and control them, such as sending actions or skills or checking measurement data. It also provides a fully customizable interface that can be easily expanded to support new devices and functionality without the need for reprogramming.

The program is designed to be scalable and secure, with features such as protection against excessive errors and the ability to recover from issues with the users implemented in the program. It is targeted towards employees of the simulated company, but also includes features for programmers and developers, such as admin, root, and developer users.

In this repository, you will find the source code for the program, as well as documentation and resources to help you get started with using and contributing to the project. We hope you find the program useful and we look forward to your contributions!

## Installation.

To install the program, you will need to have **C++** and the **make** command installed on your system. The program is distributed as source code and can be compiled using the included makefile.

It relies on standard C++ libraries and has no other dependencies. It is also important to use the bash script called **linux_patch.sh** that if you are using this project in Linux OS.

To install the program, you can either use git clone to download the repository or download the zip file directly from GitHub. Once the code has been downloaded, navigate to the project directory and run make to compile the program. The object code will be saved in the **/obj** directory, while the executable will be saved in the0 **/build** directory.

```bash
# (Optional) Patch the project if you are using Linux
sh ./linux_patch.sh

# Compile all files
make

# You are ready to run!
./build/main.exe
```

For more detailed instructions and additional information, please see the Installation chapter in the Wiki:
https://github.com/clases-julio/p9-patrones-SamthinkGit/wiki/Installation

## Documentation

The program's documentation is generated using [Doxygen](https://www.doxygen.nl/), and can be found in the `/doc` directory of the repository. Doxygen is a documentation generator that extracts documentation comments from source code and generates comprehensive documentation in various formats, such as HTML and PDF.

To view the documentation in HTML format, open the `index.html` file located in `/doc/html` using a web browser. This file serves as the main entry point to the documentation, and provides an overview of the documentation as well as links to the various documentation pages. From here, you can navigate through the documentation by following the links to the different classes, functions, and other elements of the code.

To view the documentation in PDF format, open the `refman.pdf` file located in `/doc/latex` using a PDF viewer. This file contains the complete documentation in a single, printable file.

The documentation contains detailed information on the program's code and design, as well as instructions on how to use and contribute to the project. It includes descriptions of the various classes and functions, as well as explanations of how they fit into the overall structure of the program. It is an essential resource for understanding and working with the program, and we encourage you to consult it as needed.

For more information of the project and how to use it, please see the Documentation chapter in the Wiki:
https://github.com/clases-julio/p9-patrones-SamthinkGit/wiki/Developing-JVH

## General JVH Description

JVH System is a complex system based on C++ that allows the management and control of various devices. It is designed to be easily scalable and customizable, with a modular structure that allows for the easy integration of new devices and functionalities.

We can differentiate 5 main sections in the structure of JVH System: Devices, Building, Authentication, Interfaces and Graphical Library.

### Devices
In this section, we find the classes that represent the devices that can be connected to the system. There are two main types of devices: Data Devices and Kernel Devices. Data Devices are responsible for receiving data from the outside world, such as temperature or light sensors. Kernel Devices are responsible for controlling other variables, such as alarms, cameras or the program itself. Both types of devices are built using the DeviceBuilder class, which is responsible for creating the necessary connections with the rest of the system.

### Building
The Building section contains the classes responsible for the construction and management of the devices. The DeviceBuilder class is the main class in this section, and is responsible for creating the necessary connections between the devices and the rest of the system. It also includes some datasets such as DeviceDataset (which includes the devices that will be installed), or exampleSkillsDataset (which includes some example functionalities for the data devices) for settling the behavior of the devices implemented.

### Authentication
The Authentication section contains the classes responsible for the management of user authentication and authorization. The User class is responsible for storing and managing the user IDs and passwords, and the Login class is responsible for displaying the authentication interface and verifying the user credentials.

### Interfaces
The Interfaces section contains the classes responsible for the communication between the devices and the rest of the system. The Input/Output Device Interface (IODi) class is responsible for interpreting the status of the devices and sending the necessary information to the main class when it needs to interact with a device. The Automatic Interface (AI) class is responsible for interpreting global commands requested by the main class and checking the proper functioning of the devices. It is also implemented a class called DeviceComposite which allows to use multiple interfaces simultaneously.

### Graphical Library
Finally, the Graphical Library section contains the class responsible for displaying the interface on the screen. The SimpleDisplay class is responsible for displaying the main interface, and can be replaced by any other library with the same functionalities.

With this structure, JVH System is able to manage and control a wide variety of devices in a scalable and customizable way. Additional information on the specific functions and capabilities of each class can be found in the Doxygen documentation which includes documentation about every function or variable implemented in those classes.

## Design Pattern: Device Composite

The DeviceComposite class is based on the Composite design pattern, which is a structural design pattern that allows representing a group of objects as a single object.

One of the main motivations for choosing the Composite pattern in this project is the need to treat individual objects and compositions of objects uniformly. By implementing the DeviceComposite class, we can manipulate a single device or a group of devices in the same way, using the same set of methods. This simplifies the code and makes it more flexible, as we can add or remove devices from a composite without affecting the overall functionality of the program.

In addition, the Composite pattern promotes the creation of a tree-like structure, which is particularly useful in this project as it allows us to represent the hierarchical relationships between different devices. For example, a composite can contain a group of devices that are all connected to a main device, which in turn is connected to a larger composite containing multiple main devices.

Once the DeviceComposite is installed in JVH we can manage multiple devices like:
```c++
  // Instantiate composite
  DeviceComposite composite;
 
  // Show the status
  composite.show();
  
  // Add as much devices as we want
  composite.add("Thermometer");
  composite.add("RGB Camera");
  
  // Show the status
  composite.show();
  
  // Now you can use their skills simultaneusly
  composite.useSkill("reboot");
```
```bash
[ ]
[ Thermometer RGB_Camera ]

// Note that we control all simultaneously
[IODi] Thermometer rebooted
[IODi] RGB Camera rebooted
```
