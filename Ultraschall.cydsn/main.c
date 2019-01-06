#include "project.h"
#include <stdio.h>
#include "main.h"

//globale Variablen
uint8 uiDistance = 0;
uint16 uiDistTime = 0;

CY_ISR_PROTO(isr_echo);
CY_ISR(isr_echo){
    //UART_PutString("echo got");
    
    while( inUW_Echo_Read( ) == 1 ) { };		
    uiDistTime = 500000 - Timer_ReadCounter( );         //Zeit in us
    //Ausbreitungsgeschwindigkeit (in Luft) =331,5 + (0,6 * Temp°) => 331,5+ (0,6 * 20) = 343,5 m/s
    
    uiDistance = uiDistTime / 58;                
}
CY_ISR_PROTO(isr_measure);
CY_ISR(isr_measure){
    getDistance();
    LED_Write(uiDistance);
}
//Initialisierung der einzelnen Elemente
void init(){
    //Hardware
    UART_Start();
    UART_PutString("UART init \r\n");
    
    Timer_Start();
    Timer_Measure_Enable();
    Timer_Measure_Start();
    UART_PutString("Timer init \r\n");
    
    isr_echo_StartEx(isr_echo);
    isr_measure_StartEx(isr_measure);
    UART_PutString("ISR init \r\n");
    
    UART_PutString("INIT Finished \r\n\n");
    
    CyGlobalIntEnable; 
    //Pins
    
}

int getDistance(){     				
	
    Trigger_Write( 1 ); 								
    CyDelayUs( 10 );	
    Trigger_Write( 0 );
        
    return(uiDistance); 
}

int main(void)
{
    char cOut[20];
    init();
    UART_PutString("Start\n\n\r");
    

    for(;;)
    {
        
        CyDelay(1000);
        
        //sprintf (out,"%d cm\r\n",uiDistance);
        //UART_PutString(out);
        
        /*if(a==0){UART_PutString("g\n"); a=1;}
        else{UART_PutString("x\n"); a=0;}*/
    }
    
    return 0;
}
