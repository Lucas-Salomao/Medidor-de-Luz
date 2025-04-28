#include "ST7789.h"
#include "PCF85063.h"
#include "QMI8658.h"
#include "SD_MMC.h"
#include "Wireless.h"
#include "LVGL_Example.h"
#include "BAT_Driver.h"
#include "PWR_Key.h"
#include "PCM5101.h"
#include "VEML7700.h"
#include "Screens.h"
#include "fluorimeter_screen.h"


void sensor_task(void *arg) {
    while (1) {
        float lux;
        if (VEML7700_Read_Lux(&lux) == ESP_OK) {
            update_lux_value(lux);
        }
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}

void Driver_Loop(void *parameter)
{
    Wireless_Init();
    while(1)
    {
        QMI8658_Loop();
        PCF85063_Loop();
        BAT_Get_Volts();
        PWR_Loop();
        vTaskDelay(pdMS_TO_TICKS(100));
    }
    vTaskDelete(NULL);
}
void Driver_Init(void)
{
    PWR_Init();
    BAT_Init();
    I2C_Init();
    PCF85063_Init();
    QMI8658_Init();
    Flash_Searching();
    VEML7700_Init(I2C_NUM_0);
    xTaskCreatePinnedToCore(
        Driver_Loop, 
        "Other Driver task",
        4096, 
        NULL, 
        3, 
        NULL, 
        0);
}
void app_main(void)
{
    Driver_Init();
    SD_Init();
    LCD_Init();
    Audio_Init();
    // Play_Music("/sdcard","AAA.mp3");
    LVGL_Init();   // returns the screen object

    setup_ui();

    // Cria a tarefa para leitura do sensor
    xTaskCreatePinnedToCore(sensor_task, "Sensor Task", 4096, NULL, 2, NULL, 0);

    while (1) {
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
        vTaskDelay(pdMS_TO_TICKS(10));
        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();
    }

}






