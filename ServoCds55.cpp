/*
ServoCds55.cpp - Library for Digital Servo Driver Shield
OCT 24th, 2014
Version 1.0
*/

#include "ServoCds55.h"


ServoCds55::ServoCds55 (int CS):cs(CS)
{
    velocity_temp = 150;
    upperLimit_temp = 300;
}

void ServoCds55::begin()
{
	pinMode(cs,OUTPUT);	
    digitalWrite(cs,HIGH);
	SPI.begin ();
	SPI.setClockDivider(SPI_CLOCK_DIV8);
}

byte ServoCds55::transferAndWait (const byte what)
{
  byte a = SPI.transfer (what);
  delayMicroseconds (20);
  return a;
} 

void ServoCds55::setVelocity(int velocity){   //set servo velocity
  velocity_temp = velocity;
}

void ServoCds55::setPoslimit(int posLimit){  // set servo pos limit
  upperLimit_temp =  posLimit;
}

void ServoCds55::write(int ID,int Pos){     //  Servo Mode
  SetServoLimit(ID,upperLimit_temp);
  WritePos(ID,Pos);// default velocity:150 
}

void ServoCds55::rotate(int ID,int velocity){ // Motor Mode
  SetServoLimit(ID,0);
  delay(100);
  SetMotormode(ID,velocity);  
}

void ServoCds55::WritePos(int ID,int Pos){ 

  int PosB = (Pos>>8 & 0xff);//low
  int PosS = (Pos & 0xff);//high
  int velocityB = (velocity_temp>>8 & 0xff);
  int velocityS = (velocity_temp & 0xff);
  digitalWrite(cs, LOW);    
  transferAndWait ('p');
  transferAndWait (ID); 
  transferAndWait (PosB);
  transferAndWait (PosS);
  transferAndWait (velocityB);
  transferAndWait (velocityS);
  transferAndWait ('\t');
  transferAndWait ('\r');
  transferAndWait ('\n');
  digitalWrite(cs, HIGH);
  delay(10);
}  

void ServoCds55::SetServoLimit(int ID,int  upperLimit_temp){

  int upperLimitB = (upperLimit_temp>>8 & 0xff);
  int upperLimitS =  (upperLimit_temp & 0xff);
  digitalWrite(cs, LOW);    
  transferAndWait ('s');
  transferAndWait (ID);
  transferAndWait (upperLimitB);
  transferAndWait (upperLimitS);
  transferAndWait ('\t');
  transferAndWait ('\r');
  transferAndWait ('\n');
  digitalWrite(cs, HIGH);
  delay(10);
}

void ServoCds55::SetMotormode(int ID, int velocity){	

  int velocityB = (velocity>>8 & 0xff);
  int velocityS = (velocity & 0xff);
  digitalWrite(cs, LOW);    
  transferAndWait ('m');
  transferAndWait (ID);
  transferAndWait (velocityB);
  transferAndWait (velocityS);
  transferAndWait ('\t');
  transferAndWait ('\r');
  transferAndWait ('\n');
  digitalWrite(cs, HIGH);
  delay(10);
}

void ServoCds55::SetID(int ID, int newID){

  digitalWrite(cs, LOW);    
  transferAndWait ('i');
  transferAndWait (ID);
  transferAndWait (newID);
  transferAndWait ('\t');
  transferAndWait ('\r');
  transferAndWait ('\n');
  digitalWrite(cs, HIGH);
  delay(10);
}  

void ServoCds55::Reset(int ID){

  digitalWrite(cs, LOW);    
  transferAndWait ('r');
  transferAndWait (ID);
  transferAndWait ('\t');
  transferAndWait ('\r');
  transferAndWait ('\n');
  digitalWrite(cs, HIGH);
  delay(10);
}


