#include "C:\ti\msp\MSP432Ware_3_50_00_02\driverlib\driverlib\MSP432P4xx\driverlib.h"

#include "Simple_EOS.h"
#include "PC_O_UCA0.h"
#include "Elap_232.h"
#include "PC_O.h"

uint8_t Hour_G;
uint8_t Min_G;
uint8_t Sec_G;

extern char CHAR_MAP[10];

void Elapsed_Time_RS232_Init(void)
{
    Hour_G = 0;
    Min_G = 0;
    Sec_G = 0;
}
void Elapsed_Time_RS232_Update(void)
{
    char Time_Str[30] = "\rElapsed Time: ";

    if(++Sec_G == 60)// Every 1 min
    {
        Sec_G = 0;

        if(++Min_G == 60)// Every 1 hour
        {
            Min_G = 0;

            if(++Hour_G == 24)// Every 24 hours
            {
                Hour_G = 0;
            }
        }
    }

    // Calculating hours, minutes and seconds to be displayed
    
    Time_Str[15] = CHAR_MAP[Hour_G / 10];
    Time_Str[16] = CHAR_MAP[Hour_G % 10];

    Time_Str[18] = CHAR_MAP[Min_G / 10];
    Time_Str[19] = CHAR_MAP[Min_G % 10];

    Time_Str[21] = CHAR_MAP[Sec_G / 10];
    Time_Str[22] = CHAR_MAP[Sec_G % 10];

    if((Sec_G % 2) == 0)
    {
        Time_Str[17] = ':';
        Time_Str[20] = ':';
    }
    else
    {
        Time_Str[17] = ' ';
        Time_Str[20] = ' ';
    }

    Time_Str[23] = ' ';

    // Send data to the buffer
    PC_LINK_O_Write_String_To_Buffer(Time_Str);
}
