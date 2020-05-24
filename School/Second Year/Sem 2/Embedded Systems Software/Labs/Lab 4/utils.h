#ifndef _UTILS_H
#define _UTILS_H

//Given
#define LOW(val) 									((val) & 0xFF )
#define SET_BITS(port, mask) 						((port) |= (mask))
#define CLR_BITS(port, mask )						((port) &= (~(mask)))
#define FLIP_BITS(port, mask)						((port) ^= (mask))
#define FORCE_BITS(port, bits, value)				(port) = (((port) &(~(bits))) | ((value) & (bits)))

#define LO_NYBBLE(byte)								((byte) & 0x0F)
#define HI_NYBBLE(byte)								(((byte) >> 4) & 0x0F)
//Custom



//STM32 setup stuff
#define GPIO_PIN_MODE (port, pin, mask)				(port) |= ((mask) << (2*pin))
#define GPIO_PIN_OTYPE (port, pin, mask)			(port) |= ((mask) << (pin))
#define GPIO_PIN_SPEEDR (port, pin, mask)			(port) |= ((mask) << (2*pin))
#define GPIO_PIN_PUPDR (port, pin, mask)			(port) |= ((mask) << (2*pin))



#endif

