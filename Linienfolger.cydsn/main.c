

#include "project.h"

int richtung, _richtung;

void init(){
    UART_Start();
    UART_PutString("UART init \r\n");
    UART_PutString("INIT Finished \r\n");
    
    CyGlobalIntEnable; 
}
void getDirection(){
    outM_1_Write(inIR_1_Read());
    if(inIR_1_Read()==0)richtung = 1;
        
    outM_2_Write(inIR_2_Read());
    if(inIR_2_Read()==0)richtung = 2;
        
    outM_3_Write(inIR_3_Read());
    if(inIR_3_Read()==0)richtung = 3;
}
int main(void)
{
    init();
    
     for(;;)
    {
        
        
        if(richtung != _richtung){
            if(richtung == 1)UART_PutString("Left \r\n");
            else if (richtung == 2)UART_PutString("Right \r\n");
            else if (richtung == 3)UART_PutString("Middle \r\n");
        } 
        _richtung = richtung;
    }
}

/* [] END OF FILE */
