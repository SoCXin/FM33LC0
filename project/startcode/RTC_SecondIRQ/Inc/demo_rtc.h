#ifndef __DEMO_RTC_H__
#define __DEMO_RTC_H__

#include "main.h"

uint8_t RTC_GetRTC(FL_RTC_InitTypeDef* InitStructer);
uint8_t RTC_SetRTC(FL_RTC_InitTypeDef* InitStructer);
void RTC_ReadWrite(void);
void RTC_AlarmTimeSet(void);
void RTC_TimeMarkOut(void);

#endif
