/*
 * File:   timer.c
 * Authors:
 *
 * Created on December 30, 2014, 8:07 PM
 */

#include <xc.h>
#include "timer.h"
void initTimer2(){
    TMR2=0;// clear timer2
    T2CONbits.ON=1;// enable timer2
    T2CONbits.TCKPS=0;// pre-scalar is equal to 1
    T2CONbits.TCS=0;// internal oscillator 
    IFS0bits.T2IF=0;// Put down flag
    //IPC2bits.T2IP=3;// configure the interrupt priority 
    IEC0bits.T2IE=1; // Enable the interrupt
}

//Uses timer 2 the oscillator is 8M (*20/2/1/1)
void delayUs(unsigned int delay){
 //TODO: Create a delay for "delay" micro seconds using timer 2

    TMR2=0;// clear timer1
    PR2= delay*80-1;// delay 1Us 
    IFS0bits.T2IF=0;// Put flag down
    T2CONbits.ON=1;// enable timer2
    while(IFS0bits.T2IF==0);
    T2CONbits.ON=0;//turn off timer2
   
}
