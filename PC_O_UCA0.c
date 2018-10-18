#include "C:\ti\msp\MSP432Ware_3_50_00_02\driverlib\driverlib\MSP432P4xx\driverlib.h"

#include "Simple_EOS.h"
#include "PC_O_UCA0.h"
#include "Elap_232.h"
#include "PC_O.h"

// Public variable declartion
extern uint8_t Out_written_index_G;
extern uint8_t Out_waiting_index_G;

void UCA0_Uart_Init(uint32_t BAUD_RATE)
{
    UCA0CTLW0 = 0x0001;// hold USCI in reset mode
    UCA0CTLW0 = 0x00C1;// UART,SMCLK,8bit,1 stop,no parity,LSB first

    UCA0BRW = BAUD_RATE;// baud rate = 3000000/115200 = 26.0417

    UCA0MCTLW &= ~0xFFF1;// clear first and second modulation

    P1SEL0 |= 0x0C;
    P1SEL1 &= ~0x0C;// P1.3 and P1.2 as primary module function

    UCA0CTLW0 &= ~0x0001;// enable USCI
    UCA0IE &= ~0x000F;
}
