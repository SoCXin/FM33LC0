#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__


#include "usb_conf.h"


#define USBD_CFG_MAX_NUM           1	//���������Ŀ����֧��1������
#define USBD_ITF_MAX_NUM           1	//���ӿ���Ŀ����֧��1���ӿ�

#define USB_MAX_STR_DESC_SIZ       64 	//����ַ�������������

#define USBD_SELF_POWERED   //�Թ���

#define HID_IN_EP                    0x81	//����˵㣬ʹ��EP1
#define HID_IN_PACKET                4	    //���������


#endif
