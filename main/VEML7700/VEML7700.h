#ifndef VEML7700_H
#define VEML7700_H

#include "driver/i2c.h"

#define VEML7700_I2C_ADDR 0x10  // Endereço I2C fixo do VEML7700

// Registradores do VEML7700
#define VEML7700_REG_ALS_CONF 0x00  // Configuração do ALS
#define VEML7700_REG_ALS_DATA 0x04  // Dados de luz ambiente

esp_err_t VEML7700_Init(i2c_port_t i2c_port);
esp_err_t VEML7700_Read_Lux(float *lux);

#endif