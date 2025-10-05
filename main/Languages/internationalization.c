#include "internationalization.h"
#include "nvs_flash.h"
#include "nvs.h"
#include "esp_log.h"
#include "../TELAS/Screens.h"

static const char *NVS_TAG = "NVS";
#define NVS_NAMESPACE "storage"
#define LANG_KEY "language"

// Defina o idioma padrão como Português do Brasil
static language_t current_language = LANG_PT_BR; 

static const char* strings_en[] = {
    "CLOCK SETTINGS",
    "WI-FI SETTINGS",
    "FLUORIMETER",
    "SETTINGS",
    "Place the blank for zeroing",
    "Insert the sample",
    "Measurement completed",
    "Zero",
    "Measure",
    "Save",
    "Repeat",
    "Saved!",
    "ID cannot be empty!",
    "SD Card Error!",
    "Enter Sample ID:",
    "ID...",
    "Connecting...",
    "Connected successfully!",
    "Connection failed. Please try again.",
    "Scanning for networks...",
    "No networks found",
    "Memory error",
    "Network (SSID):",
    "Password:",
    "Connect",
    "Scanning...",
    "No Wi-Fi networks detected",
    "Language:",
    "Zeroing",
    "Measuring",
    "Error zeroing!",
    "Read Error!",
    "Time:",
    "Date:",
    "Lux: ",
    "SampleID,Measurement,Time",
    "Portuguese",
    "English",
    "Spanish"
};

static const char* strings_es[] = {
    "AJUSTES DE RELOJ",
    "AJUSTES DE WI-FI",
    "FLUORÍMETRO",
    "AJUSTES",
    "Coloque el blanco para poner a cero",
    "Inserte la muestra",
    "Medición completada",
    "Cero",
    "Medir",
    "Guardar",
    "Repetir",
    "¡Guardado!",
    "¡La identificación no puede estar vacía!",
    "¡Error en la tarjeta SD!",
    "Introduzca el ID de la muestra:",
    "ID...",
    "Conectando...",
    "¡Conectado exitosamente!",
    "Falló la conexión. Por favor, inténtelo de nuevo.",
    "Buscando redes...",
    "No se encontraron redes",
    "Error de memoria",
    "Red (SSID):",
    "Contraseña:",
    "Conectar",
    "Buscando...",
    "No se detectaron redes Wi-Fi",
    "Idioma:",
    "Calibrando",
    "Midiendo",
    "¡Error al calibrar!",
    "¡Error de lectura!",
    "Hora:",
    "Fecha:",
    "Lux: ",
    "IDMuestra,Medicion,Tiempo",
    "Portugués",
    "Inglés",
    "Español"
};

// Adicionada a lista de strings para Português (BR)
static const char* strings_pt_br[] = {
    "CONFIGURAÇÕES DO RELÓGIO",
    "CONFIGURAÇÕES DE WI-FI",
    "FLUORÍMETRO",
    "CONFIGURAÇÕES",
    "Coloque o branco para zerar",
    "Insira a amostra",
    "Medição concluída",
    "Zerar",
    "Medir",
    "Salvar",
    "Repetir",
    "Salvo!",
    "A ID não pode estar vazia!",
    "Erro no cartão SD!",
    "Digite o ID da amostra:",
    "ID...",
    "Conectando...",
    "Conectado com sucesso!",
    "Falha na conexão. Tente novamente.",
    "Buscando redes...",
    "Nenhuma rede encontrada",
    "Erro de memória",
    "Rede (SSID):",
    "Senha:",
    "Conectar",
    "Buscando...",
    "Nenhuma rede Wi-Fi detectada",
    "Idioma:",
    "Zerando",
    "Medindo",
    "Erro ao zerar!",
    "Erro de leitura!",
    "Hora:",
    "Data:",
    "Lux: ",
    "ID_Amostra,Medicao,Hora",
    "Português",
    "Inglês",
    "Espanhol"
};

void save_language_to_nvs(language_t language) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READWRITE, &nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(NVS_TAG, "Error opening NVS handle: %s", esp_err_to_name(err));
        return;
    }

    err = nvs_set_u8(nvs_handle, LANG_KEY, (uint8_t)language);
    if (err != ESP_OK) {
        ESP_LOGE(NVS_TAG, "Failed to write language to NVS: %s", esp_err_to_name(err));
    } else {
        ESP_LOGI(NVS_TAG, "Language setting saved to NVS");
    }

    nvs_commit(nvs_handle);
    nvs_close(nvs_handle);
}

void initialize_language_from_nvs(void) {
    nvs_handle_t nvs_handle;
    esp_err_t err = nvs_open(NVS_NAMESPACE, NVS_READONLY, &nvs_handle);
    if (err != ESP_OK) {
        ESP_LOGE(NVS_TAG, "Error opening NVS handle for reading: %s", esp_err_to_name(err));
        set_language(LANG_PT_BR); // Default language
        return;
    }

    uint8_t lang_u8;
    err = nvs_get_u8(nvs_handle, LANG_KEY, &lang_u8);
    if (err == ESP_OK) {
        current_language = (language_t)lang_u8;
        ESP_LOGI(NVS_TAG, "Language loaded from NVS: %d", current_language);
    } else if (err == ESP_ERR_NVS_NOT_FOUND) {
        ESP_LOGI(NVS_TAG, "Language not found in NVS, using default.");
        current_language = LANG_PT_BR; // Default language
    } else {
        ESP_LOGE(NVS_TAG, "Error reading language from NVS: %s", esp_err_to_name(err));
        current_language = LANG_PT_BR; // Default on error
    }
    nvs_close(nvs_handle);
}

void set_language(language_t language) {
    current_language = language;
    save_language_to_nvs(language);
    update_all_screens_text();
}

language_t get_language(void) {
    return current_language;
}

const char* get_string(string_id_t id) {
    if (current_language == LANG_ES) {
        return strings_es[id];
    }
    if (current_language == LANG_PT_BR) {
        return strings_pt_br[id];
    }
    return strings_en[id];
}

const char* get_language_code(void) {
    if (current_language == LANG_ES) {
        return "es";
    }
    if (current_language == LANG_PT_BR) {
        return "pt_br";
    }
    return "en";
}