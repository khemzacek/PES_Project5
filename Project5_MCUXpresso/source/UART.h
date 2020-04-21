/*
 * UART.h
 *
 *  Created on: Apr 20, 2020
 *      Author: Katherine
 *
 *      https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/inc/UART.h
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include <MKL25Z4.H>
#include "queue.h"

#define USE_UART_INTERRUPTS 	(0) // 0 for polled UART communications, 1 for interrupt-driven
#define UART_OVERSAMPLE_RATE 	(16)
#define BUS_CLOCK 						(24e6)
#define SYS_CLOCK							(48e6)

void Init_UART0(uint32_t baud_rate);
void UART0_Transmit_Poll(uint8_t data);
uint8_t UART0_Receive_Poll(void);

void Send_String_Poll(uint8_t * str);
void Send_String(uint8_t * str);

uint32_t Rx_Chars_Available(void);
uint8_t	Get_Rx_Char(void);

uint8_t Echo_Poll(void);
uint8_t Echo(void);

extern Q_T TxQ, RxQ;

#endif /* UART_H_ */
