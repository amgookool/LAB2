## Part 1
Application Specific Vs Port Specific

### Identification of sdkconfig file

The sdkconfig file is an application specific configuration file that is included in each new project. This file specify the settings for communicating and flashing the ESP8266-01 device. For instance, changes in the CONFIG_ESPTOOL_PORT can negatively affect flashing and serial monitering capability if the wrong COM port is specified in its configuration.

### Identification of sdkconfig.h file
The sdkconfig.h file is the file generated from the build process of the project. It creates a header file containing the settings specified in the sdkconfig file. Changes in this file will have the same affect as changes in the sdkconfig file. 

### Identification of FreeRTOSConfig.h

The FreeRTOSConfig.h file specifies the defaults for the FreeRTOS kernel. This file governs which RTOS functions and features can be accessed in our project applications. Changes in this file can enable/disable FreeRTOS kernel specific functions and features.  

## Part 2



## Github Usage

I considered that labratory exercise as the repository itself. I determined that there are four parts to this excercise which are:

1. P1 and P2
1. Excercise/Question 1
1. Excercise/Question 2
1. Excercise/Question 3

Each part is structured as a branch on the github repository. Hence to change between the different parts of the lab excercise, the switching of the appropiate branch is required.
The branches of the repository are shown in the image below:

[![github-branch-screenshot.png](https://i.postimg.cc/Kjr7w9wv/github-branch-screenshot.png)](https://postimg.cc/K3jgg5md)

