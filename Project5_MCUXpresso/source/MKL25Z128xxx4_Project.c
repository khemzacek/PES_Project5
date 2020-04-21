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

#define USE_UART_INTERRUPTS	0	//0 = polling; 1 = interrupts

#define APPLICATION_MODE	1	//0 = echo mode; 1 = application mode

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


#include "UART.h"
#include "LED_control.h"


/* TODO: insert other definitions and declarations here. */
const char* wsCharCodes[] =
						{"NUL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", "BEL", "BS", "TAB",
						"LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3",
						"DC4", "NAK", "SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS",
						"RS", "US", "SPACE"
						};

uint8_t char_cnts[128];

#if APPLICATION_MODE==1
#if USE_UART_INTERRUPTS==0 // Polling version of code
void Print_Report_Poll(void){
	uint8_t i = 0;
	uint8_t report_line[15];
	Send_String_Poll("\n\r\n\r");
	while(1){
		if(char_cnts[i] != 0){
			if(i < 33){
				sprintf(report_line, "%s - %d; ", wsCharCodes[i], char_cnts[i]);
			}else if(i == 127){
				sprintf(report_line, "DEL - %d; ", char_cnts[i]);
			}else{
				sprintf(report_line, "%c - %d; ", i, char_cnts[i]);
			}
			Send_String_Poll(report_line);
		}
		if(i == 127){
			break;
		}
		i++;
	}
	Send_String_Poll("\n\r\n\r");
}
#elif USE_UART_INTERRUPTS==1 // Interrupt version of code
void Print_Report(void){
	uint8_t i = 0;
	uint8_t report_line[15];
	Send_String("\n\r\n\r");
	while(1){
		if(char_cnts[i] != 0){
			if(i < 33){
				sprintf(report_line, "%s - %d; ", wsCharCodes[i], char_cnts[i]);
			}else if(i == 127){
				sprintf(report_line, "DEL - %d; ", char_cnts[i]);
			}else{
				sprintf(report_line, "%c - %d; ", i, char_cnts[i]);
			}
			Send_String(report_line);
		}
		if(i == 127){
			break;
		}
		i++;
	}
	Send_String("\n\r\n\r");
}
#endif
#endif	//APPLICATION_MODE

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
    uint8_t c;

#if APPLICATION_MODE==1
    //Initialize character counts to zero
    for(uint8_t i = 127; i > 0; i--){
    	char_cnts[i] = 0;
    }
    char_cnts[0] = 0;

    uint8_t enter_cnt = 0;
#endif //APPLICATION_MODE

    //Initialize UART and LEDs
    Init_UART0(115200);
    LED_init();
    LED_on(blue);

    #if USE_UART_INTERRUPTS==0 // Polling version of code
    	Send_String_Poll("\n\r--Program Start--\n\r");

    	while (1) {
    		c = Echo_Poll();
			#if APPLICATION_MODE==1
    		// update character count
    		char_cnts[c]++;
    		// check for 3 enters in a row (cue to print report)
    		if(c == 13){	//\r
    			enter_cnt++;
    			if(enter_cnt >=3){
    				enter_cnt = 0;
    				Print_Report_Poll();
    			}
    		}else{
    			enter_cnt = 0;
    		}
			#endif //APPLICATION_MODE
    	}
    #elif USE_UART_INTERRUPTS==1 // Interrupt version of code
    	Send_String("\n\r--Program Start--\n\r");

    	while (1) {
    		c = Echo();
			#if APPLICATION_MODE==1
    		char_cnts[c]++;
    		// check for 3 enters in a row (cue to print report)
    		if(c == "\r"){
    			enter_cnt++;
    			if(enter_cnt >=3){
    				enter_cnt = 0;
    				Print_Report();
    			}
    		}else{
    			enter_cnt = 0;
    		}
			#endif //APPLICATION_MODE
    	}
    #endif

}

