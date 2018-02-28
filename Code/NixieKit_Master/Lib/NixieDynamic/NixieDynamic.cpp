#include "NixieDynamic.h"

uint8_t _nixA, _nixB, _pinA, _pinB, _pinC, _pinD;
uint8_t sel = 0;
uint8_t _interval = 10;
uint8_t _numA, _numB;
uint8_t bBlink = 0;

uint8_t mode = MODE_NORMAL;
unsigned long elaplsed, _interval_blink = 0;

// nixA/B: Anode control pins for each digit
// pinX: BCD Code digit pins for K155ID1
void NixieDynamic::init(uint8_t nixA, uint8_t nixB, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD)
{
  _nixA = nixA;
  _nixB = nixB;
  _pinA = pinA;
  _pinB = pinB;
  _pinC = pinC;
  _pinD = pinD;

  _numA = 0;
  _numB = 0;

  pinMode(_pinA, OUTPUT);
  pinMode(_pinB, OUTPUT);
  pinMode(_pinC, OUTPUT);
  pinMode(_pinD, OUTPUT);
  pinMode(_nixA, OUTPUT);
  pinMode(_nixB, OUTPUT);

  FlexiTimer2::set(_interval, write); // call every 500 1ms "ticks"
  // FlexiTimer2::set(500, flash); // MsTimer2 style is also supported
  FlexiTimer2::start();
}

void NixieDynamic::setInterval(uint8_t t)
{
  _interval = t;
  FlexiTimer2::stop();
  FlexiTimer2::set(_interval, _write);
  FlexiTimer2::start();
}

// num: 0 - 99
void NixieDynamic::write(uint8_t num)
{
  _numA = num / 10;
  _numB = num % 10;
}

void NixieDynamic::_write()
{
  uint8_t num;
  // if (sel == 0){
  //   sel = 1;
  // }
  // else {
  //   sel = 0;
  // }

  sel = sel ^ 1;

  if (sel){
    digitalWrite(_nixA, HIGH);
    digitalWrite(_nixB, LOW);
    num = _numA;
  }
  else{
    digitalWrite(_nixA, LOW);
    digitalWrite(_nixB, HIGH);
    num = _numB;
  }

  if(millis() - elapsed > _interval_blink){
    //Disable Nixie
    if(bBlink){
      digitalWrite(_nixA, LOW);
      digitalWrite(_nixB, LOW);
    }

    elapsed = millis();
  }

  if((num & 0x01) > 0) digitalWrite(_pinA, HIGH);
  else digitalWrite(_pinA, LOW);

  if((num & 0x02) > 0) digitalWrite(_pinB, HIGH);
  else digitalWrite(_pinB, LOW);

  if((num & 0x04) > 0) digitalWrite(_pinC, HIGH);
  else digitalWrite(_pinC, LOW);

  if((num & 0x08) > 0) digitalWrite(_pinD, HIGH);
  else digitalWrite(_pinD, LOW);
}

void NixieDynamic::startBlink(uint8_t interval)
{
  _interval_blink = interval;
  bBlink = 1;
}

void NixieDynamic::stopBlink()
{
  bBlink = 0;
}
