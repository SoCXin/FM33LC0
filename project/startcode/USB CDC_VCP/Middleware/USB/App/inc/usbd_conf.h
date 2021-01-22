#ifndef __USBD_CONF__H__
#define __USBD_CONF__H__

#include "usb_conf.h"

#define USBD_CFG_MAX_NUM                1		// ���������Ŀ����֧��1������
#define USBD_ITF_MAX_NUM                1		// ���ӿ���Ŀ����֧��1���ӿ�

#define USBD_SELF_POWERED               		// �Թ���

#define USB_MAX_STR_DESC_SIZ            255     // ����ַ�������������

#define CDC_IN_EP                       0x81    /* EP1 for data IN */
#define CDC_OUT_EP                      0x01    /* EP1 for data OUT */
#define CDC_EP_MAX_SIZE                 64      /* EPx Max Packet Size */  

#endif
