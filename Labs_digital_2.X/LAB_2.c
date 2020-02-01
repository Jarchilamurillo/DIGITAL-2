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

#define _XTAL_FREQ  8000000
#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>


unsigned char contador = 0;
//variable de boton de suma y suma
char IN1 = 0;
char INN1 = 0;
//variable de boton de resta y resta
char IN2 = 0;
char INN2 = 0;

void __interrupt() contadorrr(void){
    
    if(PORTDbits.RD3==1){
        IN1=1;
    }
    if(PORTDbits.RD3==0 && IN1==1){
        IN1=0;
        INN1=1;
    }
    if(PORTDbits.RD2==1){
        IN2 = 1;
    }
    if(PORTDbits.RD2==0 && IN2==1){
        IN2=0;
        INN2=1;
    }
}

void main(void){
    //Entradas/salidas
    TRISC = 0;
    //Botones
    TRISDbits.TRISD2 = 1;
    TRISDbits.TRISD3 = 1;
    //Transistores
    TRISDbits.TRISD4 = 0;
    TRISDbits.TRISD5 = 0;
    //Entrada analógica
    TRISBbits.TRISB5 = 1;
    //LED alarma
    TRISBbits.TRISB7 = 0;
    //Seteando ADC a un rate de Fosc/32
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.ADCS0 = 0;
    //Escogiendo canal del ADC
    ADCON0bits.CHS = 0b1101;
    //Formato del resultado (derecha)
    ADCON1bits.ADFM = 1;
    //Seteando reloj interno a 8MHz
    OSCCONbits.IRCF0 = 1;
    OSCCONbits.IRCF1 = 1;
    OSCCONbits.IRCF2 = 1;
    //Mas bits para ADC
    ADCON0bits.GO_nDONE = 1;
    //Enable ADC
    ADCON0bits.ADON = 1;
    //Estados iniciales
    PORTDbits.RD4 = 0;
    PORTDbits.RD5 = 0;
    PORTA = 0;
    PORTBbits.RB7 = 0;
    
    while(1){
        PORTC = ADRESL;
        PORTDbits.RD4 = 1;
        __delay_ms(10);
        PORTDbits.RD4 = 0;
        
        PORTC = ADRESH;
        PORTDbits.RD5 = 1;
        __delay_ms(10);
        PORTDbits.RD5 = 0;
        
        if(ADCON0bits.ADON==0){
            ADCON0bits.ADON = 1;
        }
        
        
        if(INN1==1){
            INN1=0;
            if((contador>=0) && (contador<255)){
                contador = contador + 1;
            }
            if(contador==255){
                contador = 255;
            }
        }
        if(INN2==1){
            INN2=0;
            if(contador>0 && contador <=255){
                contador = contador - 1;
            }
            if(contador==0){
                contador = 0;
            }
        }
    }
    return;
}
    


   
        
    
    
      
