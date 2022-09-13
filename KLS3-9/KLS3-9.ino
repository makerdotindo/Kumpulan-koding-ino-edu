// Copyrights by Makerindo EDU
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>

//LCD TFT
#define SEALEVELPRESSURE_HPA (1013.25)
#define TFT_MISO   19 //SDO
//defihne LED ke 3.3v
#define TFT_SCK    18
#define TFT_MOSI   23 //SDI
#define TFT_DC     5
#define TFT_RESET  4
#define TFT_CS     2
#define SCL 22
#define SDA 21

Adafruit_BME280 bme;
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);

void setup()
{
  Serial.begin(57600);
   
  if (!bme.begin(0x76)) { //0x76 alamat i2c hasil scan
    Serial.println("tidak ada sensor BME280, Coba cek rangkaianmu!");
    while (1);
  }
  
  display.begin();
  display.setRotation(1);
  display.fillScreen(WHITE);
}

void loop()
{
  Serial.println("Tampilan Data ada di TFT LCD di Kit !");
  Serial.println(" ");
  
  float c = bme.readTemperature();
  float h = bme.readHumidity();
  float p = bme.readPressure() / 100.0F;
  float a = bme.readAltitude(SEALEVELPRESSURE_HPA);

  cetak(90, 10, 3, BLUE, "MAKERINDO");
  cetak(20, 60, 2, BLUE, "Temperature : " + String(c) + " C");
  cetak(20, 80, 2, BLUE, "Humidity    : " + String(h) + " rh");
  cetak(20, 100, 2, BLUE, "Pressure    : " + String(p) + " pA");
  cetak(20, 120, 2, BLUE, "Altitude    : " + String(a) + " m");
  
  delay(1000);
  display.fillScreen(WHITE);
  //  display.fillRect(20, 20, 500, 500, WHITE); //x,y,width,height,color

}

void cetak(int x, int y, int siz, char warna, String valu) {
  display.setCursor(x, y);
  display.setTextSize(siz);
  display.setTextColor(warna);
  display.print(valu);
}
