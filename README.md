# Discussion

Absolute time refers to the total time the task has been in the running state.

Percentage Time refers to the percentage of the total processing time of the task.

## Round-Robin Scheduling

The Round-Robin Scheduling, each ready task runs turn by turn only in a cyclic queue for a limited time slice.

### Characteristics of Round-Robin Scheduling

- The round robin scheduling is pre-emptive.

- The CPU is shifted to the next process after fixed interval time, which is called time slice.

- The process that is preempted is added to the end of the queue.

The priority for the 3 task functions (led_on, led_off, status_message) was given the same priority of 5. When reviewing the runtime statistics of the program, both the led_off and led_on task had similar absolute and percentage time with negligible difference. The status_message task had significantly less absolute time and percentage time than both the led_off and led_on task. Additionally, when reviewing the output of the we can trace back the order of which function is executed sequentially. The pattern of the output is as follows:

led_on -> status_message -> led_off -> status_message -> led_on -> led_off -> repeat

This is expected since the led_on and led_off task are sharing a resource (GPIO2) while the status_message task only checks the state of the pin.

## Priority Inheritance

Priority Inheritance scheduling refers to if a lower priority task holds a mutex token and a higher priority task tries to preempt a lower priority task, then the priority of the lower priority task that holds the mutex will raise to that of the higher priority task.

The task are as follows:
**Task 1 - led_on**
**Task 2 - led_off**
**Task 3 - status_message**

Since there are 3 task functions, there is 3! = 3 X 2 X 1 = 6 possible combinations for setting task priority. These combinations are:

- Task1 -> Task2 -> Task3

  - When reviewing the runtime statistics of this sequence of function calls, the led_on task and led_off task had similar absolute and percentage time for their respective task with negligible difference between the values. However, the status message task had no absolute time for its execution time and less than 1% in the percentage time. However, the output of the program showcases the priority inheritance as the led_on task is executed first followed by the led_off task then the status_message task. The pattern of the output is as follows:

    Task 1 -> Task 2 -> Task 3 -> repeat

  - This was within expectation as the task's priority was set to execute as:

    Task 1 -> Task 2 -> Task 3 -> repeat

- Task1 -> Task3 -> Task2

  - When reviewing the runtime statistics of this sequence of function calls, the led_on task had a significantly high absolute and percentage time while the led_off and status_message task was significantly less. The output of the program showcases the priority inheritance as the led_task is executed first followed by the status_message task and then the led_off task. The pattern of the output is as follows:

    Task 1 -> Task 3 -> Task 2 -> repeat

  - This was within expectation as the task's priority was set to execute as:

    Task 1 -> Task 3 -> Task 2 -> repeat

- Task2 -> Task1 -> Task3

  - When reviewing the runtime statistics of this sequence of function calls, both the led_on and led_off task has comparable absolute and percentage time with negligible difference between the values. in contrast, the status message task, had no absolute time and had was only utilized less than 1% of the time. The output of the program showcases priority inversion for tasks 1 and 2. This is because the led_on task was executed first followed by the led_off task and then the status_message task. The pattern of the output is as follows:

    Task 1 -> Task 2 -> Task 3 -> repeat

  - This was not within expectation as the task's priority was set to execute as:

    Task2 -> Task1 -> Task3 -> repeat

- Task2 -> Task3 -> Task1

  - When reviewing the runtime statistics of this sequence of function calls, the led_off task had the highest absolute and percentage time than the other two tasks. The led_on task and the status_message task had significantly less absolute and percentage time. The output of the program showcases priority inversion as led_off task was executed first, followed by the led_on task and then the status_message task. The pattern of the output is as follows:

    Task 2 -> Task 1 -> Task 3 -> repeat

  - This was not within expectation as the task's priority was set to execute as:

    Task2 -> Task3 -> Task1 -> repeat

- Task3 -> Task2 -> Task1

  - When reviewing the runtime statistics of this sequence of function calls, the led_off task had the highest absolute and percentage time than the other two tasks. The led_on task and the status_message task had significantly less absolute and percentage time. The output of the program showcases priority inversion as the led_off task was executed first, followed by the led_on task and then the status_message task. The pattern of the output of as follows:

    Task 2 -> Task 1 -> Task 3 -> repeat

- This was not within expectation as the task's priority was set to execute as:

Task3 -> Task2 -> Task1 -> repeat

- Task3 -> Task1 -> Task2

  - When reviewing the runtime statistics of this sequence of function calls, the led_on task had the highest absolute and percentage time while both the status_message and led_off task were significantly less. The output of the program showcases priority inversion as the led_on task was executed first, followed by the status_message task and then the led_off task. The pattern of the output is as follows:

    Task 1 -> Task 3 -> Task 2 -> repeat

- This was not within expectation as the task's priority was set to execute as:

  Task3 -> Task1 -> Task2 -> repeat
