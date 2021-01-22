#include "main.h"
#include "user_init.h"

#define LENGTH  256
uint8_t fBuff[LENGTH];

extern ErrorStatus FL_FLASH_Write_Dma(FLASH_Type* FLASHx, uint32_t address, uint32_t *data);
extern ErrorStatus FL_FLASH_Read_Dma(FLASH_Type* FLASHx, uint32_t address, uint32_t *data, uint16_t length);

void FlashTest(void)
{
    FL_FLASH_PageErase(FLASH, 0x00004000);
    memset(fBuff, 0x00, LENGTH);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, (uint32_t *)fBuff, LENGTH/4);
    memset(fBuff, 0x55, LENGTH);
    FL_FLASH_Write_Dma(FLASH, 0x00004000, (uint32_t *)fBuff);
    memset(fBuff, 0x00, LENGTH);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, (uint32_t *)fBuff, LENGTH/4);
    
    FL_FLASH_PageErase(FLASH, 0x00004000);
    memset(fBuff, 0x00, LENGTH);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, (uint32_t *)fBuff, LENGTH/4);
    memset(fBuff, 0xAA, LENGTH);
    FL_FLASH_Write_Dma(FLASH, 0x00004000, (uint32_t *)fBuff);
    memset(fBuff, 0x00, LENGTH);
    FL_FLASH_Read_Dma(FLASH, 0x00004000, (uint32_t *)fBuff, LENGTH/4);
    
    FL_FLASH_PageErase(FLASH, 0x00004000);
}

int main(void)
{
    /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
    /* SHOULD BE KEPT!!! */
    MF_Clock_Init();
    
    /* Configure the system clock */
    /* SHOULD BE KEPT!!! */
    MF_SystemClock_Config();
    
    /* Initialize all configured peripherals */
    /* SHOULD BE KEPT!!! */
    MF_Config_Init();
    
    UserInit();
    
    FlashTest();
    
    while(1)
    {     
        LED0_TOG();
        DelayMs(1000);
    }
}


