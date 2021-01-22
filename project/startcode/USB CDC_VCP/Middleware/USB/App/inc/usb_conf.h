#ifndef __USB_CONF__H__
#define __USB_CONF__H__

// USB�ײ��������ã������ں����ú����������

// USBȫ���豸FIFO���ã����䵥λ:word��
#define RX_FIFO_FS_SIZE                          64
#define TX0_FIFO_FS_SIZE                         16
#define TX1_FIFO_FS_SIZE                         16
#define TX2_FIFO_FS_SIZE                         16 


// ϵͳAHB����ʱ��
#define SYSTEM_AHB_CLOCK    64000000

// USBģʽѡ��
#define USE_DEVICE_MODE


// �������ؼ��ֶ��壺
// ֧��ʵ��USB���еı����ͽṹ���4�ֽڶ���
//#define USB_DATA_STRUCT_ALIGNED

#ifdef USB_DATA_STRUCT_ALIGNED
    #if defined ( __ICCARM__ )          /* !< IAR Compiler */
        #pragma data_alignment=4
    #endif
#endif

#ifdef USB_DATA_STRUCT_ALIGNED
    #if defined   (__GNUC__)            /* GNU Compiler */
        #define __ALIGN_END    __attribute__ ((aligned (4)))
        #define __ALIGN_BEGIN         
    #else                           
        #define __ALIGN_END
        #if defined   (__CC_ARM)        /* ARM Compiler */
            #define __ALIGN_BEGIN    __align(4)  
        #elif defined (__ICCARM__)      /* IAR Compiler */
            #define __ALIGN_BEGIN
        #endif /* __CC_ARM */  
    #endif /* __GNUC__ */ 
#else
    #define __ALIGN_BEGIN
    #define __ALIGN_END   
#endif

// ʹ��__packed�ؼ��֣�ʵ��1�ֽڶ���
#if defined (__CC_ARM)                  /* ARM Compiler */
//    #define __packed    __packed
#elif defined (__ICCARM__)              /* IAR Compiler */
//    #define __packed    __packed
#elif defined   ( __GNUC__ )            /* GNU Compiler */                        
    #define __packed    __attribute__ ((__packed__))
#endif /* __CC_ARM */

#endif
