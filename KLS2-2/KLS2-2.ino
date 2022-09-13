// Complete Instructions: https://RandomNerdTutorials.com/esp32-digital-inputs-outputs-arduino/

// set pin numbers
const int PotenPin = 34;  // the number of the pushPoten pin
const int ledPin =  2;    // the number of the LED pin

// variable for storing the pushPoten status 
int PotenState = 0;

void setup() {
  Serial.begin(115200);  
  // initialize the pushPoten pin as an input
  pinMode(PotenPin, INPUT);
  // initialize the LED pin as an output
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the state of the pushPoten value
  PotenState = digitalRead(PotenPin);
  Serial.println(PotenState);
  // check if the pushPoten is pressed.
  // if it is, the PotenState is HIGH
  if (PotenState == HIGH) {
    // turn LED on
    digitalWrite(ledPin, HIGH);
  } else {
    // turn LED off
    digitalWrite(ledPin, LOW);
  }
}
