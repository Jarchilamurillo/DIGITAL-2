/*
 * File:   LAB_1.c
 * Author: j_arc
 *
 * Created on 31 de enero de 2020, 9:53 AM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF           // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF          // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF          // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF             // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF            // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF          // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF           // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF          // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF            // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V       // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF            // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ  8000000
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "libreria_lab2.h"


uint8_t contador = 0;
//variable de boton de suma y suma
char IN1 = 0;
char INN1 = 0;
//variable de boton de resta y resta
char IN2 = 0;
char INN2 = 0;
//Array para display (0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F)
unsigned char disp [] = {0b11101110, 0b00101000, 0b11001101, 0b01101101, 0b00101011, 
0b01100111, 0b11100111, 0b00101100, 0b11101111, 0b01101111, 0b10101111, 0b11100011, 
0b11000110, 0b11101001, 0b11000111, 0b10000111};
//Variables para conversión de ADC a hexa


void __interrupt() ISR(void){
    di();
    
    if(INTCONbits.RBIF == 1){
        INTCONbits.RBIF = 0;
    
        if(PORTBbits.RB2==1){
            IN1=1;
            di();
        }
        if(PORTBbits.RB2==0 && IN1==1){
            IN1=0;
            INN1=1;
            INTCONbits.INTF = 0;
            INTCONbits.RBIF = 0;
            ei();
            return;
        }
        if(PORTBbits.RB1==1){
            IN2 = 1;
            di();
        }
        if(PORTBbits.RB1==0 && IN2==1){
            IN2=0;
            INN2=1;
            INTCONbits.INTF = 0;
            INTCONbits.RBIF = 0;
            ei();
            return;
        }
        
        
    }
    
}

void main(void){
    
    config_adc();
    adc_conv();
    timer0();
    
    //Entradas/salidas
    TRISC = 0;
    TRISA = 0;
    //Botones
    TRISBbits.TRISB1 = 1;
    TRISBbits.TRISB2 = 1;
    IOCBbits.IOCB1 = 1;
    IOCBbits.IOCB2 = 1;
    
    //Interrupciones
    OPTION_REGbits.INTEDG = 1; // Set Rising Edge Trigger for INT
    INTCONbits.GIE = 1; // Enable The Global Interrupt
    INTCONbits.INTE = 1; // Enable INT
    
    //Transistores
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    //Entrada analógica
    TRISBbits.TRISB5 = 1;
    ANSELH = 0b00100000;
    //LED alarma
    TRISBbits.TRISB7 = 0;

    config_adc();
    
    timer0();
    
    //Seteando reloj interno a 8MHz
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;


    
    //Estados iniciales
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTA = 0;
    PORTBbits.RB7 = 0;
    
    while(1){
        
        adc_conv();
        
        //multiplexado de displays
        
        PORTC = disp[X1];
        PORTDbits.RD4 = 1;
        __delay_ms(10);
        PORTDbits.RD4 = 0;
        
        PORTC = disp[Y1];
        PORTDbits.RD5 = 1;
        __delay_ms(10);
        PORTDbits.RD5 = 0;
        
        if(ADCON0bits.GO_nDONE==0){
            ADCON0bits.GO_nDONE = 1;
        }
        
        //funciones para suma y resta
        if(INN1==1){
            INN1=0;
            if((contador>=0) & (contador<=254)){
                contador = contador + 1;
            }
            if(contador==255){
                contador = 255;
            }
        }
        
        if(INN2==1){
            INN2=0;
            if(contador>=1 & contador <=255){
                contador = contador - 1;
            }
            if(contador==0){
                contador = 0;
            }
        }
        //salida del contador
        PORTA = contador;
        
        //alarma
        if(X >= contador){
            PORTBbits.RB7 = 1;   
        }
        else{
            PORTBbits.RB7 = 0;
        }
    }
    return;
}
    


   
        
    
    
      