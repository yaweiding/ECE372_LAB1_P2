/*
 * File:   lcd.c
 * Authors:
 *
 * Created on December 31, 2014, 1:39 PM
 */

/* TODO: Make define statements for each pin used in the LCD
 */
#include <xc.h>
#include "lcd.h"
#include "timer.h"

#define LCD_DATA  LATB
#define LCD_RS  LATDbits.LATD5
#define LCD_E   LATDbits.LATD3

#define TRIS_D7  TRISbits.TRISE7 //(5) high
#define TRIS_D6  TRISbits.TRISE5 //(7)
#define TRIS_D5  TRISbits.TRISE3 //(9)
#define TRIS_D4  TRISbits.TRISE1//(11)

#define TRIS_D3  TRISbits.TRISD6
#define TRIS_D2  TRISbits.TRISD12
#define TRIS_D1  TRISbits.TRISF1
#define TRIS_D0  TRISbits.TRISG0
#define TRIS_RS  TRISbits.TRISD5
#define TRIS_E   TRISbits.TRISD5
#define LOWER 0
#define UPPER 1
#define LCD_WRITE_DATA   1
#define LCD_CONTROL_DATA 0

/* This function should take in a two-byte word and writes either the lower or upper
 * byte to the last four bits of LATB. Additionally, according to the LCD data sheet
 * It should set LCD_RS and LCD_E with the appropriate values and delays.
 * After these commands are issued, there should be a delay.
 * The command type is a simplification. From the data sheet, the RS is '1'
 * when you are simply writing a character. Otherwise, RS is '0'.
 */
void writeFourBits(unsigned char word, unsigned int commandType, unsigned int delayAfter, unsigned int lower) {
    //TODO:
    if (lower == 0) {
        LATEbits.LATE7 = (word & 0b00001000) >> 3;
        LATEbits.LATE5 = (word & 0b00000100)>>2;
        LATEbits.LATE3 = (word & 0b00000010)>>1;
        LATEbits.LATE1 = (word & 0b00000001);

    } else if (lower == 1) {
      
        LATEbits.LATE7 = (word & 0b10000000) >> 7;
        LATEbits.LATE5 = (word & 0b01000000)>>6;
        LATEbits.LATE3 = (word & 0b00100000)>>5;
        LATEbits.LATE1 = (word & 0b00010000)>>4;


    }
    LCD_RS = commandType; //D3
    delayUs(1);
    LCD_E = 1;
    delayUs(1); //
    LCD_E = 0;// D5
    delayUs(1);
    delayUs(delayAfter);
}

/* Using writeFourBits, this function should write the two bytes of a character
 * to the LCD.
 */
void writeLCD(unsigned char word, unsigned int commandType, unsigned int delayAfter) {
    //TODO:
    writeFourBits(word, commandType, delayAfter, UPPER);
    writeFourBits(word, commandType, delayAfter, LOWER);
}

/* Given a character, write it to the LCD. RS should be set to the appropriate value.
 */
void printCharLCD(char c) {
    //TODO:
    writeLCD(c, LCD_WRITE_DATA, 46); // write date delay 46us
}

/*Initialize the LCD
 */
void initLCD(void) {
    // Setup D, RS, and E to be outputs (0).
    TRIS_D0 = 0;
    TRIS_D1 = 0;
    TRIS_D2 = 0;
    TRIS_D3 = 0;
    TRIS_D4 = 0;
    TRIS_D5 = 0;
    TRIS_D6 = 0;
    TRIS_D7 = 0;
    TRIS_RS = 0;
    TRIS_E = 0;
    LCD_RS = 0;
    LCD_E = 0;
    // Initilization sequence utilizes specific LCD commands before the general configuration

    //wait 15 ms
    
    // commands can be utilized. The first few initilition commands cannot be done using the

    // WriteLCD function. Additionally, the specific sequence and timing is very important.


    // Enable 4-bit interface
     delayUs(15000);// wait 15ms
    
    writeFourBits(0x03, LCD_CONTROL_DATA, 4100, LOWER);// DB5=1, DB4=1;

    writeFourBits(0x03, LCD_CONTROL_DATA, 100, LOWER); // DB5=1 DB4=0

    writeLCD(0x32, LCD_CONTROL_DATA, 40)// no delay time put the last tow commands together 
    
            
    // Function Set (specifies data width, lines, and font.
    writeLCD(0x28, LCD_CONTROL_DATA, 40); //    4bits 2lines RE=0


    // 4-bit mode initialization is complete. We can now configure the various LCD
    // options to control how the LCD will function.

    // TODO: Display On/Off Control
    // Turn Display (D) Off 
    writeLCD(0x08, LCD_CONTROL_DATA, 40); // delay time display off cursor off no blink 
    // TODO: Clear Display (The delay is not specified in the data sheet at this point. You really need to have the clear display delay here.

    writeLCD(0x01, LCD_CONTROL_DATA, 1000); // delay time 1MS

    // TODO: Entry Mode Set
    // Set Increment Display, No Shift (i.e. cursor move)
    writeLCD(0x06, LCD_CONTROL_DATA, 40); // increment  
    // TODO: Display On/Off Control
    // Turn Display (D) On, Cursor (C) Off, and Blink(B) Off
    writeLCD(0x0C, LCD_CONTROL_DATA, 40); // 
}

/*
 * You can use printCharLCD here. Note that every time you write a character
 * the cursor increments its position automatically.
 * Since a string is just a character array, try to be clever with your use of pointers.
 */
void printStringLCD(const char* s) {

    //TODO:
    while (*s) {
        printCharLCD(*(s));
        s = s + 1;


    }
}

/*
 * Clear the display.
 */
void clearLCD() {
    //LCD_E=0;
    // LCD_RS=0;
    writeLCD(0x01, LCD_CONTROL_DATA, 1000); //82US -1.64MS
    moveCursorLCD(0, 0);

}

/*
 Use the command for changing the DD RAM address to put the cursor somewhere.
 * x row y colum 
 */
void moveCursorLCD(unsigned char x, unsigned char y) {
   
    //writeLCD(0x02, LCD_CONTROL_DATA, 40); //return home command0x02 delay40us
    
     
     if(x == 0){
         writeLCD(0x80 + y, LCD_CONTROL_DATA, 40);
         
     }
    if(x == 1){
        writeLCD(0x80 + 0x40 + y, LCD_CONTROL_DATA, 40);
    }
    
    
    
    //    for (i = 0; i < = x * 8 + y; i++) {
//        writeLCD(0x14, LCD_CONTROL_DATA, 40); //move cursor shift right 40delay
//        writeLCD(0x14, LCD_CONTROL_DATA, 40);
//    }

}

/*
 * This function is called in lab1p2.c for testing purposes.
 * If everything is working properly, you should get this to look like the video on D2L
 * However, it is suggested that you test more than just this one function.
 */
void testLCD() {
    initLCD();
    int i = 0;
    printCharLCD('c');
    for (i = 0; i < 1000; i++) delayUs(1000);
    clearLCD();
    printStringLCD("Hello!");
    moveCursorLCD(1, 2);
    for (i = 0; i < 1000; i++) delayUs(1000);
    printStringLCD("Hello!");
    for (i = 0; i < 1000; i++) delayUs(1000);
}
















