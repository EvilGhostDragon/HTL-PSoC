#include "project.h"
void setSpeed(int uiPoti){
    PWM_WriteCompare(uiPoti*10);
    //UART_PutString("in getSpeed");
    
}