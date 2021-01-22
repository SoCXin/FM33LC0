#include "I2CTest.h"




uint8_t readdata[3];
uint8_t Test_I2C(void)
{
	uint8_t Result = 0;
		
    
    while(!FL_I2C_Slave_IsActiveFlag_AddressMatch(I2C));
	readdata[0] = FL_I2C_Slave_ReadRXBuff(I2C);
	FL_I2C_Slave_ClearFlag_AddressMatch(I2C);
	FL_I2C_Slave_ClearFlag_RXComplete(I2C);
	
	while(!FL_I2C_Slave_IsActiveFlag_RXComplete(I2C));
	readdata[1] = FL_I2C_Slave_ReadRXBuff(I2C);
	FL_I2C_Slave_ClearFlag_RXComplete(I2C);
	
	while(!FL_I2C_Slave_IsActiveFlag_RXComplete(I2C));
	readdata[2] = FL_I2C_Slave_ReadRXBuff(I2C);
	FL_I2C_Slave_ClearFlag_RXComplete(I2C);
	
	
	return Result;
}
