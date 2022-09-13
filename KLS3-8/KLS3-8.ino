// Copyrights by Makerindo EDU
#include <Arduino_GFX_Library.h>
#include <Wire.h>
#include <Adafruit_BME280.h>
#include <Adafruit_Sensor.h>
#include <RTClib.h>

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


RTC_DS1307 rtc;
Adafruit_BME280 bme;
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
  Serial.begin(115200);

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }
  display.begin();
  display.setRotation(1);
  display.fillScreen(WHITE);

  if (! rtc.isrunning()) {
    Serial.println("RTC is NOT running, let's set the time!");
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  }
  
}

void loop()
{
  Serial.println("Tampilan Text ada di TFT LCD di Kit !");
  Serial.println(" ");
  DateTime now = rtc.now();
  String tim = String(now.year());
  tim += "/";
  tim += now.month();
  tim += "/";
  tim += now.day();
  tim += " ";
  tim += now.hour();
  tim += ":";
  tim += now.minute();
  tim += ":";
  tim += now.second();

  cetak(20, 10, 2, BLUE, tim);

  cetak(90, 70, 2, BLUE, "MAKERINDO EDU");

}

void cetak(int x, int y, int siz, char warna, String valu) {
  display.setCursor(x, y);
  display.setTextSize(siz);
  display.setTextColor(warna);
  display.print(valu);
}
