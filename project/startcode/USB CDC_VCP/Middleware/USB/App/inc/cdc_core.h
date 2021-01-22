#ifndef __CDC_CORE_H_
#define __CDC_CORE_H_

#include "usbd_ioreq.h"
#include "stream.h"

#define USB_CDC_CONFIG_DESC_SIZ                (60)			//������������С
	
#define DEVICE_CLASS_CDC                        0x02		//CDC��
#define DEVICE_SUBCLASS_CDC                     0x00		//CDC����

#define USB_DEVICE_DESCRIPTOR_TYPE              0x01		//�豸������
#define USB_CONFIGURATION_DESCRIPTOR_TYPE       0x02		//����������
#define USB_STRING_DESCRIPTOR_TYPE              0x03		//�ַ���������
#define USB_INTERFACE_DESCRIPTOR_TYPE           0x04		//�ӿ�������
#define USB_ENDPOINT_DESCRIPTOR_TYPE            0x05		//�˵�������

#define STANDARD_ENDPOINT_DESC_SIZE             0x09		//��ע�˵�����������

// CDC Requests
#define SEND_ENCAPSULATED_COMMAND               0x00		//���ͷ������
#define GET_ENCAPSULATED_RESPONSE               0x01		//��ȡ�����Ӧ
#define SET_COMM_FEATURE                        0x02		//����ͨ������
#define GET_COMM_FEATURE                        0x03		//��ȡͨ������
#define CLEAR_COMM_FEATURE                      0x04		//���ͨ������
#define SET_LINE_CODING                         0x20		//���ò����ʵȴ��ڲ���
#define GET_LINE_CODING                         0x21		//��ȡ�����ʵ�
#define SET_CONTROL_LINE_STATE                  0x22		//���ÿ�������״̬
#define SEND_BREAK                              0x23		//����BREAK
#define NO_CMD                                  0xFF		//û������

// CDC Endpoints parameters: you can fine tune these values depending on the needed baudrates and performance
#define CDC_DATA_MAX_SIZE               CDC_EP_MAX_SIZE      /* Total size of data buffer */ 
#define CDC_CMD_MAX_SIZE                8                    /* Control Endpoint Packet size */

// (CDC_DATA_MAX_SIZE * 8) / (MAX_BAUDARATE * 1000) should be > CDC_IN_FRAME_INTERVAL
#define CDC_IN_FRAME_INTERVAL           5                    /* Number of frames between IN transfers */

#define APP_FOPS                        VCP_fops	//�ײ�ӿڽṹ��ָ��

typedef struct _CDC_IF_PROP
{
    uint16_t (*pIf_Init)     (void);   
    uint16_t (*pIf_DeInit)   (void);   
    uint16_t (*pIf_Ctrl)     (uint32_t Cmd, uint8_t* Buf, uint32_t Len);
    uint16_t (*pIf_DataTx)   (uint8_t *Buf, uint16_t Len);
    uint16_t (*pIf_DataRx)   (uint8_t *Buf, uint16_t Len);
}
CDC_IF_Prop_TypeDef;

extern USBD_Class_cb_TypeDef  USBD_CDC_cb;

#endif
