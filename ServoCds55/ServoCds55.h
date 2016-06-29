/*
ServoCds55.h - Library for Digital Servo Driver Shield
OCT 24th, 2014
Version 1.0
*/


#ifndef __ServoCds55_H
#define __ServoCds55_H

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <SPI.h>

class ServoCds55
{
public:
    ServoCds55(int CS=10);
	void begin();
    void WritePos(int ID,int Pos);
    void write(int ID,int Pos);
    void setVelocity(int velocity);
    void setPoslimit(int posLimit);
    void rotate(int ID,int velocity);
    void SetServoLimit(int ID,int upperLimit);
    void SetMotormode(int ID, int velocity);
    void SetID(int ID, int newID);
    void Reset(int ID);
    byte transferAndWait (const byte what);

private:
    int velocity_temp;
    int upperLimit_temp;
    int cs;
};

#endif



