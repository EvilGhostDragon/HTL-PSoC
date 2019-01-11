#include "project.h"
void setSpeed(uint16 uiPoti,int inDrehung){
    int defSpeed = 250+uiPoti*2.5; //defailt - maximal 50% pwm sonst zu schwach -> PWM: 250-500 von 500
    
    //PWM1: left  side
    //PWM2: right side
    switch(inDrehung){
        //links Drehung
        case -1:    PWM_WriteCompare1(defSpeed);
                    PWM_WriteCompare2(defSpeed/1.3);
                    break;
        //rechts Drehung
        case 1:     PWM_WriteCompare1(defSpeed/1.3);
                    PWM_WriteCompare2(defSpeed);
                    break;
        default:    PWM_WriteCompare1(defSpeed);
                    PWM_WriteCompare2(defSpeed);
                    break;
    }
    //UART_PutString("in getSpeed");
    
}