#include "I2CTest.h"
#include "user_init.h"


uint8_t Test_I2C(void)
{

	uint8_t writedata[1]={0x24};
	uint8_t Result = 0;
	uint8_t tmp;
		
	while(!FL_I2C_Slave_IsActiveFlag_AddressMatch(I2C));
	tmp = FL_I2C_Slave_ReadRXBuff(I2C);
	FL_I2C_Slave_ClearFlag_AddressMatch(I2C);
	FL_I2C_Slave_ClearFlag_RXComplete(I2C);
	
	FL_I2C_Slave_WriteTXBuff(I2C,writedata[0]);
	while(!FL_I2C_Slave_IsActiveFlag_TXComplete(I2C));
	FL_I2C_Slave_ClearFlag_TXComplete(I2C);
	
	
	
	return Result;
}

