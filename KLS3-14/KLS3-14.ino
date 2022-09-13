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
#define relay 27
#define buzzer 26
#define button 25
#define led 33

RTC_DS1307 rtc;
Adafruit_BME280 bme;
Arduino_ESP32SPI bus = Arduino_ESP32SPI(TFT_DC, TFT_CS, TFT_SCK, TFT_MOSI, TFT_MISO);
Arduino_ILI9341 display = Arduino_ILI9341(&bus, TFT_RESET);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

void setup()
{
  pinMode(relay, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(button, INPUT);
  Serial.begin(57600);

  if (!bme.begin(0x76)) { //0x76 alamat i2c hasil scan
    Serial.println("tidak ada sensor BME280, Coba cek rangkaianmu!");
    while (1);
  }
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
  digitalWrite(relay, LOW);
  digitalWrite(buzzer, LOW);
  digitalWrite(led, LOW);
}

void loop()
{
  btn();
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

  float c = bme.readTemperature();
  float h = bme.readHumidity();
  float p = bme.readPressure() / 100.0F;
  float a = bme.readAltitude(SEALEVELPRESSURE_HPA);

  cetak(20, 30, 2, BLUE, "Temperature : " + String(c) + " C");
  cetak(20, 50, 2, BLUE, "Humidity    : " + String(h) + " rh");
  cetak(20, 70, 2, BLUE, "Pressure    : " + String(p) + " pA");
  cetak(20, 90, 2, BLUE, "Altitude    : " + String(a) + " m");
  cetak(90, 200, 3, BLUE, "MAKERINDO");

  delay(1000);
  display.fillScreen(WHITE);
  //  display.fillRect(20, 20, 500, 500, WHITE); //x,y,width,height,color

}

void btn() {
  int btnstate = digitalRead(button);
  if (btnstate == LOW) {
    digitalWrite(relay, HIGH);
    digitalWrite(buzzer, HIGH);
    digitalWrite(led, HIGH);

    cetak(20, 110, 2, BLUE, "Button      : Push");
    cetak(20, 130, 2, BLUE, "Buzzer      : ON");
    cetak(20, 150, 2, BLUE, "Relay       : ON");
    cetak(20, 170, 2, BLUE, "Led         : ON");

  } else {
    digitalWrite(relay, LOW);
    digitalWrite(buzzer, LOW);
    digitalWrite(led, LOW);

    cetak(20, 110, 2, BLUE, "Button      : Not Push");
    cetak(20, 130, 2, BLUE, "Buzzer      : OFF");
    cetak(20, 150, 2, BLUE, "Relay       : OFF");
    cetak(20, 170, 2, BLUE, "Led         : OFF");
  }
}

void cetak(int x, int y, int siz, char warna, String valu) {
  display.setCursor(x, y);
  display.setTextSize(siz);
  display.setTextColor(warna);
  display.print(valu);
}
