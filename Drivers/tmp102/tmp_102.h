#ifndef __TMP_102_H
#define __TMP_102_H

#include "stm32f4xx_hal.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "main.h"

#define TMP_102_ADRESS 0x90 //ADD0 is connected to ground. Write tmp102 is (0x48 << 1) = 0x90, read tmp102 is 0x91 

//Conversion rate set by CR1 and CR0 bits

#define POINTER_REGISTER_TEMP  0x00
#define POINTER_REGISTER_CONF  0x01
#define POINTER_REGISTER_TLOW  0x02
#define POINTER_REGISTER_THIGH 0x03

//Configuration register field values
#define CONF_REG_SHUTDOWN_MODE				 0x01 //Shutdown-mode(device shutdown when current conv is completed)
#define CONF_REG_THERMOSTAT_MODE			 0x02 //Thermostat mode(Device in interrupt mode, otherwise comparator mode)
#define CONF_REG_POLARITY_MODE				 0x04	//Polarity mode (ALERT pin is active-high, otherwise active-low)
#define CONF_REG_CONS_FAULT_MASK(NUM)	 ( NUM & ~0x18 ) //To evaluate current consecutive area of configuration register
#define CONF_REG_CONS_FAULT_1					 ( 0x00	<< 3 ) //Consecutive fault count 1
#define CONF_REG_CONS_FAULT_2					 ( 0x01	<< 3 ) //Consecutive fault count 2
#define CONF_REG_CONS_FAULT_4					 ( 0x02	<< 3 ) //Consecutive fault count 4
#define CONF_REG_CONS_FAULT_6					 ( 0x03	<< 3 ) //Consecutive fault count 6
#define CONF_REG_CONV_RES_MASK(NUM)	   ( NUM & ~0x60 ) 
#define CONF_REG_ONE_SHOT_CONV							 0x80 //To configure on-shot mode conversion mode
#define CONF_REG_CONT_CONV									 ~0x80 //To configure continuous conversion mode
#define CONF_REG_EM										 0x10 //To configure extended mode
#define CONF_REG_AL										 0x20	//Reading the AL bit to learn comparator status
#define CONF_REG_CONV_RATE_MSK(NUM)    ( NUM & ~0xC0)
#define CONF_REG_CONV_RATE_0_25				 0x00 //Conversion Rate 0.25Hz
#define CONF_REG_CONV_RATE_1					 0x01 //Conversion Rate 1 Hz
#define CONF_REG_CONV_RATE_4					 0x02 //Conversion Rate 4 Hz (default)
#define CONF_REG_CONV_RATE_8					 0x03 //Conversion Rate 8 Hz

//Configration register logic set
#define THERMOSTAT_MODE_INTERRUPT  1
#define THERMOSTAT_MODE_COMPARATOR 0
#define POLARITY_MODE_ALERT_ACTIVE_LOW 0
#define POLARITY_MODE_ALERT_ACTIVE_HIGH 1

uint16_t twoComlementFunc(uint16_t signed_num_bin_arr, uint8_t size);

void tmp102_write(I2C_HandleTypeDef *i2c, uint8_t pointer_reg, uint8_t reg[2]);
	
void tmp102_read(I2C_HandleTypeDef *i2c, uint8_t pointer_reg,\
	uint8_t *read_val_reg);

uint8_t tmp102_temperature_read(I2C_HandleTypeDef *i2c, double *temparature_result);

void tmp102_conf_shutdown_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
	uint8_t is_shutdown_mod);

void tmp102_conf_thermostat_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t thermostat_mod_select);

void tmp102_conf_polarity_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t is_polarity_mod);

void tmp102_conf_consecutive_fault_count(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t consecutive_fault_count);

void tmp102_conf_converter_resolution(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t converter_resolution);

void tmp102_conf_os_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
	uint8_t is_os_mode_set);

uint8_t tmp102_get_oneshot_mode_status(I2C_HandleTypeDef *i2c, uint8_t *config_reg);

void tmp102_conf_extended_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t is_extended_mode_set);

uint8_t tmp102_get_alert_status(I2C_HandleTypeDef *i2c, uint8_t *config_reg);

void tmp102_conf_conversion_rate(I2C_HandleTypeDef *i2c, uint8_t *config_reg, uint8_t conver_rate);

void tmp102_tlow_and_thigh_set(I2C_HandleTypeDef *i2c, int16_t t_low_val,\
int16_t t_high_val);

double get_tlow_val(I2C_HandleTypeDef *i2c);

double get_thigh_val(I2C_HandleTypeDef *i2c);

void tmp102_init(I2C_HandleTypeDef *i2c);

#endif
