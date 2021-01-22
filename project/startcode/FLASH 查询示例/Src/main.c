#include "main.h"
#include "user_init.h"

uint32_t ProgAddr = 0x00004000;
uint32_t DataToWrite[512];

void FlashTest(void)
{	
	FL_FLASH_PageErase(FLASH, 0x00004000);
	memset(DataToWrite, 0x55, 512);
    FL_FLASH_Program_Word(FLASH, ProgAddr, DataToWrite[0]);
	
	FL_FLASH_PageErase(FLASH, 0x00004000);
	memset(DataToWrite, 0xAA, 512);
	FL_FLASH_Program_Page(FLASH, ProgAddr / FL_FLASH_MAX_PAGE_NUM, DataToWrite);
	
	FL_FLASH_SectorErase(FLASH, 0x00004000);
	memset(DataToWrite, 0x00, 512);
	FL_FLASH_Program_Sector(FLASH, ProgAddr / FL_FLASH_SECTOR_SIZE_BYTE, DataToWrite);
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


