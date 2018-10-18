#include "C:\ti\msp\MSP432Ware_3_50_00_02\driverlib\driverlib\MSP432P4xx\driverlib.h"

#include "Simple_EOS.h"
#include "PC_O_UCA0.h"
#include "Elap_232.h"
#include "PC_O.h"

#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

int main(void)
{
	// Stop WatchDog
    MAP_WDT_A_holdTimer();

    UCA0_Uart_Init(26);// 115200 baud rate

    Elapsed_Time_RS232_Init();// prepare for elapsed time measurement

    SYSTICK_Init(5);// 5ms tick

    while(1)
    {
        sEOS_Go_To_Sleep();// letting the board sleep
    }
}
