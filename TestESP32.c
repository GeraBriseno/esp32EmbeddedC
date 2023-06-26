#include <stdio.h>
#include <driver/gpio.h>
#include <driver/adc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

void app_main(void)
{
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);
     
    
    while(true)
    {
        int val = adc1_get_raw(ADC1_CHANNEL_4);
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(100);
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(100);

    }

}
