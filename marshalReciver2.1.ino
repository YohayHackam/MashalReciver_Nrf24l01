#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include "settings.h"
#include "radio.h"

RF24 radio(CE, CSN); // Establish a new RF24 object

void setup() 
{
  Serial.begin(9600); //open serial port
  printf_begin();     //needed for Debug NRF24 Module
  PinMode();          //set I/O pins
  RadioSetup();       //setup & start NRF24 
  LedStartUp();       //test onboard LEDS 
}

void loop() 
{
  while(ReciveData())  //listen to incuming data & update leds
  {
     if(recivedData.targetId==NODE_ID) //chack if data for this node
        { 
          sentData.commandValue=recivedData.commandValue;  //prepare data for return acqnolaged
          sentData.targetId=NODE_ID;   //add reciver id for return acqnolaged
          while(!SendData());     //replay data acqnolaged
          UpdateLed();
          debug();
        }    
  }
    
}
