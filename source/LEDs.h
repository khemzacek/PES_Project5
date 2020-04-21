/*
 * LEDs.h
 *
 *  Created on: Apr 20, 2020
 *      Author: Katherine
 *
 *      https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/inc/LEDs.h
 */

#ifndef LEDS_H_
#define LEDS_H_

// Freedom KL25Z LEDs
#define RED_LED_POS (18)		// on port B
#define GREEN_LED_POS (19)	// on port B
#define BLUE_LED_POS (1)		// on port D

// function prototypes
void Init_RGB_LEDs(void);
void Control_RGB_LEDs(unsigned int red_on, unsigned int green_on, unsigned int blue_on);

#endif /* LEDS_H_ */
