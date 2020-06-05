/*
  This is a library for the HC-SR04 I2C Ultrasonic sensor.
  This version of HC-SR04 uses I2C for communication. Two pins (SCL / SDA)
  are required to interface to the device. This library does not work with 
  HC-SR04 with GPIO interface.
  Written by KC, SGBotic.com 2020.
*/

#include "SGBotic_I2CPing.h"

// Define milliseconds delay for ESP8266 platform
#if defined(ESP8266)

  #include <pgmspace.h>
  #define _delay_ms(ms) delayMicroseconds((ms) * 1000)

// Use _delay_ms from utils for AVR-based platforms
#elif defined(__avr__)
  #include <util/delay.h>

// Use Wiring's delay for compability with another platforms
#else
  #define _delay_ms(ms) delay(ms)
#endif


SGBotic_I2CPing::SGBotic_I2CPing()
{
    SR04_I2CADDR = HC_SR04_I2C_ADDR;
    ds[0]=0;
    ds[1]=0;
    ds[2]=0;
    
    // Start I2C
    Wire.begin();
    
}

unsigned long SGBotic_I2CPing::ping_cm()
{
    Wire.beginTransmission(SR04_I2CADDR);
    Wire.write(1);          //1 = cmd to start meansurement
    Wire.endTransmission();
    delay(120);             //1 cycle approx. 100mS. 
    i = 0;
    Wire.requestFrom(0x57,3);  //read distance       
    while (Wire.available())
    {
     ds[i++] = Wire.read();
    }        
    
    distance = (unsigned long)(ds[0]) * 65536;
    distance = distance + (unsigned long)(ds[1]) * 256;
    distance = (distance + (unsigned long)(ds[2])) / 10000;
    
    //distance=(unsigned long)((ds[0]*65536+ds[1]*256+ds[2])/10000);  
    
    if ((1<=distance)&&(900>=distance))    //measured value between 1cm to 9meters
    {
        return distance;
    }else 
    {
        return 0;
    }
    
}