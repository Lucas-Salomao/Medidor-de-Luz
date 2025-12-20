/*
 * OTA Manager for GitHub Releases
 *
 * This module handles checking for new firmware versions from a GitHub repository's
 * releases page and performing an OTA update if a new version is found.
 */
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_ota_ops.h"
#include "esp_http_client.h"
#include "esp_https_ota.h"
#include "esp_crt_bundle.h"
#include "cJSON.h"
#include "string.h"

#include "OTA_Manager.h"

// ************************************************************************************
// !!! USER CONFIGURATION REQUIRED !!!
// ************************************************************************************

// SET YOUR CURRENT FIRMWARE VERSION HERE
#define CURRENT_FIRMWARE_VERSION "v1.0.0"

// SET YOUR GITHUB REPOSITORY DETAILS HERE
#define GITHUB_REPO_OWNER "Lucas-Salomao"
#define GITHUB_REPO_NAME "Medidor-de-Luz"

// ************************************************************************************

static const char *TAG = "GitHub_OTA";

// Buffer to store the JSON response from the GitHub API
static char api_response_buffer[8192];
static int api_response_len = 0;

// HTTP event handler for fetching the JSON API response
esp_err_t _api_http_event_handler(esp_http_client_event_t *evt)
{
    switch (evt->event_id) {
    case HTTP_EVENT_ERROR:
        ESP_LOGD(TAG, "HTTP_EVENT_ERROR");
        break;
    case HTTP_EVENT_ON_CONNECTED:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_CONNECTED");
        break;
    case HTTP_EVENT_ON_DATA:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_DATA, len=%d", evt->data_len);
        if (api_response_len + evt->data_len < sizeof(api_response_buffer)) {
            memcpy(api_response_buffer + api_response_len, evt->data, evt->data_len);
            api_response_len += evt->data_len;
        } else {
            ESP_LOGE(TAG, "Response buffer overflow");
        }
        break;
    case HTTP_EVENT_ON_FINISH:
        ESP_LOGD(TAG, "HTTP_EVENT_ON_FINISH");
        api_response_buffer[api_response_len] = '\0'; // Null-terminate the buffer
        break;
    default:
        break;
    }
    return ESP_OK;
}

void ota_task(void *pvParameter)
{
    ESP_LOGI(TAG, "Starting OTA Check. Current version: %s", CURRENT_FIRMWARE_VERSION);

    // 1. Fetch the latest release data from GitHub API
    // ---------------------------------------------------
    api_response_len = 0; // Reset buffer
    memset(api_response_buffer, 0, sizeof(api_response_buffer));

    char github_api_url[256];
    snprintf(github_api_url, sizeof(github_api_url), "https://api.github.com/repos/%s/%s/releases/latest", GITHUB_REPO_OWNER, GITHUB_REPO_NAME);

    esp_http_client_config_t api_config = {
        .url = github_api_url,
        .event_handler = _api_http_event_handler,
        .crt_bundle_attach = esp_crt_bundle_attach, // For HTTPS
        .user_agent = "esp32-ota-checker",
        .timeout_ms = 10000,
    };

    esp_http_client_handle_t client = esp_http_client_init(&api_config);
    esp_err_t err = esp_http_client_perform(client);

    if (err != ESP_OK) {
        ESP_LOGE(TAG, "Failed to fetch release info from GitHub: %s", esp_err_to_name(err));
        esp_http_client_cleanup(client);
        vTaskDelete(NULL);
        return;
    }
    esp_http_client_cleanup(client);

    // 2. Parse the JSON response
    // ---------------------------------------------------
    cJSON *root = cJSON_Parse(api_response_buffer);
    if (root == NULL) {
        ESP_LOGE(TAG, "Failed to parse JSON response.");
        vTaskDelete(NULL);
        return;
    }

    const cJSON *tag_name_json = cJSON_GetObjectItem(root, "tag_name");
    const cJSON *assets_json = cJSON_GetObjectItem(root, "assets");

    if (!cJSON_IsString(tag_name_json) || !cJSON_IsArray(assets_json) || cJSON_GetArraySize(assets_json) == 0) {
        ESP_LOGE(TAG, "Failed to find 'tag_name' or 'assets' in JSON.");
        cJSON_Delete(root);
        vTaskDelete(NULL);
        return;
    }

    char *latest_version = tag_name_json->valuestring;
    ESP_LOGI(TAG, "Latest version on GitHub: %s", latest_version);

    // 3. Compare versions
    // ---------------------------------------------------
    if (strcmp(latest_version, CURRENT_FIRMWARE_VERSION) == 0) {
        ESP_LOGI(TAG, "Firmware is already up to date.");
        cJSON_Delete(root);
        vTaskDelete(NULL);
        return;
    }

    ESP_LOGI(TAG, "New version available. Proceeding with update.");

    // 4. Get the firmware URL and perform the OTA update
    // ---------------------------------------------------
    const cJSON *asset = cJSON_GetArrayItem(assets_json, 0);
    const cJSON *download_url_json = cJSON_GetObjectItem(asset, "browser_download_url");

    if (!cJSON_IsString(download_url_json)) {
        ESP_LOGE(TAG, "Failed to find 'browser_download_url' in JSON.");
        cJSON_Delete(root);
        vTaskDelete(NULL);
        return;
    }

    char *firmware_url = download_url_json->valuestring;
    ESP_LOGI(TAG, "Firmware URL: %s", firmware_url);

    esp_http_client_config_t ota_http_config = {
        .url = firmware_url,
        .crt_bundle_attach = esp_crt_bundle_attach, // For HTTPS
        .timeout_ms = 10000,
    };

    esp_https_ota_config_t ota_config = {
        .http_config = &ota_http_config,
    };

    esp_err_t ret = esp_https_ota(&ota_config);
    if (ret == ESP_OK) {
        ESP_LOGI(TAG, "OTA Succeed, Rebooting...");
        esp_restart();
    } else {
        ESP_LOGE(TAG, "Firmware upgrade failed");
    }

    cJSON_Delete(root);
    vTaskDelete(NULL);
}

void ota_manager_check_for_update(void)
{
    xTaskCreate(&ota_task, "ota_task", 12288, NULL, 5, NULL);
}