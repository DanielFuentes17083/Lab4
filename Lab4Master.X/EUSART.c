/*
 * File:   EUSART.c
 * Author: PowerLab
 *
 * Created on 14 de febrero de 2020, 02:18 PM
 */

//Libreria de comunicacion serial
#include <xc.h>
#include <stdint.h>
#include "SERIALCOM.h"

void ComSetup(uint16_t BR) {            //funcion que hace el setup de comunicacion serial y selecciona el BaudRate
    TXSTAbits.TX9 = 0;
    TXSTAbits.TXEN = 1;
    TXSTAbits.SYNC = 0;
    TXSTAbits.BRGH = 1;
    RCSTAbits.SPEN = 1;
    RCSTAbits.RX9 = 0;
    RCSTAbits.CREN = 1;
    BAUDCTLbits.BRG16 = 0;
    ei();
    INTCONbits.PEIE = 1;
    PIE1bits.RCIE = 1;
    switch (BR){
        case 1200:
            SPBRG = 207;
            break;
        case 2400:
            SPBRG = 103;
            break;
        case 9600:
            SPBRG = 25;
            break;
        case 10417:
            SPBRG = 23;
            break;
        case 19200:
            SPBRG = 12;
            break;
        default:
            SPBRG = 25;
            break;
    }
}

void ENVIO(uint8_t value){          //Funcion para enviar los datos por comunicacion serial
    while (TXSTAbits.TRMT == 0);
    TXREG = value;
}
