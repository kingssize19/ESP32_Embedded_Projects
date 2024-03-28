//Create source file and header file
//This code for cover state

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"
#include "esp_system.h"
#include "esp_timer.h"

#define TRIG_PIN 12
#define ECHO_PIN 13


static const char *TAG = "Cover State";


void HCSR04_Config() {

    esp_rom_gpio_pad_select_gpio(TRIG_PIN);
    esp_rom_gpio_pad_select_gpio(ECHO_PIN);
    gpio_set_direction(TRIG_PIN, GPIO_MODE_OUTPUT);
    gpio_set_direction(ECHO_PIN, GPIO_MODE_INPUT);
    gpio_set_level(TRIG_PIN, 0);

}


uint8_t Cover_State() {

    gpio_set_level(TRIG_PIN, 0);
    vTaskDelay(pdMS_TO_TICKS(2));

    gpio_set_level(TRIG_PIN, 1);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(TRIG_PIN, 0);

    uint32_t start_time = 0, end_time = 0;
    while(gpio_get_level(ECHO_PIN) == 0);
    start_time = esp_timer_get_time();
    while(gpio_get_level(ECHO_PIN) == 1);
    end_time = esp_timer_get_time();

    uint8_t cover_state = (end_time - start_time) * 0.017;
    return cover_state;

}

void app_main() {
    ESP_LOGI(TAG, "Kapak Durumu Inceleniyor...");
    HCSR04_Config();

    while (1)
    {
        uint8_t cover_state = Cover_State();
        
        if (cover_state <= 8)
        {  ESP_LOGI(TAG, "NO Problem. %d cm\n",cover_state); }
        else
        {   ESP_LOGI(TAG, "Dangerous!!! %d cm\n",cover_state); }
        
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
    
}
