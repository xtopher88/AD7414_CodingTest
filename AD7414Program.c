/*
 ============================================================================
 Name        : TestProgram.c
 Author      : Kevin Christopher
 Version     :
 Description : I2C sensor interface coding test
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "AD7414Interface.h"
#include "I2C_test.h"

// inputs file_name, c, N
int main (int argc, char *argv[])
{
    //check that there are the correct number of arguments
    if(argc < 4)
    {
        printf("not enough arguments\n./TestProgram T_high T_low Alert Continuous\n");
        printf("T_high = temperature in deg C signed\n");
        printf("T_low = temperature in deg C signed\n");
        printf("Alert = (0=disabled)\n");
        printf("Continuous = (0=disabled)\n");
        return EXIT_SUCCESS;
    }

    int t_high = atoi(argv[1]);
    int t_low = atoi(argv[2]);
    int nAlert = atoi(argv[3]);
    int nContinuous = atoi(argv[4]);
    //printf("Reading Temperature, Th=%d, Tl=%d, Alert=%d, Continuous=%d\n",t_high,t_low,nAlert,nContinuous);

#ifdef CODE_TESTS
    //Test temperature conversion
    TestTempConversion();
#endif

    //Configure the AD7414
    int nStatus = Configure(t_high,
            t_low,
            (nAlert==0) ? ALERT_DISABLED:ALERT_ENABLED,
            (nContinuous==0) ? FULL_POWER_DOWN:NORMAL_POWER_MODE,
            0x48);
    if(nStatus<0)
    {
        printf("Error configuring the Temp Sensor\n");
    }

    int nTemp_CentiC=0;
    nStatus = ReadTemperature(&nTemp_CentiC, READ_ONE_SHOT, 0x48);
    if(nStatus<0)
    {
        printf("Error configuring the Temp Sensor\n");
    }
    else
    {
        printf("Temp Reading = %f\n", (float)nTemp_CentiC/100.0);
    }

    return EXIT_SUCCESS;
}

