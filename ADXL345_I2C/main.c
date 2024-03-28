#include "adxl345.h"
#include "driver/i2c.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdint.h>
#include "i2c.h"

#define I2C_MASTER_SCL_IO 22        // I2C için GPIO pin numarası
#define I2C_MASTER_SDA_IO 21        // I2C için GPIO pin numarası
#define I2C_MASTER_NUM I2C_NUM_0    // I2C port numarası

#define TAG "ADXL345"

void i2c_master_init() {
    i2c_config_t conf;
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = I2C_MASTER_SDA_IO;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = I2C_MASTER_SCL_IO;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = 100000;
    i2c_param_config(I2C_MASTER_NUM, &conf);
    i2c_driver_install(I2C_MASTER_NUM, conf.mode, 0, 0, 0);
}

void app_main(void *pvParameters) {
    i2c_init(I2C_MASTER_NUM, I2C_MASTER_SDA_IO, I2C_MASTER_SCL_IO);
    adxl345_init(I2C_MASTER_NUM);

    while (1) {
        uint16_t x = adxl345_read_x(I2C_MASTER_NUM);
        uint16_t y = adxl345_read_y(I2C_MASTER_NUM);
        uint16_t z = adxl345_read_z(I2C_MASTER_NUM);

        ESP_LOGI(TAG, "X: %d, Y: %d, Z: %d\n", x, y, z);

        vTaskDelay(1000 / portTICK_PERIOD_MS); // 1 saniye bekle
    }
}

