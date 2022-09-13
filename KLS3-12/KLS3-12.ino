// Transmitter code
/* 
WIRING ESP32  -  EbyteE32
GPIO   16 RX      TX
       17 TX      RX
       M0         Gnd
       M1         Gnd
       Vcc        3.3v
*/
#include <SoftwareSerial.h>
int counter = 0;

SoftwareSerial loraSerial(21, 22); // TX, RX
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  loraSerial.begin(9600);
  Serial.println("LORA SENDER");
}

void loop() {
//CODE SERIAL
  if(Serial.available()>0){
    String msg = Serial.readString();
    loraSerial.print("Pesan=> "+msg);
    Serial.println("Pesan: "+msg);
  }  

//CODE Counter Sending Data
    loraSerial.print(counter);
    Serial.println(counter);
    counter++;
    delay(2000);
}
