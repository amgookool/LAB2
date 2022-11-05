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

#include <esp_sleep.h>

#include "sys/time.h"

#define GPIO_OUTPUT_IO 2 // LED

#define HIGH_PRIORITY 3
#define MEDIUM_PRIORITY 2
#define LOW_PRIORITY 1

//  Function Prototypes
static void active_wait();                 // Function for actively waiting for 0.5 seconds
static void status_message(void *pvParam); // Task function for printing status message
static void led_on(void *pvParam);         // Task function for turning on the LED (GPIO2 == 1)
static void led_off(void *pvParam);        // Task function for turning off the LED (GPIO2 == 0)
void vApplicationIdleHook(void);           // Idle Hook Task function for putting processor to sleep

static const char *TAG = "MAIN";

void vTaskGetRunTimeStats(char *writeBuffer);

SemaphoreHandle_t mutex_handle = NULL; // Handler for Mutex -> thing that controls which function access resource (GPIO2)

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

    if (mutex_handle != NULL)
    {
        xTaskCreate(led_on, "led_on_task", 1024, NULL, LOW_PRIORITY, NULL);      // RTOS task instance to set GPIO2 to HIGH
        xTaskCreate(led_off, "led_off_task", 1024, NULL, MEDIUM_PRIORITY, NULL); // RTOS task instance to set GPIO2 to LOW
    }
    xTaskCreate(status_message, "status_message_task", 1024, NULL, HIGH_PRIORITY, NULL); // RTOS task instance to display status of GPIO2 pin

    vTaskGetRunTimeStats(buffer);

    // print output of runtime function
    printf("Task            Abs. Time       %%Time \n");
    printf("---------------------------------------\n");
    printf(buffer, "\n\n");

    // Heap memory management
    for (;;)
    {
        vApplicationIdleHook();
    };
}

// Put processor to sleep for 1 second
void vApplicationIdleHook(void)
{
    esp_err_t ret;
    ESP_LOGI(TAG, "Putting processor to sleep for 1 second\n");
    ret = esp_sleep_enable_timer_wakeup(1000000); // enables processor to wakeup after x amount of time in microseconds
    if (ret == ESP_OK)
    {
        esp_light_sleep_start();
    }
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
