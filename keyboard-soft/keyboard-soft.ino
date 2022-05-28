#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 61

// For led chips like Neopixels, which have a data line, ground, and power, you just
// need to define DATA_PIN.  For led chipsets that are SPI based (four wires - data, clock,
// ground, and power), like the LPD8806, define both DATA_PIN and CLOCK_PIN
#define DATA_PIN 4
//#define CLOCK_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

#include <ESP8266WiFi.h>
int num = 0;
bool blinked = false;
bool blinkState = false;
long timer = 0;
int blinkCount = 0;
// Replace with your network credentials
const char* ssid     = "Mi9T";
const char* password = "sacz5723";
bool rainbow = true;
WiFiServer server(80);



// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

String header;


int i = 0;
long animationTimer = 0;
static uint8_t hue = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  LEDS.addLeds<WS2812, DATA_PIN, RGB>(leds, NUM_LEDS);
  LEDS.setBrightness(220);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();
  setRainbow();
}

void setRainbow(){
  for(int j = 0; j < 14; j++){
    leds[j] = CRGB::Red;
  }
  for(int j = 14; j < 28; j++){
    leds[j] = CRGB::Yellow;
  }
  for(int j = 28; j < 41; j++){
    leds[j] = CRGB::Green;
  }
  for(int j = 41; j < 53; j++){
    leds[j] = CRGB::Blue;
  }
  for(int j = 53; j < 61; j++){
    leds[j] = CRGB(131, 50, 168);
  }
  FastLED.show();
}


void loop() {
  WiFiClient client = server.available();
  if (client) {                             // If a new client connects,
    Serial.println("New Client.");          // print a message out in the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    currentTime = millis();
    previousTime = currentTime;
    while (client.connected() && currentTime - previousTime <= timeoutTime) { // loop while the client's connected
      currentTime = millis();
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        header += c;
        if (c == '\n') {                    // if the byte is a newline character
          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            FastLED.clear();
            if (header[header.indexOf("GET /") + 6] == ' ') {
              //              leds[(int)header[header.indexOf("GET /") + 5] - '0'] = CRGB::White;
              num = (int)header[header.indexOf("GET /") + 5] - '0';
            } else {
              num = ((int)header[header.indexOf("GET /") + 5] - '0') * 10 + ((int)header[header.indexOf("GET /") + 6] - '0');
              //              leds[((int)header[header.indexOf("GET /") + 5] - '0') * 10 + ((int)header[header.indexOf("GET /") + 6] - '0')] = CRGB::White;
            }
            FastLED.clear();
            leds[num] = CRGB::White;
            FastLED.show();
            delay(300);
            leds[num] = CRGB::Black;
            FastLED.show();
            delay(300);
            leds[num] = CRGB::White;
            FastLED.show();
            delay(300);
            leds[num] = CRGB::Black;
            FastLED.show();
            delay(300);
            leds[num] = CRGB::White;
            FastLED.show();
            delay(300);
            leds[num] = CRGB::Black;
            FastLED.show();
            delay(300);
            leds[num] = CRGB::White;
            FastLED.show();
            delay(300);
            leds[num] = CRGB::Black;
            FastLED.show();
            delay(300);
            setRainbow();
            break;
          } else { // if you got a newline, then clear currentLine
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }
      }
    }
    // Clear the header variable
    header = "";
    // Close the connection
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
  }
  // First slide the led in one direction
//  if (millis() - animationTimer > 1000) {
//     
//  }
//  if(hue > 254){
//    hue = 0;
//  }
//  if(i >= NUM_LEDS){
//    i = 0;
//  }
//  FastLED.show();
  
}
