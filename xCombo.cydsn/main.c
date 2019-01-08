
#include "project.h"
#include "linienfolger.h"
#include "geschwindigkeit.h"
#include <stdio.h>

//GLOBAL_VAR_START-----------------------------------------
uint16 uiPoti = 0;
int i = 0;
//GLOBAL_VAR_STOP------------------------------------------

//ISR_START------------------------------------------------
CY_ISR_PROTO(isr_ADC);
CY_ISR(isr_ADC){
    uint16 uiADCget;
    //ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    uiADCget = ADC_GetResult16()*106;   //ADC_GetResult8 geht nicht / *106 daher da nicht 100% erreicht werden
    uiPoti = uiADCget/255;
    //sprintf(cOut,"%d prc\n\r",uiPoti);
    //UART_PutString(cOut);
    ADC_Stop();
    
}
CY_ISR_PROTO(isr_1s);
CY_ISR(isr_1s){
    
    char cOut[20];
    sprintf(cOut,"%d \n\r",uiPoti*5);
    UART_PutString(cOut);
    setSpeed(uiPoti);
    ADC_Start();
    //UART_PutString("1s \n\r");
}
//ISR_END--------------------------------------------------

void init(){
    UART_Start();
    UART_PutString("UART init \r\n");
    
    Sample_Hold_Start();
    UART_PutString("Sample & Hold init \r\n");
    
    PWM_Start();
    UART_PutString("PWM init \r\n");
    
    isr_ADC_StartEx(isr_ADC);
    isr_1s_StartEx(isr_1s);
    UART_PutString("ISR init \r\n");
    
    Timer_1s_Start();
    UART_PutString("Timer init \r\n");
    
    setPWM_left_back_Write(0);
    setPWM_left_for_Write(0);
    setPWM_right_back_Write(0);
    setPWM_right_for_Write(0);
    UART_PutString("Pin Set init \r\n");
    
    UART_PutString("INIT Finished \r\n");
    UART_PutString("Program START\r\n\n\n");
    
    setSpeed(1000);
    
    CyGlobalIntEnable; 
}

int main(void)
{
    init();
    

    for(;;)
    {
        setIRDirection();
        
    }
}

/* [] END OF FILE */
