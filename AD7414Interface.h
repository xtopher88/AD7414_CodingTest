/*
 * AD7414Interface.h
 *
 */

#ifndef AD7414INTERFACE_H_
#define AD7414INTERFACE_H_

// Common definitions
#define ERROR_VALUE -1
#define NULL ((void *)0)

#define SIGN_BIT 0x200
#define TEMP_CONVERSION_FACTOR 25
// the default configuration, i2c filtering on and alert reset active
#define DEFAULT_CONFIGURATION 0x48
// masks for setting configuration
#define POWER_DOWN_SHIFT 7
#define ALERT_SHIFT 5

#define ONE_SHOT_MASK = 0x04

// Interface to AD7414
typedef enum
{
    ALERT_ENABLED,
    ALERT_DISABLED
}ALERT_VALUE;

typedef enum
{
    NORMAL_POWER_MODE,
    FULL_POWER_DOWN
}POWER_DOWN_MODE;

typedef enum
{
    READ_LAST,
    READ_ONE_SHOT
}READ_MODE;

/// Configure
/// \brief configure the AD7414
/// \param THigh_C - High temperature threshold in (deg C)
/// \param TLow_C - Low temperature threshold in (deg C)
/// \param nAlert - Alert configuration
/// \param nPower - Power Mode Configuration
/// \return - status -1 = error
int Configure(char THigh_C,
        char TLow_C,
        ALERT_VALUE nAlert,
        POWER_DOWN_MODE nPower,
        char i2c_address);


/// ReadTemperature
/// \brief Read the temperature
/// \param THighCenti_C - High temperature threshold in (deg C * 100)
/// \return - status -1 = error
int ReadTemperature(int *TempCenti_C, READ_MODE nReadMode, char i2c_address);



// Helper Functions and Descriptions

// description of the frames in the buffer for the i2c interface
typedef enum
{
    I2C_FRAME_2,
    I2C_FRAME_3
}I2C_FRAME;

// register addresses
typedef enum
{
    TEMPERATURE_REG,
    CONFIG_REG,
    T_HIGH_REG,
    T_LOW_REG
}REGISTER_ADDRESS;


/// SetRegister
/// \brief Set a given register
/// \param REGISTER_ADDRESS - register to set
/// \param nData - data to set
/// \param i2c_address - address of device
/// \return - status -1 = error
int SetRegister(REGISTER_ADDRESS nRegister, char nData, char i2c_address);

/// GetTempC
/// \brief Calculate the temperature from the binary output
/// \param nRegisterValue - register value from read
/// \return - temperature in (deg C * 100)
int GetTempC(unsigned int nRegisterValue);

/// GetTempBinary
/// \brief Inverse temperature function for testing
unsigned int GetTempBinary(int TempCenti_C);



// pre defined i2c interface

/* Performs I 2 C bus initialization. Must be performed prior to reading from or
writing to any devices on the bus. Returns less than 0 on error.*/
int i2c_open(void);
/* Performs a single I 2 C write transaction from ‘buf’ of ‘size’ bytes to device ‘addr’ on
a common I2C bus. Returns less than 0 on failed transactions, number of bytes
written on success. */
int i2c_write(char *buf, int size, char device_addr);
/* Performs a single I 2 C read transaction of ‘size’ bytes and copies read data into the
provided ‘buf’ buffer. Buffer must be large enough to store ‘size’ bytes. Returns less
than 0 on failed transactions, number of bytes read on success. */
int i2c_read(char *buf, int size, char device_addr);
/* Performs I 2 C bus cleanup. Must be performed after reading from or writing to
any devices on the bus. Returns less than 0 on error. */
int i2c_close(void);
#endif /* AD7414INTERFACE_H_ */
