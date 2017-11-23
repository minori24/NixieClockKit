#include <FlexiTimer2.h>
#include <Wire.h>

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define NIX_A 9
#define NIX_B 10

#define TRAN 10
#define MODE_NORMAL 100
#define MODE_TIMESET_MIN 102

uint8_t sel = 1;
uint8_t numA = 0;
uint8_t numB = 0;
uint8_t minute = 0;
uint8_t temp = 0;
uint16_t subcount = 0;
uint8_t mode = MODE_NORMAL;
  
void writeNix() {
  uint8_t num;
 
  if (sel == 0){
    sel = 1;
  }
  else {
    sel = 0;
  }
  
  if(mode == MODE_TIMESET_MIN){
    if(subcount < 20){
      subcount++;      
      if (sel == 0){
        digitalWrite(NIX_A, HIGH);
        digitalWrite(NIX_B, LOW);
        num = numA;
      }
      else{
        digitalWrite(NIX_A, LOW);
        digitalWrite(NIX_B, HIGH);
        num = numB;
      }
    }
    else if(subcount < 40){
      subcount++;
      digitalWrite(NIX_A, LOW);
      digitalWrite(NIX_B, LOW);
    }
    else{
      subcount = 0;
    }
  }
  else{  
    if (sel == 0){
      digitalWrite(NIX_A, HIGH);
      digitalWrite(NIX_B, LOW);
      num = numA;
    }
    else if (sel == 1){
      digitalWrite(NIX_A, LOW);
      digitalWrite(NIX_B, HIGH);
      num = numB;
    }
    else{
      digitalWrite(NIX_A, LOW);
      digitalWrite(NIX_B, LOW);
    }
  }
  if((num & 0x01) > 0) digitalWrite(PIN_A, HIGH);
  else digitalWrite(PIN_A, LOW);
  
  if((num & 0x02) > 0) digitalWrite(PIN_B, HIGH);
  else digitalWrite(PIN_B, LOW);
  
  if((num & 0x04) > 0) digitalWrite(PIN_C, HIGH);
  else digitalWrite(PIN_C, LOW);
  
  if((num & 0x08) > 0) digitalWrite(PIN_D, HIGH);
  else digitalWrite(PIN_D, LOW);
 
}

uint8_t transition(uint8_t bStart, uint8_t bEnd){
/*  
  for (uint8_t j=0; j<TRAN; j++){
    for (uint8_t i=100; i>0; i--){
      numA = bStart / 10;
      numB = bStart % 10;
      delay(i);
      numA = bEnd / 10;
      numB = bEnd % 10;
      delay(100 - i);
    }
  }
*/
  numA = bEnd / 10;
  numB = bEnd % 10;
  return bEnd;
}

void receiveEvent() {

  while (0 < Wire.available()){
    temp = Wire.read();
  }

  //if(mode == MODE_NORMAL && temp == MODE_TIMESET_MIN) mode = MODE_TIMESET_MIN;
  //if(mode == MODE_TIMESET_MIN && temp == MODE_NORMAL) mode == MODE_NORMAL;
  if(temp > 99) mode = temp;

  if(minute != temp && temp < 99) minute = transition(minute, temp);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(NIX_A, OUTPUT);
  pinMode(NIX_B, OUTPUT);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  
  FlexiTimer2::set(10, writeNix); // call every 500 1ms "ticks"
  // FlexiTimer2::set(500, flash); // MsTimer2 style is also supported
  FlexiTimer2::start();
}

void loop() {
  // put your main code here, to run repeatedly:
  while(1){
    delay(1000);
  }
}

