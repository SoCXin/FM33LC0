#include "demo_comp.h"

//�жϴ�����
void COMPx_IRQHandler(void)
{
    //COMP1
    //ע��������źŵ��˲������������󴥷��ж�
    if(SET == FL_COMP_IsActiveFlag_Comparator1(COMP))
    {
        FL_COMP_ClearFlag_Comparator1(COMP);    //���COMP�жϱ�־
        
        if(FL_COMP_OUTPUT_HIGH == FL_COMP_GetOutput(COMP1))    //�Ƚ���, P ��ѹ���� N
        {
            //�û�����    
        }
        else                                //�Ƚ���1, P ��ѹ���� N
        {
            //�û����� 
        }    
    }
    //COMP2 
    //ע��������źŵ��˲������������󴥷��ж�
    if(SET == FL_COMP_IsActiveFlag_Comparator2(COMP))
    {
        FL_COMP_ClearFlag_Comparator2(COMP);    //���COMP�жϱ�־
        
        if(FL_COMP_OUTPUT_HIGH == FL_COMP_GetOutput(COMP2))    //�Ƚ���, P ��ѹ���� N
        {
            //�û�����    
        }
        else                                //�Ƚ���1, P ��ѹ���� N
        {
            //�û����� 
        }    
    }    
}

//�Ƚ���1 ��ѯ��ʽ
void COMP1_Query(void)
{
    //�Ƚ���1 ��ѯ
    if(FL_COMP_GetOutput(COMP1)==FL_COMP_OUTPUT_HIGH)//P ��ѹ���� N
    {
        //�û�����
    }
    else//P ��ѹ���� N
    {
        //�û�����
    }
}

//�Ƚ���2 ��ѯ��ʽ
void COMP2_Query(void)
{
    //�Ƚ���2 ��ѯ
    if(FL_COMP_GetOutput(COMP2)==FL_COMP_OUTPUT_HIGH)//P ��ѹ���� N
    {
        //�û�����
    }
    else//P ��ѹ���� N
    {
        //�û�����
    }
}



