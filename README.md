# PES_Project5
#### Katherine Hemzacek

## Project Description
This program utilizes UART communication protocol to communicate between an NXP KL25Z development board and a PC terminal program. It can be compiled for polling-based UART communication or interrupt-based UART communication. The program can be compiled to run in "Echo Mode" where any character typed to the PC terminal will be sent to the board and echoed back on the screen. It can also be compiled to run in "Application Mode" where all text entered into the terminal will be processed by the board. In application mode, after three sequential return characters are entered, a report of the number of each unique character entered into the terminal will be generated and printed to the PC terminal.

## Repo Contents
This repository contains all project files from this project in MCUXpresso. All source code written for the project can be found in the folder "source".

This repository also contains a Failure Modes and Effects Analysis, which can be found in the document "FMEA.pdf".

## Installation and Execution Notes
The contents of the folder "Project5_MCUXpresso" can be imported to MCUXpresso as a new project in the MCUXpresso IDE. The define statements in the source document "PES_Project5.h" can be used to build the project in each of the different configuration modes.

The project was created to be run on an NXP KL25Z development board. The board should be connected to a PC, and a PC terminal program should be used to establish a connection with the board's UART0 port. The PC terminal program should be set up for a baud rate of 115200, 8 bits, no partity bits, no start bit, one stop bit.
 
