/*
 * GPIO_defs.h
 *
 *  Created on: Apr 20, 2020
 *      Author: Katherine
 *
 *      https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/inc/GPIO_defs.h
 */

#ifndef GPIO_DEFS_H_
#define GPIO_DEFS_H_


// basic light switch
#define LED1_POS (1)	// on port A
#define LED2_POS (2)	// on port A
#define SW1_POS (5)		// on port A

#define MASK(x) (1UL << (x))

// Speaker output
#define SPKR_POS (0) 	// on port C


#endif /* GPIO_DEFS_H_ */
