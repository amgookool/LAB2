# Discussion

An idle task hook is a function that is called during each cycle and hooks onto the idle task. For a functionality of the system to run at the idle priority, we can implement the functionality in an idle task hook. An idle task hook function is commonly used to put the ESP microcontroller into a power saving mode, or in this case put the device to sleep.

Create the idle hook by:

1. Setting configUSE_IDLE_Hook to 1 in the FreeRTOSConfig.h

1. Define a function that has the following name and prototype:
   void vApplicationIdleHook(void);

## Does the use of processor sleep affect the system performance?

No, the use of processor sleep affect the system performance. The absolute time which is the full time that the task was in the running state and the percentage time which is the percentage of the total processing time for the individual tasks were used as metrics for evaluating the performance.

When comparing the results obtained from question 2 and question 3, the round robin scheduling and priority inheritance scheduling gave similar absoute time and percentage time as the processor sleep functionality, with negligable differences. Additionally, the disparity of the numbers between tasks is attributed to which task has the higher priority for execution. A higher priority task will have a larger absolute time and percentage time.
