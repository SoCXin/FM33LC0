#ifndef __USB_DESC_H
#define __USB_DESC_H

#include "usbd_req.h"


#define USB_DEVICE_DESCRIPTOR_TYPE              0x01	//�豸������
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02	//����������
#define USB_STRING_DESCRIPTOR_TYPE              0x03	//�ַ���������
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04	//�ӿ�������
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05	//�˵�������
#define USB_SIZ_DEVICE_DESC                     18		//�豸����������
#define USB_SIZ_STRING_LANGID                   4		//�ַ���LANGID����������

//�豸ID���壬оƬUID�洢λ��
#define DEVICE_UID1          (*(uint32_t *)(0x1ffffe80))
#define DEVICE_UID2          (*(uint32_t *)(0x1ffffe84))
#define DEVICE_UID3          (*(uint32_t *)(0x1ffffe88))
#define DEVICE_UID4          (*(uint32_t *)(0x1ffffe8c))

#define  USB_SIZ_STRING_SERIAL       0x42	//�ַ������кų���


extern  uint8_t USBD_DeviceDesc  [USB_SIZ_DEVICE_DESC];                 //�豸������18�ֽ�
extern  uint8_t USBD_StrDesc[USB_MAX_STR_DESC_SIZ];						//�ַ�������������󳤶�156�ֽ�
extern  uint8_t USBD_OtherSpeedCfgDesc[USB_LEN_CFG_DESC]; 				//�����ٶ�����������
extern  uint8_t USBD_DeviceQualifierDesc[USB_LEN_DEV_QUALIFIER_DESC];	//�豸����������
extern  uint8_t USBD_LangIDDesc[USB_SIZ_STRING_LANGID];					//LANGID��������4�ֽ�
extern  USBD_DEVICE USR_desc; 										    //�������ص��ṹ��


uint8_t *USBD_USR_DeviceDescriptor( uint8_t speed , uint16_t *length);				//�����豸������
uint8_t *USBD_USR_LangIDStrDescriptor( uint8_t speed , uint16_t *length);			//����LANGID�ַ���������
uint8_t *USBD_USR_ManufacturerStrDescriptor ( uint8_t speed , uint16_t *length);	//�����������ַ���������
uint8_t *USBD_USR_ProductStrDescriptor ( uint8_t speed , uint16_t *length);		//���ز�Ʒ�ַ���������
uint8_t *USBD_USR_SerialStrDescriptor( uint8_t speed , uint16_t *length);			//�������к��ַ���������
uint8_t *USBD_USR_ConfigStrDescriptor( uint8_t speed , uint16_t *length);			//���������ַ���������
uint8_t *USBD_USR_InterfaceStrDescriptor( uint8_t speed , uint16_t *length);		//���ؽӿ��ַ���������

#ifdef USB_SUPPORT_USER_STRING_DESC
uint8_t *     USBD_USR_USRStringDesc (uint8_t speed, uint8_t idx , uint16_t *length);	//�û��ַ���������
#endif

#endif
