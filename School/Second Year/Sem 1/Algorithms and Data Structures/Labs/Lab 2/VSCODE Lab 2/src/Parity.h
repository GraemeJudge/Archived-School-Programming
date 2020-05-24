/* Parity.h	-	Defines parity enumerated datat type PAR_EVEN, PAR_ODD, PAR_ERROR
*				Copyright 2019 Graeme Judge
*/

#ifndef PARITY_H
#define PARITY_H

enum PARITY { PAR_EVEN, PAR_ODD, PAR_ERROR };

PARITY ParityOnBytes(char* buf, int iBufLen);


PARITY Parity(unsigned char *buf, int iBufLen);

#endif