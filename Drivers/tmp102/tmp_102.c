#include "tmp_102.h"

uint16_t twoComlementFunc(uint16_t signed_num_bin_arr, uint8_t size) {

	uint8_t flag = 0;

	uint8_t detect_index;
	
	for(uint8_t i = 0; i < size; i++) {
		
		if( ( flag == 1 ) && ( i > detect_index ) )	
			if( !( signed_num_bin_arr & (1 << i) ) )
				( signed_num_bin_arr |= (1 << i) ) ;
			else
				( signed_num_bin_arr &= ~(1 << i) ) ;
			
		if( ( ( signed_num_bin_arr & (1 << i) ) == 1 ) && ( flag != 1 ) ) {
		
			flag = 1;

			detect_index = i;
		}
		
	}
	
	return signed_num_bin_arr;
	
}
void tmp102_write(I2C_HandleTypeDef *i2c, uint8_t pointer_reg, uint8_t reg[2]) {

	uint8_t data[3];
	
	data[0] = pointer_reg;
	
	data[1] = reg[0];
	
	data[2] = reg[1];
	
	HAL_I2C_Master_Transmit(i2c, TMP_102_ADRESS, data, 3, 100);
}
	
void tmp102_read(I2C_HandleTypeDef *i2c, uint8_t pointer_reg, uint8_t *read_val_reg) {
	
	HAL_I2C_Mem_Read(i2c, TMP_102_ADRESS, pointer_reg, 1, read_val_reg, 2, 100);
}	
double tmp102_temperature_read(I2C_HandleTypeDef *i2c) {

	uint8_t temparature_val[2];
	
	uint8_t buf[2];
	
	double temparature_result; 
	
	tmp102_read(i2c, POINTER_REGISTER_TEMP, buf);
	
	temparature_val[0] = ( ( buf[0] << 4  ) | ( buf[1] >> 4 ) );
	
	temparature_val[1] = ( buf[0] >> 4 );
	
	if( temparature_val[1] & 0x08 ) {
		
		temparature_result = ( ( temparature_val[1] << 8 ) | temparature_val[0] ) ;
		
		temparature_result = ( twoComlementFunc( (uint16_t)temparature_result, 12) * 0.0625 );
	
	}
	else
		temparature_result = ( ( ( temparature_val[1] << 8 ) | temparature_val[0] ) * 0.0625 ) ;
	
	return temparature_result;
}

void tmp102_conf_shutdown_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t is_shutdown_mod) {

	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	if(is_shutdown_mod == SET)
		config_reg[0] |= CONF_REG_SHUTDOWN_MODE;
	else
		config_reg[0] &= ~CONF_REG_SHUTDOWN_MODE;	
	
	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}

void tmp102_conf_thermostat_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t thermostat_mod_select) {

	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	if(thermostat_mod_select == THERMOSTAT_MODE_INTERRUPT )
		config_reg[0] |= CONF_REG_THERMOSTAT_MODE; //tmp102 in interrupt mode 
	else if(thermostat_mod_select == THERMOSTAT_MODE_COMPARATOR)
		config_reg[0] &= ~CONF_REG_THERMOSTAT_MODE; //tmp102 in comparator mode
 	
	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}
	
void tmp102_conf_polarity_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t is_polarity_mod) {

	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	if(is_polarity_mod == POLARITY_MODE_ALERT_ACTIVE_HIGH)
		config_reg[0] |= CONF_REG_POLARITY_MODE; //tmp102 alert active high
	else if(is_polarity_mod == POLARITY_MODE_ALERT_ACTIVE_LOW)
		config_reg[0] &= ~CONF_REG_POLARITY_MODE; //tmp102 alert active low (default)

	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}

void tmp102_conf_consecutive_fault_count(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t consecutive_fault_count) {

	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	//Please set consecutive fault counts to active alert pin alarm
	config_reg[0] = ( CONF_REG_CONS_FAULT_MASK(config_reg[0]) | consecutive_fault_count );
	
	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}

void tmp102_conf_converter_resolution(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
	uint8_t converter_resolution) {
	
	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
		
	config_reg[0] = ( CONF_REG_CONV_RES_MASK(config_reg[0]) | (converter_resolution << 5) );
		
	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}
	
void tmp102_conf_os_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
	uint8_t is_os_mode_set) {

	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
		
	if(is_os_mode_set)
		config_reg[0] |= CONF_REG_ONE_SHOT_CONV;
	else
		config_reg[0] &= CONF_REG_CONT_CONV;

	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}
	
uint8_t tmp102_get_oneshot_mode_status(I2C_HandleTypeDef *i2c, uint8_t *config_reg) {

	tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	return ( !( ( config_reg[0] &= CONF_REG_ONE_SHOT_CONV ) >> 7 ) );
}

void tmp102_conf_extended_mode(I2C_HandleTypeDef *i2c, uint8_t *config_reg,\
uint8_t is_extended_mode_set) {

	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	if(	is_extended_mode_set )
		config_reg[1] |= CONF_REG_EM;
	else
		config_reg[1] &= ~CONF_REG_EM;
	
	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}

uint8_t tmp102_get_alert_status(I2C_HandleTypeDef *i2c, uint8_t *config_reg) {

	tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	if ( config_reg[0] & CONF_REG_POLARITY_MODE )	
		return ( ( config_reg[1] &= CONF_REG_AL ) >> 5 );
	else if( !( config_reg[0] & CONF_REG_POLARITY_MODE ) )
		return !( ( config_reg[1] &= CONF_REG_AL ) >> 5 );
	
	return 2;
}

void tmp102_conf_conversion_rate(I2C_HandleTypeDef *i2c, uint8_t *config_reg, uint8_t conver_rate) {

	//tmp102_read(i2c, POINTER_REGISTER_CONF, config_reg);
	
	config_reg[1] = ( CONF_REG_CONV_RATE_MSK( config_reg[1] ) | ( conver_rate << 6 ) ); 

	//tmp102_write(i2c, POINTER_REGISTER_CONF, config_reg);
}

void tmp102_tlow_and_thigh_set(I2C_HandleTypeDef *i2c, int16_t t_low_val,\
int16_t t_high_val) {

	uint8_t tlow_arr[2];
	uint8_t thigh_arr[2];
	
	t_high_val = ( t_high_val << 4 );
	t_low_val =  ( t_low_val << 4 );
	
	thigh_arr[0] = (t_high_val / 256);
	thigh_arr[1] = (t_high_val % 256);
	
	tlow_arr[0] = (t_low_val / 256);
	tlow_arr[1] = (t_low_val % 256);

	tmp102_write(i2c, POINTER_REGISTER_THIGH, thigh_arr);
	
	tmp102_write(i2c, POINTER_REGISTER_TLOW, tlow_arr);

}

double get_tlow_val(I2C_HandleTypeDef *i2c) {

  uint8_t t_low[2];
	
	uint8_t temparature_val[2];
	
	double temparature_result; 
	
	tmp102_read(i2c, POINTER_REGISTER_TLOW, t_low);
	
	temparature_val[0] = ( ( ( t_low[0] << 4 ) & 0xF0 ) | ( t_low[1] >> 4 ) );
	
	temparature_val[1] = ( t_low[0] >> 4 );

	if( temparature_val [1] >>  7 ) {
		
		temparature_result = ( ( temparature_val[1] << 8 ) | ( temparature_val[0] ) ) ;
		
		temparature_result = ( twoComlementFunc( (uint16_t)temparature_result, 12) * 0.0625 );
	
	}
	else
		temparature_result = ( ( temparature_val[1] << 8 ) | ( temparature_val[0] ) ) ;

	return temparature_result;

}

double get_thigh_val(I2C_HandleTypeDef *i2c) {

  uint8_t t_high[2];
	
	uint8_t temparature_val[2];
	
	double temparature_result; 
	
	tmp102_read(i2c, POINTER_REGISTER_THIGH, t_high);
	
	temparature_val[0] = ( ( ( t_high[0] << 4 ) & 0xF0 ) | ( t_high[1] >> 4 ) );
	
	temparature_val[1] = ( t_high[0] >> 4 );

	if( temparature_val [1] >>  7 ) {
		
		temparature_result = ( ( temparature_val[1] << 8 ) | ( temparature_val[0] ) ) ;
		
		temparature_result = ( twoComlementFunc( (uint16_t)temparature_result, 12) * 0.0625 );
	
	}
	else
		temparature_result = ( ( temparature_val[1] << 8 ) | ( temparature_val[0] ) ) ;

	return temparature_result;

}
void tmp102_init(I2C_HandleTypeDef *i2c) {
	
	HAL_Delay(100);

	uint8_t temp_config_reg[2];
	
	tmp102_read(i2c, POINTER_REGISTER_CONF, temp_config_reg);
	
	tmp102_conf_shutdown_mode(i2c, temp_config_reg, RESET);
	
	tmp102_conf_thermostat_mode(i2c, temp_config_reg, THERMOSTAT_MODE_COMPARATOR);
	
	tmp102_conf_polarity_mode(i2c, temp_config_reg, POLARITY_MODE_ALERT_ACTIVE_LOW);
	
	tmp102_conf_consecutive_fault_count(i2c, temp_config_reg, CONF_REG_CONS_FAULT_6);
	
	tmp102_conf_converter_resolution(i2c, temp_config_reg, 0x03); //To set converter resolution as 12 bits
	
	tmp102_conf_os_mode(i2c, temp_config_reg, RESET);
	
	tmp102_conf_extended_mode(i2c, temp_config_reg, RESET);
	
	tmp102_conf_conversion_rate(i2c, temp_config_reg, CONF_REG_CONV_RATE_4);
	
	tmp102_write(i2c, POINTER_REGISTER_CONF, temp_config_reg);
	
	tmp102_tlow_and_thigh_set(i2c, 5, 50);
}
