#ifndef __ADC_H__
#define __ADC_H__

#include "main.h"

#define ADC_VREF    (*((uint16_t *)(0x1FFFFB08)))   // 30�� vref1.22����ֵ
#define ADC_TS       (*((uint16_t *)(0x1FFFFa92)))   // 30�� PTAT����ֵ	
extern uint32_t GetSingleChannelVoltage_POLL(uint32_t channel);
extern uint32_t GetSingleChannelVoltage_IT(uint32_t channel);
extern float GetTS_POLL(void);
extern void GetConvertSample(void);
#endif 
