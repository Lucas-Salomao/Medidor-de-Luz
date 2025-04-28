#include "lvgl.h"
#include "wifi_settings_screen.h"
#include "Wireless.h"
#include "esp_log.h"
#include "Screens.h"

static lv_obj_t *wifi_screen = NULL;
static lv_obj_t *ssid_dropdown = NULL;
static lv_obj_t *password_input = NULL;
static lv_obj_t *status_label = NULL;

// Forward declarations
static void back_btn_event_handler(lv_event_t *e);
static void connect_btn_event_handler(lv_event_t *e);
static void refresh_btn_event_handler(lv_event_t *e);
static void populate_wifi_dropdown(void *data);

void wifi_settings_screen_init(void) {
    if (wifi_screen == NULL) {
        wifi_screen = lv_obj_create(NULL);
        lv_obj_set_style_bg_color(wifi_screen, lv_color_white(), LV_PART_MAIN);
        
        // Title
        lv_obj_t *title = lv_label_create(wifi_screen);
        lv_label_set_text(title, "WI-FI SETTINGS");
        lv_obj_set_style_text_font(title, &lv_font_montserrat_16, 0);
        lv_obj_set_style_text_color(title, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
        
        // Back button
        lv_obj_t *home_btn = lv_btn_create(wifi_screen);
        lv_obj_set_size(home_btn, 40, 40);
        lv_obj_align(home_btn, LV_ALIGN_TOP_LEFT, 5, 5);
        lv_obj_add_event_cb(home_btn, back_btn_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_t *gear_icon = lv_label_create(home_btn);
        lv_label_set_text(gear_icon, LV_SYMBOL_LEFT);
        lv_obj_center(gear_icon);
        
        // SSID Label
        lv_obj_t *ssid_label = lv_label_create(wifi_screen);
        lv_label_set_text(ssid_label, "Network (SSID):");
        lv_obj_set_style_text_color(ssid_label, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(ssid_label, LV_ALIGN_TOP_LEFT, 20, 60);
        
        // SSID Dropdown
        ssid_dropdown = lv_dropdown_create(wifi_screen);
        lv_obj_set_size(ssid_dropdown, 200, 40);
        lv_obj_align(ssid_dropdown, LV_ALIGN_TOP_LEFT, 20, 80);
        
        // Refresh button
        lv_obj_t *refresh_btn = lv_btn_create(wifi_screen);
        lv_obj_set_size(refresh_btn, 40, 40);
        lv_obj_align(refresh_btn, LV_ALIGN_TOP_RIGHT, -5, 5);
        lv_obj_add_event_cb(refresh_btn, refresh_btn_event_handler, LV_EVENT_CLICKED, NULL);
        lv_obj_t *refresh_icon = lv_label_create(refresh_btn);
        lv_label_set_text(refresh_icon, LV_SYMBOL_REFRESH);
        lv_obj_center(refresh_icon);
        
        // Password Label
        lv_obj_t *pwd_label = lv_label_create(wifi_screen);
        lv_label_set_text(pwd_label, "Password:");
        lv_obj_set_style_text_color(pwd_label, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(pwd_label, LV_ALIGN_TOP_LEFT, 20, 130);
        
        // Password Input
        password_input = lv_textarea_create(wifi_screen);
        lv_textarea_set_password_mode(password_input, true);
        lv_textarea_set_one_line(password_input, true);
        lv_obj_set_size(password_input, 200, 40);
        lv_obj_align(password_input, LV_ALIGN_TOP_LEFT, 20, 155);
        
        // Connect Button
        lv_obj_t *connect_btn = lv_btn_create(wifi_screen);
        lv_obj_set_size(connect_btn, 200, 50);
        lv_obj_align(connect_btn, LV_ALIGN_TOP_LEFT, 20, 210);
        lv_obj_add_event_cb(connect_btn, connect_btn_event_handler, LV_EVENT_CLICKED, NULL);
        
        lv_obj_t *connect_label = lv_label_create(connect_btn);
        lv_label_set_text(connect_label, "Connect");
        lv_obj_center(connect_label);
        
        // Status label (for connection status/error messages)
        status_label = lv_label_create(wifi_screen);
        lv_label_set_text(status_label, "");
        lv_obj_set_style_text_color(status_label, lv_color_black(), LV_PART_MAIN);
        lv_obj_align(status_label, LV_ALIGN_BOTTOM_MID, 0, -10);
        
        // Populate dropdown with dummy values initially
        lv_dropdown_set_options(ssid_dropdown, "Scanning...");
        
        // Schedule Wi-Fi scan to populate the dropdown
        // This will be called when the screen is loaded
    }
}

void wifi_settings_screen_load(void) {
    if (wifi_screen == NULL) {
        wifi_settings_screen_init();
    }
    
    lv_scr_load_anim(wifi_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
    
    // Refresh Wi-Fi networks when screen is loaded
    refresh_btn_event_handler(NULL);
}

static void back_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Back button clicked");
    if (config_screen != NULL) {
        lv_scr_load_anim(config_screen, LV_SCR_LOAD_ANIM_FADE_ON, 500, 0, false);
    }
}

static void connect_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Connect button clicked");
    
    char selected_ssid[64];
    char password[64];
    
    // Get selected SSID
    uint16_t selected_id = lv_dropdown_get_selected(ssid_dropdown);
    lv_dropdown_get_selected_str(ssid_dropdown, selected_ssid, sizeof(selected_ssid));
    
    // Get password
    const char *pwd_text = lv_textarea_get_text(password_input);
    strncpy(password, pwd_text, sizeof(password) - 1);
    password[sizeof(password) - 1] = '\0';
    
    ESP_LOGI(TAG, "Connecting to SSID: %s", selected_ssid);
    
    // Here you would call your Wi-Fi connection function
    // For example:
    // bool connected = connect_to_wifi(selected_ssid, password);
    
    // For demonstration, we'll simulate a connection
    bool connected = true; // Replace with actual connection attempt
    
    if (connected) {
        lv_label_set_text(status_label, "Connected successfully!");
        lv_obj_set_style_text_color(status_label, lv_color_make(0, 128, 0), LV_PART_MAIN); // Green
    } else {
        lv_label_set_text(status_label, "Connection failed. Please try again.");
        lv_obj_set_style_text_color(status_label, lv_color_make(255, 0, 0), LV_PART_MAIN); // Red
    }
}

static void refresh_btn_event_handler(lv_event_t *e) {
    ESP_LOGI(TAG, "Refresh button clicked");
    
    // Show scanning message
    lv_dropdown_set_options(ssid_dropdown, "Scanning...");
    lv_label_set_text(status_label, "Scanning for networks...");
    lv_obj_set_style_text_color(status_label, lv_color_black(), LV_PART_MAIN);
    
    // Start Wi-Fi scan in a separate task
    // This is a simplified example, you should adapt it to your application
    xTaskCreate(
        scan_wifi_task,
        "wifi_scan_task",
        4096,
        NULL,
        5,
        NULL
    );
}

// Task to scan for Wi-Fi networks
static void scan_wifi_task(void *pvParameters) {
    // Call your Wi-Fi scan function
    uint16_t ap_count = WIFI_Scan();
    
    // In a real application, you would get the scan results and
    // update the UI. Here we'll simulate some networks
    
    // This needs to run on the main LVGL task
    lv_async_call(populate_wifi_dropdown, NULL);
    
    vTaskDelete(NULL);
}

// This function must be called from the main LVGL task
static void populate_wifi_dropdown(void *data) {
    // In a real application, you would get actual scan results
    // For demo purpose, we'll create a list of dummy networks
    
    // Clear status message
    lv_label_set_text(status_label, "");
    
    // Check if we actually found networks
    if (WIFI_NUM == 0) {
        lv_dropdown_set_options(ssid_dropdown, "No networks found");
        lv_label_set_text(status_label, "No Wi-Fi networks detected");
        return;
    }
    
    // Create a buffer for the options string
    // Each option needs to be separated by \n
    char *buffer = malloc(WIFI_NUM * 32 + 1); // Assuming max 32 chars per SSID
    if (buffer == NULL) {
        ESP_LOGE(TAG, "Failed to allocate memory for dropdown options");
        return;
    }
    
    buffer[0] = '\0'; // Initialize empty string
    
    // In a real application, you would get actual network names
    // For demo, we'll use dummy names
    char temp[64];
    for (int i = 0; i < WIFI_NUM; i++) {
        snprintf(temp, sizeof(temp), "Network_%d", i+1);
        
        // Add to options string with \n separator
        if (i > 0) {
            strcat(buffer, "\n");
        }
        strcat(buffer, temp);
    }
    
    // Update dropdown options
    lv_dropdown_set_options(ssid_dropdown, buffer);
    
    // Free the buffer
    free(buffer);
    
    ESP_LOGI(TAG, "Found %d networks", WIFI_NUM);
}