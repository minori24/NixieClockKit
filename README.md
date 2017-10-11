# NixieClockKit
1枚あたり2桁を表示するニキシー管コントロール基板です。

## 仕様
Nixie Tube: IN-12A/B
Controller: ATMEGA88/168/328

## 制御プログラム書き込み方法
方法1: SPI Header Pinを使ってSPIから書き込む (参考: [Arduino IDE から、生の AVR に ISP でスケッチを書き込む方法（ArduinoIDE 1.6.4以降版）- nomolkのブログ](http://nomolk.hatenablog.com/entry/2016/06/21/001322))

方法2: USB-UARTを使ってArduinoのプログラムを書き込む(Arduino Bootloaderが必要)

## 気になる点
### マイコンどれ使う?
Arduino Unoとして使うためにAVRを載せているが、Arduino Nanoクローン($2.5くらい)をそのまま乗せることも可能

メリット
* デバッグが簡単になる
* 少し安くなる

デメリット
* マイコンの信頼性が無い
