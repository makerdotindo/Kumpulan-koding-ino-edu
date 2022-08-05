#include <WiFi.h>
#include <ThingSpeak.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

const char* ssid = "MAKERINDO2";   // Write your SSID
const char* password = "makerindo2019";   // Write your WIFI password

WiFiClient  client;

unsigned long Channel_ID = 1822638;  //replace with your Channel ID
const char * API_key = "BNQWF498F91NEVBQ";


unsigned long last_time = 0;
unsigned long Delay = 30000;

float temperature;

// Create a sensor object
Adafruit_BME280 bme; 

void initBME(){
  if (!bme.begin(0x76)) {
    Serial.println("BME280 not connected properly!");
    while (1);
  }
}

void setup() {
  Serial.begin(115200);  
  initBME();
  
  WiFi.mode(WIFI_STA);   
  
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  if ((millis() - last_time) > Delay) {
    

    if(WiFi.status() != WL_CONNECTED){
      Serial.print("Connecting...");
      while(WiFi.status() != WL_CONNECTED){
        WiFi.begin(ssid, password); 
        delay(5000);     
      } 
      Serial.println("\nConnected.");
    }


    temperature = bme.readTemperature();
    Serial.print("Temperature (degree celsius): ");
    Serial.println(temperature);
        
    int Data = ThingSpeak.writeField(Channel_ID, 1, temperature,API_key);
 
    if(Data == 200){
      Serial.println("Channel updated successfully!");
    }
    else{
      Serial.println("Problem updating channel. HTTP error code " + String(Data));
    }
    last_time = millis();
  }
}
