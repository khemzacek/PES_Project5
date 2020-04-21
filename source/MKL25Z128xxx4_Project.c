/*
 * Copyright 2016-2020 NXP
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of NXP Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
 
/**
 * @file    MKL25Z128xxx4_Project.c
 * @brief   Application entry point.
 */
#include <stdio.h>
#include "board.h"
#include "peripherals.h"
#include "pin_mux.h"
#include "clock_config.h"
#include "MKL25Z4.h"
#include "fsl_debug_console.h"
/* TODO: insert other include files here. */

#include "gpio_defs.h"
#include "UART.h"
#include "LEDs.h"


/* TODO: insert other definitions and declarations here. */

/*
 * @brief   Application entry point.
 */
int main(void) {

  	/* Init board hardware. */
    BOARD_InitBootPins();
    BOARD_InitBootClocks();
    BOARD_InitBootPeripherals();
  	/* Init FSL debug console. */
    BOARD_InitDebugConsole();

    PRINTF("Hello World\n");

    // https://github.com/alexander-g-dean/ESF/blob/master/NXP/Code/Chapter_8/Serial-Demo/src/main.c
    uint8_t buffer[80], c, * bp;

    Init_UART0(115200);
    Init_RGB_LEDs();

    printf("\n\rGood morning!\n\r");

    #if USE_UART_INTERRUPTS==0 // Polling version of code
    	Send_String_Poll("\n\rHello, World!\n\r");

    	// Code listing 8.9, p. 233
    	while (1) {
    		c = UART0_Receive_Poll();
    		Control_RGB_LEDs(0, 0, 1);
    		UART0_Transmit_Poll(c+1);
    		Control_RGB_LEDs(0, 0, 0);
    	}
    #elif USE_UART_INTERRUPTS==1 // Interrupt version of code
    	Send_String("\n\rHello, World!\n\r");

    	// Code listing 8.10, p. 234
    	while (1) {
    		// Blocking receive
    		while (Q_Size(&RxQ) == 0)
    			; // wait for character to arrive
    		c = Q_Dequeue(&RxQ);

    		// Blocking transmit
    		sprintf((char *) buffer, "You pressed %c\n\r", c);
    		// enqueue string
    		bp = buffer;
    		while (*bp != '\0') {
    			// copy characters up to null terminator
    			while (Q_Full(&TxQ))
    				; // wait for space to open up
    			Q_Enqueue(&TxQ, *bp);
    			bp++;
    		}
    		// start transmitter if it isn't already running
    		if (!(UART0->C2 & UART0_C2_TIE_MASK)) {
    			UART0->C2 |= UART0_C2_TIE(1);
    		}
    	}
    #endif

}

