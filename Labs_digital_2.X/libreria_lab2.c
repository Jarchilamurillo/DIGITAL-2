#include <xc.h>
#include "libreria_lab2.h"

void timer0(void){
        //TMRO
    OPTION_REGbits.nRBPU = 1;
    OPTION_REGbits.INTEDG = 0;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.T0SE = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS = 0b000;
    TMR0 = 3;
}


void config_adc(void){
        
    //Seteando ADC a un rate de Fosc/32
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.ADCS0 = 0;
    //Escogiendo canal del ADC
    ADCON0bits.CHS = 0b1101;
    //Enable ADC
    ADCON0bits.ADON = 1;
    //Formato del resultado (izquierda)
    ADCON1bits.ADFM = 0;
    //Pines de v ref
    ADCON1bits.VCFG1 = 0;
    ADCON1bits.VCFG0 = 0;
}

void adc_conv(void){
    X = ADRESH;
    Y = ADRESH;
    
    X1 = (X & 0b00001111);
    Y1 = (Y & 0b11110000)>>4;
}