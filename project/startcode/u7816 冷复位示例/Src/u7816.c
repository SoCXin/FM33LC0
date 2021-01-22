#include "main.h"
#include "u7816.h"
#include "user_init.h"	


//����Netu��ʱ������1��bit��ʱ��
void Delay_Netu( unsigned char Num ) //Num*1etu
{
   DelayUs(93*Num);	//1 etu=93 us(4M),����1 etu=186 us(2M)    
// DelayUs(104*Num);	 
}

//��λ��Ӧ����ʱ��Ϊ400/f~40000/f��100us~10ms
//����ֵ: 1Ϊ�½���; 0Ϊ�ޱ仯
uint8_t Judge_Edge(void)                                 //�ж���
{
	uint32_t i;
	Delay_Netu(1);
	for(i=0; i<100; i++) //Լ10ms(4M),����20ms(2M)
	{
		if(SET == FL_U7816_IsActiveFlag_RXBusy(U7816)) //1=�������ݽ���״̬���յ���ʼλ��1���յ�ֹͣλ����
		{
		  return 1;    //�½���
		}
		else
		{
		  Delay_Netu(1);
		}
	}
		
  return 0;         //�ޱ仯
}

//�ʱ��ӦΪ9600etu,ĿǰΪ9600etu,1etu=93us
uint8_t Get_7816_Char(unsigned char *Data)
{
	uint32_t i;	
    for(i=0x00; i<10000; i++) 	//Լ900ms(4M),����1800ms(2M)
	{
//  IWDT_Clr();
	Delay_Netu(1);
	if(SET == FL_U7816_IsActiveFlag_RXComplete(U7816)) //RX_FLAG�Ѿ���λ
		{
		  *Data = FL_U7816_ReadRXBuff(U7816);
	return 1; //�ɹ�
		}
	if(SET == FL_U7816_IsActiveFlag_Error(U7816)) //ERROR_FLAG�Ѿ���λ
		{
		  FL_U7816_ClearFlag_TXParityError(U7816);
          FL_U7816_ClearFlag_RXParityError(U7816);
          FL_U7816_ClearFlag_RXFrameError(U7816); //����֡��ʽ����
          FL_U7816_ClearFlag_RXOverflow(U7816);
			
	return 2; //error
		}
	}
	return 3;
}

uint8_t Snd_7816_Byte( unsigned char Data )
{
	uint32_t i;

	Delay_Netu(2); //��ʱ2��etu,��֤���豸�ȶ�����

	FL_U7816_WriteTXBuff(U7816,Data); //������������д��write buffer���Զ�����
	
	for( i=0x00; i<400; i++ ) //Լ39ms(4M),����78ms(2M)
	{
//    IWDT_Clr();
     Delay_Netu(1);
      if(SET == FL_U7816_IsActiveFlag_TXBuffEmpty(U7816)) //TX_FLAG��λ
		 {
		   return 0; //���ݷ��ͳɹ�
		 }
	  if(SET == FL_U7816_IsActiveFlag_Error(U7816))	//ERROR_FLAG��λ
		 {
		  FL_U7816_ClearFlag_TXParityError(U7816); //��TxParityError��־��ʹU7816ERR����Ӧ�Ĵ����־����
          FL_U7816_ClearFlag_RXParityError(U7816);        
          FL_U7816_ClearFlag_RXFrameError(U7816); 
          FL_U7816_ClearFlag_RXOverflow(U7816);
             
		  return 1; //error
		 }
	}
	
	return 1;
}

//���㼤��&�临λ
//��⵽�������, RST�õ͵�ƽ, VCC�ϵ�, ��ʱһ��ʱ��, IO����Ϊ����̬, CLK���ʱ���ź�(T0ʱ��)
//��T0��40000~45000��CLK��, ��RST��Ϊ�ߵ�ƽ(T1ʱ��), ��T1���400~40000��CLK��, ��λӦ��Ӧ�ÿ�ʼ, 
//��IC���ĸ�λӦ��û���ڴ�ʱ����ڿ�ʼ, �ն˽������ͷ�ʱ��.���յ���λӦ��, ��������Э��淶, ����Ҫ�ȸ�λ
uint8_t ColdReset(void)
{
	uint8_t n, Result, Temp_ATR; // T0, TD1, TD2;        
	uint8_t cardRst8B[13];	//CARD��λ��Ϣ�к�13�ֽ�            
	
	DelayMs(100);//��ʱ100ms
  
    FL_U7816_EnableTX(U7816); //ͨ������ʹ��
	FL_U7816_EnableClockOutput(U7816);
	//----------------------------------------------------------------------------------------------
	FL_GPIO_ResetOutputPin(GPIOC,FL_GPIO_PIN_10);		//��PC10�������ͣ�RST����͵�ƽ��
	
	//RSTʱ�䱣����40000~45000��CLK;4MƵ����Ӧ�ñ��ֲ�����10ms;
	DelayMs(11);
	//-------- T1ʱ��, RST����ߵ�ƽ --------
	FL_GPIO_SetOutputPin(GPIOC,FL_GPIO_PIN_10); //�ȴ�RSTʱ��,����400����,��100us
	FL_U7816_EnableRX(U7816); //����λ��ɺ������������,֮ǰIO��ƽ���ȶ�,
	Result = FL_U7816_ReadRXBuff(U7816);  //RX������, �����rx_flag=1, ����ͨ����ȡRXBUF������˱�־.
    FL_U7816_ClearFlag_TXParityError(U7816); //��TxParityError��־��ʹU7816ERR����Ӧ�Ĵ����־����
    FL_U7816_ClearFlag_RXParityError(U7816);        
    FL_U7816_ClearFlag_RXFrameError(U7816); 
    FL_U7816_ClearFlag_RXOverflow(U7816);

	//��λ�����400~40000��CLK����ATR����
	Result = Judge_Edge(); 		//40000��CLK�ڲ鿴IO�ڵĵ�ƽ�ر仯
	if(Result == 0) //40000��CLK��IO��û�г����½���
	{
		return 2;	//�쳣: 40000��CLK��û���յ���ʼλ
	}
	for(n=0; n<13; n++)
	{
		Result = Get_7816_Char(&Temp_ATR ); //receive TS.
		if( Result != 1 )
		{ 
			return 3; 
		}
		cardRst8B[ n ] = Temp_ATR;
	}
	
	if(cardRst8B[0] != 0x3b)
	{
		return 3; 
	}
	
	return 0;
}

uint8_t Test_U7816(void)
{
    uint8_t sent_data[5] = {0x00,0xA4,0x00,0x00,0x02};
    uint8_t i,n,Result,temp_ATR;
    uint8_t cardReply1[1];
    uint8_t cardReply2[2];
    
    FL_U7816_EnableClockOutput(U7816); //U7816ʱ�����ʹ��   
	ColdReset();
	
	/*�临λ����ʱһ��ʱ�䲢������־������PSAM������ͨ��*/
	DelayMs(50);//��ʱ50ms

	FL_U7816_EnableRX(U7816);
	Result = FL_U7816_ReadRXBuff(U7816); //RX������, �����rx_flag=1, ����ͨ����ȡRXBUF������˱�־.
		
    FL_U7816_ClearFlag_TXParityError(U7816); //������־
    FL_U7816_ClearFlag_RXParityError(U7816);        
    FL_U7816_ClearFlag_RXFrameError(U7816); 
    FL_U7816_ClearFlag_RXOverflow(U7816);
	
	FL_U7816_EnableTX(U7816);
	
  /*----------------------------
	����00 A4 00 00 02 ����յ� A4
	-----------------------------*/	
 for(i=0;i<5;i++)
	{
		 Snd_7816_Byte( sent_data[i] );
	}
	
  Result = Judge_Edge(); 		//40000��CLK�ڲ鿴IO�ڵĵ�ƽ�ر仯,�ȴ����ݵĻط����½��ص���ʱ��˵���ط�����
	if( Result == 0 ) //IO��û�г����½���
	  {
		  return 2;	//�쳣: 40000��CLK��û���յ���ʼλ
	  }
	else
 	  {
	    for(n=0; n<1; n++)
	     {
		     Result=Get_7816_Char(&temp_ATR ); //receive TS.
		        if( Result != 1 )   //û�г����½���
		          { 
	             	return 3; //�쳣
	           	}
		     cardReply1[n] = temp_ATR;   
	     }
	  }
 
 if(cardReply1[0] == 0xA4 )
	{
	    Snd_7816_Byte(0x3F);
		Snd_7816_Byte(0x0);
	}	

 Result = Judge_Edge(); 		//40000��CLK�ڲ鿴IO�ڵĵ�ƽ�ر仯,�ȴ����ݵĻط����½��ص���ʱ��˵���ط�����
	if( Result == 0 ) //IO��û�г����½���
	  {
		  return 2;	//�쳣: 40000��CLK��û���յ���ʼλ
	  }
	else
 	  {
	    for(n=0; n<2; n++)
	     {
		     Result=Get_7816_Char(&temp_ATR ); //receive TS.
		        if( Result != 1 )   //û�г����½���
		          { 
	             	return 3; //�쳣
	           	}
		   cardReply2[n] = temp_ATR;   
	     }
	  }	
 return 0;     
}

