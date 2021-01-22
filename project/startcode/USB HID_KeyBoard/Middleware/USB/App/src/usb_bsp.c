#include "usb_bsp.h"
#include "usbd_conf.h"
#include "hid_core.h"

// USB�弶��ʼ���ļ�
#include <string.h>
#include "user_init.h"

#ifdef USB_DATA_STRUCT_ALIGNED
    #if defined ( __ICCARM__ )          /* !< IAR Compiler */
        #pragma data_alignment=4
    #endif
#endif
__ALIGN_BEGIN USB_OTG_CORE_HANDLE USB_OTG_dev __ALIGN_END;

// USB��ʼ��
static void USB_Clock_Init(void)
{
    RCC->PCLKCR1 |= 0x1 << 1;   // ����USB����ʱ��
    
    RCC->PHYCR |= 0x1 << 2;     // VDD15��־�ѽ���
    
    RCC->PHYCR |= 0x1 << 4;     // USB PHYģ�鸴λ�ͷ�
    RCC->PHYCR |= 0x1 << 0;     // USB BCKģ�鸴λ�ͷ�
    
    RCC->PHYCR &= ~(0x1 << 3);  // USB PHY����
    RCC->PHYCR &= ~(0x1 << 1);  // USB BCK����
    
    RCC->PHYBCKCR |= 0x1 << 8;  // PHY���48Mʹ��
    
    DelayMs(1000);
}

// USBȥ��ʼ��
static void USB_Clock_DeInit(void)
{
    RCC->PHYBCKCR &= ~(0x1 << 8);   // PHY�ر�48M���
    
    RCC->PHYCR |= 0x1 << 1;     // �ر�USB BCK
    RCC->PHYCR |= 0x1 << 3;     // �ر�USB PHY
    RCC->PHYCR &= ~(0x1 << 0);  // USB BCKģ�鸴λ
    RCC->PHYCR &= ~(0x1 << 4);  // USB PHYģ�鸴λ
    
    RCC->PHYCR &= ~(0x1 << 2);  // VDD15������־���
    
    RCC->PCLKCR1 &= ~(0x1 << 1);// �ر�USB����ʱ��
}

// USB�������
static void USB_Soft_Connect(USB_OTG_CORE_HANDLE *pdev)
{
	USB_OTG_DCTL_TypeDef     dctl;
	
	dctl.d32 = USB_OTG_READ_REG32(&pdev->regs.DREGS->DCTL);
	dctl.b.sftdiscon = 0;
	USB_OTG_WRITE_REG32( &pdev->regs.DREGS->DCTL, dctl.d32);
}

// USB����Ͽ�
static void USB_Soft_Disconnect(USB_OTG_CORE_HANDLE *pdev)
{
	USB_OTG_DCTL_TypeDef     dctl;
	
	dctl.d32 = USB_OTG_READ_REG32(&pdev->regs.DREGS->DCTL);
	dctl.b.sftdiscon = 1;
	USB_OTG_WRITE_REG32( &pdev->regs.DREGS->DCTL, dctl.d32);
}

// ��ʼ��USB(GPIO��ʱ��)
void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE * pdev)
{
    USB_Clock_Init();
	
	// Init FIFO Debug Read/Write Region
    memset((uint32_t*)0x50020000, 0x400, 0x00);
}

// ��ʼ��USB(GPIO��ʱ��)
void USB_OTG_BSP_DeInit(USB_OTG_CORE_HANDLE * pdev)
{
    USB_Clock_DeInit();
}

// ʹ��USBȫ���ж�
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE * pdev)
{
	NVIC_ClearPendingIRQ(USB_IRQn);
	NVIC_DisableIRQ(USB_IRQn);
	NVIC_SetPriority(USB_IRQn,2);
	NVIC_EnableIRQ(USB_IRQn);
	
	// �������������
	USB_Soft_Disconnect(&USB_OTG_dev);
	USB_OTG_BSP_mDelay(1000);
	USB_Soft_Connect(&USB_OTG_dev);
}

void USB_OTG_BSP_DisableInterrupt(USB_OTG_CORE_HANDLE * pdev)
{
	// �������
	USB_Soft_Disconnect(&USB_OTG_dev);
    
    NVIC_DisableIRQ(USB_IRQn);
}

#define count_us 6	//ϵͳʱ��Ϊ32MHZ

// USB����us����ʱ
void USB_OTG_BSP_uDelay(const uint32_t usec)
{
    DelayUs(usec);
}

// USB����ms����ʱ 
void USB_OTG_BSP_mDelay(const uint32_t msec)
{
    USB_OTG_BSP_uDelay(msec * 1000);
}
