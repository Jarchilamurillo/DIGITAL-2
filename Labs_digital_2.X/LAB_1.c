/*
 * File:   LAB_1.c
 * Author: j_arc
 *
 * Created on 27 de enero de 2020, 12:11 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ  4000000
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>



   
  char IN1 = 0;
  char IN2 = 0;
  char IN3 = 0;
  
  unsigned char risp [] = {0b01101101, 0b11001101, 0b00101000, 0b11101110, 0b00000000};
  char rontrol = 0;
      
  unsigned char jug1 [] = {0b00000000, 0b01000000, 0b10000000, 0b00100000, 0b00010000, 0b00001000, 0b00000100, 0b00000010, 0b00000001, 0b00000000};
  char rontroljug1 = 0;
  unsigned char jug2 [] = {0b00000000, 0b00000001, 0b00000010, 0b00000100, 0b00001000, 0b00010000, 0b00100000, 0b01000000, 0b10000000, 0b00000000};
  char rontroljug2 = 0;
  
void main(void) {
    
    //Bits para salida LEDs izquierda
  TRISA=0;
//Bits para salida LEDs derecha
  TRISB=0;
//Botones de juego (1,2) e inicio del juego (3)
  TRISDbits.TRISD1=1;
  TRISDbits.TRISD2=1;
  TRISDbits.TRISD3=1;
  //7 segmentos
  TRISC=0;
  //Semaforo
  TRISDbits.TRISD7=0;
  TRISDbits.TRISD6=0;
  TRISDbits.TRISD5=0;
  //LEDs ganador
  TRISDbits.TRISD0=0;
  TRISDbits.TRISD4=0;
  //Estados iniciales
  PORTDbits.RD5=0;
  PORTDbits.RD6=0;
  PORTDbits.RD7=0;
  PORTC=0;
  PORTB=0;
  PORTA=0;
  PORTDbits.RD0=0;
  PORTDbits.RD4=0;
  
  
  
  //anti rebote boton 1
    while (1){
      if(PORTDbits.RD1==1){
        IN1 = 1;
        }
      
      if (PORTDbits.RD1==0 && IN1==1){
        IN1 = 0;
        PORTC=risp[rontrol];
        PORTDbits.RD5=1;
        PORTDbits.RD6=0;
        PORTDbits.RD7=0;
        __delay_ms(1000);
        rontrol = rontrol + 1;
        PORTC=risp[rontrol];
        PORTDbits.RD5=0;
        PORTDbits.RD6=1;
        PORTDbits.RD7=0;
        __delay_ms(1000);
        rontrol = rontrol + 1;
        PORTC=risp[rontrol];
        PORTDbits.RD5=0;
        PORTDbits.RD6=0;
        PORTDbits.RD7=1;
        __delay_ms(1000);
        rontrol = rontrol + 1;
        PORTC=risp[rontrol];
        __delay_ms(1000);
        rontrol = 0;
        PORTC=risp[4];
        PORTDbits.RD5=0;
        PORTDbits.RD6=0;
        PORTDbits.RD7=0;
        __delay_ms(50);
        
        while(1){
            //para poder reiniciar en cualquier momento
            if(PORTDbits.RD1==1){
                IN1=1;
            }
            if(PORTDbits.RD0==0 && IN1==1){
                IN1=0;
                return;
            }
            //jugador 1
            if(PORTDbits.RD2==1){
              IN2 = 1;  

            }
            if (PORTDbits.RD2==0 && IN2==1){
              IN2 = 0;
              rontroljug1 = rontroljug1 + 1;
              PORTA = jug1[rontroljug1];

            }        
            if (rontroljug1 == 9){
                PORTDbits.RD0=1;
                PORTC=risp[2];
                IN3=0;
                PORTB=0;
                PORTA=0;
                rontroljug2=0;            
                __delay_ms(4000);
                return;
                
            }


          //jugador 2
            if(PORTDbits.RD3==1){
              IN3 = 1;
              }
            if (PORTDbits.RD3==0 && IN3==1){
              IN3 = 0;
              rontroljug2 = rontroljug2 + 1;
              PORTB = jug2[rontroljug2];
              } 
            //se cambi� a 9 en vez de 8 para que se apaguen solas las LEDs de los jugadores
            //sin necesidad de apagar el puerto completo, pero igual se hizo por seguridad
            if (rontroljug2 == 9){
                PORTDbits.RD4=1;
                PORTC=risp[1];
                IN2=0;
                PORTA=0;
                PORTB=0;
                rontroljug1=0;   
                __delay_ms(4000); 
                return;
                }
            }  
        }  
    }
    return;
}
