

#include <stdio.h>
#include "I2C_test.h"
#include "AD7414Interface.h"

// Test interface


// test a subset of the temperature values
// returns -1 if there was an error
int TestTempConversion()
{
    //−55°C 11 0010 0100
    //−50°C 11 0011 1000
    //−25°C 11 1001 1100
    //−0.25°C 11 1111 1111
    //0°C 00 0000 0000
    //+0.25°C 00 0000 0001
    //+10°C 00 0010 1000
    //+25°C 00 0110 0100
    //+50°C 00 1100 1000
    //+75°C 01 0010 1100
    //+100°C 01 1001 0000
    //+125°C 01 1111 0100
    const unsigned int nTests = 6;
    const int temps[] = { -5500, -5000, -25, 1000, 7500, 12500};
    const unsigned int binary[] = { 804, 824, 1023, 40, 300, 500};
    unsigned int nIndex;
    // Test a subset of calculations match the table from the data sheet
    for(nIndex=0;nIndex<nTests;nIndex++)
    {
        int nCalcTemp = GetTempC(binary[nIndex]);
        unsigned int nCalcBinary = GetTempBinary(temps[nIndex]);
        if( (nCalcTemp!=temps[nIndex]) || (nCalcBinary!=binary[nIndex]))
        {
            printf("Error Converting Temps %d, %d, %d, %d\n",nCalcTemp,temps[nIndex],nCalcBinary, binary[nIndex]);
            return -1;
        }
    }

    // test conversion to temperature and back for all inputs
    for(nIndex=0;nIndex<0x3FF;nIndex++)
    {
        unsigned int nCalcBinary = GetTempBinary(GetTempC(nIndex));
        if(nCalcBinary != nIndex)
        {
            printf("Error Converting Temp at %d, %d\n",nIndex,nCalcBinary);
            return -1;
        }
    }
    printf("Conversion Test Successful\n");
    return nIndex;
}

/* Performs I 2 C bus initialization. Must be performed prior to reading from or
writing to any devices on the bus. Returns less than 0 on error.*/
int i2c_open(void)
{
    printf("i2c open\n");
    return 0;
}

/* Performs a single I 2 C write transaction from ‘buf’ of ‘size’ bytes to device ‘addr’ on
a common I2C bus. Returns less than 0 on failed transactions, number of bytes
written on success. */
int i2c_write(char *buf, int size, char device_addr)
{
    printf("i2c write to %d ", device_addr);
    int count = size;
    while(count-- > 0)
    {
        printf(", %d",(unsigned char)*buf++);
    }
    printf("\n");
    return size;
}
/* Performs a single I 2 C read transaction of ‘size’ bytes and copies read data into the
provided ‘buf’ buffer. Buffer must be large enough to store ‘size’ bytes. Returns less
than 0 on failed transactions, number of bytes read on success. */
int i2c_read(char *buf, int size, char device_addr)
{
    printf("i2c read %d, %d\n",size,device_addr);
    int count = size;
    while(count-- > 0)
    {
        //TODO add a better test here
        *buf++=0x70;
    }
    return size;
}

/* Performs I 2 C bus cleanup. Must be performed after reading from or writing to
any devices on the bus. Returns less than 0 on error. */
int i2c_close(void)
{
    printf("i2c close\n");
    return 0;
}
