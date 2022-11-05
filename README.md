## Part 1

### Identification of sdkconfig file

The sdkconfig file is an application specific configuration file that is included in each new project. This file specify the settings and functionality for the ESP8266_RTOS_SDK. For instance, changes in the CONFIG_ESPTOOL_PORT can negatively affect flashing and serial monitering capability if the wrong COM port is specified in its configuration.

### Identification of sdkconfig.h file

The sdkconfig.h file is the file generated from the build process of the project for the esp device. It creates a header file containing the settings specified in the sdkconfig file. Changes in this file will have the same affect as changes in the sdkconfig file. During compilation, the configurations specified will be sdkconfig will be translated as #define macros in the sdkconfig.h file

### Identification of FreeRTOSConfig.h

The FreeRTOSConfig.h file specifies the defaults for the FreeRTOS kernel. This file governs which RTOS functions and features can be accessed in our project applications. Changes in this file can enable/disable FreeRTOS kernel specific functions and features.
It does not matter what configurations were set in the sdkconfig or sdkconfig.h, changes in the FreeRTOSConfig.h file will overide any changes in those files.
Changes of the functionality of ESP8266_RTOS_SDK was evident when conducting Question 2 of the labratory.

## Part 2

Runtime Statistics in FreeRTOS:
[Runtime Stats](https://www.freertos.org/a00021.html#vTaskGetRunTimeStats)

FreeRTOS can collect information on the amount of processing time that has been used by each task.The runtime statistics function in FreeRTOS can then be used to present this information in a tabular format. The use of this feature is not enabled by default. To enable this feature, the following is used from the FreeRTOSConfig.h:

1.configGENERATE_RUN_TIME_STATS

2.portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

3.portGET_RUN_TIME_COUNTER_VALUE()

The runtime statistics functionality is called using the vTaskGetRunTimeStats function. 

To use this function, configGENERATE_RUN_TIME_STATS must be set to 1. Setting this to 0 will disable the use of the vTaskGetRunTimeStats function. 

portCONFIGURE_TIMER_FOR_RUN_TIME_STATS and portGET_RUN_TIME_COUNTER_VALUE macros are utilized as debugging for the runtime statistics function. 

The use of this function also requires counters or timers since this function is based on time. The internal clock of the ESP is used to satisfy this condition.

In FreeRTOSConfig.h, the following macros are set:

1.configGENERATE_RUN_TIME_STATS

2.portCONFIGURE_TIMER_FOR_RUN_TIME_STATS()

3.portGET_RUN_TIME_COUNTER_VALUE()

In sdkconfig, the following is set:

CONFIG_FREERTOS_USE_TRACE_FACILITY=y

CONFIG_FREERTOS_USE_STATS_FORMATTING_FUNCTIONS=y

CONFIG_FREERTOS_GENERATE_RUN_TIME_STATS=y

CONFIG_FREERTOS_RUN_TIME_STATS_USING_ESP_TIMER=y

## Github Usage

I considered that labratory exercise as the repository itself. I determined that there are four parts to this excercise which are:

1. P1 and P2
1. Excercise/Question 1
1. Excercise/Question 2
1. Excercise/Question 3

Each part is structured as a branch on the github repository. Hence to change between the different parts of the lab excercise, the switching of the appropiate branch is required.
The branches of the repository are shown in the image below:

[![github-branch-screenshot.png](https://i.postimg.cc/mrybcCv1/github-branch-screenshot.png)](https://postimg.cc/QBVLw9xj)
