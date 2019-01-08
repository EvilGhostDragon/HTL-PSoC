#include "project.h"
void setSpeed(int uiPoti){
    PWM_WriteCompare(uiPoti*5);
    //UART_PutString("in getSpeed");
    
}