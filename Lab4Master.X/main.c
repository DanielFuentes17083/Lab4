/*
 * File:   main.c
 * Author: Daniel Fuentes
 *
 * Created on 19 de febrero de 2020, 02:29 PM
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
#include "SPI.h"
#include "SERIALCOM.h"

//codigo principal del master
#define _XTAL_FREQ 8000000                      //frecuencia del oscilador

uint8_t pot1 = 0;                               //variables para los pots
uint8_t pot2 = 0;

void setup(void);

void __interrupt() ISR(){                           //Interrupciones
    di();
    if(PIR1bits.RCIF == 1){                         //Si recibio algun valor
        PORTB = RCREG;
    }
    ei();
}
void main(void) {
    setup();                                        
    ComSetup(9600);                               //se activa comunicacion serial a 9600
    while(1){
        PORTCbits.RC2 = 0;      //Slave Select
        __delay_ms(1);
        spiWrite(1);            //le pide el valor del primer pot
        pot1 = spiRead();       //aca lo lee
        __delay_ms(10);
        spiWrite(0);            //le pide el segundo valor del pot
        pot2 = spiRead();       //aca lo lee
         __delay_ms(10);
       PORTCbits.RC2 = 1;       //Slave Deselect 
       ENVIO(pot1);             //envia el valor del pot1
       __delay_ms(1);
       ENVIO(pot2);             //envia el valor del pot2
       __delay_ms(1);
    }
    
}

void setup(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISC2 = 0;
    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    PORTA = 0;
    PORTB = 0;
    PORTD = 0;
    PORTCbits.RC2 = 1;
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE); //configuracion del spi como master
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
}