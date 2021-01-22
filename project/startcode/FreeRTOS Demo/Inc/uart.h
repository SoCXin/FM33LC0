#ifndef __Uart_H__
#define __Uart_H__

#include "main.h"

extern void Uartx_Init(UART_Type* UARTx);
extern void Test_Uart5(void);
extern void DebugInit(void);
extern void UARTx_DMA(UART_Type* UARTx, uint8_t *buffer,uint32_t length);
extern void UARTx_DMA_Rx(UART_Type* UARTx, uint8_t *buffer);

#ifdef DEBUG_PRINT
    #define PRINT   printf
#else
    #define PRINT(...)
#endif    

#endif
