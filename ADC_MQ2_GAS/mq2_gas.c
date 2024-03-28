#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/adc.h"



void mq2_config(void) {

    adc1_config_width(ADC_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_6, ADC_ATTEN_DB_0);
}

uint32_t read_mq2(void) {

    uint32_t adc_value = adc1_get_raw(ADC1_CHANNEL_6);

    return adc_value;
}
