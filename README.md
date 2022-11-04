## Part 1
Application Specific Vs Port Specific

### Identification of sdkconfig file

The sdkconfig file is an application specific configuration file that is included in each new project. This file specify the settings for communicating and flashing the ESP8266-01 device. For instance, changes in the CONFIG_ESPTOOL_PORT can negatively affect flashing and serial monitering capability if the wrong COM port is specified in its configuration.

### Identification of sdkconfig.h file
The sdkconfig.h file is the file generated from the build process of the project. It creates a header file containing the settings specified in the sdkconfig file. Changes in this file will have the same affect as changes in the sdkconfig file. 

### Identification of FreeRTOSConfig.h

The FreeRTOSConfig.h file specifies the defaults for the FreeRTOS kernel. This file governs which RTOS functions and features can be accessed in our project applications. Changes in this file can enable/disable FreeRTOS kernel specific functions and features.  

## Part 2
Runtime Statistics in FreeRTOS
[Runtime Stats](https://www.freertos.org/a00021.html#vTaskGetRunTimeStats)

FreeRTOS can collect information on the amount of processing time that has been used by each task.The runtime statistics function in FreeRTOS can then be used to present this information in a tabular format. The use of this feature is not enabled by default. To enable this feature, follow the following steps:
- Step 0: Check FreeRtosConfig.h
    
    - Check to ensure configGenerate_RUN_TIME_STATS is set to 1. This is done through the use of #defines
    
    - Check for portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() function. Reccomended to make the time base between 10 and 100 times faster than the tick interrupt. Thhe faster the time base, the more accurate the statistics will be but this also leads to the timer value overflowing much sooner. If configGENERATE_RUN_TIME_STATS is defined as 1 then the RTOS kernel will automatically call portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() as it is started (it is called from within the vTaskStartScheduler() API function).

    - Go into FreeRTOSConfig.h and add line:
        extern void vConfigureTimerForRunTimeStats(void);

- Step 1: Initialize function prototype for vTaskGetRunTimeStats in your program Eg. 

    - void vTaskGetRunTimestats (char * pcWriteBuffer);

- Step 2: Declare a static char array to hold the data for the runtimestats function -> buffer_variable

- Step 3: Call vTaskGetRunTimeStats(buffer_variable)

- Step 4: Print the output of the buffer_variable




## Github Usage

I considered that labratory exercise as the repository itself. I determined that there are four parts to this excercise which are:

1. P1 and P2
1. Excercise/Question 1
1. Excercise/Question 2
1. Excercise/Question 3

Each part is structured as a branch on the github repository. Hence to change between the different parts of the lab excercise, the switching of the appropiate branch is required.
The branches of the repository are shown in the image below:

[![github-branch-screenshot.png](https://i.postimg.cc/mrybcCv1/github-branch-screenshot.png)](https://postimg.cc/QBVLw9xj)

