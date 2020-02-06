

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef _LIBRERIA_LAB2_H_
#define	_LIBRERIA_LAB2_H_

#include <xc.h> // include processor files - each processor file is guarded.  

//VARIABLES
char X1 = 0;
char Y1 = 0;
char X = 0;
char Y = 0;

//FUNCIONES
void timer0(void);
void config_adc(void);
void adc_conv(void);

#endif	/* XC_HEADER_TEMPLATE_H */

