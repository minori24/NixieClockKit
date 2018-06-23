#include <Wire.h>
#include <RTClib.h>
#include "NixieDynamic.h"

#define TRAN 200
#define NIX_INTERVAL_MSEC 5
#define NIX_BLINK_MSEC 500
#define PIN_BUTTON_MODE A0
#define PIN_BUTTON_COUNT A2

#define PIN_A 5
#define PIN_B 6
#define PIN_C 7
#define PIN_D 8
#define NIX_A 9
#define NIX_B 10

#define PIN_LED 1

#define BUTTON_COUNT_SHORT 2
#define BUTTON_COUNT_LONG 8

#define ADDR_MIN 8

#define MODE_NORMAL 100
#define MODE_TIMESET_HOUR 101
#define MODE_TIMESET_MIN 102

NixieDynamic NIXHour;

uint8_t hour = 0;
uint8_t minute = 0;
uint8_t second = 0;
uint16_t subcount = 0;
uint8_t bTimeSetDone = 0;
uint8_t bCountStart = 0;
uint8_t cMinute = 0;
uint8_t ledFlg = 0; 
uint8_t tSecond = 0;
  int count = 0;

uint8_t mode = MODE_NORMAL;

unsigned long prev_t = 0;

void setup() {

  pinMode(PIN_BUTTON_MODE, INPUT_PULLUP);
  pinMode(PIN_BUTTON_COUNT, INPUT_PULLUP);
  pinMode(A1, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(PIN_LED, OUTPUT);
  digitalWrite(A1, LOW);
  digitalWrite(A3, LOW);

  Wire.begin(7);
  
  mode = MODE_NORMAL;

  NIXHour.init(NIX_A, NIX_B, PIN_A, PIN_B, PIN_C, PIN_D);
  NIXHour.setInterval(NIX_INTERVAL_MSEC);
}

void loop() {
  // put your main code here, to run repeatedly:
//
//
//  Wire.beginTransmission(ADDR_MIN);
//  Wire.write(count);
//  Wire.endTransmission();
  
  NIXHour.write(count);
  if(count < 99) count += 11;
  else count = 0;
  delay(500);
}

