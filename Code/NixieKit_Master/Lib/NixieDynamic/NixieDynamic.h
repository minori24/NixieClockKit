// Nixie Tube Dynamic Driver Library for Nixie Clock bu Fablab Kannai

#include <FlexiTimer2.h>

#define MODE_NORMAL 0
#define MODE_BLINK 1

class NixieDynamic
{
  public:
    void initNixie(uint8_t nixA, uint8_t nixB, uint8_t pinA, uint8_t pinB, uint8_t pinC, uint8_t pinD);
    void setInterval(uint8_t t);
    void write(uint8_t numA, uint8_t numB);
    void startBlink(uint8_t interval);
    void stopBlink();
  private:
    _write();
};
