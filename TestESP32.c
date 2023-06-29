#include <stdio.h>
#include <esp_err.h>
#include <driver/uart.h>
#include <driver/gpio.h>
#include <driver/adc.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <string.h>

const uart_port_t uart_num = UART_NUM_0;
uart_config_t uart_config = {
    .baud_rate = 115200,
    .data_bits = UART_DATA_8_BITS,
    .parity = UART_PARITY_DISABLE,
    .stop_bits = UART_STOP_BITS_1,
    .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
    .rx_flow_ctrl_thresh = 122,
    .source_clk = UART_SCLK_DEFAULT,
};

const int uart_buffer_size = (1024 * 2);
QueueHandle_t uart_queue;


void app_main(void)
{
    gpio_set_direction(GPIO_NUM_2, GPIO_MODE_OUTPUT);
    adc1_config_channel_atten(ADC1_CHANNEL_4, ADC_ATTEN_DB_11);
    adc1_config_width(ADC_WIDTH_BIT_12);

    char* test_str = "%0.2f\n";

    char* Txdata = (char*) malloc(100);

    ESP_ERROR_CHECK(uart_param_config(uart_num, &uart_config));

    ESP_ERROR_CHECK(uart_set_pin(uart_num, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE, UART_PIN_NO_CHANGE));

    ESP_ERROR_CHECK(uart_driver_install(uart_num, uart_buffer_size, uart_buffer_size, 10, &uart_queue, 0));

    while(true)
    {   
        float pot = adc1_get_raw(ADC1_CHANNEL_4);
        gpio_set_level(GPIO_NUM_2, 1);
        vTaskDelay(20);
        gpio_set_level(GPIO_NUM_2, 0);
        vTaskDelay(20);
        sprintf (Txdata, test_str, pot);
        uart_write_bytes(uart_num, Txdata, strlen(Txdata));
   
    }

}
