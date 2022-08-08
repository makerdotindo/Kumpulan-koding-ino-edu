// Receiver code
/* 
WIRING ESP32  -  EbyteE32
GPIO   16 RX      TX
       17 TX      RX
       M0         Gnd
       M1         Gnd
       Vcc        3.3v
*/
#include <SoftwareSerial.h>

SoftwareSerial loraSerial(16, 17); // TX, RX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  loraSerial.begin(9600);
  Serial.println("LORA RECEIVED");
}

void loop() {
  // put your main code here, to run repeatedly:
  if(loraSerial.available()>0){
    String input = loraSerial.readString();
    Serial.print("I Received msg : ");
    Serial.println(input);
  }

}
