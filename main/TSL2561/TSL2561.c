#include "TSL2561.h"
#include "esp_log.h"

static const char *TAG = "TSL2561";

static esp_err_t i2c_write_reg(i2c_port_t i2c_port, uint8_t reg, uint8_t data) {
    uint8_t write_buf[2] = {0x80 | reg, data}; // 0x80 para comando de registrador
    return i2c_master_write_to_device(i2c_port, TSL2561_I2C_ADDR, write_buf, sizeof(write_buf), 1000 / portTICK_PERIOD_MS);
}

static esp_err_t i2c_read_reg(i2c_port_t i2c_port, uint8_t reg, uint16_t *data) {
    uint8_t read_buf[2];
    uint8_t reg_cmd = 0x80 | reg; // 0x80 para comando de registrador
    esp_err_t ret = i2c_master_write_read_device(i2c_port, TSL2561_I2C_ADDR, &reg_cmd, 1, read_buf, 2, 1000 / portTICK_PERIOD_MS);
    if (ret == ESP_OK) {
        *data = (read_buf[1] << 8) | read_buf[0];
    }
    return ret;
}

esp_err_t TSL2561_Init(i2c_port_t i2c_port) {
    // Liga o sensor (Power ON)
    esp_err_t ret = i2c_write_reg(i2c_port, TSL2561_REG_CONTROL, 0x03);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao ligar o TSL2561");
        return ret;
    }

    // Configuração: ganho 1x, tempo de integração 402ms
    ret = i2c_write_reg(i2c_port, TSL2561_REG_TIMING, 0x02); // 0x02 = 402ms, ganho 1x
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao configurar o TSL2561");
    }
    return ret;
}

esp_err_t TSL2561_Read_Lux(float *lux) {
    uint16_t ch0, ch1;
    esp_err_t ret;

    // Lê canal 0 (visível + IR)
    ret = i2c_read_reg(I2C_NUM_0, TSL2561_REG_DATA0, &ch0);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao ler canal 0");
        return ret;
    }

    // Lê canal 1 (IR)
    ret = i2c_read_reg(I2C_NUM_0, TSL2561_REG_DATA1, &ch1);
    if (ret != ESP_OK) {
        ESP_LOGE(TAG, "Falha ao ler canal 1");
        return ret;
    }

    // Cálculo simplificado de lux (baseado em ganho 1x e 402ms)
    if (ch0 == 0) {
        *lux = 0.0;
        return ESP_OK;
    }

    float ratio = (float)ch1 / (float)ch0;
    if (ratio <= 0.5) {
        *lux = 0.0304 * ch0 - 0.0272 * ch0 * ratio;
    } else if (ratio <= 0.61) {
        *lux = 0.0224 * ch0 - 0.031 * ch1;
    } else if (ratio <= 0.80) {
        *lux = 0.0128 * ch0 - 0.0153 * ch1;
    } else if (ratio <= 1.30) {
        *lux = 0.00146 * ch0 - 0.00112 * ch1;
    } else {
        *lux = 0.0; // Fora da faixa válida
    }

    // Ajuste para ganho 1x e 402ms (resolução base)
    *lux *= 1.0; // Multiplicador seria ajustado se ganho ou tempo fossem diferentes

    return ESP_OK;
}