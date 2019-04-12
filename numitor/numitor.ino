#include <SoftwareSerial.h>
SoftwareSerial bluetooth(3, 4);  // RX, TX
 int ledpin=13; 

float wheelsRadius = 0.33;  // the radius of  wheel 
 volatile byte rotation; 
 float timetaken,rpm,dtime;
 int velocity;
 unsigned long pevtime;



 void motor(void);
 char command;
 int mRelayPin = 6;
void setup()
  {
    motor();
    bluetooth.begin(9600); 
    pinMode(mRelayPin,HIGH);
    attachInterrupt(0, hallMagnet, RISING); 
    rotation = rpm = pevtime = 0;
  }
 void loop()
 {
   
  if(millis()-dtime>1500) 
  {
   rpm= velocity = 0; 
   bluetooth.write(velocity);
   dtime=millis();
  }
  velocity = wheelsRadius * rpm * 0.37699; 
 }
 void hallMagnet() 
 {
   rotation++;
   dtime=millis();
   if(rotation>=2)
   {
     timetaken = millis()-pevtime; //time in millisec for two rotations
     rpm=(1000/timetaken)*60;    //formulae to calculate rpm
     pevtime = millis();
     rotation=0;
     bluetooth.write(velocity);
  
   }
    }
   void motor(void)
   {
   command = bluetooth.read();
    if(command == 'a')
    digitalWrite(mRelayPin,LOW);
    else if(command == 'b')
    digitalWrite(mRelayPin,HIGH);
   }
