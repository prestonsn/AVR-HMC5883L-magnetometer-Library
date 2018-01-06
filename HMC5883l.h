//
//  HMC5883l.h
//
//
//  Created by ZeroWolf on 06/05/16.
//

#ifndef HMC5883l_h
#define HMC5883l_h

#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "simple_twi.h"



#define HMC5883l_ADDRESS           0x1E
#define HMC5883l_MODE_REGISTER     0x02
#define HMC5883l_CONTINOUS         0x00

//the different registers in the module that hold the values
#define HMC5883l_XregisterMSB   0x03
#define HMC5883l_XregisterLSB   0x04

#define HMC5883l_YregisterMSB   0x07
#define HMC5883l_YregisterLSB   0x08

#define HMC5883l_ZregisterMSB   0x05
#define HMC5883l_ZregisterLSB   0X06




int HMC5883l_getX(void){
    uint8_t XbufferMSB[1];
    uint8_t XbufferLSB[1];
    int x = 0;
    
    //clear the mode register to ensure continuse measurement
    //check data sheet
    twi_write(HMC5883l_ADDRESS, 1, HMC5883l_MODE_REGISTER, HMC5883l_CONTINOUS);

    
    twi_read(HMC5883l_ADDRESS, 1, HMC5883l_XregisterMSB, XbufferMSB);           //read register 0x03, MSB for x value
    twi_read(HMC5883l_ADDRESS, 1, HMC5883l_XregisterLSB, XbufferLSB);           //read register 0x04, LSB for x value
    x = XbufferMSB[0] << 8;    //msb
    x|= XbufferLSB[0];         //lsb
    
    //clear the mode register to ensure continuse measurement
    //check data sheet
    twi_write(HMC5883l_ADDRESS, 1, HMC5883l_MODE_REGISTER, HMC5883l_CONTINOUS);
    _delay_ms(5);
    
    return x;
}

int HMC5883l_getY(void){
    uint8_t YbufferMSB[1];
    uint8_t YbufferLSB[1];
    int y = 0;
    
    //clear the mode register to ensure continuse measurement
    //check data sheet
    twi_write(HMC5883l_ADDRESS, 1, HMC5883l_MODE_REGISTER, HMC5883l_CONTINOUS);
    
    
    twi_read(HMC5883l_ADDRESS, 1, HMC5883l_YregisterMSB, YbufferMSB);           //read register 0x07, MSB for y value
    twi_read(HMC5883l_ADDRESS, 1, HMC5883l_YregisterLSB, YbufferLSB);           //read register 0x08, LSB for y value
    y = YbufferMSB[0] << 8;    //msb
    y|= YbufferLSB[0];         //lsb
    
    //clear the mode register to ensure continuse measurement
    //check data sheet
    twi_write(HMC5883l_ADDRESS, 1, HMC5883l_MODE_REGISTER, HMC5883l_CONTINOUS);
    
    
    return y;
}

int HMC5883l_getZ(void){
    uint8_t ZbufferMSB[1];
    uint8_t ZbufferLSB[1];
    int z = 0;
    
    
    twi_read(HMC5883l_ADDRESS, 1, HMC5883l_ZregisterMSB, ZbufferMSB);           //read register 0x05, MSB for z value
    twi_read(HMC5883l_ADDRESS, 1, HMC5883l_ZregisterLSB, ZbufferLSB);           //read register 0x06, LSB for z value
    z = ZbufferMSB[0] << 8;    //msb
    z|= ZbufferLSB[0];         //lsb
    
    //clear the mode register to ensure continuse measurement
    //check data sheet
    twi_write(HMC5883l_ADDRESS, 1, HMC5883l_MODE_REGISTER, HMC5883l_CONTINOUS);
    
    
    return z;
}

float HMC5883l_getHeadingDegrees(void){
    
    float heading = atan2(HMC5883l_getY(),HMC5883l_getX());
    
    // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
    // using 0.22 for now
    
    float declinationAngle = 0.22;
    heading += declinationAngle;
    
    // Correct for when signs are reversed.
    if(heading < 0){
        heading += 2*M_PI;
    }
    // Check for wrap due to addition of declination.
    if(heading > 2*M_PI){
        heading -= 2*M_PI;
    }
    // Convert radians to degrees for readability.
    float headingDegrees = (heading * 180/M_PI);
    
    return headingDegrees;
}



#endif /* HMC5883l_h */
