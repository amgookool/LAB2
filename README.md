## Part 1
Application Specific Vs Port Specific

### Identification of sdkconfig file

The sdkconfig file is an application specific configuration file that is included in each new project. This file specify the settings for communicating and flashing the ESP8266-01 device. For instance, changes in the CONFIG_ESPTOOL_PORT can negatively affect flashing and serial monitering capability if the wrong COM port is specified in its configuration.

### Identification of sdkconfig.h file
The sdkconfig.h file is the file generated from the build process of the project. It creates a header file containing the settings specified in the sdkconfig file. Changes in this file will have the same affect as changes in the sdkconfig file. 

### Identification of FreeRTOSConfig.h

The FreeRTOSConfig.h file specifies the defaults for the FreeRTOS kernel. This file governs which RTOS functions and features can be accessed in our project applications. Changes in this file can enable/disable FreeRTOS kernel specific functions and features.  

## Part 2

