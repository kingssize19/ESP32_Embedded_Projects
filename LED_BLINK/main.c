#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define LED_PIN GPIO_NUM_18 // ESP32 üzerindeki 18. pine LED bağlı

void led_task(void *pvParameter) {
    esp_rom_gpio_pad_select_gpio(LED_PIN);
    gpio_set_direction(LED_PIN, GPIO_MODE_OUTPUT);

    while(1) {
        // LED'i yak
        gpio_set_level(LED_PIN, 1);
        vTaskDelay(2000 / portTICK_PERIOD_MS);

        // LED'i söndür
        gpio_set_level(LED_PIN, 0);
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
}

void app_main() {
    xTaskCreate(&led_task, "led_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}
