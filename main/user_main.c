#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"

#include "freertos/semphr.h"

#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"

#include "sys/time.h"

#define GPIO_OUTPUT_IO 2 // LED

#define ROUND_ROBIN 5

//  Function Prototypes
static void active_wait();                 // Function for actively waiting for 0.5 seconds
static void status_message(void *pvParam); // Task function for printing status message
static void led_on(void *pvParam);         // Task function for turning on the LED (GPIO2 == 1)
static void led_off(void *pvParam);        // Task function for turning off the LED (GPIO2 == 0)

static const char *TAG = "main";

void vTaskGetRunTimeStats(char *writeBuffer);

SemaphoreHandle_t mutex_handle = NULL; // Handler for Mutex -> thing that controls which function access resource (GPIO2)

/* 2.a) Round Robin Scheduling
            - priority is the same for all task functions
            - Code Functions:
            {
                xTaskCreate(led_on, "led_on_task", 2048, NULL, ROUND_ROBIN, NULL);
                xTaskCreate(led_off, "led_off_task", 2048, NULL, ROUND_ROBIN, NULL);
                xTaskCreate(status_message, "status_message_task", 2048, NULL, ROUND_ROBIN, NULL);
            }
*/

/* 2.b) Priority Inheritance
    - Tasks:
        * Task1 - LED ON
        * Task2 - LED OFF
        * Task3 - Status Message
    - Since there are 3 task functions, there is 3! = 3 X 2 X 1 = 6 possible combinations for setting task priority
        1. Task1 -> Task2 -> Task3
            - Code Functions:
            {
                xTaskCreate(led_on, "led_on_task", 2048, NULL, 3, NULL);
                xTaskCreate(led_off, "led_off_task", 2048, NULL, 2, NULL);
                xTaskCreate(status_message, "status_message_task", 2048, NULL, 1, NULL);
            }
        2. Task1 -> Task3 -> Task2
            - Code Functions:
            {
                xTaskCreate(led_on, "led_on_task", 2048, NULL, 3, NULL);
                xTaskCreate(led_off, "led_off_task", 2048, NULL, 1, NULL);
                xTaskCreate(status_message, "status_message_task", 2048, NULL, 2, NULL);
            }
        3. Task2 -> Task1 -> Task3
            - Code Functions:
            {
                xTaskCreate(led_on, "led_on_task", 2048, NULL, 2, NULL);
                xTaskCreate(led_off, "led_off_task", 2048, NULL, 3, NULL);
                xTaskCreate(status_message, "status_message_task", 2048, NULL, 1, NULL);
            }
        4. Task2 -> Task3 -> Task1
            - Code Functions:
            {
                xTaskCreate(led_on, "led_on_task", 2048, NULL, 1, NULL);
                xTaskCreate(led_off, "led_off_task", 2048, NULL, 3, NULL);
                xTaskCreate(status_message, "status_message_task", 2048, NULL, 2, NULL);
            }
        5. Task3 -> Task2 -> Task1
            - Code Functions:
            {
                xTaskCreate(led_on, "led_on_task", 2048, NULL, 1, NULL);
                xTaskCreate(led_off, "led_off_task", 2048, NULL, 2, NULL);
                xTaskCreate(status_message, "status_message_task", 2048, NULL, 3, NULL);
            }
        6. Task3 -> Task1 -> Task2
            - Code Functions:
            {
                xTaskCreate(led_on, "led_on_task", 2048, NULL, 2, NULL);
                xTaskCreate(led_off, "led_off_task", 2048, NULL, 1, NULL);
                xTaskCreate(status_message, "status_message_task", 2048, NULL, 3, NULL);
            }
*/

void app_main(void)
{
    gpio_config_t io_conf; // struct for configuring gpio pins

    // GPIO 2 IO Configuration
    io_conf.intr_type = GPIO_INTR_DISABLE;           // disable interrupt
    io_conf.mode = GPIO_MODE_OUTPUT;                 // set as output mode
    io_conf.pin_bit_mask = (1ULL << GPIO_OUTPUT_IO); // bit mask of the pin that you want to set
    io_conf.pull_down_en = 0;                        // disable pull-down mode
    io_conf.pull_up_en = 0;                          // disable pull-up mode
    gpio_config(&io_conf);                           // configure GPIO with the given settings

    // Creating Mutex
    mutex_handle = xSemaphoreCreateMutex();

    // Run Time Stats Buffer
    static char buffer[1500];

    // Give the Semaphore
    xSemaphoreGive(mutex_handle);

    // Round-Robin Scheduling
    // xTaskCreate(led_on, "led_on_task", 2048, NULL, ROUND_ROBIN, NULL);
    // xTaskCreate(led_off, "led_off_task", 2048, NULL, ROUND_ROBIN, NULL);
    // xTaskCreate(status_message, "status_message_task", 2048, NULL, ROUND_ROBIN, NULL);

    // RTOS Task Functions (3-1-2)
    xTaskCreate(led_on, "led_on_task", 2048, NULL, 2, NULL);
    xTaskCreate(led_off, "led_off_task", 2048, NULL, 1, NULL);
    xTaskCreate(status_message, "status_message_task", 2048, NULL, 3, NULL);

    // Call Runtime stats function
    vTaskGetRunTimeStats(buffer);

    // print output of runtime function
    printf("Task            Abs. Time       %%Time \n");
    printf("---------------------------------------\n");
    printf(buffer, "\n\n");

    // Heap memory management
    for (;;)
        ;
}

static void active_wait()
{
    struct timeval present_tv; // Structure returned by gettimeofday function
    gettimeofday(&present_tv, NULL);

    int64_t start_time = (int64_t)present_tv.tv_sec * 1000000L + (int64_t)present_tv.tv_usec; // time since last reset in microseconds

    while (1)
    {
        gettimeofday(&present_tv, NULL);
        int64_t current_time = (int64_t)present_tv.tv_sec * 1000000L + (int64_t)present_tv.tv_usec;

        // check if 0.5 seconds have elapsed
        if ((current_time - start_time) >= 500000)
        {
            break;
        }
    }
}

static void status_message(void *pvParam)
{
    while (1)
    {
        ESP_LOGI(TAG, "The LED Status: %d\n", gpio_get_level(GPIO_OUTPUT_IO));
        vTaskDelay(1000 / portTICK_PERIOD_MS); // delay for 1 second
    }
}

static void led_on(void *pvParam)
{
    while (1)
    {
        while (1)
        {
            if (xSemaphoreTake(mutex_handle, (TickType_t)15) == pdTRUE)
            {
                // Obtained Mutex...
                ESP_LOGI(TAG, "Turning LED ON\n");
                gpio_set_level(GPIO_OUTPUT_IO, 1);
                break;
            }
            else
            {
                continue;
            }
        }
        active_wait(); // wait for 0.5 seconds

        // Give back Mutex
        xSemaphoreGive(mutex_handle);

        // delay for 1 second
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

static void led_off(void *pvParam)
{
    while (1)
    {
        while (1)
        {
            if (xSemaphoreTake(mutex_handle, (TickType_t)15) == pdTRUE)
            {
                ESP_LOGI(TAG, "Turning LED OFF\n");
                gpio_set_level(GPIO_OUTPUT_IO, 0);
                break;
            }
            else
            {
                continue;
            }
        }
        active_wait(); // wait for 0.5 seconds

        // Give back Mutex
        xSemaphoreGive(mutex_handle);

        // delay for 1 second
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}