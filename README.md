# IN-12A Nixie Clock Kit by Fablab Kannai
Nixie tube controller board and Arduino code for digital clock. Two nixie tubes for each board,
multiple boards can be connected with pin headers/sockets soldered on board side.


1枚あたり2桁を表示するニキシー管コントロール基板です。ピンソケット/ピンヘッダを基板に取り付けることで複数枚を接続し、
表示する桁を拡張することが可能です。

## 仕様
Nixie Tube: IN-12A/B (dp not used)
Controller: ATMEGA88/168/328


Release
## v1.0
RTC付き時計完成版
第1回ニキシー管組み立てワークショップ(2017/12/16)で使用

## v2.0
### 基板
Footprintの間違いを修正
I/Oピン名のシルクを追加
制御基板とニキシー管基板を繋いでいたLong HoleをV-cutに変更

### ファームウェア
毎分残り10秒から分桁に秒を表示するよう変更

