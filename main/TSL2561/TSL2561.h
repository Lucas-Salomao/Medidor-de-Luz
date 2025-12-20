#ifndef TSL2561_H
#define TSL2561_H

#include "driver/i2c.h"

#define TSL2561_I2C_ADDR 0x39  // Endereço I2C padrão (ADDR flutuante)

#define TSL2561_REG_CONTROL 0x00  // Controle (power on/off)
#define TSL2561_REG_TIMING  0x01  // Configuração de ganho e tempo de integração
#define TSL2561_REG_DATA0   0x0C  // Dados do canal 0 (visível + IR)
#define TSL2561_REG_DATA1   0x0E  // Dados do canal 1 (IR)

esp_err_t TSL2561_Init(i2c_port_t i2c_port);
esp_err_t TSL2561_Read_Lux(float *lux);

#endif