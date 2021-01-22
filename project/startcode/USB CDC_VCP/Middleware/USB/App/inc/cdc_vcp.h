#ifndef __CDC_VCP_H__
#define __CDC_VCP_H__

#include "cdc_core.h"
#include "usbd_conf.h"

/* The following structures groups all needed parameters to be configured for the 
   ComPort. These parameters can modified on the fly by the host through CDC class
   command class requests. 
*/
typedef struct
{
    uint32_t bitrate;       // ������
    uint8_t  format;        // ֹͣλ  0: 1bit, 1: 1.5bit, 2: 2bit
    uint8_t  paritytype;    // У��λ  0: NONE, 1: ODD, 2: EVEN, 3: MARK, 4: SPACE
    uint8_t  datatype;      // ����λ  5: 5bit, 6: 6bit, 7: 7bit, 8: 8bit 
}LINE_CODING;

#define DEFAULT_CONFIG                  0
#define OTHER_CONFIG                    1


#endif
