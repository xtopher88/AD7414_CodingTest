compiled it and run on ubuntu linux using gcc version 5.4.0

AD7414Interface.c,h - the interface to the AD7414 Temperature Sensor

I2C_test.c,h i is a test i2c interface implementation to debug the interface

AD7414Program.c - the console interface to read temperature

Test Outputs

$ ./TestProgram 
not enough arguments
./TestProgram T_high T_low Alert Continuous
T_high = temperature in deg C signed
T_low = temperature in deg C signed
Alert = (0=disabled)
Continuous = (0=disabled)

Testing output
$ ./TestProgram 100 -5 0 0
Conversion Test Successful
i2c open
i2c write to 72 , 1, 236
i2c close
i2c open
i2c write to 72 , 2, 100
i2c close
i2c open
i2c write to 72 , 3, 251
i2c close
i2c open
i2c write to 72 , 0
i2c close
i2c open
i2c read 2, 72
i2c close
Temp Reading = 112.250000

$ ./TestProgram 50 10 1 0
Conversion Test Successful
i2c open
i2c write to 72 , 1, 204
i2c close
i2c open
i2c write to 72 , 2, 50
i2c close
i2c open
i2c write to 72 , 3, 10
i2c close
i2c open
i2c write to 72 , 0
i2c close
i2c open
i2c read 2, 72
i2c close
Temp Reading = 112.250000

$ ./TestProgram 80 5 0 1
Conversion Test Successful
i2c open
i2c write to 72 , 1, 108
i2c close
i2c open
i2c write to 72 , 2, 80
i2c close
i2c open
i2c write to 72 , 3, 5
i2c close
i2c open
i2c write to 72 , 0
i2c close
i2c open
i2c read 2, 72
i2c close
Temp Reading = 112.250000








