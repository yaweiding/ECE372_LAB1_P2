// ******************************************************************************************* //
//
// File:         lab1p2.c
// Date:         12-30-2014
// Authors:      Garrett Vanhoy
//
// Description: 
// ******************************************************************************************* //

#include <xc.h>
#include <sys/attribs.h>
#include "lcd.h"
#include "timer.h"
#include "config.h"
#include "interrupt.h"
#define OUTPUT 0
#define INPUT 1
#define delay 5
#define PRESS 0
#define RELEASE 1
#define SW1 PORTGbits.RG13// for run/stop swith


// ******************************************************************************************* //

int main(void)
{

    while(1)
    {
        testLCD();
    }
    
    return 0;
}
