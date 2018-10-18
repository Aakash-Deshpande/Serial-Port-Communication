#include "C:\ti\msp\MSP432Ware_3_50_00_02\driverlib\driverlib\MSP432P4xx\driverlib.h"

#include "Simple_EOS.h"
#include "PC_O_UCA0.h"
#include "Elap_232.h"
#include "PC_O.h"

static uint32_t Call_Count_G;

void SysTick_Handler(void)
{
    PC_LINK_O_Update();// Updated at very 5ms

    // for every one sec the below method is called
    if(++Call_Count_G == 200)
    {
        Call_Count_G = 0;
        Elapsed_Time_RS232_Update();// Update the time
    }
}
void SYSTICK_Init(const uint32_t MS_TICKS)
{
    SysTick->LOAD = 3000*MS_TICKS - 1;
    SysTick->CTRL = 7;
}
void sEOS_Go_To_Sleep(void)
{
    __wfi();// enter idle mode
}
