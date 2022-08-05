include <WiFi.h>
#include <HTTPClient.h>

const char* ssid = "MAKERINDO2";
const char* password =  "makerindo2019";

const char* root_ca = \
                      "-----BEGIN CERTIFICATE-----\n" \
               
                      "-----END CERTIFICATE-----\n";

void setup() {
  Serial.begin(115200);
  delay(1000);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");
}

long speedtest(int buf_size) {
  unsigned long start;
  long total = 0;
  if ((WiFi.status() == WL_CONNECTED)) { //Check the current connection status
    
    HTTPClient http;
    Serial.print("starting...");
    //http.begin("https://proof.ovh.net/files/1Mb.dat", root_ca); //Specify the URL and certificate
    http.begin("http://speedtest.tele2.net/1MB.zip"); //Specify the URL and certificate
    int httpCode = http.GET();                                                  //Make the request

    if (httpCode > 0) { //Check for the returning code
      Serial.print(httpCode); Serial.print("           ");
      if (httpCode == HTTP_CODE_OK) {
        // get length of document (is -1 when Server sends no Content-Length header)
        total = http.getSize();
        uint8_t buff[buf_size] = { 0 };
        int buf_size_actual = sizeof(buff);
        Serial.print("\t\t Buff Size: "); Serial.println(buf_size_actual);
        WiFiClient * stream = http.getStreamPtr();
        http.setReuse(true);
        start = millis();
        size_t size = 1;
        long remaining = total;
        while (http.connected() && (remaining > 0 || remaining == -1)) {
          if (stream->available()) {
            remaining -= stream->readBytes(buff, buf_size);
          }
        }
      }
    }
    else {
      Serial.println("Error on HTTP request");
    }

    http.end();
    Serial.print("\t\tTime: "); Serial.print(millis() - start);
    Serial.print("\t\tBytes: "); Serial.print(total);
    Serial.print("\t\tThroughput :"); Serial.print("\t"); Serial.print(total / (millis() - start) * 8); Serial.print("\tkbps");
    return total / (millis() - start) * 8;
  }
}

void loop() {
  Serial.println(speedtest(50));
  delay(5000);
  Serial.println(speedtest(500));
  delay(5000);
  Serial.println(speedtest(1000));
  delay(5000);
  Serial.println(speedtest(2000));
  delay(5000);
}
