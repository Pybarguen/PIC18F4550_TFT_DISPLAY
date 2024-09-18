// CONFIG1L
#pragma config PLLDIV = 1       // PLL Prescaler Selection bits (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CPUDIV = OSC1_PLL2// System Clock Postscaler Selection bits ([Primary Oscillator Src: /1][96 MHz PLL Src: /2])
#pragma config USBDIV = 2       // USB Clock Selection bit (used in Full-Speed USB mode only; UCFG:FSEN = 1) (USB clock source comes from the 96 MHz PLL divided by 2)

// CONFIG1H
#pragma config FOSC = XTPLL_XT  // Oscillator Selection bits (XT oscillator, PLL enabled (XTPLL))
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOR = OFF        // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (Minimum setting 2.05V)
#pragma config VREGEN = OFF     // USB Voltage Regulator Enable bit (USB voltage regulator disabled)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 1        // Watchdog Timer Postscale Select bits (1:1)

// CONFIG3H
#pragma config CCP2MX = OFF     // CCP2 MUX bit (CCP2 input/output is multiplexed with RB3)
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config ICPRT = OFF      // Dedicated In-Circuit Debug/Programming Port (ICPORT) Enable bit (ICPORT disabled)
#pragma config XINST = OFF      // Extended Instruction Set Enable bit (Instruction set extension and Indexed Addressing mode disabled (Legacy mode))

// CONFIG5L
#pragma config CP0 = OFF        // Code Protection bit (Block 0 (000800-001FFFh) is not code-protected)
#pragma config CP1 = OFF        // Code Protection bit (Block 1 (002000-003FFFh) is not code-protected)
#pragma config CP2 = OFF        // Code Protection bit (Block 2 (004000-005FFFh) is not code-protected)
#pragma config CP3 = OFF        // Code Protection bit (Block 3 (006000-007FFFh) is not code-protected)

// CONFIG5H
#pragma config CPB = OFF        // Boot Block Code Protection bit (Boot block (000000-0007FFh) is not code-protected)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit (Data EEPROM is not code-protected)

// CONFIG6L
#pragma config WRT0 = OFF       // Write Protection bit (Block 0 (000800-001FFFh) is not write-protected)
#pragma config WRT1 = OFF       // Write Protection bit (Block 1 (002000-003FFFh) is not write-protected)
#pragma config WRT2 = OFF       // Write Protection bit (Block 2 (004000-005FFFh) is not write-protected)
#pragma config WRT3 = OFF       // Write Protection bit (Block 3 (006000-007FFFh) is not write-protected)

// CONFIG6H
#pragma config WRTC = OFF       // Configuration Register Write Protection bit (Configuration registers (300000-3000FFh) are not write-protected)
#pragma config WRTB = OFF       // Boot Block Write Protection bit (Boot block (000000-0007FFh) is not write-protected)
#pragma config WRTD = OFF       // Data EEPROM Write Protection bit (Data EEPROM is not write-protected)

// CONFIG7L
#pragma config EBTR0 = OFF      // Table Read Protection bit (Block 0 (000800-001FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR1 = OFF      // Table Read Protection bit (Block 1 (002000-003FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR2 = OFF      // Table Read Protection bit (Block 2 (004000-005FFFh) is not protected from table reads executed in other blocks)
#pragma config EBTR3 = OFF      // Table Read Protection bit (Block 3 (006000-007FFFh) is not protected from table reads executed in other blocks)

// CONFIG7H
#pragma config EBTRB = OFF      // Boot Block Table Read Protection bit (Boot block (000000-0007FFh) is not protected from table reads executed in other blocks)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.



#define CCS LATBbits.LATB2
#define DCs  LATBbits.LATB3
#define RES LATBbits.LATB4


#include <xc.h>
#include <stdio.h>
#define _XTAL_FREQ 48000000
#include<math.h>
#include "Fonts.h"
#include "Pic18f4550_spi.h"
#include "St7735_Widgets.h"
#include "ST7735.h"

//#include "Image.h"

 
ProgressBar ProgressBar_ADC = {.Coordinates.x_start =10, .Coordinates.y_start = 90,
                               .Coordinates.Widht = 100, .Coordinates.Height =20, Black_Color, White_Color};

/*
ProgressBar ProgressBar_Temp = {.Coordinates.x_start = 50, .Coordinates.y_start = 50,
                               .Coordinates.Widht = 40, .Coordinates.Height =5   };
*/
Animation_Progress ProgressBar_animation;
  
char character_buffer[];

void main(void) 
{
    
 


    
    //SPI
   Spi_init();//start spi interface
   Spi_mode(CPOL_1_CPHA_0);//SPI mode 0 0 
   Spi_clock_mode(SPI_MASTER_CLOCK_DIV_4);//SPI clock = FOSC/4 
   TRISBbits.RB2 = 0;//SLAVE control PIN
   TRISBbits.RB3 = 0;//output DC comman/data ST7735 control
   TRISBbits.RB4 = 0;//output DC comman/data ST7735 control
   

   
   __delay_ms(10);
    RES = 1;
    CCS = 1;
    DCs = 0;
   
    ST7735S_Init(ST7735_128_x_160);
    ST7735S_Fill_display(Black_Color); 
    
      sprintf(character_buffer, "Test Char");
        ST7735S_Print_String(Blue_Color, character_buffer, 0, 0, 1);
        __delay_ms(1);
        sprintf(character_buffer, "Test Numbers");
        ST7735S_Print_String(Blue_Color, character_buffer, 0, 30, 1);
    __delay_ms(1);
     
      sprintf(character_buffer, "1234567890");   
   
     print_7_segments_string(0, 60, character_buffer,  1, Blue_Color);
    
   
     
       

          // ST7735S_Fill_display(Black_Color); 
    //ST7735S_Fill_image(Image_array);
   /*
     
       ST7735_Progress_Bar(&ProgressBar_ADC);
       ST7735S_Print_Char(Blue_Color, 't', 20, 50, 3);
      sprintf(character_buffer, "Testing");
          ST7735S_Print_String(Blue_Color, character_buffer, 40, 40, 3);
     */
          //
      // print_7_segments(20, 20);
      
            
             /*
              sprintf(character_buffer, "abcdefghijklmnopqr");
              ST7735S_Print_String(Blue_Color, character_buffer, 0, 0, 2);
              sprintf(character_buffer, "stuvwxyzABCDEFGHIJK");

              ST7735S_Print_String(Red_Color , character_buffer, 0, 23, 2);

              ST7735S_Print_String(Red_Color, character_buffer, 0, 23, 2);

               sprintf(character_buffer, "LMNOPQRSTUVWXYZ");
              ST7735S_Print_String(Green_Color, character_buffer, 0, 46, 2);
              sprintf(character_buffer, "0123456789");
              ST7735S_Print_String(Red_Color , character_buffer, 0, 69, 2);
    //ST7735S_Fill_image(Image_array);
              
      */
     
    
      
  
 
    
     
    
         
    
      
    
     
   



   
   while(1)
   {
        // sprintf(character_buffer, "its ok");
         //ST7735_Animating_ProgressBar(&ProgressBar_ADC, 400, character_buffer);
          //ST7735_Animating_ProgressBar(&ProgressBar_ADC, 300, character_buffer);
         
         //ST7735_Animating_ProgressBar(&ProgressBar_ADC, 300, character_buffer);
       
       
       
   }    
    
     

   

}