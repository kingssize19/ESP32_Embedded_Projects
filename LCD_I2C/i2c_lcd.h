#ifndef i2c_lcd
#define i2c_lcd

void lcd_init(void);

void lcd_send_cmd(char cmd);

void lcd_send_data(char data);

void lcd_send_string(char *str);

void lcd_put_cur(int row, int col);

void lcd_clear(void);



#endif
