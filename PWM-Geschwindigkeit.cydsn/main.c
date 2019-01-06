
#include "project.h"
#include <stdio.h>

//
uint16 uiPoti = 0;

CY_ISR_PROTO(isr_ADC);
CY_ISR(isr_ADC){
    char cOut[20];
    uint16 uiADCget;
    //ADC_IsEndConversion(ADC_WAIT_FOR_RESULT);
    uiADCget = ADC_GetResult16()*106;   //ADC_GetResult8 geht nicht / *106 daher da nicht 100% erreicht werden
    uiPoti = uiADCget/255;
    sprintf(cOut,"%d prc\n\r",uiPoti);
    UART_PutString(cOut);
    ADC_Stop();
}
CY_ISR_PROTO(isr_1s);
CY_ISR(isr_1s){
    ADC_Start();
    //UART_PutString("1s \n\r");
}

void init(){
    //Hardware
    UART_Start();
    UART_PutString("UART init \r\n");
    
    //ADC_Start();
    Sample_Hold_Start();
    UART_PutString("Sample & Hold init \r\n");
    
    PWM_Start();
    UART_PutString("PWM init \r\n");
    
    isr_ADC_StartEx(isr_ADC);
    isr_1s_StartEx(isr_1s);
    UART_PutString("ISR init \r\n");
    
    Timer_1s_Start();
    UART_PutString("Timer init \r\n");
    
    UART_PutString("INIT Finished \r\n\n");
    
    CyGlobalIntEnable; 
    //Pins
    
}
void setLeds(){
    switch(uiPoti){
        case 0: LED_5_Write(0);
        case 1 ... 16: LED_4_Write(0); 
        case 17 ... 33: LED_3_Write(0); 
        case 34 ... 50: LED_2_Write(0); 
        case 51 ... 66: LED_1_Write(0); 
        case 67 ... 83: LED_0_Write(0); 
    }
    switch(uiPoti){
        case 84 ... 100: LED_0_Write(1);  
        case 67 ... 83: LED_1_Write(1); 
        case 51 ... 66: LED_2_Write(1); 
        case 34 ... 50: LED_3_Write(1); 
        case 17 ... 33: LED_4_Write(1); 
        case 1 ... 16: LED_5_Write(1);break;
    }
    //UART_PutString("in SetLeds\n\r");
}
void setSpeed(){
    PWM_WriteCompare(uiPoti*10);
    //UART_PutString("in getSpeed");
    
}

int main(void)
{
    init();
    UART_PutString("Start\n\n\r");

    

    for(;;)
    {
        setLeds();
        setSpeed();
    }
}

