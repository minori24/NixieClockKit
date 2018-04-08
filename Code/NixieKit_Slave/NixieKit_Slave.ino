#include <FlexiTimer2.h>
#include <Wire.h>
#include "NixieDynamic.h"

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define NIX_A 9
#define NIX_B 10

#define MODE_NORMAL 100
#define MODE_TIMESET_MIN 102
#define NIX_INTERVAL_MSEC 8
#define NIX_BLINK_MSEC 500

NixieDynamic NIXMin;

uint8_t minute = 0;
uint8_t temp = 0;
uint8_t mode = MODE_NORMAL;
uint8_t tMinute = 0;

void receiveEvent(int numByte) {

  while (Wire.available() > 0){
    temp = Wire.read();
  }
  
  if(temp > 99 && mode != temp){
    mode = temp;
    switch(mode){
      case  MODE_NORMAL:
        NIXMin.stopBlink();
        break;
      case MODE_TIMESET_MIN:
        NIXMin.startBlink(NIX_BLINK_MSEC);
        break;
      default:
        break;
    }
  }
  else if(temp < 60){
    minute = temp;
    NIXMin.write(temp);
  }
  else{
    
  }
}

void setup() {
  NIXMin.init(NIX_A, NIX_B, PIN_A, PIN_B, PIN_C, PIN_D);
  //NIXMin.setInterval(NIX_INTERVAL_MSEC);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() {
  while(1){
    // put your main code here, to run repeatedly:

  }
}
