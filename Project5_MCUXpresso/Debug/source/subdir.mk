################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../source/LED_control.c \
../source/MKL25Z128xxx4_Project.c \
../source/UART.c \
../source/delay.c \
../source/mtb.c \
../source/queue.c \
../source/semihost_hardfault.c 

OBJS += \
./source/LED_control.o \
./source/MKL25Z128xxx4_Project.o \
./source/UART.o \
./source/delay.o \
./source/mtb.o \
./source/queue.o \
./source/semihost_hardfault.o 

C_DEPS += \
./source/LED_control.d \
./source/MKL25Z128xxx4_Project.d \
./source/UART.d \
./source/delay.d \
./source/mtb.d \
./source/queue.d \
./source/semihost_hardfault.d 


# Each subdirectory must supply rules for building sources it contributes
source/%.o: ../source/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DCPU_MKL25Z128VLK4_cm0plus -DCPU_MKL25Z128VLK4 -DSDK_OS_BAREMETAL -DFSL_RTOS_BM -DSDK_DEBUGCONSOLE=0 -DCR_INTEGER_PRINTF -DPRINTF_FLOAT_ENABLE=0 -D__MCUXPRESSO -D__USE_CMSIS -DDEBUG -I"C:\Users\Katherine.000\Documents\Spring 2020\PES\Project 5\workspace\MKL25Z128xxx4_Project\board" -I"C:\Users\Katherine.000\Documents\Spring 2020\PES\Project 5\workspace\MKL25Z128xxx4_Project\source" -I"C:\Users\Katherine.000\Documents\Spring 2020\PES\Project 5\workspace\MKL25Z128xxx4_Project" -I"C:\Users\Katherine.000\Documents\Spring 2020\PES\Project 5\workspace\MKL25Z128xxx4_Project\drivers" -I"C:\Users\Katherine.000\Documents\Spring 2020\PES\Project 5\workspace\MKL25Z128xxx4_Project\CMSIS" -I"C:\Users\Katherine.000\Documents\Spring 2020\PES\Project 5\workspace\MKL25Z128xxx4_Project\utilities" -I"C:\Users\Katherine.000\Documents\Spring 2020\PES\Project 5\workspace\MKL25Z128xxx4_Project\startup" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fmerge-constants -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m0plus -mthumb -D__REDLIB__ -fstack-usage -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


