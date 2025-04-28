#include "Wireless.h"

uint16_t BLE_NUM = 0;
uint16_t WIFI_NUM = 0;
bool Scan_finish = 0;
bool WiFi_Scan_Finish = 0;
bool BLE_Scan_Finish = 0;
wifi_ap_info_t wifi_aps[MAX_APS]; // Array para armazenar redes escaneadas

// Variáveis globais para SSID e senha
static char wifi_ssid[33] = "";      // SSID com até 32 caracteres + null
static char wifi_password[64] = "";   // Senha com até 63 caracteres + null
static SemaphoreHandle_t wifi_mutex = NULL; // Mutex para proteger acesso

void Wireless_Init(void)
{
    // Initialize NVS.
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK( ret );
    // WiFi
    xTaskCreatePinnedToCore(
        WIFI_Init, 
        "WIFI task",
        4096, 
        NULL, 
        1, 
        NULL, 
        0);
    // // BLE
    // xTaskCreatePinnedToCore(
    //     BLE_Init, 
    //     "BLE task",
    //     4096, 
    //     NULL, 
    //     2, 
    //     NULL, 
    //     0);
}

void WIFI_Init(void *arg)
{
    esp_netif_init();                                                     
    esp_event_loop_create_default();                                      
    esp_netif_create_default_wifi_sta();                                 
    wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();                 
    esp_wifi_init(&cfg);                                      
    esp_wifi_set_mode(WIFI_MODE_STA);              
    esp_wifi_start();                            

    // WIFI_NUM = WIFI_Scan();
    // printf("WIFI:%d\r\n",WIFI_NUM);
    
    vTaskDelete(NULL);
}
// uint16_t WIFI_Scan(void)
// {
//     uint16_t ap_count = 0;
//     esp_wifi_scan_start(NULL, true);
//     ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));
//     esp_wifi_scan_stop();
//     WiFi_Scan_Finish =1;
//     if(BLE_Scan_Finish == 1)
//         Scan_finish = 1;
//     return ap_count;
// }

uint16_t WIFI_Scan(void) {
    wifi_scan_config_t scan_config = {
        .ssid = NULL,
        .bssid = NULL,
        .channel = 0,
        .show_hidden = true,
    };

    ESP_ERROR_CHECK(esp_wifi_scan_start(&scan_config, true));
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&WIFI_NUM));

    if (WIFI_NUM > MAX_APS) {
        WIFI_NUM = MAX_APS; // Limita ao máximo definido
    }

    wifi_ap_record_t ap_records[MAX_APS];
    ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&WIFI_NUM, ap_records));

    // Preenche o array global com os SSIDs e RSSI
    for (int i = 0; i < WIFI_NUM; i++) {
        strncpy(wifi_aps[i].ssid, (char *)ap_records[i].ssid, sizeof(wifi_aps[i].ssid) - 1);
        wifi_aps[i].ssid[sizeof(wifi_aps[i].ssid) - 1] = '\0';
        wifi_aps[i].rssi = ap_records[i].rssi;
    }

    esp_wifi_scan_stop();
    WiFi_Scan_Finish = 1;
    if (BLE_Scan_Finish == 1) {
        Scan_finish = 1;
    }

    ESP_LOGI("WIFI", "Found %d networks", WIFI_NUM);
    return WIFI_NUM;
}

bool WIFI_Connect(const char *ssid, const char *password) {
    // Atualiza as credenciais globais
    WIFI_Set_Credentials(ssid, password);

    wifi_config_t wifi_config = {
        .sta = {
            .scan_method = WIFI_ALL_CHANNEL_SCAN,
            .sort_method = WIFI_CONNECT_AP_BY_SIGNAL,
        },
    };

    // Usa as credenciais globais
    xSemaphoreTake(wifi_mutex, portMAX_DELAY);
    strncpy((char *)wifi_config.sta.ssid, wifi_ssid, sizeof(wifi_config.sta.ssid) - 1);
    wifi_config.sta.ssid[sizeof(wifi_config.sta.ssid) - 1] = '\0';
    strncpy((char *)wifi_config.sta.password, wifi_password, sizeof(wifi_config.sta.password) - 1);
    wifi_config.sta.password[sizeof(wifi_config.sta.password) - 1] = '\0';
    xSemaphoreGive(wifi_mutex);

    ESP_ERROR_CHECK(esp_wifi_disconnect());
    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
    ESP_ERROR_CHECK(esp_wifi_connect());

    // Aguarda conexão (timeout de 15 segundos)
    vTaskDelay(pdMS_TO_TICKS(15000));
    wifi_ap_record_t ap_info;
    esp_err_t ret = esp_wifi_sta_get_ap_info(&ap_info);
    if (ret == ESP_OK) {
        ESP_LOGI("WIFI", "Connected to %s", wifi_ssid);
        return true;
    } else {
        ESP_LOGE("WIFI", "Failed to connect to %s", wifi_ssid);
        return false;
    }
}

void WIFI_Set_Credentials(const char *ssid, const char *password) {
    if (ssid == NULL || password == NULL) {
        ESP_LOGE("WIFI", "Invalid SSID or password");
        return;
    }

    xSemaphoreTake(wifi_mutex, portMAX_DELAY);
    strncpy(wifi_ssid, ssid, sizeof(wifi_ssid) - 1);
    wifi_ssid[sizeof(wifi_ssid) - 1] = '\0';
    strncpy(wifi_password, password, sizeof(wifi_password) - 1);
    wifi_password[sizeof(wifi_password) - 1] = '\0';
    xSemaphoreGive(wifi_mutex);

    ESP_LOGI("WIFI", "Credentials set: SSID=%s", wifi_ssid);
}

void WIFI_Get_SSID(char *ssid, size_t max_len) {
    if (ssid == NULL || max_len == 0) return;

    xSemaphoreTake(wifi_mutex, portMAX_DELAY);
    strncpy(ssid, wifi_ssid, max_len - 1);
    ssid[max_len - 1] = '\0';
    xSemaphoreGive(wifi_mutex);
}

void WIFI_Get_Password(char *password, size_t max_len) {
    if (password == NULL || max_len == 0) return;

    xSemaphoreTake(wifi_mutex, portMAX_DELAY);
    strncpy(password, wifi_password, max_len - 1);
    password[max_len - 1] = '\0';
    xSemaphoreGive(wifi_mutex);
}

#define GATTC_TAG "GATTC_TAG"
#define SCAN_DURATION 5  
#define MAX_DISCOVERED_DEVICES 100 

typedef struct {
    uint8_t address[6];
    bool is_valid;
} discovered_device_t;

static discovered_device_t discovered_devices[MAX_DISCOVERED_DEVICES];
static size_t num_discovered_devices = 0;
static size_t num_devices_with_name = 0; 

static bool is_device_discovered(const uint8_t *addr) {
    for (size_t i = 0; i < num_discovered_devices; i++) {
        if (memcmp(discovered_devices[i].address, addr, 6) == 0) {
            return true;
        }
    }
    return false;
}

static void add_device_to_list(const uint8_t *addr) {
    if (num_discovered_devices < MAX_DISCOVERED_DEVICES) {
        memcpy(discovered_devices[num_discovered_devices].address, addr, 6);
        discovered_devices[num_discovered_devices].is_valid = true;
        num_discovered_devices++;
    }
}

static bool extract_device_name(const uint8_t *adv_data, uint8_t adv_data_len, char *device_name, size_t max_name_len) {
    size_t offset = 0;
    while (offset < adv_data_len) {
        if (adv_data[offset] == 0) break; 

        uint8_t length = adv_data[offset];
        if (length == 0 || offset + length > adv_data_len) break; 

        uint8_t type = adv_data[offset + 1];
        if (type == ESP_BLE_AD_TYPE_NAME_CMPL || type == ESP_BLE_AD_TYPE_NAME_SHORT) {
            if (length > 1 && length - 1 < max_name_len) {
                memcpy(device_name, &adv_data[offset + 2], length - 1);
                device_name[length - 1] = '\0'; 
                return true;
            } else {
                return false;
            }
        }
        offset += length + 1;
    }
    return false;
}

static void esp_gap_cb(esp_gap_ble_cb_event_t event, esp_ble_gap_cb_param_t *param) {
    static char device_name[100]; 

    switch (event) {
        case ESP_GAP_BLE_SCAN_RESULT_EVT:
            if (param->scan_rst.search_evt == ESP_GAP_SEARCH_INQ_RES_EVT) {
                if (!is_device_discovered(param->scan_rst.bda)) {
                    add_device_to_list(param->scan_rst.bda);
                    BLE_NUM++; 

                    if (extract_device_name(param->scan_rst.ble_adv, param->scan_rst.adv_data_len, device_name, sizeof(device_name))) {
                        num_devices_with_name++;
                        // printf("Found device: %02X:%02X:%02X:%02X:%02X:%02X\n        Name: %s\n        RSSI: %d\r\n",
                        //          param->scan_rst.bda[0], param->scan_rst.bda[1],
                        //          param->scan_rst.bda[2], param->scan_rst.bda[3],
                        //          param->scan_rst.bda[4], param->scan_rst.bda[5],
                        //          device_name, param->scan_rst.rssi);
                        // printf("\r\n");
                    } else {
                        // printf("Found device: %02X:%02X:%02X:%02X:%02X:%02X\n        Name: Unknown\n        RSSI: %d\r\n",
                        //          param->scan_rst.bda[0], param->scan_rst.bda[1],
                        //          param->scan_rst.bda[2], param->scan_rst.bda[3],
                        //          param->scan_rst.bda[4], param->scan_rst.bda[5],
                        //          param->scan_rst.rssi);
                        // printf("\r\n");
                    }
                }
            }
            break;
        case ESP_GAP_BLE_SCAN_STOP_COMPLETE_EVT:
            ESP_LOGI(GATTC_TAG, "Scan complete. Total devices found: %d (with names: %d)", BLE_NUM, num_devices_with_name);
            break;
        default:
            break;
    }
}

void BLE_Init(void *arg)
{
    ESP_ERROR_CHECK(esp_bt_controller_mem_release(ESP_BT_MODE_CLASSIC_BT));
    esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
    esp_err_t ret = esp_bt_controller_init(&bt_cfg);                                            
    if (ret) {
        printf("%s initialize controller failed: %s\n", __func__, esp_err_to_name(ret));        
        return;}
    ret = esp_bt_controller_enable(ESP_BT_MODE_BLE);                                            
    if (ret) {
        printf("%s enable controller failed: %s\n", __func__, esp_err_to_name(ret));            
        return;}
    ret = esp_bluedroid_init();                                                                 
    if (ret) {
        printf("%s init bluetooth failed: %s\n", __func__, esp_err_to_name(ret));               
        return;}
    ret = esp_bluedroid_enable();                                                               
    if (ret) {
        printf("%s enable bluetooth failed: %s\n", __func__, esp_err_to_name(ret));             
        return;}

    //register the  callback function to the gap module
    ret = esp_ble_gap_register_callback(esp_gap_cb);                                            
    if (ret){
        printf("%s gap register error, error code = %x\n", __func__, ret);                      
        return;
    }
    BLE_Scan();
    // while(1)
    // {
    //     vTaskDelay(pdMS_TO_TICKS(150));
    // }
    
    vTaskDelete(NULL);

}
uint16_t BLE_Scan(void)
{
    esp_ble_scan_params_t scan_params = {
        .scan_type = BLE_SCAN_TYPE_ACTIVE,
        .own_addr_type = BLE_ADDR_TYPE_RPA_PUBLIC,
        .scan_filter_policy = BLE_SCAN_FILTER_ALLOW_ALL,
        .scan_interval = 0x50,     
        .scan_window = 0x30,        
        .scan_duplicate         = BLE_SCAN_DUPLICATE_DISABLE
    };
    ESP_ERROR_CHECK(esp_ble_gap_set_scan_params(&scan_params));

    printf("Starting BLE scan...\n");
    ESP_ERROR_CHECK(esp_ble_gap_start_scanning(SCAN_DURATION));
    
    // Set scanning duration
    vTaskDelay(SCAN_DURATION * 1000 / portTICK_PERIOD_MS);
    
    printf("Stopping BLE scan...\n");
    // ESP_ERROR_CHECK(esp_ble_gap_stop_scanning());
    // ESP_ERROR_CHECK(esp_ble_dtm_stop());
    BLE_Scan_Finish = 1;
    if(WiFi_Scan_Finish == 1)
        Scan_finish = 1;
    return BLE_NUM;
}