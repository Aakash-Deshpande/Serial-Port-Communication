#include "C:\ti\msp\MSP432Ware_3_50_00_02\driverlib\driverlib\MSP432P4xx\driverlib.h"

#include "Simple_EOS.h"
#include "PC_O_UCA0.h"
#include "Elap_232.h"
#include "PC_O.h"

// Public variable definitions
uint8_t Out_written_index_G;
uint8_t Out_waiting_index_G;

// Private func prototype
static void PC_LINK_O_Send_Char(const char);

// Transmit buffer length
#define TRAN_BUFFER_LENGTH 23

static uint8_t Tran_Buffer[TRAN_BUFFER_LENGTH];

void PC_LINK_O_Update(void)
{
    // Deal with transmit bytes here
    // is there any data to send ?
    if(Out_written_index_G < Out_waiting_index_G)
    {
        PC_LINK_O_Send_Char(Tran_Buffer[Out_written_index_G]);
        Out_written_index_G++;
    }
    else
    {
        // No data to send - just reset the buffer
        Out_written_index_G = 0;
        Out_waiting_index_G = 0;
    }
}
void PC_LINK_O_Write_String_To_Buffer(const char* const STR_PTR)
{
    uint8_t i = 0;

    while(STR_PTR[i] != '\0')
    {
        PC_LINK_O_Write_Char_To_Buffer(STR_PTR[i]);
        i++;
    }
}
void PC_LINK_O_Write_Char_To_Buffer(const char CHARACTER)
{
    // Write to the buffer only if there is space
    if(Out_waiting_index_G < TRAN_BUFFER_LENGTH)
    {
        Tran_Buffer[Out_waiting_index_G] = CHARACTER;
        Out_waiting_index_G ++;
    }
}
void PC_LINK_O_Send_Char(const char CHARACTER)
{
    uint32_t Timeout = 0;

    if(CHARACTER == '\n')
    {
        Timeout = 0;

        while((++Timeout) && (UCA0IFG & 0x02 == 0));

        if(Timeout == 0) return;

        UCA0IFG = 0;

        UCA0TXBUF = 0x0d;
    }

    Timeout = 0;

    while((++Timeout) && (UCA0IFG & 0x02 == 0));

    if(Timeout == 0) return;

    UCA0IFG = 0;

    UCA0TXBUF = CHARACTER;
}