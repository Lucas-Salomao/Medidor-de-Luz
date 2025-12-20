#pragma once

#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "esp_wifi.h"
#include "nvs_flash.h" 
#include "esp_log.h"
#include <stdio.h>
#include <string.h>  // For memcpy
#include "esp_system.h"
#include "esp_bt.h"
#include "esp_gap_ble_api.h"
#include "esp_bt_main.h"

#define MAX_APS 20 // Máximo de redes Wi-Fi a serem armazenadas

// Estrutura para armazenar informações de redes Wi-Fi
typedef struct {
    char ssid[33]; // SSID com até 32 caracteres + null terminator
    int8_t rssi;   // Força do sinal
} wifi_ap_info_t;

extern uint16_t BLE_NUM;
extern uint16_t WIFI_NUM;
extern bool Scan_finish;
extern wifi_ap_info_t wifi_aps[MAX_APS]; // Array global para armazenar redes escaneadas

void Wireless_Init(void);
void WIFI_Init(void *arg);
uint16_t WIFI_Scan(void);
void BLE_Init(void *arg);
uint16_t BLE_Scan(void);
bool WIFI_Connect(const char *ssid, const char *password); // Função para conectar ao Wi-Fi
void WIFI_Set_Credentials(const char *ssid, const char *password); // Define SSID e senha
void WIFI_Get_SSID(char *ssid, size_t max_len);                   // Obtém SSID
void WIFI_Get_Password(char *password, size_t max_len);