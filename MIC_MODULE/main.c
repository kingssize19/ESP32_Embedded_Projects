// Create Source file and header file !!!!  
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "driver/adc.h"

#define MIC_CHANNEL ADC_CHANNEL_4
#define NUM_SAMPLES 64 // Ortalama almak için örnek sayısı



void app_main() {
    // ADC başlatma
    adc1_config_width(ADC_WIDTH_BIT_12); // ADC çözünürlüğü 12 bit olarak ayarlanır
    adc1_config_channel_atten(MIC_CHANNEL, ADC_ATTEN_DB_0); // ADC girişine 0dB kazanç uygulanır

    // Sonsuz döngüde ADC okuma
    while (1) {
        uint32_t sum = 0;
        // Birkaç örnek alıp ortalamasını hesapla
        for (int i = 0; i < NUM_SAMPLES; i++) {
            sum += adc1_get_raw(MIC_CHANNEL);
            vTaskDelay(1 / portTICK_PERIOD_MS); // Her örneği alırken kısa bir gecikme ekle
        }
        uint32_t adc_value = sum / NUM_SAMPLES; // Ortalama al

        // Okunan ADC değeri seri bağlantı üzerinden yazdırılır
        printf("ADC değeri: %ld\n", adc_value);

        // Kısa bir döngü gecikmesi ekleyin
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}

/*    v2 Code

#define MIC_GPIO_PIN 32

uint32_t mic_value;

void mic_config() {
    adc1_config_width(ADC1_WIDTH_BIT_12);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_0);
}

uint32_t read_mic() {

    mic_value = adc1_get_raw(ADC1_CHANNEL_4);
    return mic_value;
}

void app_main() {
    mic_config();

    while(1) {
        printf("mikrofon değeri = %ld\n",read_mic());
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}


*/
