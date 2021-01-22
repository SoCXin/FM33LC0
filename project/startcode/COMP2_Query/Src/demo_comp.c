#include "demo_comp.h"

//中断处理函数
void COMPx_IRQHandler(void)
{
    //COMP1
    //注意对输入信号的滤波，否则容易误触发中断
    if(SET == FL_COMP_IsActiveFlag_Comparator1(COMP))
    {
        FL_COMP_ClearFlag_Comparator1(COMP);    //清除COMP中断标志
        
        if(FL_COMP_OUTPUT_HIGH == FL_COMP_GetOutput(COMP1))    //比较器, P 电压高于 N
        {
            //用户代码    
        }
        else                                //比较器1, P 电压低于 N
        {
            //用户代码 
        }    
    }
    //COMP2 
    //注意对输入信号的滤波，否则容易误触发中断
    if(SET == FL_COMP_IsActiveFlag_Comparator2(COMP))
    {
        FL_COMP_ClearFlag_Comparator2(COMP);    //清除COMP中断标志
        
        if(FL_COMP_OUTPUT_HIGH == FL_COMP_GetOutput(COMP2))    //比较器, P 电压高于 N
        {
            //用户代码    
        }
        else                                //比较器1, P 电压低于 N
        {
            //用户代码 
        }    
    }    
}

//比较器1 查询方式
void COMP1_Query(void)
{
    //比较器1 查询
    if(FL_COMP_GetOutput(COMP1)==FL_COMP_OUTPUT_HIGH)//P 电压高于 N
    {
        //用户代码
    }
    else//P 电压低于 N
    {
        //用户代码
    }
}

//比较器2 查询方式
void COMP2_Query(void)
{
    //比较器2 查询
    if(FL_COMP_GetOutput(COMP2)==FL_COMP_OUTPUT_HIGH)//P 电压高于 N
    {
        //用户代码
    }
    else//P 电压低于 N
    {
        //用户代码
    }
}



