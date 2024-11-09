## 1. GPIO Çıkış Modu (LED Yakma)

**GPIO Numaralandırması ve Pin Seçimi**

ESP32'de her pinin bir GPIO numarası vardır. Örneğin, **GPIO_NUM_2**, ESP32'de GPIO2 pinini temsil eder. Bu numaralandırma ESP-IDF içindeki gpio_num_t tipinde tanımlıdır. 

------------------------------------------------------------------------------------------------------------------------------------------

**Adım Adım LED Yakma Kodu ve Analizi**

**1. Pinin Yönünü Çıkış Olarak Ayarlayalım :**

```c
gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
```

* **Fonksiyon :** gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode);
* **Parametreler :**
  * **gpio_num :** Ayarlanacak pinin numarası girilir. Örneğin, GPIO_NUM_2.
  * **mode :** Pinin çalışma modu. LED yakmak için GPIO_MODE_OUTPUT kullanılır.
* Bu fonksiyon, belirtilen GPIO pinini çıkış olarak ayarlar. GPIO_MODE_OUTPUT, GPIO pinini dijital sinyal gönderebilecek bir çıkış olarak konfigüre eder.

------------------------------------------------------------------------------------------------------------------------------------------

**2. Çıkış Seviyesini Ayarlayalım (LED Yakma veya Söndürme) :**

```c
gpio_set_level(GPIO_NUM_2, 1);    // LED'i yakar.
```
* **Fonksiyon :** gpio_set_level(gpio_num_t gpio_num, uint32_t level);
* **Parametreler :**
  * **gpio_num :** Seviyesini ayarlamak istediğimiz pinin numarasını yazarız.
  * **level :** Çıkış seviyesi. 1 LED'i yakmak (HIGH), 0 ise LED'i söndürmek (LOW) anlamına gelir.
* Bu fonksiyon, GPIO pinine bir dijital çıkış seviyesi atar. Eğer seviyeyi 1 yaparsanız, pini yüksek (HIGH) konumuna getirir ve bu da genellikle LED'i yakar. Seviyeyi 0 yaparsanız, düşük (LOW) konumuna çekilir ve LED söner.

------------------------------------------------------------------------------------------------------------------------------------------

## LED YAKMA ÖRNEĞİ

```c
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_GPIO_PIN    GPIO_NUM_18

void app_main()
{
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);

    while (1)
    {
        gpio_set_level(LED_GPIO_PIN, 1);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

        gpio_set_level(LED_GPIO_PIN, 0);
        vTaskDelay(1000 / portTICK_PERIOD_MS);

    }
    
}
```
Bu kod, LED'i 1 snaiye boyunca yakar ve 1 saniye boyunca söndürür.

------------------------------------------------------------------------------------------------------------------------------------------

## 2. GPIO Giriş Modu (Buton Okuma)

**Adım Adım Buton Durumunu Okuma Kodu ve Açıklaması**

**1. Pinin Yönünü Giriş Olarak Ayarlayalım :**

```c
gpio_set_direction(GPIO_NUM_0, GPIO_MODE_INPUT);
```
* **Fonksiyon :** gpio_set_direction(gpio_num_t gpio_num, gpio_mode_t mode);
* **Parametreler :**
  * **gpio_num :** Pin numarası, burada GPIO_NUM_0 (genelde buton için kullanılan GPIO pinlerinden biri.)
  * **mode :** Pinin çalışma modu, burada GPIO_MODE_INPUT.
* Bu fonksiyon, GPIO pinini giriş olarak yapılandırır, böylece dışarıdan bir sinyal (örneğin butona basılması) okunabilir hale gelir.

------------------------------------------------------------------------------------------------------------------------------------------

**2. Pull-Up veya Pull-Down Dirençleri Etkinleştirme :**

Buton okuma uygulamalarında gürültüyü önlemek ve doğru sonuçlar almak için pull-up veya pull-down dirençlerini etkinleştirmek yararlı olabilir.

```c
gpio_set_pull_mode(GPIO_NUM_0, GPIO_PULLUP_ONLY);
```
* **Fonksiyon :** gpio_set_pull_mode(gpio_num_t gpio_num, gpio_pull_mode_t pull);
* **Parametreler :**
  * **gpio_num :** Direnci etkinleştireceğimiz pinin numaraso.
  * **pull :** Direnç türü (GPIO_PULLUP_ONLY veya GPIO_PULLDOWN_ONLY).
* GPIO_PULLUP_ONLY butonun 0 (LOW) olması durumunda devreye giren pull-up direnci ekler. Bu, pinin varsayılan olarak 1 (HIGH) seviyesinde olmasını sağlar. GPIO_PULLDOWN_ONLY ise tam tersini yaparak pinin varsayılan olarak 0 seviyesinde olmasını sağlar.

------------------------------------------------------------------------------------------------------------------------------------------

**3. Buton Durumunu Okuma :**

```c
uint8_t button_state = gpio_get_level(GPIO_NUM_0);
```
* **Fonksiyon :** gpio_get_level(gpio_num_t gpio_num);
* **Parametreler :**
  * **gpio_num :** Okuma yapacağımız pinin numarası.
* Bu fonksiyon belirtilen GPIO pininin durumunu okur. Giriş pini HIGH durumundaysa 1, LOW durumundaysa 0 döner.

------------------------------------------------------------------------------------------------------------------------------------------

## BUTON OKUMA ÖRNEĞİ

```c
#include "driver/gpio.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

#define LED_GPIO_PIN    GPIO_NUM_18
#define BUTTON_GPIO_PIN GPIO_NUM_19

void app_main()
{
    gpio_set_direction(LED_GPIO_PIN, GPIO_MODE_OUTPUT);

    gpio_set_direction(BUTTON_GPIO_PIN, GPIO_MODE_INPUT);
    gpio_set_pull_mode(BUTTON_GPIO_PIN, GPIO_PULLDOWN_ONLY);

    uint8_t led_state = 0;
    uint8_t last_button_state = 0;

    while (1)
    {
       uint8_t button_state = gpio_get_level(BUTTON_GPIO_PIN);
       vTaskDelay(10 / portTICK_PERIOD_MS);       //Döngüyü biraz yavaşlatmak ve "debounce" (titreşim önleme) sağlamak için 10 ms bekler.
    
        if (button_state == 1 && last_button_state == 0)
        {
            led_state = !led_state;
            gpio_set_level(LED_GPIO_PIN, led_state);
        }

        last_button_state = button_state;
    
    }
    
}
```
Bu kod, butona bir kez basıldığında LED'i yakar, Diğer basılışta LED'i söndürür. Bu şekilde buton ile led kontrol edilir.

![image](https://github.com/user-attachments/assets/12f2b40f-b27f-4c16-80dc-c9b83b6b4603)




































