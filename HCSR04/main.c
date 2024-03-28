// Create source file and header file  
//This code for water level

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"


#define TRIGGER_PIN 26
#define ECHO_PIN 27

static const char *TAG = "SU_SEVIYE";


void HCSR04_Config() {

    esp_rom_gpio_pad_select_gpio(TRIGGER_PIN);
    esp_rom_gpio_pad_select_gpio(ECHO_PIN);
    gpio_set_direction(TRIGGER_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);
    gpio_set_level(TRIGGER_PIN, 0);
}

float Read_HCSR04() {

    gpio_set_level(TRIGGER_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(2));

    gpio_set_level(TRIGGER_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(TRIGGER_PIN, 0);

    uint32_t start_time, end_time;

    while(gpio_get_level(ECHO_PIN) == 0);
    start_time = esp_timer_get_time();
    while(gpio_get_level(ECHO_PIN) == 1);
    end_time = esp_timer_get_time();

    double water_level = (end_time - start_time) * 0.017;
    return water_level;

}

void app_main() {

    ESP_LOGI(TAG, "Su seviyesi ölçümü Başlatiliyor...");

    HCSR04_Config();

    while(1) {

        double water_level = Read_HCSR04();
        ESP_LOGI(TAG, "Su seviyesi: %.2lf cm\n",25 - water_level);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
