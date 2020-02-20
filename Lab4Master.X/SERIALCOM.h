
#ifndef __SERIALCOM_H
#define	__SERIALCOM_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void ComSetup(uint16_t BR);
void ENVIO(uint8_t value);
#endif	/* XC_HEADER_TEMPLATE_H */

