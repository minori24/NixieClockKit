#include <Wire.h>
#include <RTClib.h>
#include "NixieDynamic.h"

#define TRAN 200
#define NIX_INTERVAL_MSEC 10
#define NIX_BLINK_MSEC 500
#define PIN_BUTTON_MODE A0
#define PIN_BUTTON_COUNT A2

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define NIX_A 9
#define NIX_B 10

#define BUTTON_COUNT_SHORT 2
#define BUTTON_COUNT_LONG 8

#define ADDR_MIN 8

#define MODE_NORMAL 100
#define MODE_TIMESET_HOUR 101
#define MODE_TIMESET_MIN 102

RTC_DS1307 RTC;
NixieDynamic NIXHour;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
uint16_t subcount = 0;
uint8_t bTimeSetDone = 0;
uint8_t bCountStart = 0;
uint8_t cMinute = 0;
uint8_t ledFlg = 0;


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

void setup() {

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

  NIXHour.init(NIX_A, NIX_B, PIN_A, PIN_B, PIN_C, PIN_D);
  NIXHour.setInterval(NIX_INTERVAL_MSEC);

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
  second = now.second();
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
    NIXHour.startBlink(NIX_BLINK_MSEC);
    Serial.println("Mode: SET_HOUR");
  }
  else if(mode == MODE_TIMESET_HOUR){
    mode = MODE_TIMESET_MIN;
    NIXHour.stopBlink();
    Serial.println("Mode: SET_MIN");
  }
  else if(mode == MODE_TIMESET_MIN){
    mode = MODE_NORMAL;
    Serial.println("Mode: NORMAL");
    bTimeSetDone = 1;
  }
  else{
    mode = MODE_NORMAL;
    Serial.println("Mode: NORMAL");
    bTimeSetDone = 0;
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
        DateTime newDate = DateTime(now.year(), now.month(), now.day(), hour, minute, 50);
        RTC.adjust(newDate);
        bTimeSetDone = 0;
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
    if(second < 49) Wire.write(minute);
    else Wire.write(second);
    Wire.endTransmission();

    if(minute != cMinute){
      cMinute = minute;
      if(ledFlg){
        ledFlg = 0;
        digitalWrite(A0, HIGH);
        digitalWrite(A3, HIGH);
      }
      else{
        digitalWrite(A0, LOW);
        digitalWrite(A3, LOW);
      }
    }

    Serial.println(String(hour) + ":" + String(minute) + ":" + String(second));

    NIXHour.write(hour);
  }
}

