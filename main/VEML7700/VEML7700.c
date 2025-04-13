#include "VEML7700.h"
#include "esp_log.h"

static const char *TAG = "VEML7700";

static esp_err_t i2c_write_reg(i2c_port_t i2c_port, uint8_t reg, uint16_t data) {
    uint8_t write_buf[3] = {reg, (uint8_t)(data & 0xFF), (uint8_t)(data >> 8)};
    return i2c_master_write_to_device(i2c_port, VEML7700_I2C_ADDR, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);
}

static esp_err_t i2c_read_reg(i2c_port_t i2c_port, uint8_t reg, uint16_t *data) {
    uint8_t read_buf[2];
    esp_err_t ret = i2c_master_write_read_device(i2c_port, VEML7700_I2C_ADDR, &reg, 1, read_buf, 2, 1000 / portTICK_PERIOD_MS);
    if (ret == ESP_OK) {
        *data = (read_buf[1] << 8) | read_buf[0];
    }
    return ret;
}

esp_err_t VEML7700_Init(i2c_port_t i2c_port) {
    // Configuração padrão: ganho 1x, tempo de integração 100ms, sem shutdown
    uint16_t config = 0x0000; // Ganho 1x (bits 12:11 = 00), IT 100ms (bits 9:6 = 0000)
    esp_err_t ret = i2c_write_reg(i2c_port, VEML7700_REG_ALS_CONF, config);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao inicializar VEML7700");
    }
    return ret;
}

esp_err_t VEML7700_Read_Lux(float *lux) {
    uint16_t raw_data;
    esp_err_t ret = i2c_read_reg(I2C_NUM_0, VEML7700_REG_ALS_DATA, &raw_data);
    if (ret == ESP_OK) {
        // Resolução padrão para ganho 1x e IT 100ms é 0.0576 lux por contagem
        *lux = raw_data * 0.0576;
    } else {
        ESP_LOGE(TAG, "Falha ao ler dados do VEML7700");
    }
    return ret;
}