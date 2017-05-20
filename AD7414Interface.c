/*
 * AD7414Interface.c
 *
 */

#include "AD7414Interface.h"

/// Configure
/// \brief configure the AD7414
/// \param THighCenti_C - High temperature threshold in (deg C / 100)
/// \param TLowCenti_C - Low temperature threshold in (deg C / 100)
/// \param nAlert - Alert configuration
/// \param nPower - Power Mode Configuration
/// \return - status -1 = error
int Configure(char THigh_C,
        char TLow_C,
        ALERT_VALUE nAlert,
        POWER_DOWN_MODE nPower,
        char i2c_address)
{
    //Set the Configuration Register
    char reg_value = DEFAULT_CONFIGURATION |
            (nAlert<<ALERT_SHIFT) |
            (nPower<<POWER_DOWN_SHIFT);
    // if configuring for power down operation ensure the one shot is set
    if(nPower == FULL_POWER_DOWN)
    {
        reg_value |= ONE_SHOT_MASK;
    }
    int nStatus = SetRegister(CONFIG_REG, reg_value, i2c_address);
    if(nStatus<0)
    {
        return nStatus;
    }
    nStatus = SetRegister(T_HIGH_REG, THigh_C, i2c_address);
    if(nStatus<0)
    {
        return nStatus;
    }
    nStatus = SetRegister(T_LOW_REG, TLow_C, i2c_address);
    //TODO determine if we need to read back the registers to ensure properly setup?
    return nStatus;
}

/// ReadTemperature
/// \brief Read the temperature
/// \param THighCenti_C - High temperature threshold in (deg C * 100)
/// \return - status -1 = error
int ReadTemperature(int *TempCenti_C, READ_MODE nReadMode, char i2c_address)
{
    if(TempCenti_C == NULL)
    {
        return ERROR_VALUE;
    }
//
    // Write to select reading from the Temperature Register
    char nRegister = TEMPERATURE_REG;
    int nStatus = i2c_open();
    if(nStatus<0)
    {
        i2c_close();
        return nStatus;
    }
    int nBytes = i2c_write(&nRegister, sizeof(nRegister), i2c_address);
    nStatus = i2c_close();
    if((nBytes!=1) || (nStatus<0))
    {
        return ERROR_VALUE;
    }
    char ReadBuffer[2];
    nStatus = i2c_open();
    if(nStatus<0)
    {
        i2c_close();
        return nStatus;
    }
    nBytes = i2c_read(ReadBuffer, sizeof(ReadBuffer), i2c_address);
    nStatus = i2c_close();
    if(nBytes != 2)
    {
        return ERROR_VALUE;
    }
    // calculate the temperature value
    *TempCenti_C = GetTempC((ReadBuffer[0]<<2) + (ReadBuffer[1]>>6));
    return nStatus;
}


/// SetRegister
/// \brief Set a given register
/// \param REGISTER_ADDRESS - register to set
/// \param nData - data to set
/// \param i2c_address - address of device
/// \return - status -1 = error
int SetRegister(REGISTER_ADDRESS nRegister, char nData, char i2c_address)
{
    char Buffer[2];
    Buffer[I2C_FRAME_2] = nRegister & 0x3;
    Buffer[I2C_FRAME_3] = nData;
    // must open the i2c prior to read or write and close after
    int nStatus = i2c_open();
    if(nStatus<0)
    {
        i2c_close();
        return nStatus;
    }
    int nBytes = i2c_write(Buffer, sizeof(Buffer), i2c_address);
    nStatus = i2c_close();
    if(nBytes != 2)
    {
        return ERROR_VALUE;
    }
    return nStatus;
}

/// GetTempC
/// \brief Calculate the temperature from the binary output
/// \param nRegisterValue - register value from read
/// \return - temperature in (deg C * 100)
int GetTempC(unsigned int nRegisterValue)
{
    //Check the sign bit and add bits to make into signed int
    if((nRegisterValue & SIGN_BIT) == SIGN_BIT)
    {
        nRegisterValue = nRegisterValue | ~0x3FF;
    }
    return ((int)nRegisterValue) * TEMP_CONVERSION_FACTOR;
}

/// GetTempBinary
unsigned int GetTempBinary(int TempCenti_C)
{
    // TODO determine if rounding here is an issue
    return (TempCenti_C/TEMP_CONVERSION_FACTOR)&0x3FF;
}
