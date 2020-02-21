/*
 * File:   main.c
 * Author: Daniel Fuentes
 *
 * Created on 19 de febrero de 2020, 02:31 PM
 */


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

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "ADC.h"
#include "SPI.h"

//Programa principal del Slave
#define _XTAL_FREQ 8000000          //se selecciona frecuencia de 8M

void setup(void);                   //variables
uint8_t ADCF = 0;
uint8_t va1 = 0;
uint8_t va2 = 0;

void __interrupt() ISR(){           //Interrupciones
    di();
    if(PIR1bits.ADIF == 1 && ADCF == 0){            //Si es el ADC
        PIR1bits.ADIF = 0;
        ADCF = 1;
        va1 = ADRESH;                               //Primer Pot
        ADRESH = 0;
        channelS(1);
    } else if(PIR1bits.ADIF == 1 && ADCF == 1){
        PIR1bits.ADIF = 0;
        ADCF = 0;
        va2 = ADRESH;                               //Segundo Pot
        ADRESH = 0;
        channelS(0);
    }
    ei();
}
void main(void) {
    setup();
    ADConfig();             //Configuracion de ADC
    channelS(0);            //canal inicial del ADC
    while(1){
        ADCON0bits.GO = 1;
        __delay_ms(10);
        if(spiRead() == 1){ //si lee un 1 del master, envia el valor del primer pot
            spiWrite(va1);
        }
        if(spiRead() == 0){ //si lee un 0 del master, envia el valor del segundo pot
            spiWrite(va2);
        }
    }
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    ANSELbits.ANS0 = 1;     
    ANSELbits.ANS1 = 1;
    
    TRISA = 0x03;
    TRISB = 0;
    TRISD = 0;
    
    PORTB = 0;
    PORTD = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIE1bits.ADIE = 1;
    PIR1bits.ADIF = 0;
    PIE1bits.SSPIE = 0;         
    TRISAbits.TRISA5 = 1;       // Slave Select
    spiInit(SPI_SLAVE_SS_EN, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);    //configuracion de la comunicacion SPI como slave
}