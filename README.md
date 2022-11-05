# Discussion
Absolute time refers to the total time the task has been in the running state.

Percentage Time refers to the percentage of the total processing time of the task.

## Round-Robin Scheduling

The Round-Robin Scheduling, each ready task runs turn by turn only in a cyclic queue for a limited time slice.

### Characteristics of Round-Robin Scheduling

- The round robin scheduling is pre-emptive.

- The CPU is shifted to the next process after fixed interval time, which is called time slice.

- The process that is preempted is added to the end of the queue.

The priority for the 3 task functions (led_on, led_off, status_message) was given the same priority of 5. When reviewing the runtime statistics of the program, both the led_off and led_on task had similar absolute and percentage time with negligable difference. The status_message task had significantly less absolute time and percentage time than both the led_off and led_on task. Additionally, when reviewing the output of the we can traceback the order of which function is executed sequentially. The pattern of the output is as follows:

led_on -> status_message -> led_off -> status_message -> led_on -> led_off -> repeat

This is expected since the led_on and led_off task are sharing a resource (GPIO2) while the status_message task only checks the state of the pin.

## Priority Inheritance

Priority Inheritance scheduling refers to if a lower priority task holds a mutex token and a higher priority task treies to prempt a lower priority task, then the priority of the lower priority task that holds the mutex will raise to that of the higher priority task.

The task are as follows:
**Task 1 - led_on**
**Task 2 - led_off**
**Task 3 - status_message**

Since there are 3 task functions, there is 3! = 3 X 2 X 1 = 6 possible combinations for setting task priority. These combinations are: 

- Task1 -> Task2 -> Task3
    - When reviewing the runtime statistics of this sequence of function calls, the led_on task and led_off task had similar absolute and percentage time for their respective task with negligable difference between the values. However, the status message task had no absolute time for its execution time and less than 1% in the percentage time. 

- Task1 -> Task3 -> Task2

- Task2 -> Task1 -> Task3

- Task2 -> Task3 -> Task1

- Task3 -> Task2 -> Task1

- Task3 -> Task1 -> Task2
