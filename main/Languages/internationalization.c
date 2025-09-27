#include "internationalization.h"

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
    "Language:"
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
    "Idioma:"
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
    "Idioma:"
};


void set_language(language_t language) {
    current_language = language;
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