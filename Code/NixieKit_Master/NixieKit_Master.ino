#include <FlexiTimer2.h>
#include <Wire.h>
#include <RTClib.h>

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define NIX_A 9
#define NIX_B 10

#define TRAN 200
#define NIX_INTERVAL_MSEC 10
#define PIN_BUTTON_MODE A0
#define PIN_BUTTON_COUNT A2

#define BUTTON_COUNT_SHORT 2
#define BUTTON_COUNT_LONG 8

#define ADDR_MIN 8
#define ADDR_RTC 

#define MODE_NORMAL 100
#define MODE_TIMESET_HOUR 101
#define MODE_TIMESET_MIN 102

RTC_DS1307 RTC;

uint8_t sel = 1;
uint8_t numA = 0;
uint8_t numB = 0;
uint8_t numC = 0;
uint8_t numD = 0;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
uint16_t subcount = 0;
uint8_t bTimeSetDone = 0;
uint8_t bCountStart = 0;


uint8_t mode = MODE_NORMAL;

unsigned long prev_t = 0;

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit (digitalPinToPCMSKbit(pin));  // enable pin
    PCIFR  |= bit (digitalPinToPCICRbit(pin)); // clear any outstanding interrupt
    PCICR  |= bit (digitalPinToPCICRbit(pin)); // enable interrupt for the group
}

ISR (PCINT1_vect) // handle pin change interrupt for A0 to A5 here
 {
    if(millis() - prev_t > 300){
      if(digitalRead(PIN_BUTTON_MODE) == LOW) setMode();
      if(digitalRead(PIN_BUTTON_COUNT) == LOW) setTime();
      prev_t = millis();
    }
}

void writeNix() {
  uint8_t num;
  
  if (sel == 0){
    sel = 1;
  }
  else {
    sel = 0;
  }
  
  numA = hour / 10;
  numB = hour % 10; 
  
  if(mode == MODE_TIMESET_HOUR){
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

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_A, OUTPUT);
  pinMode(PIN_B, OUTPUT);
  pinMode(PIN_C, OUTPUT);
  pinMode(PIN_D, OUTPUT);
  pinMode(NIX_A, OUTPUT);
  pinMode(NIX_B, OUTPUT);

  pinMode(PIN_BUTTON_MODE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_COUNT, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
  pinMode(A3, OUTPUT);
  digitalWrite(A1, LOW);
  digitalWrite(A3, LOW);
  
  Wire.begin(7);

  RTC.begin();
  if (! RTC.isrunning()) {
    Serial.println("RTC is NOT running!");
    // following line sets the RTC to the date & time this sketch was compiled
    RTC.adjust(DateTime(__DATE__, __TIME__));
  }

  mode = MODE_NORMAL;
  
  FlexiTimer2::set(NIX_INTERVAL_MSEC, writeNix); // call every 500 1ms "ticks"
  // FlexiTimer2::set(500, flash); // MsTimer2 style is also supported
  FlexiTimer2::start();

  Serial.begin(9600);
  pciSetup(PIN_BUTTON_MODE);
  pciSetup(PIN_BUTTON_COUNT);
  EICRA |= bit (ISC11);
  sei();
}

void getTime(){
  DateTime now = RTC.now();
  hour = now.hour();
  minute = now.minute();
}

uint8_t transition(uint8_t bStart, uint8_t bEnd){
/*
  for (int i=TRAN; i>0; i--){
    numA = bStart / 10;
    numB = bStart % 10;
    delay(i);
    numA = bEnd / 10;
    numB = bEnd % 10;
    delay(TRAN-i);
  }
*/
  return bEnd; 
}

int buttonPressCount = 0;

void setMode(){
  //delay(50);
  if(mode == MODE_NORMAL){
    mode = MODE_TIMESET_HOUR;
    Serial.println("Mode: HOUR");
  }
  else if(mode == MODE_TIMESET_HOUR){
    mode = MODE_TIMESET_MIN;
    Serial.println("Mode: MIN");
  }
  else if(mode == MODE_TIMESET_MIN){
    mode = MODE_NORMAL;
    Serial.println("Mode: NORMAL");
    bTimeSetDone = 1;
  }
  else{
    mode = MODE_NORMAL;
    Serial.println("Mode: NORMAL");
    bTimeSetDone = 1;
    bCountStart = 0;
  }
}

void setTime(){
  //delay(50);
  if(mode == MODE_TIMESET_HOUR){
    if(hour < 23) hour++;
    else hour = 0;
    bCountStart = 1; 
   }
  else if(mode == MODE_TIMESET_MIN){
    if(minute < 59) minute++;
    else minute = 0;
    bCountStart = 1;
  }
  else{
    
  }
  
  Serial.println(String(hour) + ":" + String(minute));

}

void loop() {
  // put your main code here, to run repeatedly:

  while(1){
      if(bTimeSetDone == 1){
        DateTime now = RTC.now();
        DateTime newDate = DateTime(now.year(), now.month(), now.day(), hour, minute, now.second());
        RTC.adjust(newDate);
        bTimeSetDone == 0;
     }
     
    if(mode == MODE_NORMAL){
      getTime();
      Wire.beginTransmission(ADDR_MIN);
      Wire.write(MODE_NORMAL);
      Wire.endTransmission();
    }

    if(mode == MODE_TIMESET_HOUR){
       if(bCountStart){
        if(digitalRead(PIN_BUTTON_COUNT) == LOW){
            buttonPressCount++;
            if(buttonPressCount > BUTTON_COUNT_LONG){
              if(hour < 23) hour++;
              else hour = 0;
              buttonPressCount = 0;
            }
        }
        else{
          buttonPressCount = 0;
          bCountStart = 0;
        }
      }
    }

    if(mode == MODE_TIMESET_MIN){
      Wire.beginTransmission(ADDR_MIN);
      Wire.write(MODE_TIMESET_MIN);
      Wire.endTransmission();
      
      if(bCountStart){
        if(digitalRead(PIN_BUTTON_COUNT) == LOW){
            buttonPressCount++;
            if(buttonPressCount > BUTTON_COUNT_LONG){
              if(minute < 59) minute++;
              else minute = 0;
              buttonPressCount = 0;
            }
        }
        else{
          buttonPressCount = 0;
          bCountStart = 0;
        }
      }
   }
  
    delay(50);
    Wire.beginTransmission(ADDR_MIN);
    Wire.write(minute);
    Wire.endTransmission();  
 }  
}
