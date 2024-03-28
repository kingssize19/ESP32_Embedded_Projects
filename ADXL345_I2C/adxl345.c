#include <stdio.h>
#include <string.h>
#include "esp_event.h"
#include "i2c.h"
#include <stdint.h>
#include "adxl345.h"

void adxl345_init(uint8_t i2c_master_port)
{
	printf("Manufacturer ID:        0x%02X\r\n",i2c_read_byte(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_DEVID));
	i2c_write_byte(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_POWER_CTL, 0b00001000);	// Enable measure mode

	// Enable threshold interrupt on Z axis
	i2c_write_byte(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_THRESH_ACT, 4);			// Set threshold
	i2c_write_byte(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_ACT_INACT_CTL, ACT_AC_COUPLED | ACT_Z_EN);	// Enable activity in Z axis
	i2c_write_byte(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_INT_MAP, 0b00000000);		// All functions generate INT1
	i2c_write_byte(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_INT_ENABLE, ACTIVITY);		// Enable activity function
}

uint16_t adxl345_read_x(uint8_t i2c_master_port)
{
	return (__bswap16(i2c_read_short(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_DATAX)));
}

uint16_t adxl345_read_y(uint8_t i2c_master_port)
{
	return (__bswap16(i2c_read_short(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_DATAY)));
}

uint16_t adxl345_read_z(uint8_t i2c_master_port)
{
	return (__bswap16(i2c_read_short(i2c_master_port, ADXL345_ALT_SLAVE_ADDRESS, ADXL345_DATAZ)));
}
