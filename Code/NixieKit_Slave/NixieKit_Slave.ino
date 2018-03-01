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
#define NIX_INTERVAL_MSEC 10

#define NIX_INTERVAL_MSEC 10
#define NIX_BLINK_MSEC 500


uint8_t sel = 1;
uint8_t numA = 0;
uint8_t numB = 0;
uint8_t minute = 0;
uint8_t temp = 0;
uint16_t subcount = 0;
uint8_t mode = MODE_NORMAL;

//
// uint8_t transition(uint8_t bStart, uint8_t bEnd){
// /*
//   for (uint8_t j=0; j<TRAN; j++){
//     for (uint8_t i=100; i>0; i--){
//       numA = bStart / 10;
//       numB = bStart % 10;
//       delay(i);
//       numA = bEnd / 10;
//       numB = bEnd % 10;
//       delay(100 - i);
//     }
//   }
// */
//   numA = bEnd / 10;
//   numB = bEnd % 10;
//   return bEnd;
// }

void receiveEvent() {

  while (0 < Wire.available()){
    temp = Wire.read();
  }

  if(temp > 99 && mode != temp){
    mode = temp;
    switch(mode){
      MODE_NORMAL:
        NIXMin.stopBlink();
        break;
      MODE_TIMESET_MIN:
        NIXMin.startBlink(NIX_BLINK_MSEC);
        break;
      default:
        break;
    }
  }

  if(minute != temp && temp < 99) minute = temp;
}

void setup() {
  NIXMin.init(NIX_A, NIX_B, PIN_A, PIN_B, PIN_C, PIN_D);
  NIXMin.setInterval(NIX_INTERVAL_MSEC);

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
}

void loop() {
  // put your main code here, to run repeatedly:

}
