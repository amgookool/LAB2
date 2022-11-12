# Discussion

The following criteria is used for assessing system performance:

1. Task Priority Inversion - When a high priority task is preempted by a lower priority task.

1. Execution of tasks always meet their deadlines

1. Utilization - System utilization of each task.

1. Jitter - The amount of variations in the timing of a task over the next iteration of a program or loop.

**Note:**  
 Absolute time refers to the total time the task has been in the running state.

Percentage Time refers to the percentage of the total processing time of the task.

## Round-Robin Scheduling

The Round-Robin Scheduling, each ready task runs turn by turn only in a cyclic queue for a limited time slice.

### Characteristics of Round-Robin Scheduling

- The round robin scheduling is pre-emptive.

- The CPU is shifted to the next process after fixed interval time, which is called time slice.

- The process that is preempted is added to the end of the queue.

It is seen that the round robin scheduling, the "led_on" task had the largest percentage of utilization and absolute execution time. The utilization percentage and absolute execution time of the "led_off" task was slightly less than than "led_on" task where the difference can be considered negligible. The "status_message" task utilization percentage was less than 1% while the "Tmr Svc" task had a percentage utilization of 12%. This was not expected since the "status_message" task was expected to utilize a higher percentage of the system utilization.

The comparable utilization and execution time for the "led_off" and "led_on" was expected due to the nature of Round-Robin scheduling (tasks are given a time slice and are executed in a cyclic manner). Jitter cannot be discussed as there was no defined expected output for the scheduling and the outputs were the same when the program is executed multiple times.
Based on the absolute time, all tasks meet their deadlines as all tasks successfully executed. Since task priority is equal for all tasks, there is no priority inversion and all tasks in the ready queue are executed provided that they are waiting to be executed.

When reviewing the output of the we can trace back the order of which function is executed sequentially. The pattern of the output is as follows:

led_on -> status_message -> led_off -> status_message -> led_on -> led_off -> repeat

It is seen that the "led_on" task is executed first then followed by the "status_message" task. This was not expected since the "led_off" task was called after the "led_on" task in the "app_main" function. This behavior can be attributed to the active wait function used where both "led_on" and "led_off" tasks has to wait for the mutex to be released. This is shown since the "led_off" task is only executed called after the "status_message".

## Priority Inheritance

Priority Inheritance scheduling refers to if a lower priority task holds a mutex token and a higher priority task tries to preempt a lower priority task, then the priority of the lower priority task that holds the mutex will raise to that of the higher priority task.

The task are as follows:

**Task 1 - led_on**

**Task 2 - led_off**

**Task 3 - status_message**

Since there are 3 task functions, there is 3! = 3 X 2 X 1 = 6 possible combinations for setting task priority. These combinations are:

- Task1 -> Task2 -> Task3

![Task1 -> Task2 -> Task3](https://i.postimg.cc/264nnHTg/task-123.png)

- Task2 -> Task1 -> Task3

![Task2 -> Task1 -> Task3](https://i.postimg.cc/Y0Rgsh53/task-213.png)

- Task1 -> Task3 -> Task2

![Task1 -> Task3 -> Task2](https://i.postimg.cc/mkBCjQ5k/task-132.png)

- Task3 -> Task1 -> Task2

![Task3 -> Task1 -> Task2](https://i.postimg.cc/59Sw0RXC/task-312.png)

- Task2 -> Task3 -> Task1

![Task2 -> Task3 -> Task1](https://i.postimg.cc/L6yLkgB4/task-231.png)

- Task3 -> Task2 -> Task1

![Task3 -> Task2 -> Task1](https://i.postimg.cc/3Jr2DFGb/task-321.png)

It is observed that (Task1 -> Task2 -> Task3) and (Task2 -> Task1 -> Task3) have similar absolute execution time and system utilization performance characteristics.

It is observed that (Task1 -> Task3 -> Task2) and (Task3 -> Task1 -> Task2) have similar absolute execution time and system utilization performance characteristics.

It is observed that (Task2 -> Task3 -> Task1) and (Task3 -> Task2 -> Task1) have similar absolute execution time and system utilization performance characteristics.

It is seen that all tasks were executed, therefore, all deadlines were met.

Jitter is not analyzed for priority inheritance since priorities are changed which can affect the order of execution of tasks.

Priority inversion would occur as both "led_on" and "led_off" functions preempts each other and the "status_message" task is executed while the mutex is held. In (Task 1 -> Task 2 -> Task 3) and (Task 1 -> Task 3 -> Task 2), it is observed from the output that system behaves in accordance to the priority set. The other task combinations showcased priority inversion as the task functions were not executed in accordance to its priority level.
