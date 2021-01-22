#include "main.h"
#include "user_init.h"
#include "opa1_buffer.h"

void OPA1_Init(void)
{
    FL_GPIO_InitTypeDef    GPIO_InitStruct;
    FL_OPA_InitTypeDef     OPA1_InitStruct;
    
   //OPA1正端输入，INP1 
    GPIO_InitStruct.pin         = FL_GPIO_PIN_11;
    GPIO_InitStruct.mode        = FL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.outputType  = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull        = DISABLE;
    GPIO_InitStruct.remapPin    = DISABLE;

    FL_GPIO_Init( GPIOB, &GPIO_InitStruct );

   //OPA1负端输入，INN2
//    GPIO_InitStruct.pin         = FL_GPIO_PIN_6;
//    GPIO_InitStruct.mode        = FL_GPIO_MODE_ANALOG;
//    GPIO_InitStruct.outputType  = FL_GPIO_OUTPUT_PUSHPULL;
//    GPIO_InitStruct.pull        = DISABLE;
//    GPIO_InitStruct.remapPin    = DISABLE;

//    FL_GPIO_Init( GPIOA, &GPIO_InitStruct );


   //OPA1输出，OUT
    GPIO_InitStruct.pin         = FL_GPIO_PIN_4;
    GPIO_InitStruct.mode        = FL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.outputType  = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull        = DISABLE;
    GPIO_InitStruct.remapPin    = DISABLE;

    FL_GPIO_Init( GPIOC, &GPIO_InitStruct );
    
    //OPA1配置
   OPA1_InitStruct.INP              = FL_OPA_INP_SOURCE_INP1;               
   OPA1_InitStruct.INN              = FL_OPA_INN_SOURCE_INN2;     
   OPA1_InitStruct.mode             = FL_OPA_MODE_BUFFER;                   
   OPA1_InitStruct.digitalFilter    = DISABLE;     
   OPA1_InitStruct.negtiveToPin     = DISABLE;     
   OPA1_InitStruct.gain             = FL_OPA_GAIN_X2;   
   OPA1_InitStruct.lowPowermode     = DISABLE; 

  FL_OPA_Init(OPA1, &OPA1_InitStruct);

}


void Test_OPA1Buffer(void)
{

    //OPA1_Init();
    FL_OPA_Enable(OPA1);
}
