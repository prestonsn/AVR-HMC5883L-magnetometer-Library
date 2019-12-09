# AVR-HMC5883L-magnetometer-Library
C library to interface the HMC5883L with the AVR microcontrollers.

## Functionality:
HMC5883l_getX(void) -> returns the change in X position from restart

HMC5883l_getY(void) -> returns the change in Y position from restart  

HMC5883l_getZ(void) -> returns the change in Z position from restart

HMC5883l_getHeadingDegrees(void) -> returns the current bearing relative to true north.
